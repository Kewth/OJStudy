/*
 * Author: Kewth

 * Date:
  2021.05.14

 * Solution:
  考虑对于每个 x 计算 a_i = x 所产生的贡献。不难发现当 x < n 时其贡献次数就是
(n - x + 3) 2^{n-x-2} 。随便前缀和算算即可。

 * Digression:
  smctr
  难度：3 / 12

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

static struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 500005, mod = 998244353;
ll tmp[maxn];
ll s[maxn], f[maxn];
ll a[maxn], b[maxn], c[maxn];
ll p2[maxn], ip2[maxn];
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

void combinator_init (int n) {
	fac[0] = 1;
	for (int i = 1; i <= n; i ++)
		fac[i] = fac[i - 1] * i % mod;
	ifac[n] = power(fac[n], -1);
	for (int i = n; i; i --)
		ifac[i - 1] = ifac[i] * i % mod;
	p2[0] = 1;
	for (int i = 1; i <= n; i ++)
		p2[i] = p2[i - 1] * 2 % mod;
	ip2[n] = power(p2[n], -1);
	for (int i = n; i; i --)
		ip2[i - 1] = ip2[i] * 2 % mod;
}

int main () {
	int N = 500000;
	combinator_init(N);
	for (int i = 1; i <= N; i ++) {
		a[i] = (a[i - 1] + ifac[i] * ip2[i]) % mod;
		b[i] = (b[i - 1] + ifac[i] * ip2[i] % mod * (mod - i)) % mod;
	}
	int T = read;
	while (T --) {
		int n = read;
		if (n == 1) {
			puts("1");
			continue;
		}
		ll ans = (n + 3) * p2[n - 2] % mod * a[n - 1] +
			p2[n - 2] * b[n - 1] + ifac[n];
		ans %= mod;
		(ans *= ip2[n - 1]) %= mod;
		printf("%lld\n", ans);
	}
}
