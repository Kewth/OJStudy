#if 0
2020.05.01

  考虑序列前缀和，那么选一个区间异或就等价于在前缀和里选两个点异或，对于点 i ，可以通过
01 Trie 树简单求出第 k 大贡献的点 j ，那么用一个堆存每个点 i ，每次找到贡献最大的点进行
贡献即可，由于直接算是无序的， (i, j) 和 (j, i) 会被算两次，但是 (i, i) 不会对答案产生贡
献。
#endif
#include <cstdio>
#include <algorithm>
#include <queue>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef unsigned int ui;
typedef std::pair<ui, int> par;
typedef unsigned long long ull;

struct {
	inline operator ui () { ui x; return scanf("%u", &x), x; }
	inline operator int () { int x; return scanf("%d", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
} read;

const int maxn = 500005, maxk = 32;
int ch[maxn * (maxk + 1)][2], size[maxn * (maxk + 1)], cp;
int rk[maxn];
ui num[maxn];

void insert (int &now, ui x, int k) {
	if (!now) now = ++ cp;
	++ size[now];
	if (k >= 0)
		insert(ch[now][x >> k & 1], x, k - 1);
}

ui query (int now, ui x, int r, int k) {
	if (k < 0) return 0;
	int t = x >> k & 1;
	if (r <= size[ch[now][!t]])
		return 1u << k | query(ch[now][!t], x, r, k - 1);
	return query(ch[now][t], x, r - size[ch[now][!t]], k - 1);
}

int main () {
	int n = read, m = read, t = 0;
	for (int i = 1; i <= n; i ++) read(num[i]);
	for (int i = 0; i <= n; i ++)
		insert(t, num[i] ^= i ? num[i - 1] : 0, maxk - 1);

	std::priority_queue<par> q;
	for (int i = 0; i <= n; i ++)
		q.push(par(query(t, num[i], ++ rk[i], maxk - 1), i));

	ull ans = 0;
	for (int i = 1; i <= m * 2; i ++) {
		par p = q.top();
		q.pop();
		/* debug("%u %d\n", p.first, p.second); */
		ans += p.first;
		int id = p.second;
		q.push(par(query(t, num[id], ++ rk[id], maxk - 1), id));
	}

	printf("%llu\n", ans >> 1);
}
