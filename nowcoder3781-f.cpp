#if 0
2020.01.10

设 a[i][j] = a[i - 1][j] + a[i - 1][j - 1] ，其中 a[0][~] 是给定的数组。
那么询问相当于询问 a[r - l][r] 的值。
每个 a[i][j] 通过组合数可以由 a[i - k][j - k] 到 a[i - k][j] 这 k + 1 个值 O(k) 得出。
考虑分块，对于块大小 B ，预处理每个 a[kB][~] 。
这样询问就可以找到一个对应的 a[kB][~] 然后 O(B) 计算。
现在的问题在于预处理，直接从一层通过组合数算到另一层复杂度仍然是 O(n^2) 的。
注意到 a[i] 的生成函数乘上 (1 + x) 就是 a[i + 1] 的生成函数，
这样通过 NTT 预处理每个 a[kB][~] 即可，总复杂度 O(n sqrt(nlogn)) 。
#endif
#include <cstdio>
#include <algorithm>
#include <cmath>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
} read;

const int maxn = 140005, maxl = 1 << 18, maxs = 400, mod = 998244353;

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
				__a(a[k] = a0 + a1);
				__d(a[k + m] = a0 - a1);
			}

/* 	for (int i = 0; i < n; ++i) __d(a[i] %= mod); */
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


poly a[maxs];
poly c, tmp;
ll fac[maxn], ifac[maxn];

inline ll C(int n, int m) {
	return fac[n] * ifac[m] % mod * ifac[n - m] % mod;
}

int main() {
	init();

	int n = read, q = read;
	for(int i = 0; i < n; i ++)
		read(a[0][i]);

	int B = int(sqrt(n * log2(n + 1)) * 1.7 + 1);
	fac[0] = 1;
	for(int i = 1; i <= B; i ++)
		fac[i] = fac[i - 1] * i % mod;
	ifac[B] = power(fac[B], -1);
	for(int i = B; i; i --)
		ifac[i - 1] = ifac[i] * i % mod;

	/* debug("B = %d\n", B); */

	for(int i = 0; i <= B; i ++)
		c[i] = C(B, i);

	int len = 1;
	while(len < n + B)
		len <<= 1;

	DFT(c, len);

	for(int b = 1; b * B <= n; b ++) {
		std::copy(a[b - 1], a[b - 1] + len, tmp);
		DFT(tmp, len);
		for(int i = 0; i < len; i ++)
			a[b][i] = tmp[i] * c[i] % mod;
		IDFT(a[b], len);
		std::fill(a[b] + n, a[b] + len, 0);
	}

	int ans = 0;
	while(q --) {
		int l = read ^ ans, r = read ^ ans;
		-- l;
		-- r;
		/* debug("%d %d\n", l, r); */
		if(l < 0 or l >= n) return 1;
		if(r < 0 or r >= n) return 1;
		int b = r - l;
		int base = b / B, dep = b % B;
		ll sum = 0;
		for(int i = 0; i <= dep; i ++)
			sum += a[base][r - i] * C(dep, i) % mod;
		ans = sum % mod;
		printf("%d\n", ans);
#ifdef LOCAL
		ans = 0;
#endif
	}
}
