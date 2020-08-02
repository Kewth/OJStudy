/*
 * Author: Kewth

 * Date:
  2020.08.02

 * Solution:
  KM 模板。

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

const int maxn = 405;
const int inf = 2000000000;
int edge[maxn][maxn];
int hl[maxn], hr[maxn], slack[maxn];
int matchl[maxn], matchr[maxn], pre[maxn];
bool visl[maxn], visr[maxn];
std::queue<int> q;

bool add (int v) { // 添加右边节点
	visr[v] = 1;
	if (matchr[v]) return q.push(matchr[v]), visl[matchr[v]] = 1, 0;
	while (v) std::swap(matchl[matchr[v] = pre[v]], v);
	return 1;
}

bool check (int n) { // 找最短路
	for (int v = 1; v <= n; v ++)
		if (!visr[v] and slack[v] == 0 and add(v)) return 1;
	return 0;
}

void bfs (int s, int n) {
	std::fill(visl, visl + n + 1, 0);
	std::fill(visr, visr + n + 1, 0);
	std::fill(pre, pre + n + 1, 0);
	std::fill(slack, slack + n + 1, inf);
	while (!q.empty()) q.pop(); // XXX: 这都能忘？
	q.push(s);
	visl[s] = 1;
	while (1) {
		while (!q.empty()) {
			int u = q.front(); q.pop();
			for (int v = 1; v <= n; v ++)
				if (!visr[v]) {
					int dt = hl[u] + hr[v] - edge[u][v];
					if (dt <= slack[v]) pre[v] = u, slack[v] = dt;
				}
			if (check(n)) return;
		}
		// 更新顶标
		int dt = inf;
		for (int v = 1; v <= n; v ++)
			if (!visr[v])
				dt = std::min(dt, slack[v]);
		for (int x = 1; x <= n; x ++) if (visl[x]) hl[x] -= dt;
		for (int v = 1; v <= n; v ++) visr[v] ? hr[v] += dt : slack[v] -= dt;
		if (check(n)) return;
	}
}

int main () {
	int nl = read, nr = read, m = read;
	int n = std::max(nl, nr);
	for (int i = 1; i <= m; i ++) {
		int u = read, v = read, w = read;
		edge[u][v] = w;
	}
	for (int u = 1; u <= n; u ++)
		for (int v = 1; v <= n; v ++)
			hl[u] = std::max(hl[u], edge[u][v]);
	for (int u = 1; u <= n; u ++) bfs(u, n);
	ll ans = 0;
	for (int i = 1; i <= n; i ++) ans += hl[i] + hr[i];
	printf("%lld\n", ans);
	for (int u = 1; u <= nl; u ++)
		printf("%d ", edge[u][matchl[u]] ? matchl[u] : 0);
	puts("");
}
