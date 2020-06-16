/*
 * Since g++10 is released, some characters is not valid inside #if 0 :(
 * So, why not using clang++? :D

 * Date:
  2020.06.16

 * Solution:
 * 考虑特殊情况（菊花），推广结论

  从特殊情况入手，考虑菊花图的填数，那么就是要在集合内选择至多两个数，容易想到“拆系数”，
对于需要表示的一个数 k ，设 k = xB + y ，那么只需要填 1 到 B - 1 的所有数，再填 B 的所
有倍数即可，计算这样可以表示的数的数量，就是 B (n - B + 1) + B - 1 ，可以近似看做 AB ，
其中 A + B = n ，显然 A, B 接近 n/2 是最优的，能表示的值域大小约为 n^2/4 。

  考虑推广，观察这个值域大小 n^2 * (2/9) ，注意到 2/9 = 1/3 * 2/3 ，也就是 A 取 n/3 ，
B 取 2n/3 时的情况。

  那么问题到这里就比较简单了，如果能够找到一个点 u 作为根，然后把 u 的儿子划分为两部分，
小的一部分的节点数不小于 n/3 ，那么当做菊花图去做，每个部分的节点到根的距离两两不同且
连续即可。

  如何找到这个点以及划分？不难发现 u 可以选取重心，这样每个儿子的大小不超过 n/2 ，按大
小从小到大枚举儿子加入一个部分，如果当前部分的大小和达到 n/3 就退出，这部分的大小就一
定不小于 n/3 且不超过 2n/3 。

  可以反证，如果分出的部分超过了 2n/3 ，说明最后加入的儿子大小超过 n/3 ，而最后剩下的
儿子的大小和不超过 n/3 ，这与最后加入的儿子大小不超过剩下的任意一个儿子矛盾。

 * Digression:
  就这？晚了 10min 才 AC ，要是 C 不浪费太多时间就很 nice 了。

 * CopyRight:
          ▁▃▄▄▄▃▃▃▃▄▶
        ▗▇▀▔    ▔▔▔▔
       ▄▛   ▃▅━━■▄▂
      ▟▊   ▐▘     ▀▙
     ▟▜▌   ▐▖   ▋  ▐▍
    ▟▘ ▜   ▝▀▇▆●▘  ▐▌
  ▗▟▘   ▜▃       ▁▅▛
  ▔▀▼▅▄▃▃██▅▄▄▄▅■▀▔
        ▔▔▔▔▔▔
 */

#include <cstdio>
#include <algorithm>
#include <vector>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 1005;
std::vector<int> G[maxn];
int size[maxn], son[maxn];

void dfs (int u, int fa) {
	size[u] = 1;
	son[u] = 0;
	for (int v : G[u])
		if (v != fa) {
			dfs(v, u);
			size[u] += size[v];
			if (size[v] >= size[son[u]])
				son[u] = v;
		}
}

int p1, p2;
void calc1 (int u, int fa, int d) {
	for (int v : G[u])
		if (v != fa) {
			++ p1;
			printf("%d %d %d\n", u, v, p1 - d);
			calc1(v, u, p1);
		}
}
void calc2 (int u, int fa, int d) {
	for (int v : G[u])
		if (v != fa) {
			++ p2;
			printf("%d %d %d\n", u, v, (p1 + 1) * (p2 - d));
			calc2(v, u, p2);
		}
}

int main () {
	int n = read;
	for (int i = 1; i < n; i ++) {
		int u = read, v = read;
		G[u].push_back(v);
		G[v].push_back(u);
	}

	dfs(1, 0);
	int rt = 1;
	while (size[son[rt]] * 2 > n)
		rt = son[rt];
	dfs(rt, 0);

	std::sort(G[rt].begin(), G[rt].end(), [] (int x, int y) {
				return size[x] < size[y];
			});

	int now = 0;
	int sta = 1;
	for (int u : G[rt]) {
		now += size[u];
		if (sta == 1) {
			++ p1;
			printf("%d %d %d\n", rt, u, p1);
			calc1(u, rt, p1);
		}
		if (sta == 2) {
			++ p2;
			printf("%d %d %d\n", rt, u, (p1 + 1) * p2);
			calc2(u, rt, p2);
		}
		if (now * 3 >= n - 1) sta = 2;
	}
}
