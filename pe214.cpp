/*
 * Author: Kewth

 * Date:
  2021.01.26

 * Solution:
  In blog.

 * Digression:
  牛逼题。

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

#ifdef PE
const int maxn = 40000005, maxp = maxn, K = 50000, maxl = 1 << 17, mod = 1004535809;
#else
const int maxn = 2000005, maxp = maxn, K = 50000, maxl = 1 << 17, mod = 1004535809;
#endif

int minp[maxn], f[maxn];
int prime[maxp], pp;
ll F[K + 5], ans[K + 5], tp[K + 5];
int tot[100];
ll fac[maxn + K], ifac[maxn + K];

inline void __a (ll &x) { x >= mod ? x -= mod : x; }
inline void __d (ll &x) { x < 0 ? x += mod : x; }
inline void __a (int &x) { x >= mod ? x -= mod : x; }
inline void __d (int &x) { x < 0 ? x += mod : x; }

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

struct NTT { // {{{
	int ra[maxl], G[maxl + 1];
	NTT () {
		ll g = power(3, (mod - 1) / maxl); // 原根
		G[maxl >> 1] = 1;
		for (int i = (maxl >> 1) + 1; i <= maxl; i ++)
			G[i] = G[i - 1] * g % mod;
		for (int i = (maxl >> 1) - 1; i; i --)
			G[i] = G[i << 1];
		for (int i = 1; i < maxl; i ++)
			ra[i] = ra[i >> 1] >> 1 | (maxl >> 1) * (i & 1);
	}
	inline void DFT (int *a, int n) {
		int nk = __builtin_ctz(maxl) - __builtin_ctz(unsigned(n));
		for (int i = 0; i < n; i ++)
			if (i < (ra[i] >> nk))
				std::swap(a[i], a[ra[i] >> nk]);
		for (int m = 1; m < n; m <<= 1)
			for (int i = 0; i < n; i += m << 1)
				for (int k = i; k < i + m; k ++) {
					int a0 = a[k], a1 = 1ll * a[k + m] * G[m + k - i] % mod;
					__a(a[k] = a0 + a1);
					__d(a[k + m] = a0 - a1);
				}
	}
	inline void IDFT (int *a, int n) {
		std::reverse(a + 1, a + n);
		DFT(a, n);
		int invn = mod - (mod - 1) / n;
		for (int i = 0; i < n; i ++)
			a[i] = 1ll * a[i] * invn % mod;
	}
} ntt;
// }}}

void mul (ll *a, ll *b) {
	static int A[maxl], B[maxl];
	std::copy(a, a + K + 1, A);
	std::copy(b, b + K + 1, B);
	std::fill(A + K + 1, A + maxl, 0);
	std::fill(B + K + 1, B + maxl, 0);
	ntt.DFT(A, maxl);
	ntt.DFT(B, maxl);
	for (int i = 0; i < maxl; i ++)
		A[i] = 1ll * A[i] * B[i] % mod;
	ntt.IDFT(A, maxl);
	std::copy(A, A + K + 1, a);
}

int main () {
	f[2] = 1;
	ll sum = 0;
#ifdef PE
	for (int i = 2, N = 40000000; i <= N; i ++)
#else
	for (int i = 2, N = 2000000; i <= N; i ++)
#endif
		if (!minp[i]) {
			prime[++ pp] = i;
			minp[i] = i;
			if (i <= N / i)
				for (int j = i * i; j <= N; j += i)
					if (!minp[j])
						minp[j] = i;
			for (int x = i - 1; x > 1; x /= minp[x])
				f[i] += f[minp[x]];
			if (f[i] == 23)
				sum += i;
		}
#ifdef PE
	printf("%lld\n", sum);
	return 0;
#endif

	int n = read, a = read, q = read, maxf = 0;
	combinator_init(n + K);
	for (int i = 2; i <= n; i ++) {
		++ tot[f[prime[i]]];
		maxf = std::max(f[prime[i]], maxf);
	}

	F[0] = 1;
	for (int x = 1; x <= maxf; x ++) {
		int t = tot[x];
		std::fill(tp, tp + K + 1, 0);
		for (int i = 0; i * x <= K; i ++)
			tp[i * x] = C(t - 1 + i, i);
		mul(F, tp);
		/* for (int i = 1; i <= t; i ++) */
		/* 	for (int j = x; j <= K; j ++) */
		/* 		__a(F[j] += F[j - x]); */
		std::fill(tp, tp + K + 1, 0);
		for (int i = 0; i * x * (a + 1) <= K and i <= t; i ++)
			tp[i * x * (a + 1)] = i & 1 ? mod - C(t, i) : C(t, i);
		mul(F, tp);
		/* for (int i = 1; i <= t; i ++) */
		/* 	for (int j = K; j >= x * a + x; j --) */
		/* 		__d(F[j] -= F[j - x * a - x]); */
	}
	ans[1] = ans[2] = 1;
	for (int j = 3; j <= K; j ++)
		ans[j] = F[j - 2];
	for (int j = 1; j <= K; j ++)
		__a(F[j] += F[j - 1]);
	for (int j = K; j >= a; j --)
		__d(F[j] -=  F[j - a]);
	for (int j = 3; j <= K; j ++)
		__a(ans[j] += F[j - 2]);

	while (q --)
		printf("%lld\n", ans[int(read)]);
}
