#pragma GCC optimize(3)
#if 0
2020.01.13

对于每个物品，数量是无限的，就是 loj “烧菜” 的弱化版。
若其体积为 k ，那么可以构造形式幂级数 f(x) = x^k + x^2k + x^3k + ...
那么所有物品的 f(x) 的卷积 g(x) 就是答案的生成函数。

但是直接卷是不行的，注意到 f(x) 有封闭形式 1 / (1 - x^k) 。
可以将所有 (1 - x^k) 卷起来然后求逆，然而对复杂度并没有优化。

多个数相乘可以转换为取对数相加然后取 exp ，
换言之 A B C D ... = e^(lnA + lnB + lnC + lnD + ...) 。
那么只要 ln(1 - x^k) 很好算，这个就是可做的。

根据 ln 的套路先求导再积分，不难得到 ln(1 - x^k) = - (x^k/1 + x^2k/2 + x^3k/3 + ...)
对于不同的 k 算这个，复杂度就是个调和级数。
（其实就是泰勒展开）
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
	static poly res, tmp;
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

	std::copy(res, res + n, a);
}

inline void polyln(pit a, int n) {
	static poly res, tmp;
	assert(a[0] == 1);
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
	static poly res, tmp;
	assert(a[0] == 0);
	res[0] = 1;
	std::fill(res + 1, res + n, 0);

	for(int m = 2; m <= n; m <<= 1) {
		std::copy(res, res + (m >> 1), tmp);
		std::fill(tmp + (m >> 1), tmp + (m << 1), 0);

		polyln(tmp, m);
		for(int i = 0; i < m; i ++)
			__d(tmp[i] = a[i] - tmp[i]);

		DFT(tmp, m << 1);
		DFT(res, m << 1);
		for(int i = 0; i < (m << 1); i ++)
			(res[i] *= 1 + tmp[i]) %= mod;
		IDFT(res, m << 1);

		std::fill(res + m, res + (m << 1), 0);
	}

	std::copy(res, res + n, a);
}

poly A;
const int maxn = 100005;
int need[maxn];
int main() {
	int n = read, m = read, len = 1;
	while(len < m + 1)
		len <<= 1;

	while(n --) {
		int k = read;
		if(!k) {
			debug("wdnmd\n");
			continue;
		}
		if(k <= m)
			++ need[k];
	}

	for(int k = 1; k <= m; k ++)
		for(int i = 1; i * k <= m; i ++)
			(A[i * k] += inv[i] * (need[k] + mod)) %= mod;

	polyexp(A, len);

	for(int i = 1; i <= m; i ++)
		printf("%lld\n", A[i]);
}
