/*
 * Author: Kewth

 * Date:
  2020.08.02

 * Solution:
  In blog.

 * Digression:

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
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

static struct {
    inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int mod = 998244353;

ll power (ll x, int k) {
	if (k < 0) k += mod - 1;
	ll res = 1;
	while (k) {
		if (k & 1) (res *= x) %= mod;
		(x *= x) %= mod;
		k >>= 1;
	}
	return res;
}

int main () {
	int n = read, m = read;

	ll ans = 0, fac = 1;
	for (int i = 0; i <= n; i ++) {
		ll now = power(i, m) * fac % mod;
		i & 1 ? ans += mod - now : ans += now;
		(fac *= i + 1) %= mod;
	}
	ans %= mod;
	printf("%lld\n", ans);
}
