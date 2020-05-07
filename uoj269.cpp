#if 0
2020.05.07

  设 X 是满足二项分布的一个随机变量，那么要求就是 F(X) 的期望。
  对于一个随机变量 X ，设其生成函数为 g(s) ，那么其 k 阶矩 E(A(X, k)) 就是 g^(k) (1) ，其
中 A(X, k) 是 X 的 k 次下降幂，g^(k) 是 g 进行 k 次求导后的结果。
  二项分布的生成函数是 g(s) = (1 - p + px)^n ，满足 g^(k) (1) = A(n, k) p^k ，也就是说可
可以很容易地知道 X 的下降幂的期望。那么把 F(X) 转成下降幂多项式，根据期望线性性，对于每项
下降幂单独计算贡献即可。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxl = 1 << 16, mod = 998244353;

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

const int maxn = 20005;
ll fac[maxn], ifac[maxn];

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
}

poly f, g;

int main () {
	combinator_init(20000);
	int n = read, m = read, p = read;
	for (int i = 0; i <= m; i ++)
		f[i] = read * ifac[i] % mod;
	for (int i = 0; i <= m; i ++)
		g[i] = i & 1 ? mod - ifac[i] : ifac[i];

	int len = 1;
	while (len < m * 2 + 1) len <<= 1;

	DFT(f, len);
	DFT(g, len);
	for (int i = 0; i < len; i ++)
		(f[i] *= g[i]) %= mod;
	IDFT(f, len);

	ll ans = 0, coe = 1;
	for (int i = 0; i <= m; i ++) {
		(ans += f[i] * coe) %= mod;
		(coe *= n - i) %= mod;
		(coe *= p) %= mod;
	}
	printf("%lld\n", ans);
}
