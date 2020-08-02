/*
 * Author: Kewth

 * Date:
  2020.07.29

 * Solution:
  In blog.

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
#include <queue>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

static struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
} read;

const int maxn = 255;
const int inf = 1000000000;
struct node { int i, j, t, d; };
int p[maxn];
int dis[maxn][maxn];
int f[maxn][maxn], g[maxn][maxn];
std::vector<int> G[maxn];

bool operator < (node a, node b) { return a.d > b.d; }

int main () {
	int n = read, m = read;
	for (int i = 1; i <= n; i ++)
		for (int j = 1; j <= n; j ++)
			f[i][j] = g[i][j] = dis[i][j] = inf;

	for (int i = 1; i <= n; i ++) read(p[i]);
	for (int i = 1; i <= n; i ++) dis[i][i] = -p[i];

	for (int i = 1; i <= m; i ++) {
		int u = read, v = read;
		G[u].push_back(v);
		G[v].push_back(u);
		dis[u][v] = 0;
	}

	for (int k = 1; k <= n; k ++)
		for (int i = 1; i <= n; i ++)
			for (int j = 1; j <= n; j ++)
				dis[i][j] = std::min(dis[i][j], dis[i][k] + p[k] + dis[k][j]);

	std::priority_queue<node> q;
	f[1][1] = p[1];
	q.push({1, 1, 0, p[1]});
	int ans = inf;

	/* for (int i = 1; i <= n; i ++) { */
	/* 	for (int j = 1; j <= n; j ++) */
	/* 		debug(" %d", dis[i][j]); */
	/* 	debug("\n"); */
	/* } */

	while (!q.empty()) {
		int i = q.top().i, j = q.top().j, t = q.top().t, d = q.top().d;
		q.pop();

		if (t == 0) {
			if (d > f[i][j]) continue;
			/* debug("f[%d][%d] = %d\n", i, j, f[i][j]); */
			for (int k = 1; k <= n; k ++)
				if (k != i and k != j and f[i][j] + dis[k][i] + p[k] < g[j][k]) {
					g[j][k] = f[i][j] + dis[k][i] + p[k];
					q.push({j, k, 1, g[j][k]});
				}
		}

		if (t == 1) {
			if (d > g[i][j]) continue;
			/* debug("g[%d][%d] = %d\n", i, j, g[i][j]); */
			if (j == n) ans = std::min(ans, g[i][j] + dis[i][j]);
			for (int k = 1; k <= n; k ++)
				if (k != i and g[i][j] + dis[i][k] + p[k] + dis[k][j] < f[k][j]) {
					f[k][j] = g[i][j] + dis[i][k] + p[k] + dis[k][j];
					q.push({k, j, 0, f[k][j]});
				}
		}
	}

	printf("%d\n", ans == inf ? -1 : ans);
}
