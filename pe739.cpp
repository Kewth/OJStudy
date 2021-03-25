/*
 * Author: Kewth

 * Date:
  2021.03.12

 * Solution:
  考虑每个位置的贡献，翻折法计算即可。

 * Digression:

 * CopyRight:
   __  __                  __   __
  |  |/  |.-----.--.--.--.|  |_|  |--.
  |     < |  -__|  |  |  ||   _|     |
  |__|\__||_____|________||____|__|__|

 */

#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

const int N = 100000000, mod = 1000000007;
int fac[N * 2 + 1], ifac[N * 2 + 1];

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
	return 1ll * fac[n] * ifac[m] % mod * ifac[n - m] % mod;
}

int main () {
	fac[0] = 1;
	for (int i = 1; i <= N * 2; i ++)
		fac[i] = 1ll * fac[i - 1] * i % mod;
	ifac[N * 2] = int(power(fac[N * 2], -1));
	for (int i = N * 2; i; i --)
		ifac[i - 1] = 1ll * ifac[i] * i % mod;

	ll ans = 0, now = 1, las = 2;
	for (int i = 1; i <= N; i ++) {
		(ans += now * (C(N - 2 + N - i, N - 2) + mod - C(N - 2 + N - i, N - 1))) %= mod;
		std::swap(now, las);
		now += las;
		if (now >= mod) now -= mod;
	}
	printf("%lld\n", ans);
}
