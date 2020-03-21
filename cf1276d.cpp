#if 0
2020.03.20

称点 u 被边 e 覆盖，当且仅当处理到 e 时选择了 u 这个点。
问题就是求合法的覆盖方案数。
DP 设 f[u], bf[u], af[u], nf[u] 分别表示 u 子树内的以下四种情况的覆盖方案数：
f: u 被父亲边覆盖
bf: u 被编号小于父亲边的儿子边覆盖
af: u 被编号大于父亲边的儿子边覆盖
nf: u 没有被覆盖
转移时将儿子边按编号从小到大进行子树合并，讨论当前儿子边与父亲边的编号关系即可。
#endif
#include <cstdio>
#include <algorithm>
#include <vector>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 200005, mod = 998244353;
ll f[maxn], bf[maxn], af[maxn], nf[maxn], g[maxn];
struct Edge { int v, w; };
std::vector<Edge> G[maxn];

void dp (int u, int fw) {
	f[u] = nf[u] = 1;
	for (Edge e : G[u]) {
		if (e.w < fw) {
			dp(e.v, e.w);
			(f[u] *= f[e.v] + bf[e.v]) %= mod;
			bf[u] = (bf[u] * g[e.v] + nf[u] * (nf[e.v] + af[e.v])) % mod;
			af[u] = 0;
			(nf[u] *= f[e.v] + bf[e.v]) %= mod;
		}
		if (e.w > fw) {
			dp(e.v, e.w);
			(f[u] *= g[e.v]) %= mod;
			(bf[u] *= g[e.v]) %= mod;
			af[u] = (af[u] * g[e.v] + nf[u] * (nf[e.v] + af[e.v])) % mod;
			(nf[u] *= f[e.v] + bf[e.v]) %= mod;
		}
	}
	g[u] = (bf[u] + af[u] + nf[u]) % mod;
	/* debug("%d: %lld %lld %lld %lld\n", u, f[u], bf[u], af[u], nf[u]); */
}

int main () {
	int n = read;
	for (int i = 1; i < n; i ++) {
		int u = read, v = read;
		G[u].push_back({v, i});
		G[v].push_back({u, i});
	}
	dp(1, 0);
	printf("%lld\n", g[1]);
}
