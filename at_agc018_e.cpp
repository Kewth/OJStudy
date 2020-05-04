#if 0
2020.05.03

  考虑一个点到一个矩阵的路径数，转为四个矩阵的加加减减，每个通过组合数可以化简到 O(1) 。那么
枚举中间矩阵的所有点然后计算就可以做到 O(n^2) 。考虑枚举进入中间矩阵的点 (a, b) ，可以简单算
出方案数，但是每条路径的贡献系数不一，取决于在中间矩阵经过了多少点。但如果直到离开中间矩阵的
点 (c, d) ，那么贡献系数就是 (c + d - a - b + 1) ，在 (a, b) 算上 (1 - a - b) 的贡献系数，在
(c, d) 算上 (c + d) 的贡献系数即可，复杂度 O(n) 。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 2000005, mod = 1000000007;
ll fac[maxn], ifac[maxn];

inline ll power (ll x, int k) {
	if (k < 0) k += mod - 1;
	ll res = 1;
	while (k) {
		if (k & 1) (res *= x) %= mod;
		(x *= x) %= mod;
		k >>= 1;
	}
	return res;
}

inline ll C (int n, int m) {
	return fac[n] * ifac[m] % mod * ifac[n - m] % mod;
}

void combinator_init (int n) {
	fac[0] = 1;
	for (int i = 1; i <= n; i ++)
		fac[i] = fac[i - 1] * i % mod;
	ifac[n] = power(fac[n], -1);
	for (int i = n; i; i --)
		ifac[i - 1] = ifac[i] * i % mod;
}

ll F (int n, int m) {
	if (n < 0 or m < 0) return 0;
	return C(n + m + 2, m + 1) - 1;
}

ll G (int x1, int x2, int y1, int y2) {
	/* if (x1 > x2 or y1 > y2) debug("ERROR\n"); */
	/* if (x1 < 0 or y1 < 0) debug("ERROR\n"); */
	-- x1, -- y1;
	return (F(x2, y2) - F(x1, y2) - F(x2, y1) + F(x1, y1) + mod * 2) % mod;
}

int main () {
	combinator_init(2000002);
	int x1 = read, x2 = read, x3 = read, x4 = read, x5 = read, x6 = read;
	int y1 = read, y2 = read, y3 = read, y4 = read, y5 = read, y6 = read;

	ll ans = 0;

	for (int i = x3; i <= x4; i ++)
		(ans += G(x5 - i, x6 - i, y5 - y4 - 1, y6 - y4 - 1) *
		 G(i - x2, i - x1, y4 - y2, y4 - y1) % mod *
		 (1 + i + y4)) %= mod;

	for (int i = y3; i <= y4; i ++)
		(ans += G(x5 - x4 - 1, x6 - x4 - 1, y5 - i, y6 - i) *
		 G(x4 - x2, x4 - x1, i - y2, i - y1) % mod *
		 (1 + i + x4)) %= mod;

	for (int i = x3; i <= x4; i ++)
		(ans += G(i - x2, i - x1, y3 - y2 - 1, y3 - y1 - 1) *
		 G(x5 - i, x6 - i, y5 - y3, y6 - y3) % mod *
		 (mod - i - y3)) %= mod;

	for (int i = y3; i <= y4; i ++)
		(ans += G(x3 - x2 - 1, x3 - x1 - 1, i - y2, i - y1) *
		 G(x5 - x3, x6 - x3, y5 - i, y6 - i) % mod *
		 (mod - i - x3)) %= mod;

	printf("%lld\n", ans);
}
