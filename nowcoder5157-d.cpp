#pragma GCC optimize(2)
#if 0
2020.04.17

垃圾题，先子集卷积再 NTT 再异或卷积即可。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef unsigned int ui;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
} read;

const int maxk = 18, maxl = 2 << maxk, mod = 998244353;

typedef ll poly[maxl];
typedef ll *pit;
ll G[maxl + 1];
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

	// if module is small
/* 	for (int i = 0; i < n; ++i) __d(a[i] %= mod); */
}

inline void IDFT(pit a, int n) {
	std::reverse(a + 1, a + n);
	DFT(a, n);
	int invn = mod - (mod - 1) / n;
	for(int i = 0; i < n; i ++)
		(a[i] *= invn) %= mod;
}

void FWT_or (ll *a, int n) {
	for (int m = 1; m < n; m <<= 1)
		for (int i = 0; i < n; i += m << 1)
			for (int k = i; k < i + m; k ++)
				__a(a[k + m] += a[k]);
}

void iFWT_or (ll *a, int n) {
	for (int m = 1; m < n; m <<= 1)
		for (int i = 0; i < n; i += m << 1)
			for (int k = i; k < i + m; k ++)
				__d(a[k + m] -= a[k]);
}

void FWT_xor (ll *a, int n) {
	for (int m = 1; m < n; m <<= 1)
		for (int i = 0; i < n; i += m << 1)
			for (int k = i; k < i + m; k ++) {
				ll x = a[k], y = a[k + m];
				__a(a[k] = x + y);
				__d(a[k + m] = x - y);
			}
}

void iFWT_xor (ll *a, int n) {
	FWT_xor(a, n);
	ll inv = mod - (mod - 1) / n;
	for (int i = 0; i < n; i ++)
		(a[i] *= inv) %= mod;
}

ll a[maxk + 1][maxl], b[maxk + 1][maxl], c[maxl], d[maxl];
ll g[maxk + 1][maxl], f[maxl];

int main () {
	int n = read + 1;
	for (int i = 0; i < n; i ++) read(a[__builtin_popcount(ui(i))][i]);
	for (int i = 0; i < n; i ++) read(b[__builtin_popcount(ui(i))][i]);
	for (int i = 0; i < n; i ++) read(c[i]);
	for (int i = 0; i < n; i ++) read(d[i]);

	int len = 1, k = 0;
	while (len < n) len <<= 1, ++ k;

	for (int i = 0; i <= k; i ++) {
		FWT_or(a[i], len);
		FWT_or(b[i], len);
	}
	for (int i = 0; i <= k; i ++)
		for (int j = 0; j <= i; j ++)
			for (int x = 0; x < len; x ++)
				(g[i][x] += a[j][x] * b[i - j][x]) %= mod;
	for (int i = 0; i <= k; i ++) {
		iFWT_or(g[i], len);
		/* for (int x = 0; x < len; x ++) */
		/* 	if (__builtin_popcount(ui(x)) != i) */
		/* 		g[i][x] = 0; */
		/* for (int x = 0; x < len; x ++) */
		/* 	debug(" %lld", g[i][x]); */
		/* debug("\n"); */
		for (int x = 0; x < len; x ++)
			if (__builtin_popcount(ui(x)) == i)
				f[x] += g[i][x];
	}
	/* iFWT_or(f, len); */

	/* for (int x = 0; x < len; x ++) */
	/* 	debug("%lld\n", f[x]); */

	DFT(f, len << 1);
	DFT(c, len << 1);
	for (int x = 0; x < (len << 1); x ++)
		(f[x] *= c[x]) %= mod;
	IDFT(f, len << 1);

	FWT_xor(f, len << 1);
	FWT_xor(d, len << 1);
	for (int x = 0; x < (len << 1); x ++)
		(f[x] *= d[x]) %= mod;
	iFWT_xor(f, len << 1);

	/* for (int x = 0; x < (len << 1); x ++) */
	/* 	debug("%lld\n", f[x]); */

	int q = read;
	while (q --) {
		int x = read;
		printf("%lld\n", f[x]);
	}

	/* debug("%lf\n", (sizeof a) / 1024. / 1024.); */
}
