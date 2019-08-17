#if 0
2019.08.01

加油站才是真正的点，其他点可以抽象成路径中的一个元素。
考虑建出加油站之间的最小生成树。
先用多源最短路求出每个点最近的加油站，然后枚举边 (u, v) ，构造出新图上的边，(pool[u], pool[v]) ，
其中 pool[u] 是 u 最近的加油站，距离就是两点都各自最近加油站的距离和加上 u-v 距离。
在新图上求最小生成树即可。
#endif
#include <cstdio>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

inline int input() {
	int c = getchar(), x = 0;
	while(c < '0' or c > '9') c = getchar();
	while(c >= '0' and c <= '9') x = x * 10 + c - '0', c = getchar();
	return x;
}

struct Edge {
	int v, w, u;
	Edge(int v, int w, int u = 0): v(v), w(w), u(u) {}
};
const int maxn = 200005;
std::vector<Edge> G[maxn], T[maxn];
int dis[maxn], pool[maxn];
int fa[maxn];
bool vis[maxn];
int deep[maxn], dist[maxn][20], up[maxn][20];

int find(int x) {
	if(fa[x] == x) return x;
	return fa[x] = find(fa[x]);
}

bool operator < (Edge a, Edge b) {
	return a.w > b.w;
}

void dfs(int u) {
	debug("%d\n", u);
	vis[u] = true;
	for(size_t i = 0; i < T[u].size(); i ++) {
		int v = T[u][i].v, w = T[u][i].w;
		if(v != up[u][0]) {
			deep[v] = deep[u] + 1;
			dist[v][0] = w;
			up[v][0] = u;
			for(int k = 1; k < 20; k ++) {
				dist[v][k] = std::max(dist[v][k - 1], dist[up[v][k - 1]][k - 1]);
				up[v][k] = up[up[v][k - 1]][k - 1];
			}
			dfs(v);
		}
	}
}

int max(int x, int y) {
	if(deep[x] < deep[y])
		std::swap(x, y);
	int d = deep[x] - deep[y];
	int res = 0;
	for(int k = 0; k < 20; k ++)
		if(d >> k & 1) {
			res = std::max(res, dist[x][k]);
			x = up[x][k];
		}
	for(int k = 19; k >= 0; k --)
		if(up[x][k] != up[y][k]) {
			res = std::max(res, dist[x][k]);
			res = std::max(res, dist[y][k]);
			x = up[x][k];
			y = up[y][k];
		}
	if(x != y) {
		res = std::max(res, dist[x][0]);
		res = std::max(res, dist[y][0]);
		if(not up[x][0] and not up[y][0]) return INT_MAX >> 1;
	}
	return res;
}

int main() {
	int n = input(), s = input(), m = input();
	for(int i = 1; i <= n; i ++) {
		dis[i] = INT_MAX >> 1;
		fa[i] = i;
	}
	std::priority_queue<Edge> qu;
	for(int i = 1; i <= s; i ++) {
		int u = input();
		qu.push(Edge(u, 0));
		pool[u] = u;
		dis[u] = 0;
	}
	for(int i = 1; i <= m; i ++) {
		int u = input(), v = input(), w = input();
		G[u].push_back(Edge(v, w));
		G[v].push_back(Edge(u, w));
	}
	while(not qu.empty()) {
		int u = qu.top().v;
		qu.pop();
		if(vis[u]) continue;
		vis[u] = true;
		// debug("dis[%d] = %d\n", u, dis[u]);
		for(size_t i = 0; i < G[u].size(); i ++) {
			int v = G[u][i].v;
			if(dis[u] + G[u][i].w < dis[v]) {
				pool[v] = pool[u];
				dis[v] = dis[u] + G[u][i].w;
				qu.push(Edge(v, dis[v]));
			}
		}
	}
	for(int u = 1; u <= n; u ++)
		if(vis[u]) {
			for(size_t i = 0; i < G[u].size(); i ++) {
				int v = G[u][i].v, w = G[u][i].w;
				if(not vis[v])
					qu.push(Edge(pool[v], dis[u] + w + dis[v], pool[u]));
			}
			vis[u] = false;
		}
	while(not qu.empty()) {
		Edge e = qu.top();
		qu.pop();
		if(find(e.u) != find(e.v)) {
			fa[find(e.u)] = fa[find(e.v)];
			debug("Tadd %d %d %d\n", e.u, e.v, e.w);
			T[e.u].push_back(Edge(e.v, e.w));
			T[e.v].push_back(Edge(e.u, e.w));
		}
	}
	for(int i = 1; i <= n; i ++)
		if(dis[i] == 0 and not vis[i])
			dfs(i);
	int q = input();
	while(q --) {
		int u = input(), v = input(), b = input();
		if(max(u, v) <= b)
			puts("TAK");
		else
			puts("NIE");
	}
}
