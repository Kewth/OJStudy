#pragma GCC optimize(3)
#if 0
2020.05.29

  求出两边得到每个数的概率，其生成函数显然是一个多项式快速幂的形式，考虑其封闭形式，
可以用多项式求逆代替多项式快速幂。
  不知道是不是因为常数，只能得 85pts 。

  UPDATE on 2020.06.08:
  妈的傻逼了，(1 - x)^n 的逆元就是在做高维前缀和，直接拿组合数算就行了，求逆是没有
必要的。
        ▁▃▄▄▄▃▃▃▃▄▶
      ▗▇▀▔    ▔▔▔▔
     ▄▛   ▃▅━━■▄▂
    ▟▊   ▐▘     ▀▙
   ▟▜▌   ▐▖   ▋  ▐▍
  ▟▘ ▜   ▝▀▇▆●▘  ▐▌
▗▟▘   ▜▃       ▁▅▛
▔▀▼▅▄▃▃██▅▄▄▄▅■▀▔   CopyRight :)
      ▔▔▔▔▔▔
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxl = 1 << 21, mod = 1012924417;

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
		ll g = power(5, (mod - 1) / maxl); // 原根
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

const int maxn = 1000005;
ll fac[maxn << 1], ifac[maxn << 1];

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


void getf (pit f, int n, int s) {
	static poly A, B;
	int len = 1;
	while (len < n * s * 2 - n + 1) len <<= 1;
	std::fill(A, A + len, 0);
	std::fill(B, B + len, 0);
	for (int i = 0; i <= n; i ++)
		B[i * s] = i & 1 ? mod - C(n, i) : C(n, i);
	B[n * s] = 0;
	for (int i = 0; i <= n * s; i ++)
		A[i] = C(n + i - 1, i);
	std::fill(A + n * (s - 1) + 1, A + len, 0);
	DFT(A, len);
	DFT(B, len);
	for (int i = 0; i < len; i ++)
		(A[i] *= B[i]) %= mod;
	IDFT(A, len);
	ll coe = power(s, -n);
	std::fill(f, f + n, 0);
	for (int i = n; i <= n * s; i ++)
		f[i] = A[i - n] * coe % mod;
}

ll f[maxn], g[maxn];
int main () {
	combinator_init(2000000);
	int T = read;
	while (T --) {
		int n1 = read, s1 = read, n2 = read, s2 = read;
		getf(f, n1, s1);
		getf(g, n2, s2);
		for (int i = 1; i <= n2 * s2; i ++)
			if ((g[i] += g[i - 1]) >= mod)
				g[i] -= mod;
		ll ans = 0;
		for (int i = 1; i <= n1 * s1; i ++)
			(ans += f[i] * g[std::min(n2 * s2, i - 1)]) %= mod;
		printf("%lld\n", ans);
	}
}
