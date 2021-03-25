/*
 * Author: Kewth

 * Date:
  2021.03.12

 * Solution:
  建出 dfs 树，首先满足条件的点得在 (x, y) 的树上路径上，设 val[u] 表示把 fa[u] 删掉
后 u 点是否能连向子树外的点，答案就是 val 的链上求和。
  求 val 使用 tarjan 算法即可。

 * Digression:
  难度 5 / 12

 * CopyRight:
   __  __                  __   __
  |  |/  |.-----.--.--.--.|  |_|  |--.
  |     < |  -__|  |  |  ||   _|     |
  |__|\__||_____|________||____|__|__|

 */

#include <cstdio>
#include <algorithm>
#include <vector>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

static struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	/* inline operator ll () { ll x; return scanf("%lld", &x), x; } */
	/* template<class T> inline void operator () (T &x) { x = *this; } */
	/* template<class T, class ...A> inline void operator () (T &x, A &...a) */
	/* { x = *this; this -> operator () (a...); } */
} read;

const int maxn = 200005, maxk = 20;
std::vector<int> G[maxn];
int dfn[maxn], low[maxn], list[maxn], lp;
int deep[maxn], fa[maxk][maxn];
int val[maxn], sum[maxn];

void dfs (int u) {
	deep[u] = deep[fa[0][u]] + 1;
	for (int k = 1; k < maxk; k ++)
		fa[k][u] = fa[k - 1][fa[k - 1][u]];
	list[low[u] = dfn[u] = ++ lp] = u;
	int son = 0, ok = 1;
	for (int v : G[u]) {
		if (!dfn[v]) {
			/* debug("%d -> %d\n", u, v), */
			++ son;
			fa[0][v] = u;
			dfs(v);
			low[u] = std::min(low[u], low[v]);
			ok &= low[v] < dfn[u];
		}
		else if (v != fa[0][u])
			low[u] = std::min(low[u], dfn[v]);
	}
	val[u] = u > 1 and low[u] >= dfn[fa[0][u]];
}

int lca (int x, int y) {
	if (deep[x] < deep[y]) std::swap(x, y);
	for (int k = maxk - 1; k >= 0; k --)
		if (deep[fa[k][x]] >= deep[y])
			x = fa[k][x];
	for (int k = maxk - 1; k >= 0; k --)
		if (fa[k][x] != fa[k][y])
			x = fa[k][x], y = fa[k][y];
	return x == y ? x : fa[0][x];
}

int main () {
	int n = read, m = read;
	for (int i = 1; i <= m; i ++) {
		int u = read, v = read;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	dfs(1);
	int tot = 0;
	for (int u = 2; u <= n; u ++)
		tot += fa[0][u] == 1;
	for (int i = 1; i <= n; i ++) {
		int u = list[i];
		sum[u] = val[u] + sum[fa[0][u]];
	}
	/* for (int u = 1; u <= n; u ++) */
	/* 	debug("%d\n", val[u]); */
	int q = read;
	while (q --) {
		int x = read, y = read;
		if (deep[x] < deep[y]) std::swap(x, y);
		int X = x, Y = y;
		for (int k = maxk - 1; k >= 0; k --)
			if (deep[fa[k][x]] > deep[y])
				x = fa[k][x];
		if (fa[0][x] == y)
			printf("%d\n", sum[X] - sum[x]);
		else {
			if (deep[x] > deep[y]) x = fa[0][x];
			for (int k = maxk - 1; k >= 0; k --)
				if (fa[k][x] != fa[k][y])
					x = fa[k][x], y = fa[k][y];
			int c = fa[0][x];
			printf("%d\n", sum[X] + sum[Y] - sum[c] * 2 - (val[x] and val[y]));
		}
	}
}
