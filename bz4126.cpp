/*
 * Author: Kewth

 * Date:
  2020.07.23

 * Solution:
  同 th1689-b 。

 * Digression:

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
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
} read;

const int maxn = 500005, mod = 1000000007;
ll f[maxn], g[maxn];
ll fac[maxn], ifac[maxn], inv[maxn];
ll ga[maxn], gb[maxn];

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
	inv[1] = 1;
	for (int i = 2; i <= n; i ++)
		inv[i] = (mod - mod / i) * inv[mod % i] % mod;
}

ll G (ll x, int k) {
	if (x <= k) return g[x];
	x %= mod;
	ll res = 0;
	ll coe = ifac[k];
	for (int i = k; i >= 0; i --) {
		(res += coe * g[i] % mod * power(x + mod - i, -1)) %= mod;
		(coe *= i) %= mod;
		(coe *= mod - inv[k + 1 - i]) %= mod;
	}
	for (int i = k; i >= 0; i --)
		(res *= x - i) %= mod;
	return res;
}

int main () {
	ll N = read;
	int k = read, q = k;
	if (k == 1)
		return printf("%lld\n", (N * (N + 1) >> 1) % mod), 0;
	for (int i = 0; i <= k; i ++) f[i] = power(i, k);

	combinator_init(k + 1);

	ga[k + 1] = 1, gb[k + 1] = 0;
	for (int i = k + 1; i; i --) {
		ga[i - 1] = ga[i] * q % mod;
		gb[i - 1] = (gb[i] * q + mod - f[i - 1]) % mod;
	}

	ll a = 0, b = 0;
	for (int i = 0, c = 1; i <= k + 1; i ++, c = -c) {
		(a += C(k + 1, i) * ga[k + 1 - i] * c) %= mod;
		(b += C(k + 1, i) * gb[k + 1 - i] * c) %= mod;
	}

	g[k + 1] = (mod - b) * power(mod + a, -1) % mod; // ax + b = 0
	for (int i = k + 1; i; i --)
		g[i - 1] = (q * g[i] + mod - f[i - 1]) % mod;

	ll S = power(q, (N + 1) % (mod - 1)) * G(N + 1, k) - g[0];
	S %= mod;
	if (S < 0) S += mod;
	printf("%lld\n", S);
}
