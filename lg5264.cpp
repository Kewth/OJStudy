#if 0
2019.11.08

开始吸多项式毒。
sin(x) = (e^ix - e^{-ix}) / 2i
cos(x) = (e^ix + e^{-ix}) / 2
多项式 exp 即可。
#endif
#include <cstdio>
#include <algorithm>
#include <cassert>
#include <cctype>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
} read;

const int maxn = 1 << 19, mod = 998244353;
typedef ll poly[maxn];
typedef ll *pit;
poly A, B;
ll G[maxn + 1];
ll inv[maxn];
ll ra[maxn];

inline ll power(ll x, int k) {
	if(k < 0) k += mod - 1;
	ll res = 1;
	while(k) {
		if(k & 1) (res *= x) %= mod;
		(x *= x) %= mod;
		k >>= 1;
	}
	return res;
}

inline void __a(ll &x) { if(x >= mod) x -= mod; }
/* inline void __d(ll &x) { if(x < 0) x += mod; } */
inline void __d(ll &x) { x += x >> 31 & mod; }

inline void DFT(pit a, int n) {
	for(int i = 0; i < n; i ++)
		if(i < ra[maxn / n * i])
			std::swap(a[i], a[ra[maxn / n * i]]);

	for(int m = 1; m < n; m <<= 1)
		for(int i = 0; i < n; i += m << 1)
			for(int k = i; k < i + m; k ++) {
				ll a0 = a[k], a1 = a[k + m] * G[m + k - i] % mod;
				__a(a[k] = a0 + a1);
				__d(a[k + m] = a0 - a1);
			}
}

inline void IDFT(pit a, int n) {
	std::reverse(a + 1, a + n);
	DFT(a, n);
	for(int i = 0; i < n; i ++)
		(a[i] *= inv[n]) %= mod;
}

inline void derivative(pit a, int n) {
	for(int i = 1; i < n; i ++)
		a[i - 1] = i * a[i] % mod;
	a[n - 1] = 0;
}

inline void integrate(pit a, int n) {
	for(int i = n - 1; i; i --)
		a[i] = a[i - 1] * inv[i] % mod;
	a[0] = 0;
}

inline void polyinv(pit a, int n) {
	/* assert(a[0] == 1); */
	static poly res;
	/* res[0] = 1; */
	res[0] = power(a[0], -1);
	std::fill(res + 1, res + (n << 1), 0);

	for(int m = 2; m <= n; m <<= 1) {
		static poly tmp;
		std::copy(a, a + m, tmp);
		std::fill(tmp + m, tmp + (m << 1), 0);

		DFT(tmp, m << 1);
		DFT(res, m << 1);
		for(int i = 0; i < (m << 1); i ++)
			(res[i] *= 2 + mod - res[i] * tmp[i] % mod) %= mod;
		IDFT(res, m << 1);

		std::fill(res + m, res + (m << 1), 0);
	}

	std::copy(res, res + n, a);
}

inline void polyln(pit a, int n) {
	assert(a[0] = 1);
	static poly tmp;
	std::copy(a, a + n, tmp);
	std::fill(tmp + n, tmp + (n << 1), 0);
	derivative(a, n);
	polyinv(tmp, n);

	DFT(tmp, n << 1);
	DFT(a, n << 1);
	for(int i = 0; i < (n << 1); i ++)
		(a[i] *= tmp[i]) %= mod;
	IDFT(a, n << 1);
	std::fill(a + n, a + (n << 1), 0);

	integrate(a, n);
}

inline void polyexp(pit a, int n) {
	assert(a[0] == 0);
	static poly res;
	res[0] = 1;
	std::fill(res + 1, res + n, 0);

	for(int m = 2; m <= n; m <<= 1) {
		static poly tmp;
		std::copy(res, res + m, tmp);
		std::fill(tmp + m, tmp + (m << 1), 0);

		polyln(tmp, m);
		for(int i = 0; i < m; i ++)
			__d(tmp[i] = a[i] - tmp[i]);

		DFT(tmp, m << 1);
		DFT(res, m << 1);
		for(int i = 0; i < (m << 1); i ++)
			(res[i] *= 1 + tmp[i]) %= mod;
		IDFT(res, m << 1);
	}

	std::copy(res, res + n, a);
}

int main() {
	ll g = power(3, (mod - 1) / maxn);

	G[maxn >> 1] = 1;
	for(int i = (maxn >> 1) + 1; i <= maxn; i ++)
		G[i] = G[i - 1] * g % mod;
	for(int i = (maxn >> 1) - 1; i; i --)
		G[i] = G[i << 1];

	inv[1] = 1;
	for(int i = 2; i < maxn; i ++)
		inv[i] = inv[mod % i] * (mod - mod / i) % mod;

	for(int i = 1; i < maxn; i ++)
		ra[i] = ra[i >> 1] >> 1 | (maxn >> 1) * (i & 1);

	int n = read, t = read;
	for(int i = 0; i < n; i ++)
		A[i] = read * G[2 + 1] % mod;

	int len = 1;
	while(len < n)
		len <<= 1;

	if(t) {
		polyexp(A, len);
		std::copy(A, A + len, B);
		polyinv(B, len);
		for(int i = 0; i < n; i ++)
			printf("%lld ", (A[i] + B[i]) * inv[2] % mod);
	}

	else {
		polyexp(A, len);
		std::copy(A, A + len, B);
		polyinv(B, len);
		for(int i = 0; i < n; i ++)
			printf("%lld ", (A[i] + mod - B[i]) * power(G[2 + 1] << 1, -1) % mod);
	}
}
