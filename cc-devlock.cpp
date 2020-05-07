#if 0
2020.05.06

  预处理 lim[x] 表示有多少数位 k 满足 10^k = x (mod p) ，这些数位视为同种数位。
  对于每种数位通过多项式快速幂求出 f[i] 表示在这种数位中填数数位和为 i 的方案数。
  把 f 稍作变换得到 h[i][j] 表示数位模 p 贡献和为 i ，数位和为 j 的填数方案数。那么将所
有 h 二维卷积（第一维是循环卷积）后得到 g[i][j] 就是所有填数方案中模 p 为 i 且数位和为 j
的方案数。
  注意到这个二维卷积的第一维特别小，暴力卷即可。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxl = 1 << 15, mod = 998244353;
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
}

inline void IDFT(pit a, int n) {
	std::reverse(a + 1, a + n);
	DFT(a, n);
	int invn = mod - (mod - 1) / n;
	for(int i = 0; i < n; i ++)
		(a[i] *= invn) %= mod;
}

const int maxp = 52;
int lim[maxp];
poly f, g[maxp], h[maxp], s[maxp], tmp;

void rho (int n, int p) {
	static int las[maxp];
	static int shit[maxp];
	for (int i = 1, x = 1 % p; i <= n; i ++, x = x * 10 % p) {
		if (las[x]) {
			int len = i - las[x];
			int m = n - i + 1;
			for (int j = las[x]; j < i; j ++)
				lim[shit[j]] += m / len;
			for (int j = las[x]; j - las[x] < m % len; j ++)
				++ lim[shit[j]];
			break;
		}
		shit[i] = x;
		las[x] = i;
		++ lim[x];
	}
}

int len = 1;
void polypower (int m, int k, pit res) {
	static poly po;
	std::copy(res, res + len, po);
	std::fill(res, res + len, 0);
	res[0] = 1;
	while (k) {
		if (k & 1) {
			std::copy(po, po + len, tmp);
			DFT(res, len);
			DFT(tmp, len);
			for (int i = 0; i < len; i ++)
				(res[i] *= tmp[i]) %= mod;
			IDFT(res, len);
			std::fill(res + m + 1, res + len, 0);
		}
		DFT(po, len);
		for (int i = 0; i < len; i ++)
			(po[i] *= po[i]) %= mod;
		IDFT(po, len);
		std::fill(po + m + 1, po + len, 0);
		k >>= 1;
	}
}

int main () {
	int n = read, p = read, m = read;
	rho(n, p);
	while (len < m * 2 + 1) len <<= 1;

	g[0][0] = 1;
	for (int x = 0; x < p; x ++) {
		std::fill(f, f + len, 0);
		for (int y = 0; y < 10 and y <= m; y ++)
			f[y] = 1;
		polypower(m, lim[x], f);

/* 		for (int y = 0; y <= m; y ++) */
/* 			debug(" %lld", f[y]); */
/* 		debug(" is f (lim = %d)\n", lim[x]); */

		for (int i = 0; i < p; i ++)
			std::fill(h[i], h[i] + len, 0);
		for (int y = 0; y <= m; y ++)
			__a(h[x * y % p][y] += f[y]);

/* 		for (int i = 0; i < p; i ++) { */
/* 			for (int k = 0; k <= m; k ++) */
/* 				debug(" %lld", h[i][k]); */
/* 			debug("  is h\n"); */
/* 		} */

		for (int i = 0; i < p; i ++) {
			DFT(h[i], len);
			DFT(g[i], len);
		}

		for (int i = 0; i < p; i ++)
			std::fill(s[i], s[i] + len, 0);

		for (int i = 0; i < p; i ++)
			for (int j = 0; j < p; j ++) {
				for (int k = 0; k < len; k ++)
					tmp[k] = h[i][k] * g[j][k] % mod;
				IDFT(tmp, len);
				int ij = (i + j) % p;
				for (int k = 0; k <= m; k ++)
					s[ij][k] += tmp[k];
			}

		for (int i = 0; i < p; i ++)
			for (int k = 0; k < len; k ++)
				g[i][k] = s[i][k] % mod;

/* 		for (int i = 0; i < p; i ++) { */
/* 			for (int k = 0; k <= m; k ++) */
/* 				debug(" %lld", g[i][k]); */
/* 			debug("   is g\n"); */
/* 		} */
/* 		debug("\n"); */
	}

	pit ans = g[0];
	for (int k = 1; k <= m; k ++)
		__a(ans[k] += ans[k - 1]);
	for (int k = 0; k <= m; k ++)
		printf("%lld ", ans[k]);
	puts("");
}
