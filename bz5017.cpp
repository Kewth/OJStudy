#if 0
2019.11.11

区间连边可以离散化后线段树优化建图，
然后求一个有向图每个点作为起点能走到多少关键点，
SCC 缩点转成 DAG ，在 DAG 上 DP 即可。
#endif
#include <cstdio>
#include <vector>
#include <algorithm>
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

const int maxn = 500005, maxd = maxn << 2, mod = 1000000007;
std::vector<int> G[maxd];
bool key[maxd];
int pos[maxn];

void build(int now, int L, int R) {
	if(L == R) return pos[L] = now, key[now] = 1, void();
	G[now].push_back(now << 1);
	G[now].push_back(now << 1 | 1);
	int M = (L + R) >> 1;
	build(now << 1, L, M);
	build(now << 1 | 1, M + 1, R);
}

void link(int now, int L, int R, int u, int l, int r) {
	if(r < L or l > R) return;
	if(l <= L and R <= r) return G[u].push_back(now);
	int M = (L + R) >> 1;
	link(now << 1, L, M, u, l, r);
	link(now << 1 | 1, M + 1, R, u, l, r);
}

int dfn[maxd], low[maxd], ins[maxd], stack[maxd], sp, ip;
int belong[maxd], bp;
std::vector<int> contain[maxd];
int f[maxd];

void dfs(int u) {
	low[u] = dfn[u] = ++ ip;
	stack[++ sp] = u;
	ins[u] = 1;

	/* for(int v : G[u]) */
	/* 	debug("%d -> %d\n", u, v); */

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
			/* debug("%d belong to %d\n", x, bp); */
			ins[x] = 0;
			belong[x] = bp;
			contain[bp].push_back(x);
			f[bp] += key[x];
		}
	}
}

bool vis[maxd];
void dp(int u) {
	if(vis[u]) return;
	vis[u] = 1;

	std::set<int> to;
	for(int x : contain[u])
		for(int v : G[x])
			to.insert(belong[v]);
	to.erase(u);

	for(int v : to) {
		dp(v);
		f[u] += f[v];
	}

	/* debug("f[%d] = %d\n", u, f[u]); */
}

ll x[maxn], r[maxn], tmp[maxn];

int main() {
	int n = read;
	build(1, 1, n);

	for(int i = 1; i <= n; i ++) {
		tmp[i] = x[i] = read;
		read(r[i]);
	}

	std::sort(tmp + 1, tmp + n + 1);

	for(int i = 1; i <= n; i ++) {
		int L = int(std::lower_bound(tmp + 1, tmp + n + 1, x[i] - r[i]) - tmp);
		int R = int(std::upper_bound(tmp + 1, tmp + n + 1, x[i] + r[i]) - tmp - 1);
		link(1, 1, n, pos[i], L, R);
	}

	dfs(1);
	for(int i = 1; i <= bp; i ++)
		dp(i);

	int ans = 0;
	for(int i = 1; i <= n; i ++)
		ans = (ans + 1ll * i * f[belong[pos[i]]]) % mod;

	printf("%d\n", ans);
}
