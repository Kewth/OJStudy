#if 0
2020.04.12

DP 设 f[u][i] 表示考虑 u 的子树的向上的连边，其中 u 有 i 个点可以连的方案数。
暴力转移枚举 u 连第几个点即可，可以前缀和优化。
#endif
#include <cstdio>
#include <algorithm>
#include <vector>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	/* inline operator ll () { ll x; return scanf("%lld", &x), x; } */
	/* template<class T> inline void operator () (T &x) { x = *this; } */
	/* template<class T, class ...A> inline void operator () (T &x, A &...a) */
	/* { x = *this; this -> operator () (a...); } */
} read;

const int maxn = 3005, mod = 998244353;
ll f[maxn][maxn], g[maxn];
std::vector<int> G[maxn];

void dp (int u, int d) {
	for (int v : G[u])
		dp (v, d + 1);
	for (int i = 1; i <= d + 1; i ++) {
		g[i] = 1;
		for (int v : G[u])
			(g[i] *= f[v][i]) %= mod;
	}
	for (int i = 1; i <= d; i ++)
		f[u][i] = (f[u][i - 1] + g[i + 1]) % mod;
}

int main () {
	int n = read;
	for (int i = 1; i < n; i ++) {
		int u = read, v = read;
		if (u > v) G[u].push_back(v);
		if (v > u) G[v].push_back(u);
	}
	ll ans = 1;
	for (int u : G[n]) {
		dp(u, 1);
		(ans *= f[u][1]) %= mod;
	}
	printf("%lld\n", ans);
}
