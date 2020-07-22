/*
 * Author: Kewth

 * Date:
  2020.07.21

 * Solution:
  随机化匈牙利就可以跑了，既然如此带花树岂不是。。。

 * Digression:

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
#include <random>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

static struct {
    inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 1005;
std::vector<int> G[maxn];
int tmp[maxn];
bool vis[maxn];
int match[maxn];

std::mt19937 e;

bool dfs (int u) {
	std::shuffle(G[u].begin(), G[u].end(), e);
	vis[u] = 1;
	for (int v : G[u])
		if (!vis[v]) {
			vis[v] = 1;
			if (!match[v] or dfs(match[v])) {
				match[u] = v;
				match[v] = u;
				return 1;
			}
		}
	return 0;
}

int main () {
	clock_t start = clock();
	e = std::mt19937(std::random_device()());
	int n = read, m = read;

	for (int i = 1; i <= m; i ++) {
		int u = read, v = read;
		G[u].push_back(v);
		G[v].push_back(u);
	}

	int ans = 0;
    while (double(clock() - start) / CLOCKS_PER_SEC < 0.1) {
		/* for (int u = 1; u <= n; u ++) */
		/* std::shuffle(G[u].begin(), G[u].end(), e); */
		for (int u = 1; u <= n; u ++)
			if (!match[u]) {
				// debug("dfs %d\n", u);
				std::fill(vis, vis + n + 1, 0);
				ans += dfs(u);
			}
	}

	printf("%d\n", ans);
	for (int u = 1; u <= n; u ++)
		printf("%d ", match[u]);
	puts("");
}
