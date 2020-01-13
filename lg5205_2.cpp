#if 0
2019.11.07

开始吸多项式毒。
多项式开根可以看做 1/2 次方，快速幂即可。
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

inline void polyln(pit a, int n) {
	assert(a[0] = 1);
	static poly tmp;
	std::copy(a, a + n, tmp);
	std::fill(tmp + n, tmp + (n << 1), 0);
	derivative(a, n);
	polyinv(tmp, n);

	NTT(a, n << 1, 1);
	NTT(tmp, n << 1, 1);
	for(int i = 0; i < (n << 1); i ++)
		(a[i] *= tmp[i]) %= mod;
	NTT(a, n << 1, -1);
	std::fill(a + n, a + (n << 1), 0);

	integrate(a, n);
}

inline void polyexp(pit a, int n) {
	assert(a[0] == 0);
	static poly res;
	res[0] = 1;
	std::fill(res + 1, res + n, 0);

	for(int m = 2; m <= n; m <<= 1) {
		static poly tmp, ln;
		std::copy(a, a + m, tmp);
		std::copy(res, res + m, ln);
		std::fill(tmp + m, tmp + (m << 1), 0);
		std::fill(ln + m, ln + (m << 1), 0);

		polyln(ln, m);

		NTT(tmp, m << 1, 1);
		NTT(ln, m << 1, 1);
		NTT(res, m << 1, 1);
		for(int i = 0; i < (m << 1); i ++)
			(res[i] *= 1 + mod - ln[i] + tmp[i]) %= mod;
		NTT(res, m << 1, -1);
	}

	std::copy(res, res + n, a);
}

void polypower(pit a, int n, ll k) {
	polyln(a, n);
	for(int i = 0; i < n; i ++)
		(a[i] *= k) %= mod;
	polyexp(a, n);
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

	polypower(A, len, inv[2]);

	for(int i = 0; i < n; i ++)
		printf("%lld ", A[i]);
	puts("");
}
