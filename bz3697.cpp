#if 0
2020.01.11

点分，对于一侧的路径根据是否存在能做休息站的点分为两类。
两侧路径合并统计答案时只要两者存在一侧可以有休息站即可。
另外还有两侧都没有休息站但是当前根做休息站的情况，
以及一侧有休息站加上当前根节点。
#endif
#include <cstdio>
#include <algorithm>
#include <vector>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
} read;

const int maxn = 100005;
struct Edge {
	int to, w;
};
std::vector<Edge> G[maxn];

int size[maxn];
int center, minsize;
bool vis[maxn];
void get_center(int u, int n) {
	size[u] = 1;
	int max = 0;
	vis[u] = 1;
	for(Edge e : G[u])
		if(!vis[e.to]) {
			get_center(e.to, n);
			size[u] += size[e.to];
			max = std::max(max, size[e.to]);
		}
	vis[u] = 0;
	max = std::max(max, n - size[u]);
	if(max < minsize) {
		center = u;
		minsize = max;
	}
}

int get[2][maxn], gp[2];
int pass[maxn << 1];
void dfs(int u, int d) {
	bool o = pass[maxn + d];
	get[o][++ gp[o]] = d;
	++ pass[maxn + d];
	size[u] = 1;
	vis[u] = 1;
	for(Edge e : G[u])
		if(!vis[e.to]) {
			dfs(e.to, d + e.w);
			size[u] += size[e.to];
		}
	vis[u] = 0;
	-- pass[maxn + d];
}

int tot[2][maxn << 1];
int allget[2][maxn], ap[2];
ll ans;
void divi(int u, int n) {
	minsize = n;
	center = u;
	get_center(u, n);
	u = center;
	/* debug("%d %d\n", u, n); */

	vis[u] = 1;
	for(Edge e : G[u])
		if(!vis[e.to]) {
			dfs(e.to, e.w);
			for(int i = 1; i <= gp[0]; i ++)
				ans += tot[1][maxn - get[0][i]] + (get[0][i] ? 0 : tot[0][maxn]);
			for(int i = 1; i <= gp[1]; i ++)
				ans += tot[1][maxn - get[1][i]] +
					tot[0][maxn - get[1][i]] + (get[1][i] ? 0 : 1);
			/* for(int i = 1; i <= gp[0]; i ++) */
			/* 	debug(" %d", get[0][i]); */
			/* debug(" <get0 %d\n", e.to); */
			/* for(int i = 1; i <= gp[1]; i ++) */
			/* 	debug(" %d", get[1][i]); */
			/* debug(" <get1 %d\n", e.to); */
			for(int i = 0; i < 2; i ++)
				while(gp[i])
					++ tot[i][maxn + (allget[i][++ ap[i]] = get[i][gp[i] --])];
			/* debug("%lld\n", ans); */
		}

	for(int i = 0; i < 2; i ++)
		while(ap[i])
			-- tot[i][maxn + allget[i][ap[i] --]];

	for(Edge e : G[u])
		if(!vis[e.to])
			divi(e.to, size[e.to]);
}

int main() {
	int n = read;
	for(int i = 1; i < n; i ++) {
		int u = read, v = read, w = read;
		if(w == 0) w = -1;
		G[u].push_back(Edge({v, w}));
		G[v].push_back(Edge({u, w}));
	}
	divi(1, n);
	printf("%lld\n", ans);
}
