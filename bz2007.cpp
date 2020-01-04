#if 0
2020.01.04

首先海拔只能有 0 和 1 ，其次海拔为 0/1 的点分别各自构成联通块。
那么一个海拔分配就是把格点划分为两个联通块，代价是 0 联通块到 1 联通块之间的边权和。
也就是 s 到 t 的最小割。
但直接跑网络流复杂度太大，利用到网格图的优秀性质，转对偶图跑最短路即可。
#endif
#include <cstdio>
#include <vector>
#include <queue>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef std::pair<ll, int> par;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
} read;

const int maxn = 250005;
struct Edge { int v, w; };
std::vector<Edge> G[maxn];
ll dis[maxn];

int main() {
	int n = read;
	int s = n * n, t = n * n + 1;

	for(int j = 0; j < n; j ++)
		G[0 * n + j].push_back(Edge({t, read}));
	for(int i = 1; i < n; i ++)
		for(int j = 0; j < n; j ++)
			G[i * n + j].push_back(Edge({(i - 1) * n + j, read}));
	for(int j = 0; j < n; j ++)
		G[s].push_back(Edge({(n - 1) * n + j, read}));

	for(int i = 0; i < n; i ++) {
		G[s].push_back(Edge({i * n + 0, read}));
		for(int j = 1; j < n; j ++)
			G[i * n + j - 1].push_back(Edge({i * n + j, read}));
		G[i * n + n - 1].push_back(Edge({t, read}));
	}

	for(int j = 0; j < n; j ++)
		G[t].push_back(Edge({0 * n + j, read}));
	for(int i = 1; i < n; i ++)
		for(int j = 0; j < n; j ++)
			G[(i - 1) * n + j].push_back(Edge({i * n + j, read}));
	for(int j = 0; j < n; j ++)
		G[(n - 1) * n + j].push_back(Edge({s, read}));

	for(int i = 0; i < n; i ++) {
		G[i * n + 0].push_back(Edge({s, read}));
		for(int j = 1; j < n; j ++)
			G[i * n + j].push_back(Edge({i * n + j - 1, read}));
		G[t].push_back(Edge({i * n + n - 1, read}));
	}

	for(int i = 0; i < n * n + 2; i ++)
		dis[i] = 1000000000000000000;

	std::priority_queue<par> q;
	q.push(par(dis[s] = 0, s));
	while(!q.empty()) {
		ll d = - q.top().first;
		int u = q.top().second;
		q.pop();
		if(d > dis[u]) continue;

		for(Edge e : G[u])
			if(dis[u] + e.w < dis[e.v]) {
				dis[e.v] = dis[u] + e.w;
				q.push(par(- dis[e.v], e.v));
			}
	}

	printf("%lld\n", dis[t]);
}
