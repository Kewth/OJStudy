#if 0
2019.08.12

朴素 DP 设 f[i][j] 表示 n, m 分别为 i, j 时的答案。
考虑每个 f[i][j] 对最后 f[n][m] 的贡献，
设 g[n][m] 表示所有 i != j 的 f[i][j] 对 f[n][m] 的贡献和，
假设 n > m ，由 f 的递推式可以得出 g[n][m] = g[n][m - 1] ，
进一步的，g[n][m] = max(n, m) 。

那么现在的问题是计算每个 f[i][i] 对 f[n][m] 的贡献。
不难发现每条转移路径上的 f[i][i] 的贡献是 1 / 2 ，
那么 f[i][i] 的贡献就是 1 / 2 乘上转移到 f[i][i] 的系数，即概率，
而这个概率就是经过 f[i][i] 的转移上的路径数除以总路径数。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;
inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 500005, mod = 998244353;
lolong fac[maxn << 1];
lolong invfac[maxn << 1];

inline lolong power(lolong x, int k) {
	if(k < 0) k += mod - 1;
	lolong res = 1;
	while(k) {
		if(k & 1) (res *= x) %= mod;
		(x *= x) %= mod;
		k >>= 1;
	}
	return res;
}

inline lolong C(int n, int m) {
	return fac[n] * invfac[m] % mod * invfac[n - m] % mod;
}

int main() {
	int n = input(), m = input();
	fac[0] = 1;
	for(int i = 1; i <= n + m; i ++)
		fac[i] = fac[i - 1] * i % mod;
	invfac[n + m] = power(fac[n + m], -1);
	for(int i = n + m - 1; i >= 0; i --)
		invfac[i] = invfac[i + 1] * (i + 1) % mod;
	lolong ans = 0;
	for(int i = 1; i <= n and i <= m; i ++)
		/* debug("%lld\n", ans), */
		ans += C(i << 1, i) * C(n + m - (i << 1), n - i) % mod;
	ans %= mod;
	(ans *= power(2 * C(n + m, n) % mod, -1)) %= mod;
	 ans += std::max(n, m);
	printf("%lld\n", ans);
}
