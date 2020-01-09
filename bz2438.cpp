#if 0
2020.01.09

考虑警察被搞死的概率，如果有 k 个点是警察必须通过尝试得到身份的，那么被搞死的概率是 k / n 。
求出这个 k ，将图缩点，DAG 上入度每个为 0 的强连通分量中对 k 贡献为 1 。
但是有一种特殊情况，如果已经查了 k - 1 个点，并由此得到了 n - 1 个点，
此时最后一个点被孤立，通过排除法可以知道其身份，
换言之如果存在一个强联通分量大小为 1 入度为 0 且其能到达的强连通分量入度都大于 1 ，
那么 k 需要减一。
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
std::vector<int> G[maxn], D[maxn];
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
			/* debug("%d in %d\n", x, bp); */
			ins[x] = 0;
			belong[x] = bp;
			con[bp].push_back(x);
		}
	}
}

int indeg[maxn];
bool vis[maxn];
int main() {
	int n = read, m = read;

	for(int i = 1; i <= m; i ++) {
		int u = read, v = read;
		G[u].push_back(v);
	}

	for(int i = 1; i <= n; i ++)
		if(!dfn[i])
			dfs(i);

	for(int u = 1; u <= bp; u ++) {
		vis[u] = 1;
		for(int x : con[u])
			for(int v : G[x])
				if(!vis[belong[v]]) {
					/* debug("%d -> %d -> %d -> %d\n", u, x, v, belong[v]); */
					D[u].push_back(belong[v]);
					vis[belong[v]] = 1;
				}
		for(int x : con[u])
			for(int v : G[x])
				vis[belong[v]] = 0;
		vis[u] = 0;
	}

	for(int u = 1; u <= bp; u ++)
		for(int v : D[u])
			++ indeg[v];

	int tot = 0;
	for(int u = 1; u <= bp; u ++)
		if(!indeg[u] and con[u].size() == 1) {
			bool ok = 1;
			for(int v : D[u])
				ok &= indeg[v] > 1;
			if(ok) tot = -1;
		}

	for(int u = 1; u <= bp; u ++)
		tot += !indeg[u];

	printf("%.6lf\n", 1 - 1.0 * tot / n);
}
