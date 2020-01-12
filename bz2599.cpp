#if 0
2020.01.11

点分治，只需要考虑经过某个点的路径的贡献。
#endif
#include <cstdio>
#include <algorithm>
#include <vector>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef std::pair<int, int> par;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
} read;

const int maxn = 200005, maxk = 1000005;
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
	/* debug("%d : %d %d\n", u, max, size[u]); */
	if(max < minsize) {
		center = u;
		minsize = max;
	}
}

int min[maxk], k;
std::vector<par> get;
void dfs(int u, int ed, ll d) {
	if(d <= k)
		get.push_back(par(d, ed));
	size[u] = 1;
	vis[u] = 1;
	for(Edge e : G[u])
		if(!vis[e.to]) {
			dfs(e.to, ed + 1, d + e.w);
			size[u] += size[e.to];
		}
	vis[u] = 0;
}

int ans = maxn;
void divi(int u, int n) {
	minsize = n;
	center = u;
	get_center(u, n);
	u = center;

	std::vector<int> allget;
	vis[u] = 1;
	for(Edge e : G[u])
		if(!vis[e.to]) {
			get.clear();
			dfs(e.to, 1, e.w);
			for(par p : get)
				ans = std::min(ans, min[k - p.first] + p.second);
			for(par p : get) {
				min[p.first] = std::min(min[p.first], p.second);
				allget.push_back(p.first);
			}
		}

	for(int d : allget)
		if(d)
			min[d] = maxn;

	for(Edge e : G[u])
		if(!vis[e.to])
			divi(e.to, size[e.to]);
}

int main() {
	int n = read;
	read(k);
	for(int i = 1; i < n; i ++) {
		int u = read + 1, v = read + 1, w = read;
		G[u].push_back(Edge({v, w}));
		G[v].push_back(Edge({u, w}));
	}

	for(int i = 1; i < maxk; i ++)
		min[i] = maxn;
	min[0] = 0;

	divi(1, n);

	if(ans >= n) puts("-1");
	else printf("%d\n", ans);
}
