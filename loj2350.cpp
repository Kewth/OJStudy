/*
 * Author: Kewth

 * Date:
  2020.09.19

 * Solution:
  把 s 的最短路图建出来，如果需要用到免费边那么最优方案一定是先跑到最短路的一个点，
然后走最短路到另一点，最后直接跑到终点。在最短路图上 DP 即可。

 * Digression:

 * CopyRight:
   __  __                  __   __
  |  |/  |.-----.--.--.--.|  |_|  |--.
  |     < |  -__|  |  |  ||   _|     |
  |__|\__||_____|________||____|__|__|

 */

#include <cstdio>
#include <algorithm>
#include <queue>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef std::pair<ll, int> par;

static struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 200005;
const ll inf = 1000000000000000000;
int head[maxn], nxt[maxn << 1], to[maxn << 1], len[maxn << 1], hp = 1;
ll diss[maxn], disa[maxn], disb[maxn];
int list[maxn], lp;
ll fa[maxn], fb[maxn];

inline void add (int u, int v, int w) {
	nxt[++ hp] = head[u];
	head[u] = hp;
	to[hp] = v;
	len[hp] = w;
}

void dijkstra (int s, int n, ll *dis) {
	std::fill(dis, dis + n + 1, inf);
	std::priority_queue<par> q;
	q.push(par(dis[s] = 0, s));
	lp = 0;
	while (!q.empty()) {
		int u = q.top().second;
		ll d = - q.top().first;
		q.pop();
		if (d > dis[u]) continue;
		list[++ lp] = u;
		for (int i = head[u]; i; i = nxt[i]) {
			int v = to[i], w = len[i];
			if (dis[u] + w < dis[v]) {
				dis[v] = dis[u] + w;
				q.push(par(- dis[v], v));
			}
		}
	}
}

int main () {
	int n = read, m = read;
	int s = read, t = read;
	int a = read, b = read;

	for (int i = 1; i <= m; i ++) {
		int u = read, v = read, w = read;
		add(u, v, w);
		add(v, u, w);
	}

	dijkstra(a, n, disa);
	dijkstra(b, n, disb);
	dijkstra(s, n, diss);

	ll ans = disa[b];
	for (int p = lp; p; p --) {
		int u = list[p];
		fa[u] = fb[u] = inf;
		for (int i = head[u]; i; i = nxt[i]) {
			int v = to[i], w = len[i];
			if (diss[u] + w == diss[v]) {
				fa[u] = std::min(fa[u], fa[v]);
				fb[u] = std::min(fb[u], fb[v]);
			}
		}
		if (u == t or fa[u] < inf) fa[u] = std::min(fa[u], disa[u]);
		if (u == t or fb[u] < inf) fb[u] = std::min(fb[u], disb[u]);
		ans = std::min({ans, fa[u] + disb[u], fb[u] + disa[u]});
		/* debug("%d : %lld %lld %lld\n", u, diss[u], fa[u], fb[u]); */
	}

	printf("%lld\n", ans);
}
