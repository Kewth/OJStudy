#if 0
2020.01.03

第一类斯特灵数第 n 行的生成函数就是 x 的 n 次上升幂。
直接分治 + FFT 复杂度 O(nlog^2n) 。
考虑倍增，设 x 的 n 次上升幂为多项式 F_{n} (x) 。
若当前 n = 2k + 1 ，则 F_{2k+1}(x) = F_{2k} (x+2k) ，直接算。
若当前 n = 2k ，则 F_{2k}(x) = F_{k}(x) F_{k}(x+n) 。
将 F_{k}(x+n) 用二项式定理展开，就是一个多项式与 F_{k}(x) 的卷积形式，
求出 F_{k}(x+n) 再直接与 F_{k}(x) 卷起来。
总复杂度 O(nlogn) 。
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

const int maxn = 1 << 19, mod = 167772161;
typedef ll poly[maxn];
typedef ll *pit;
ll G[maxn + 1];
int ra[maxn];

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
	int nk = __builtin_ctz(maxn) - __builtin_ctz(unsigned(n));
	for(int i = 0; i < n; i ++)
		if(i < (ra[i] >> nk))
			std::swap(a[i], a[ra[i] >> nk]);

	for(int m = 1; m < n; m <<= 1)
		for(int i = 0; i < n; i += m << 1)
			for(int k = i; k < i + m; k ++) {
				ll a0 = a[k], a1 = a[k + m] * G[m + k - i] % mod;
				// 一个很神奇的地方是模数为 167772161 时这里不用取模
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

ll fac[maxn], ifac[maxn];
void init() {
	ll g = power(3, (mod - 1) / maxn);

	G[maxn >> 1] = 1;
	for(int i = (maxn >> 1) + 1; i <= maxn; i ++)
		G[i] = G[i - 1] * g % mod;
	for(int i = (maxn >> 1) - 1; i; i --)
		G[i] = G[i << 1];

	fac[0] = 1;
	for(int i = 1; i < maxn; i ++)
		fac[i] = fac[i - 1] * i % mod;
	ifac[maxn - 1] = power(fac[maxn - 1], -1);
	for(int i = maxn - 1; i; i --)
		ifac[i - 1] = ifac[i] * i % mod;

	for(int i = 1; i < maxn; i ++)
		ra[i] = ra[i >> 1] >> 1 | (maxn >> 1) * (i & 1);
}

poly s, a, b;
void solve(int n) {
	if(n == 1) return s[1] = 1, void();

	if(n & 1) {
		solve(n - 1);
		for(int i = n; i; i --)
			s[i] = (s[i] * (n - 1) + s[i - 1]) % mod;
		return;
	}

	solve(n >> 1);
	int len = 1, m = n >> 1;
	while(len < n + 1) len <<= 1;

	std::copy(s, s + m + 1, b);
	std::fill(b + m + 1, b + len, 0);
	for(int i = 0; i <= m; i ++)
		(b[i] *= fac[i]) %= mod;
	std::reverse(b, b + m + 1);

	std::fill(a + m + 1, a + len, 0);
	ll po = 1;
	for(int i = 0; i <= m; i ++) {
		a[i] = po * ifac[i] % mod;
		(po *= m) %= mod;
	}

	DFT(b, len);
	DFT(a, len);
	for(int i = 0; i < len; i ++)
		(b[i] *= a[i]) %= mod;
	IDFT(b, len);

	std::fill(b + m + 1, b + len, 0);
	std::reverse(b, b + m + 1);
	for(int i = 0; i <= m; i ++)
		(b[i] *= ifac[i]) %= mod;

	DFT(b, len);
	DFT(s, len);
	for(int i = 0; i < len; i ++)
		(s[i] *= b[i]) %= mod;
	IDFT(s, len);
}

int main() {
	init();
	int n = read;
	solve(n);
	for(int i = 0; i <= n; i ++)
		printf("%lld ", s[i]);
	puts("");
}
