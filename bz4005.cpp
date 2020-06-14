/*
 * Since g++10 is released, some characters is not valid inside #if 0 :(
 * So, why not using clang++? :D

 * Date:
  2020.06.02

 * Solution:
 * 问题转换，折线法容斥的推广（反复折线）

  首先每一行只有一个数没有出现，不妨设 a[i] 表示第 i 行没有出现的数，不难发现就是要统计
满足 a[i] >= a[i - 1] - 1 的序列 a 的个数。

  设计一个朴素 DP f[i][j] 表示考虑前 i 个数满足 a[i] = j 的方案数，根据转移方程，可以知
道其组合意义就是在二维平面上从一个点 A 到另一个点 B ，不能触碰两条直线 l1, l2 的路径数。

  如果只有 l1 ，显然折线法可以简单统计，有了两条直线的限制，可以将折线法扩展，如果路径
重复经过了 l1, l2, l1 ... ，可以多次折线容斥以统计方案数。

 * CopyRight:
          ▁▃▄▄▄▃▃▃▃▄▶
        ▗▇▀▔    ▔▔▔▔
       ▄▛   ▃▅━━■▄▂
      ▟▊   ▐▘     ▀▙
     ▟▜▌   ▐▖   ▋  ▐▍
    ▟▘ ▜   ▝▀▇▆●▘  ▐▌
  ▗▟▘   ▜▃       ▁▅▛
  ▔▀▼▅▄▃▃██▅▄▄▄▅■▀▔
        ▔▔▔▔▔▔
 */

#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 3000005, mod = 1000000007;
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
	if (n < m or m < 0) return 0;
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

inline ll To (int x, int y) {
	/* debug("%d %d -> %lld\n", x, y, C(x, (x + y) >> 1)); */
	return C(x, (x + y) >> 1);
}

int main () {
	int n = read, m = read;
	combinator_init(n * 2 + m);

	int X = n * 2 + m - 1, Y = 1 - m;
	int U = 2, D = - m - 1, H = m + 3;

	ll ans = To(X, Y);
	int y1 = Y, y2 = Y, fg = -1;
	while (1) {
		y1 = U * 2 - y1;
		y2 = D * 2 - y2;
		ll now = To(X, y1) + To(X, y2);
		if (!now) break;
		ans += now * fg;
		fg *= -1;
		U += H;
		D -= H;
	}

	if ((ans %= mod) < 0) ans += mod;
	printf("%lld\n", ans);
}
