#if 0
2020.01.03

第一次在 51nod 上拿到一血。
一个点 u 一定要通过非树边跳出子树，然后一直走树边到 1 。
假设从 v 经过非树边 (v -> x, w) 跳出去，由于是最短路树，u 到 v 的最短路一定是走树边。
那么这个答案就是 dis[v] - dis[u] + w + dis[x] 。
对于每个非树边 (v -> x, w) ，设 c = lca(v, x) ，
那么其可以贡献的 u 在 v 到 c 之间（不包括 c ），且贡献为 dis[v] + w + dis[x] 。
那么只需要支持对一条路径区间取最小值即可，可以用 set 打差分标记然后启发式合并。
（讲道理直接树剖套线段树也是可以的）
#endif
#include <cstdio>
#include <vector>
#include <set>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
} read;

const int maxn = 4040, maxk = 20, maxm = 100005;
struct Edge { int v, w; };
std::vector<Edge> G[maxn], T[maxn];

int dis[maxn], fa[maxn][maxk];
int deep[maxn];
void dfs1(int u) {
	deep[u] = deep[*fa[u]] + 1;
	for(int k = 1; fa[u][k - 1]; k ++)
		fa[u][k] = fa[fa[u][k - 1]][k - 1];
	for(Edge e : T[u])
		if(e.v != *fa[u]) {
			*fa[e.v] = u;
			dis[e.v] = dis[u] + e.w;
			dfs1(e.v);
		}
}

int lca(int x, int y) {
	if(deep[x] < deep[y]) std::swap(x, y);
	for(int k = maxk - 1; k >= 0; k --)
		if(deep[fa[x][k]] >= deep[y])
			x = fa[x][k];
	for(int k = maxk - 1; k >= 0; k --)
		if(fa[x][k] != fa[y][k]) {
			x = fa[x][k];
			y = fa[y][k];
		}
	return x == y ? x : *fa[x];
}

std::multiset<int> add[maxn], erase[maxn];
void dfs2(int u) {
	for(Edge e : T[u])
		if(e.v != *fa[u])
			dfs2(e.v);
	for(Edge e : G[u]) {
		int c = lca(u, e.v);
		add[u].insert(dis[u] + e.w + dis[e.v]);
		erase[c].insert(dis[u] + e.w + dis[e.v]);
	}
}

int ans[maxn];
void dfs3(int u) {
	for(Edge e : T[u])
		if(e.v != *fa[u]) {
			dfs3(e.v);
			if(add[u].size() < add[e.v].size())
				std::swap(add[u], add[e.v]);
			for(int x : add[e.v])
				add[u].insert(x);
		}
	for(int x : erase[u])
		add[u].erase(add[u].find(x));
	if(add[u].empty()) ans[u] = -1;
	else ans[u] = *add[u].begin() - dis[u];
}

int main() {
	int n = read, m = read;

	for(int i = 1; i <= m; i ++) {
		int u = read, v = read, w = read, t = read;
		if(t) {
			T[u].push_back(Edge({v, w}));
			T[v].push_back(Edge({u, w}));
		} else {
			G[u].push_back(Edge({v, w}));
			G[v].push_back(Edge({u, w}));
		}
	}

	dfs1(1);
	dfs2(1);
	dfs3(1);

	for(int u = 2; u <= n; u ++)
		printf("%d ", ans[u]);
	puts("");
}
