#pragma GCC optimize(3)
#if 0
2020.01.13

通过系数翻转，多项式除法可以转换为求逆。
#endif
#include <cstdio>
#include <algorithm>
#include <cassert>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
} read;

const int maxl = 1 << 19, mod = 998244353;
typedef ll poly[maxl];
typedef ll *pit;
ll G[maxl + 1];
ll inv[maxl];
int ra[maxl];

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
inline void __d(ll &x) { if(x < 0) x += mod; }

struct Initer {
	Initer() {
		ll g = power(3, (mod - 1) / maxl);
		G[maxl >> 1] = 1;
		for(int i = (maxl >> 1) + 1; i <= maxl; i ++)
			G[i] = G[i - 1] * g % mod;
		for(int i = (maxl >> 1) - 1; i; i --)
			G[i] = G[i << 1];
		inv[1] = 1;
		for(int i = 2; i < maxl; i ++)
			inv[i] = inv[mod % i] * (mod - mod / i) % mod;
		for(int i = 1; i < maxl; i ++)
			ra[i] = ra[i >> 1] >> 1 | (maxl >> 1) * (i & 1);
	}
} Initer;

inline void DFT(pit a, int n) {
	int nk = __builtin_ctz(maxl) - __builtin_ctz(unsigned(n));
	for(int i = 0; i < n; i ++)
		if(i < (ra[i] >> nk))
			std::swap(a[i], a[ra[i] >> nk]);

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
	int invn = mod - (mod - 1) / n;
	for(int i = 0; i < n; i ++)
		(a[i] *= invn) %= mod;
}

poly res, tmp;
inline void polyinv(pit a, int n) {
	res[0] = power(a[0], -1);
	std::fill(res + 1, res + (n << 1), 0);

	for(int m = 2; m <= n; m <<= 1) {
		std::copy(a, a + m, tmp);
		std::fill(tmp + m, tmp + (m << 1), 0);

		DFT(tmp, m << 1);
		DFT(res, m << 1);
		for(int i = 0; i < (m << 1); i ++)
			(res[i] *= 2 + mod - res[i] * tmp[i] % mod) %= mod;
		IDFT(res, m << 1);

		std::fill(res + m, res + (m << 1), 0);
	}

	/* std::copy(res, res + n, a); */
}

void mul(pit a, pit b, pit c, int deg, int len) {
	std::copy(a, a + len, c);
	DFT(c, len);
	std::copy(b, b + len, tmp);
	DFT(tmp, len);
	for(int i = 0; i < len; i ++)
		(c[i] *= tmp[i]) %= mod;
	IDFT(c, len);
	std::fill(c + deg + 1, c + len, 0);
}

poly f, g, q, r;
int main() {
	int n = read, m = read;
	for(int i = n; i >= 0; i --)
		read(f[i]);
	for(int i = m; i >= 0; i --)
		read(g[i]);

	int len = 1;
	while(len < n - m + 1)
		len <<= 1;
	std::copy(g, g + n - m + 1, q);
	polyinv(q, len);
	std::fill(res + n - m + 1, res + len, 0);

	while(len < n + n - m + 1)
		len <<= 1;
	mul(f, res, q, n - m, len);

	len = 1;
	while(len < n + 1)
		len <<= 1;
	mul(g, q, r, n, len);

	for(int i = 0; i <= n; i ++)
		__d(r[i] = f[i] - r[i]);

	for(int i = n - m; i >= 0; i --)
		printf("%lld ", q[i]);
	puts("");
	for(int i = n; i >= n - m + 1; i --)
		printf("%lld ", r[i]);
	puts("");
}
