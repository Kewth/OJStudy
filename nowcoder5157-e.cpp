#if 0
2020.04.17

  问题可以转换为求单调的序列数。枚举序列的数的种类数 k ，那么首先有 C(m, k) 的系数，然后
由于 k 种数每种必须出现，并且同种数位置连续，可以知道此时的序列方案数就是 C(n - 1, k - 1) 。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 1000005, mod = 998244353;
ll fac[maxn], ifac[maxn], inv[maxn];

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

	inv[1] = 1;
	for (int i = 2; i <= n; i ++)
		inv[i] = (mod - mod / i) * inv[mod % i] % mod;
}

int main () {
	combinator_init(1000000);
	int T = read;
	while (T --) {
		int n = read, m = read;
		ll ans = 0;
		ll Ck = 1;
		for (int k = 1; k <= m; k ++) {
			(ans += C(m, k) * Ck) %= mod;
			if (k > 1)
				(ans += C(m, k) * Ck) %= mod;
			(Ck *= n - k) %= mod;
			(Ck *= inv[k]) %= mod;
		}
		ans = (power(m, n) + mod - ans) % mod;
		printf("%lld\n", ans);
	}
}
