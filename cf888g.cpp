#if 0
2019.08.22

考虑 kruskal 的过程：每次找最小边。
最开始的最小边 (x, y) 一定满足 x 与 y 的最高位相同，
直到最高位相同的点都联通了，这时就把最高位 0/1 的两种数中选最小边合并。
那么这样一个分治算法就构造出来了，现在需要解决的是最高位不同的数间的最小边。
对两个集合分别维护 01Trie ，
合并的时候枚举一个集合的元素 x 在另一颗 Trie 上找最小 x xor y 即可，同时合并 Trie 。

一个更简单的实现方式是把数从小到大排序后插入 Trie 。
那么 Trie 上每个子树一定控制连续区间，
直接在 dfs 这颗 Trie 进行分治算法就可以大大简化合并。
#endif
#include <cstdio>
#include <vector>
#include <algorithm>
#include <climits>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;

inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 200005, maxk = 32;
int ch[maxn * maxk][2], cp = 1;
int l[maxn * maxk], r[maxn * maxk];
int a[maxn];

int query(int x, int d, int now) {
	if(d < 0)
		return 0;

	if(ch[now][x >> d & 1])
		return query(x, d - 1, ch[now][x >> d & 1]);

	return query(x, d - 1, ch[now][! (x >> d & 1)]) + (1 << d);
}

lolong dfs(int now, int d) {
	if(not now) return 0;

	lolong res = dfs(ch[now][0], d - 1) + dfs(ch[now][1], d - 1);

	/* debug("%d - %d : %d\n", l[now], r[now], now); */

	if(ch[now][0] and ch[now][1]) {
		int min = INT_MAX;
		for(int i = l[ch[now][0]]; i <= r[ch[now][0]]; i ++)
			min = std::min(min, query(a[i], d - 1, ch[now][1]));
		res += min + (1 << d);

		/* debug("get %d\n", min + (1 << d)); */
	}

	return res;
}

int main() {
	int n = input();

	for(int i = 1; i <= n; i ++)
		a[i] = input();

	std::sort(a + 1, a + n + 1);

	for(int i = 1; i <= n; i ++) {
		int now = 1;
		for(int k = maxk - 1; k >= 0; k --) {
			if(not l[now])
				l[now] = i;
			r[now] = i;
			int &to = ch[now][a[i] >> k & 1];
			if(not to)
				to = ++ cp;
			now = to;
		}
	}

	printf("%lld\n", dfs(1, maxk - 1));
}
