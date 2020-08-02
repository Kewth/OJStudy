/*
 * Author: Kewth

 * Date:
  2020.08.02

 * Solution:
  KM 模板，注意由于是求完美匹配，不存在的边必须设为 -inf 而不是 0 。

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
#include <queue>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

static struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 505;
const int inf = 1000000000;
bool link[maxn][maxn];
int val[maxn][maxn];
int lh[maxn], rh[maxn], slk[maxn];
bool lvis[maxn], rvis[maxn];
int lmatch[maxn], rmatch[maxn], pre[maxn];

std::queue<int> q;

bool add (int v) {
	rvis[v] = 1;
	if (rmatch[v]) return lvis[rmatch[v]] = 1, q.push(rmatch[v]), 0;
	while (v) std::swap(lmatch[rmatch[v] = pre[v]], v); // XXX: 这都能写反 l, r ？
	return 1;
}

#define CHECK for (int v = 1; v <= n; v ++) if (!rvis[v] and slk[v] == 0 and add(v)) return
void bfs (int s, int n) {
	std::fill(lvis, lvis + n + 1, 0);
	std::fill(rvis, rvis + n + 1, 0);
	std::fill(slk, slk + n + 1, inf);
	std::fill(pre, pre + n + 1, 0);
	while (!q.empty()) q.pop();
	q.push(s);
	lvis[s] = 1;
	while (1) {
		while (!q.empty()) {
			int u = q.front(); q.pop();
			for (int v = 1; v <= n; v ++)
				if (!rvis[v]) { // XXX: 这都能忘？
					int dt = lh[u] + rh[v] - val[u][v];
					if (dt <= slk[v]) slk[v] = dt, pre[v] = u;
				}
			CHECK;
		}
		int dt = inf;
		for (int v = 1; v <= n; v ++) if (!rvis[v]) dt = std::min(dt, slk[v]);
		for (int u = 1; u <= n; u ++) if (lvis[u]) lh[u] -= dt;
		for (int v = 1; v <= n; v ++) rvis[v] ? rh[v] += dt : slk[v] -= dt;
		CHECK;
	}
}

int main () {
	int n = read, m = read;
	for (int u = 1; u <= n; u ++)
		for (int v = 1; v <= n; v ++)
			val[u][v] = -inf;
	for (int i = 1; i <= m; i ++) {
		int u = read, v = read, w = read;
		link[u][v] = 1, val[u][v] = w;
	}
	for (int u = 1; u <= n; u ++)
		for (int v = 1; v <= n; v ++)
			if (link[u][v])
				lh[u] = std::max(lh[u], val[u][v]);
	for (int u = 1; u <= n; u ++) bfs(u, n);
	ll ans = 0;
	for (int i = 1; i <= n; i ++) ans += lh[i] + rh[i];
	printf("%lld\n", ans);
	// XXX: 这都能写成 lmatch ？
	for (int v = 1; v <= n; v ++) printf("%d ", link[rmatch[v]][v] ? rmatch[v] : 0);
	puts("");
}
