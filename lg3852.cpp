/*
 * Author: Kewth

 * Date:
  2020.08.04

 * Solution:
  弦图基础。

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

const int maxn = 10005;
std::vector<int> G[maxn], P[maxn];
int label[maxn], id[maxn], iid[maxn];
bool vis[maxn];

int main () {
	int n = read, m = read;
	for (int i = 1; i <= m; i ++) {
		int u = read, v = read;
		G[u].push_back(v);
		G[v].push_back(u);
	}

	for (int i = n; i; i --) P[0].push_back(i);
	int best = 0, ans = 0;

	for (int i = n; i; i --) {
		while (P[best].empty()) -- best;
		int &u = iid[i] = P[best].back();
		P[best].pop_back();
		while (id[u]) {
			while (P[best].empty()) -- best;
			u = P[best].back();
			P[best].pop_back();
		}
		id[u] = i;
		for (int v : G[u])
			if (!id[v])
				P[++ label[v]].push_back(v);
		while (!P[best + 1].empty()) ++ best;
	}

	for (int i = 1; i <= n; i ++)
		if (!vis[iid[i]]) {
			++ ans;
			for (int v : G[iid[i]]) vis[v] = 1;
		}

	printf("%d\n", ans);
}
