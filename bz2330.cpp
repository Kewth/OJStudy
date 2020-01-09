#if 0
2020.01.09

先将 a >= b 关系连边，然后缩点，一个 scc 内的值必须相等。
然后对于 a > b 的关系连边，如果成环或者 a, b 在同一个 scc 那么不合法。
否则在 DAG 上 DP 即可。
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

std::vector<int> D[maxn], D2[maxn];
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

int f[maxn];
void dp(int u) {
	if(ins[u]) puts("-1"), exit(0);
	if(vis[u]) return;
	vis[u] = ins[u] = 1;
	for(int v : D[u]) {
		/* debug("%d >= %d\n", u, v); */
		dp(v);
		f[u] = std::max(f[u], f[v]);
	}
	for(int v : D2[u]) {
		/* debug("%d > %d\n", u, v); */
		dp(v);
		f[u] = std::max(f[u], f[v] + 1);
	}
	ins[u] = 0;
}

int t[maxn], a[maxn], b[maxn];
int main() {
	int n = read, m = read;
	for(int i = 1; i <= m; i ++)
		read(t[i], a[i], b[i]);

	for(int i = 1; i <= m; i ++) {
		if(t[i] == 1 or t[i] == 3)
			G[a[i]].push_back(b[i]);
		if(t[i] == 1 or t[i] == 5)
			G[b[i]].push_back(a[i]);
	}

	for(int i = 1; i <= n; i ++)
		if(!dfn[i])
			dfs(i);
	rebuild();

	for(int i = 1; i <= m; i ++) {
		int x = belong[a[i]], y = belong[b[i]];
		if(t[i] == 2) {
			if(x == y) return puts("-1"), 0;
			D2[y].push_back(x);
		}
		if(t[i] == 4) {
			if(x == y) return puts("-1"), 0;
			D2[x].push_back(y);
		}
	}

	ll ans = 0;
	for(int u = 1; u <= bp; u ++) {
		dp(u);
		ans += 1ll * f[u] * int(con[u].size());
	}

	printf("%lld\n", ans + n);
}
