#if 0
date +%Y.%m.%d

开始吸多项式毒。
牛顿迭代求多项式开根，需要多项式求逆。
#endif
#include <cstdio>
#include <algorithm>
#include <cassert>
#include <cctype>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
} read;

const int maxn = 1 << 19, mod = 998244353;
typedef ll poly[maxn];
typedef ll *pit;
poly A;
ll G[maxn + 1];
ll inv[maxn];

inline void __a(ll &x) { if(x >= mod) x -= mod; }
inline void __d(ll &x) { if(x < 0) x += mod; }

inline void NTT(pit a, int n, int t) {
	static poly ra;
	for(int i = 1; i < n; i ++)
		ra[i] = ra[i >> 1] >> 1 | (n >> 1) * (i & 1);
	for(int i = 0; i < n; i ++)
		if(i < ra[i])
			std::swap(a[i], a[ra[i]]);

	for(int m = 1; m < n; m <<= 1) {
		int base = maxn / (m << 1);
		for(int i = 0; i < n; i += m << 1)
			for(int k = i; k < i + m; k ++) {
				ll a0 = a[k], a1 = a[k + m] *
					(t == 1 ? G[base * (k - i)] : G[maxn - base * (k - i)]) % mod;
				__a(a[k] = a0 + a1);
				__d(a[k + m] = a0 - a1);
			}
	}

	if(t == -1)
		for(int i = 0; i < n; i ++)
			(a[i] *= inv[n]) %= mod;
}

inline void polyinv(pit a, int n) {
	assert(a[0] == 1);
	static poly res;
	res[0] = 1;
	// res[0] = power(a[0], -1);
	std::fill(res + 1, res + (n << 1), 0);

	for(int m = 2; m <= n; m <<= 1) {
		static poly tmp;
		std::copy(a, a + m, tmp);
		std::fill(tmp + m, tmp + (m << 1), 0);

		NTT(tmp, m << 1, 1);
		NTT(res, m << 1, 1);
		for(int i = 0; i < (m << 1); i ++)
			(res[i] *= 2 + mod - res[i] * tmp[i] % mod) %= mod;
		NTT(res, m << 1, -1);

		std::fill(res + m, res + (m << 1), 0);
	}

	std::copy(res, res + n, a);
}

inline void polysqrt(pit a, int n) {
	assert(a[0] == 1);
	static poly res;
	res[0] = 1;
	// res[0] = a[0] 的二次剩余？
	std::fill(res + 1, res + (n << 1), 0);

	for(int m = 2; m <= n; m <<= 1) {
		static poly tmp, pinv;
		std::copy(a, a + m, tmp);
		std::copy(res, res + m, pinv);
		std::fill(tmp + m, tmp + (m << 1), 0);
		std::fill(pinv + m, pinv + (m << 1), 0);

		polyinv(pinv, m);

		NTT(tmp, m << 1, 1);
		NTT(pinv, m << 1, 1);
		NTT(res, m << 1, 1);
		for(int i = 0; i < (m << 1); i ++)
			res[i] = (res[i] * res[i] + tmp[i]) % mod * inv[2] % mod * pinv[i] % mod;
		NTT(res, m << 1, -1);

		std::fill(res + m, res + (m << 1), 0);
	}

	std::copy(res, res + n, a);
}

int main() {
	ll g = 1;
	for(int i = 0; i < (mod - 1) / maxn; i ++)
		(g *= 3) %= mod;

	G[0] = 1;
	for(int i = 1; i <= maxn; i ++)
		G[i] = G[i - 1] * g % mod;

	inv[1] = 1;
	for(int i = 2; i < maxn; i ++)
		inv[i] = inv[mod % i] * (mod - mod / i) % mod;

	int n = read;
	for(int i = 0; i < n; i ++)
		read(A[i]);

	int len = 1;
	while(len < n)
		len <<= 1;

	polysqrt(A, len);

	for(int i = 0; i < n; i ++)
		printf("%lld ", A[i]);
	puts("");
}
