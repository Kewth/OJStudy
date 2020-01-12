#if 0
2020.01.11

点分板子，由于需要查询不超过一个距离的点数，用树状数组维护即可。
#endif
#include <cstdio>
#include <algorithm>
#include <vector>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
} read;

const int maxn = 40005;
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

int K;
int bit[maxn];
int query(int p) {
	int res = bit[0];
	for(int k = p; k; k -= k & -k)
		res += bit[k];
	return res;
}

void modify(int p, int x) {
	bit[p] += x;
	// 少一个括号调一年
	for(int k = p + (p & -p); k and k <= K; k += k & -k)
		bit[k] += x;
}

int get[maxn], gp;
void dfs(int u, int d) {
	if(d <= K)
		get[++ gp] = d;
	size[u] = 1;
	vis[u] = 1;
	for(Edge e : G[u])
		if(!vis[e.to]) {
			dfs(e.to, d + e.w);
			size[u] += size[e.to];
		}
	vis[u] = 0;
}

ll ans;
int allget[maxn], ap;
void divi(int u, int n) {
	minsize = n;
	center = u;
	get_center(u, n);
	u = center;

	vis[u] = 1;
	modify(0, 1);
	for(Edge e : G[u])
		if(!vis[e.to]) {
			dfs(e.to, e.w);
			for(int i = 1; i <= gp; i ++)
				ans += query(K - get[i]);
			while(gp)
				modify(allget[++ ap] = get[gp --], 1);
		}

	modify(0, -1);
	while(ap)
		modify(allget[ap --], -1);

	for(Edge e : G[u])
		if(!vis[e.to])
			divi(e.to, size[e.to]);
}

int main() {
	int n = read;
	for(int i = 1; i < n; i ++) {
		int u = read, v = read, w = read;
		G[u].push_back(Edge({v, w}));
		G[v].push_back(Edge({u, w}));
	}
	read(K);
	divi(1, n);
	printf("%lld\n", ans);
}
