#if 0
2019.08.24

直接 O(n^2 logn) 枚举源点 s 跑最短路，然后在这个过程中计算出所有 D[s][i]
#endif
#include <cstdio>
#include <queue>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;
typedef std::pair<lolong, int> Par;

inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 1005, maxm = 2020, mod = 998244353;
int head[maxn], nxt[maxm << 1], to[maxm << 1], val[maxm << 1], hp;
int d[maxn][maxn];
lolong dis[maxn];
int pathmax[maxn];

inline void add(int u, int v, int w) {
	nxt[++ hp] = head[u];
	head[u] = hp;
	to[hp] = v;
	val[hp] = w;
}

void dijkstra(int s, int n) {
	std::priority_queue<Par> q;

	for(int i = 1; i <= n; i ++) {
		dis[i] = 1000000000000000;
		pathmax[i] = n + 1;
	}

	dis[s] = 0;
	pathmax[s] = 0;
	q.push(Par(0, s));

	while(not q.empty()) {
		lolong dd = - q.top().first;
		int u = q.top().second;
		q.pop();

		if(dd > dis[u])
			continue;

		d[s][u] = pathmax[u];
		/* debug("%d %d : %d\n", s, u, pathmax[u]); */

		for(int i = head[u]; i; i = nxt[i]) {
			lolong tod = dis[u] + val[i];
			int top = u == s ? 0 : std::max(pathmax[u], u);
			int v = to[i];
			if(tod < dis[v]) {
				pathmax[v] = top;
				dis[v] = tod;
				q.push(Par(- dis[v], v));
			} else if(tod == dis[v])
				pathmax[v] = std::min(pathmax[v], top);
		}
	}
}

int main() {
	int T = input();

	while(T --) {
		int n = input(), m = input();

		hp = 0;
		for(int i = 1; i <= n; i ++)
			head[i] = 0;

		for(int i = 1; i <= m; i ++) {
			int u = input(), v = input(), w = input();
			add(u, v, w);
			add(v, u, w);
		}

		for(int i = 1; i <= n; i ++)
			dijkstra(i, n);

		int ans = 0;
		for(int i = 1; i <= n; i ++)
			for(int j = 1; j <= n; j ++)
				(ans += d[i][j]) %= mod;
		printf("%d\n", ans);
	}
}
