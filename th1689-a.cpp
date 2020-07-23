/*
 * Author: Kewth

 * Date:
  2020.07.23

 * Solution:
  设 01 变量 f[x][u] 表示物品 u 是否放在节点 u 上，然后限制都能用 2-SAT 表示，然而每条
路径限制带来的边数是 O(n^2) 的，难以承受。不难发现换一个方式，设 g[x][u] 表示物品 x 是
否能放在子树 u 内，这样一来每条路径限制带来的边数就只有 O(n) 。

 * Digression:

 * CopyRight:
          ▁▃▄▄▄▃▃▃▃▄▶
        ▗▇▀▔    ▔▔▔▔
       ▄▛   ▃▅━━■▄▂
      ▟▊   ▐▘     ▀▙
     ▟▜▌   ▐▖   ▋  ▐▍
    ▟▘ ▜   ▝▀▇▆■▘  ▐▌
  ▗▟▘   ▜▃       ▁▅▛
  ▔▀▼▅▄▃▃██▅▄▄▄▅■▀▔
        ▔▔▔▔▔▔
 */

#include <cstdio>
#include <algorithm>
#include <vector>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

static struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 252, maxi = maxn * maxn * 2;;
std::vector<int> T[maxn], G[maxi];
int deep[maxn], fa[maxn];
int id[2][maxn][maxn], ip;
int stack[maxi], sp, ins[maxi];
int low[maxi], dfn[maxi], dfc;
int bl[maxi], bp;

void tarjan (int u) {
	low[u] = dfn[u] = ++ dfc;
	stack[++ sp] = u;
	ins[u] = 1;
	for (int v : G[u])
		if (!dfn[v])
			tarjan(v), low[u] = std::min(low[u], low[v]);
		else if (ins[v])
			low[u] = std::min(low[u], dfn[v]);
	if (low[u] == dfn[u]) {
		++ bp;
		while (stack[sp + 1] != u) {
			int x = stack[sp --];
			bl[x] = bp;
			ins[x] = 0;
		}
	}
}

void dfs (int u) {
	deep[u] = deep[fa[u]] + 1;
	for (int v : T[u])
		if (v != fa[u]) {
			fa[v] = u;
			dfs(v);
		}
}

int main () {
	int n = read, m = read, q = read;
	for (int i = 1; i < n; i ++) {
		int u = read, v = read;
		T[u].push_back(v);
		T[v].push_back(u);
	}

	for (int x = 0; x<  2; x ++)
		for (int i = 1; i <= m; i ++)
			for (int j = 1; j <= n; j ++)
				id[x][i][j] = ++ ip;

	dfs(1);

	for (int x = 1; x <= m; x ++)
		G[id[0][x][1]].push_back(id[1][x][1]);

	for (int u = 1; u <= n; u ++)
		for (int x = 1; x <= m; x ++) {
			int v = fa[u];
			if (v) {
				G[id[1][x][u]].push_back(id[1][x][v]);
				G[id[0][x][v]].push_back(id[0][x][u]);
			}
			for (int v1 : T[u])
				for (int v2 : T[u])
					if (v1 != v2 and v1 != v and v2 != v) {
						G[id[1][x][v1]].push_back(id[0][x][v2]);
						G[id[1][x][v2]].push_back(id[0][x][v1]);
					}
		}

	while (q --) {
		int x = read, y = read, c = read;
		for (int u : T[c])
			if (u != fa[c]) {
				G[id[1][x][u]].push_back(id[0][y][u]);
				G[id[1][y][u]].push_back(id[0][x][u]);
			}
		G[id[0][x][c]].push_back(id[1][y][c]);
		G[id[0][y][c]].push_back(id[1][x][c]);
	}

	for (int i = 1; i <= ip; i ++)
		if (!dfn[i])
			tarjan(i);

	for (int x = 1; x <= m; x ++) {
		int ans = 0;
		for (int u = 1; u <= n; u ++)
			if (bl[id[1][x][u]] < bl[id[0][x][u]] and deep[u] > deep[ans])
				ans = u;
		printf("%d ", ans);
	}
	puts("");
}
