#if 0
2020.01.04

被 6 级题虐自闭。
首先建出最短路图（在此之前我只知道最短路树），
问题转换为对于最短路图上每条边，割掉它之后有多少点无法到达 S 。
考虑对于每个点找出它到 S 必须经过的边，这样的边数是 O(m) 的，
注意到这些边一定在一条路径中，否则如果有两条边不在一条路径，那么它们都不是必须经过的。
而只需要关注这些边离 S 最远的一个，如果把边上也看做点，
那么对于 u 只需要找到离 S 最远的一个必经点 x = f(u) ，然后 x 同样可以找到这样一个点 f(x) ，
直到找到 S = f(x) ，中间经过的点就构成了 u 必须经过的点集。
不难发现这个关系是一颗树，f(u) 就是树上 u 的父亲。
考虑建出这颗“必经点树”，关键在于求 f(u) ，
事实上 f(u) 就是最短路图上 u 能到达的所有点 v 在“必经点树”上的 lca 。
那么每个点如果删掉后，该点子树内的点都无法到达 S 。
在树上简单计数即可。
#endif
#include <cstdio>
#include <vector>
#include <queue>
#include <stack>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef std::pair<ll, int> par;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
} read;

const int maxn = 300005, maxk = 20;
struct Edge { int v, w; };
std::vector<Edge> G[maxn];
std::vector<int> D[maxn];

int ip;
int deg[maxn];
ll dis[maxn];
void dijk(int s) {
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
			} else if(dis[e.v] + e.w == dis[u]) {
				D[e.v].push_back(++ ip);
				++ deg[ip];
				D[ip].push_back(u);
				++ deg[u];
			}

	}
}

int topsort[maxn], tp;
int fa[maxn][maxk];
int deep[maxn];

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

int tot[maxn], ans[maxn];

int main() {
	int n = read, m = read;
	for(int i = 1; i <= m; i ++) {
		int u = read, v = read, w = read;
		G[u].push_back(Edge({v, w}));
		G[v].push_back(Edge({u, w}));
	}
	int s = read;

	ip = n;
	for(int i = 1; i <= n; i ++)
		dis[i] = 1000000000000000000;
	dijk(s);

	std::stack<int> st;
	st.push(s);
	while(!st.empty()) {
		int u = st.top();
		st.pop();
		topsort[++ tp] = u;
		deep[u] = deep[*fa[u]] + 1;
		for(int k = 1; k < maxk; k ++)
			fa[u][k] = fa[fa[u][k - 1]][k - 1];
		for(int v : D[u]) {
			if(-- deg[v] == 0)
				st.push(v);
			if(!*fa[v])
				*fa[v] = u;
			else
				*fa[v] = lca(*fa[v], u);
		}
	}

	for(int i = tp; i; i --) {
		int u = topsort[i];
		if(u <= n) ++ tot[u];
		tot[*fa[u]] += tot[u];
	}

	for(int u = 1; u <= n; u ++)
		for(int v : D[u])
			ans[u] += tot[v];

	for(int u = n + 1; u <= ip; u ++)
		for(int v : D[u])
			ans[v] += tot[u];

	for(int u = 1; u <= n; u ++)
		printf("%d\n", ans[u]);
}
