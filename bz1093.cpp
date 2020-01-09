#if 0
2020.01.09

首先对于一个强连通分量，如果半联通子图包含了其中一个点，
那么包含这个强连通分量的所有点一定仍然可以保持半联通的性质，并且点数不会减少。
那么缩点，相当于在 dag 上选半联通子图，也就是一条链。
dag 上 DP 设 f[u], g[u] 分别表示最大链和方案数即可。
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

const int maxn = 100005;
std::vector<int> G[maxn];
bool ins[maxn];
int stack[maxn], sp;
int dfn[maxn], low[maxn], ip;
int belong[maxn], bp;
std::vector<int> con[maxn];

void dfs(int u) {
	low[u] = dfn[u] = ++ ip;
	stack[++ sp] = u;
	ins[u] = 1;
	for(int v : G[u])
		if(!dfn[v]) {
			dfs(v);
			low[u] = std::min(low[u], low[v]);
		} else if(ins[v])
			low[u] = std::min(low[u], low[v]);
	if(low[u] == dfn[u]) {
		++ bp;
		while(stack[sp + 1] != u) {
			int x = stack[sp --];
			ins[x] = 0;
			belong[x] = bp;
			con[bp].push_back(x);
		}
	}
}

std::vector<int> D[maxn];
bool vis[maxn];
void rebuild() {
	for(int u = 1; u <= bp; u ++) {
		vis[u] = 1;
		for(int x : con[u])
			for(int v : G[x])
				if(!vis[belong[v]]) {
					D[u].push_back(belong[v]);
					vis[belong[v]] = 1;
				}
		for(int x : con[u])
			for(int v : G[x])
				vis[belong[v]] = 0;
		vis[u] = 0;
	}
}

int f[maxn], g[maxn], mod;
void dp(int u) {
	int sz = int(con[u].size());
	f[u] = sz;
	g[u] = 1;
	for(int v : D[u]) {
		if(!f[v]) dp(v);
		if(f[v] + sz > f[u]) {
			f[u] = f[v] + sz;
			g[u] = g[v];
		} else if(f[v] + sz == f[u])
			(g[u] += g[v]) %= mod;
	}
}

int main() {
	int n = read, m = read;
	read(mod);

	for(int i = 1; i <= m; i ++) {
		int u = read, v = read;
		G[u].push_back(v);
	}

	for(int i = 1; i <= n; i ++)
		if(!dfn[i])
			dfs(i);
	rebuild();

	int fans = 0, gans = 1;
	for(int u = 1; u <= bp; u ++)
		if(!f[u]) {
			dp(u);
			if(f[u] > fans) {
				fans = f[u];
				gans = g[u];
			} else if(f[u] == fans)
				(gans += g[u]) %= mod;
		}

	printf("%d\n%d\n", fans, gans);
}
