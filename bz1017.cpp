#if 0
2019.05.18

树形 dp + 背包。
f[i][j][k] 表示节点 i 及其子树中， i 舍弃 j 个，恰好花费 k 的最大力量。
转移特复杂，令人抓狂。
g[u][i][m] 辅助转移，表示 u 点及其子树中，u 共有 i 个，
不包括 u 本身的贡献恰好花费 m 的最大力量。
考虑 u 本身的贡献后就可以从 g 转移到 f 。
吐槽一句，yzoj 上同一份代码用 c++11 AC, c++ mle.
#endif
#define debug(...) fprintf(stderr, __VA_ARGS__)
#include <cstdio>
#include <utility>
#include <vector>
#include <cassert>

typedef int lolong;
typedef std::pair<int, int> par;
const int maxn = 52, maxqu = 101, maxm = 2001;
lolong f[maxn][maxqu][maxm];
int power[maxn], cost[maxn], limit[maxn];
std::vector<par> G[maxn];
bool istop[maxn];

int Money;
lolong g[maxm];
void dp(int u) {
	for(par e : G[u]) {
		dp(e.first);
		cost[u] += cost[e.first] * e.second;
		limit[u] = std::min(limit[u], limit[e.first] / e.second);
	}
	limit[u] = std::min(limit[u], Money / cost[u]);
	for(int i = 0; i < maxqu; i ++)
		for(int m = 0; m <= Money; m ++)
			f[u][i][m] = -1;
	if(G[u].empty()) {
		for(int i = 0; i <= limit[u]; i ++)
			for(int j = i; j <= limit[u]; j ++)
				f[u][i][j * cost[u]] = (j - i) * power[u];
		return;
	}
	/* lolong g[maxqu][maxm]; */
	for(int i = 0; i <= limit[u]; i ++) {
		g[0] = 0;
		for(int m = 1; m <= Money; m ++)
			g[m] = -1;
		/* debug("%d's %d\n", u, i); */
		for(par e : G[u]) {
			for(int m = Money; m >= 0; m --) {
				if(g[m] == -1 or f[e.first][i * e.second][0] == -1)
					g[m] = -1;
				for(int give = 1; give <= m; give ++)
					if(~g[m - give] and ~f[e.first][i * e.second][give])
						g[m] = std::max(g[m], g[m - give]
								+ f[e.first][i * e.second][give]);
			}
			/* for(int m = 0; m <= 20; m ++) */
			/* 	debug("%2lld ", g[i][m]); */
			/* debug("\n"); */
		}
		for(int j = 0; j <= i; j ++)
			for(int m = 0; m <= Money; m ++)
				if(~g[m])
					f[u][j][m] = std::max(f[u][j][m],
							g[m] + (i - j) * power[u]);
	}
}

int main() {
	int n;
	scanf("%d %d", &n, &Money);
	for(int i = 1; i <= n; i ++)
		istop[i] = true;
	for(int i = 1; i <= n; i ++) {
		char level;
		scanf("%d %c", &power[i], &level);
		if(level == 'A') {
			int quan;
			scanf("%d", &quan);
			while(quan --) {
				int to, need;
				scanf("%d %d", &to, &need);
				G[i].push_back(par(to, need));
				istop[to] = false;
			}
			limit[i] = 100000;
		} else {
			assert(level == 'B');
			scanf("%d %d", &cost[i], &limit[i]);
		}
	}
	lolong ans = 0;
	for(int i = 1; i <= n; i ++)
		if(istop[i]) {
			dp(i);
			for(int j = 0; j <= Money; j ++)
				ans = std::max(ans, f[i][0][j]);
		}
	printf("%d\n", ans);
}
