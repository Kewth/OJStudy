/*
 * Author: Kewth

 * Date:
  2020.08.10

 * Solution:
  In blog.

 * Digression:
  又被踩了。

 * CopyRight:
          ▁▃▄▄▄▃▃▃▃▄▶
        ▗▇▀▔    ▔▔▔▔
       ▄▛   ▃▅━━■▄▂
      ▟▊   ▐▘     ▀▙
     ▟▜▌   ▐▖   ▋  ▐▍
    ▟▘ ▜   ▝▀▇▆■▘  ▐▌
  ▗▟▘   ▜▃       ▁▅▛
  ▔▀▼▅▄▃▃██▅▄▄▄▅■▀▔
        ▔▔▔▔▔▔
 */

#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

static struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 200005, mod = 998244353;
ll fac[maxn], ifac[maxn];
ll pa[maxn], pb[maxn], pc[maxn];
ll f[maxn];

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
	if (n < m) return 0;
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

int main () {
	combinator_init(200000);
	int T = read;
	ll inv = power(100, -1);

	while (T --) {
		int n = read, m = read;
		ll p = read * inv % mod, q = read * inv % mod;
		ll a = p * (mod + 1 - q) % mod, b = q * (mod + 1 - p) % mod, c = p * q % mod;
		ll d = power(a + b + c, -1);
		(a *= d) %= mod;
		(b *= d) %= mod;
		(c *= d) %= mod;

		pa[0] = pb[0] = pc[0] = 1;
		for (int i = 1; i <= m; i ++) pa[i] = pa[i - 1] * a % mod;
		for (int i = 1; i <= n; i ++) pb[i] = pb[i - 1] * b % mod;
		for (int i = 1; i <= m; i ++) pc[i] = pc[i - 1] * c % mod;

		for (int i = 0; i <= n; i ++)
			f[i] = pb[i] * C(m - 1 + i, i) % mod;
		for (int i = 1; i <= n; i ++)
			(f[i] += f[i - 1]) %= mod;

		ll ans = 0;
		for (int i = 0; i < n && i < m; i ++)
			(ans += f[n - 1 - i] * C(m - 1, i) % mod *
			 pc[i] % mod * pa[m - 1 - i]) %= mod;
		(ans *= a + c) %= mod;
		printf("%lld\n", ans);
	}
}
