#if 0
2020.02.05

对两个点分别建最短路树，
DP 设 fa[i][j] 表示 a 点在最短路树上选了深度前 i 的点，b 点选了前 j 的点，
这样的前提下 a 先手，到游戏结束还能拿多少分。
fb 有类似的定义，不同的是 b 先手。

fa[i][j] 朴素转移枚举 a 的下一次决策 k ，
那么就是 max_{tot[k][j] > tot[i][j]} (sum[n][n] - sum[i][j] - fb[k][j])
其中 sum[i][j], tot[i][j] 分别代表 a, b 选了前 i, j 的点的情况下，
选择的点的点权和一级选择的点的个数。
fb 转移同理。

这个转移是个区间转移，设 gb[t][j] = min_{tot[k][j] > t} fb[k][j] 即可优化。
#endif
#include <cstdio>
#include <algorithm>
#include <queue>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	inline operator char () { char x[3]; return scanf("%s", x), *x; }
} read;

const int maxn = 2020;
struct Edge { int v, w; };
std::vector<Edge> G[maxn];

ll dis[maxn];
void dijk(int s, int n, std::vector<int> *vec) {
	typedef std::pair<ll, int> par;
	std::priority_queue<par> q;
	std::fill(dis + 1, dis + n + 1, 1000000000000000000);
	q.push(par(dis[s] = 0, s));
	int now = 1;
	ll last = 0;

	while(!q.empty()) {
		ll d = - q.top().first;
		int u = q.top().second;
		q.pop();
		if(d > dis[u]) continue;

		// debug("%d: %llu\n", u, dis[u]);
		if(dis[u] > last) {
			last = dis[u];
			++ now;
		}
		vec[now].push_back(u);

		for(Edge e : G[u])
			if(dis[u] + e.w < dis[e.v]) {
				dis[e.v] = dis[u] + e.w;
				q.push(par(- dis[e.v], e.v));
			}
	}
}

int val[maxn];
ll sum[maxn][maxn];
int tot[maxn][maxn];
std::vector<int> va[maxn], vb[maxn];
bool vis[maxn];

ll fa[maxn][maxn], fb[maxn][maxn];
ll ga[maxn][maxn], gb[maxn][maxn];

int main() {
	int n = read, m = read;
	int a = read, b = read;
	for(int i = 1; i <= n; i ++)
		val[i] = read;
	for(int i = 1; i <= m; i ++) {
		int u = read, v = read, w = read;
		G[u].push_back({v, w});
		G[v].push_back({u, w});
	}

	dijk(a, n, va);
	dijk(b, n, vb);

	for(int i = 0; i <= n; i ++) {
		if(i) {
			sum[i][0] = sum[i - 1][0];
			tot[i][0] = tot[i - 1][0];
			for(int u : va[i]) {
				sum[i][0] += val[u];
				++ tot[i][0];
				vis[u] = 1;
			}
		}
		for(int j = 1; j <= n; j ++) {
			sum[i][j] = sum[i][j - 1];
			tot[i][j] = tot[i][j - 1];
			for(int u : vb[j])
				if(!vis[u]) {
					sum[i][j] += val[u];
					++ tot[i][j];
				}
		}
	}

	// for(int i = 0; i <= n; i ++)
		// for(int j = 0; j <= n; j ++)
			// debug("sum[%d][%d] = %lld\n", i, j, sum[i][j]);
	ll all = sum[n][n];

	for(int i = n; i >= 0; i --)
		for(int j = n; j >= 0; j --)
			if(tot[i][j] < n) {
				ll s = all - sum[i][j];
				int t = tot[i][j];
				fa[i][j] = s - gb[t + 1][j];
				fb[i][j] = s - ga[i][t + 1];
				ga[i][t] = std::min({ga[i][t], ga[i][t + 1], fa[i][j]});
				gb[t][j] = std::min({gb[t][j], gb[t + 1][j], fb[i][j]});
				// fa[i][j] = fb[i][j] = - 1000000000000000000;
				// for(int k = n; tot[k][j] > t; k --)
					// fa[i][j] = std::max(fa[i][j], s - fb[k][j]); 
				// for(int k = n; tot[i][k] > t; k --)
					// fb[i][j] = std::max(fb[i][j], s - fa[i][k]);
				// debug("f[%d][%d] = %lld %lld\n", i, j, fa[i][j], fb[i][j]);
			}

	ll A = fa[0][0], B = all - fa[0][0];
	if(A > B) puts("Break a heart");
	if(A == B) puts("Flowers");
	if(A < B) puts("Cry");

	// debug("%lld %lld\n", A, B);
}
