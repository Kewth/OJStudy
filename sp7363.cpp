#if 0
2020.01.02

把 dist(u, v)^k 用第二类斯特灵数展开，然后套路交换枚举顺序。
化简后转换为求 f[u][i] = sum_v C(dist(u, v), i) ，根据组合数的递推式可以得到 f 的转移，
用换根 DP 求出所有 f[u][i] 即可。
#endif
#include <cstdio>
#include <vector>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
} read;

const int maxn = 20005, maxk = 22, mod = 1000000007;
std::vector<int> G[maxn];
ll f[maxn][maxk], g[maxn][maxk];

void add(ll *a, ll *b, int k, int x) {
	for(int i = 0; i <= k; i ++) (a[i] += mod + b[i] * x) %= mod;
	for(int i = 1; i <= k; i ++) (a[i] += mod + b[i - 1] * x) %= mod;
}

void dp1(int u, int fa, int k) {
	g[u][0] = g[u][1] = 1;
	for(int i = 2; i <= k; i ++)
		g[u][i] = 0;
	for(int v : G[u])
		if(v != fa) {
			dp1(v, u, k);
			add(g[u], g[v], k, 1);
		}
	for(int i = 0; i <= k; i ++)
		f[u][i] = g[u][i];
}

void dp2(int u, int fa, int k) {
	for(int v : G[u])
		if(v != fa) {
			add(f[u], g[v], k, -1);
			add(f[v], f[u], k, 1);
			add(f[u], g[v], k, 1);
			dp2(v, u, k);
		}
}

ll S[maxk][maxk];
ll fac[maxk];

int main() {
	int T = read;
	while(T --) {
		int n = read, k = read;

		S[0][0] = 1;
		for(int i = 1; i <= k; i ++)
			for(int j = 1; j <= i; j ++)
				S[i][j] = (j * S[i - 1][j] + S[i - 1][j - 1]) % mod;

		fac[0] = 1;
		for(int i = 1; i <= k; i ++)
			fac[i] = fac[i - 1] * i % mod;

		for(int u = 1; u <= n; u ++)
			G[u].clear();
		for(int i = 1; i < n; i ++) {
			int u = read + 1, v = read + 1;
			G[u].push_back(v);
			G[v].push_back(u);
		}

		dp1(1, 0, k);
		dp2(1, 0, k);

		for(int u = 1; u <= n; u ++) {
			ll ans = 0;
			for(int i = 0; i <= k; i ++)
				(ans += S[k][i] * fac[i] % mod * f[u][i]) %= mod;
			printf("%lld\n", ans);
		}
		puts("");
	}
}
