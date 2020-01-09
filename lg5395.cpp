#if 0
2020.01.09

板子，把第二类斯特林数的通项公式的组合数拆开就能配成卷积形式。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
} read;

const int maxn = 200005, maxl = 1 << 20, mod = 167772161;
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

inline void DFT(pit a, int n) {
	int nk = __builtin_ctz(maxl) - __builtin_ctz(unsigned(n));
	for(int i = 0; i < n; i ++)
		if(i < (ra[i] >> nk))
			std::swap(a[i], a[ra[i] >> nk]);

	for(int m = 1; m < n; m <<= 1)
		for(int i = 0; i < n; i += m << 1)
			for(int k = i; k < i + m; k ++) {
				ll a0 = a[k], a1 = a[k + m] * G[m + k - i] % mod;
				// 这个小模数不用取模
				a[k] = a0 + a1;
				a[k + m] = a0 - a1;
			}

	for (int i = 0; i < n; ++i) __d(a[i] %= mod);
}

inline void IDFT(pit a, int n) {
	std::reverse(a + 1, a + n);
	DFT(a, n);
	int invn = mod - (mod - 1) / n;
	for(int i = 0; i < n; i ++)
		(a[i] *= invn) %= mod;
}

void init() {
	ll g = power(3, (mod - 1) / maxl);

	G[maxl >> 1] = 1;
	for(int i = (maxl >> 1) + 1; i <= maxl; i ++)
		G[i] = G[i - 1] * g % mod;
	for(int i = (maxl >> 1) - 1; i; i --)
		G[i] = G[i << 1];

	for(int i = 1; i < maxl; i ++)
		ra[i] = ra[i >> 1] >> 1 | (maxl >> 1) * (i & 1);
}

poly a, b;
ll fac[maxn], ifac[maxn];
int main() {
	init();

	int n = read, len = 1;
	while(len < n * 2 + 1)
		len <<= 1;

	fac[0] = 1;
	for(int i = 1; i <= n; i ++)
		fac[i] = fac[i - 1] * i % mod;
	ifac[n] = power(fac[n], -1);
	for(int i = n; i; i --)
		ifac[i - 1] = ifac[i] * i % mod;

	for(int i = 0; i <= n; i ++)
		a[i] = power(i, n) * ifac[i] % mod;
	for(int i = 0; i <= n; i ++)
		b[i] = (i & 1 ? mod - 1 : 1) * ifac[i] % mod;

	DFT(a, len);
	DFT(b, len);
	for(int i = 0; i < len; i ++)
		(a[i] *= b[i]) %= mod;
	IDFT(a, len);

	for(int i = 0; i <= n; i ++)
		printf("%lld ", a[i]);
	puts("");
}
