#if 0
2020.01.09

问题就是求选出一些 gcd 为 1 的数的方案数，
设 f(x) 表示选出 gcd 为 x 的方案数。
令 F(x) = sum(f(y) [x | y, y <= n]) ，那么 F(x) 的就是选数都是 x 的倍数的方案数，
也就是有 F(x) = 2^floor(n / x) - 1，莫反得到 f(1) 的表达式。
floor 可以整除分块，问题转换为求 mu 的前缀和，杜教筛即可。
#endif
#include <cstdio>
#include <algorithm>
#include <cmath>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
} read;

const int maxn = 30000005, maxs = 1000000, mod = 1000000007;

inline ll power(ll x, ll k) {
	if(k < 0) k += mod - 1;
	ll res = 1;
	while(k) {
		if(k & 1) (res *= x) %= mod;
		(x *= x) %= mod;
		k >>= 1;
	}
	return res;
}

ll n;
int s, m;
inline int id(ll x) {
	return x <= s ? int(x) : int(m - (n / x) + 1);
}

ll Smu[maxs];
ll w[maxs];
int mu[maxn];
int minp[maxn];

int main() {
	int N = 30000000;
	mu[1] = 1;
	for(int i = 2; i <= N; i ++) {
		int &p = minp[i];
		if(!p) {
			p = i;
			if(p <= N / p)
				for(int j = p * p; j <= N; j += p)
					if(!minp[j])
						minp[j] = p;
		}
		if(minp[i / p] != p)
			mu[i] = - mu[i / p];
	}
	for(int i = 1; i <= N; i ++)
		mu[i] += mu[i - 1];

	read(n);
	s = int(sqrtl(n));

	for(ll l = 1, r; l <= n; l = r + 1) {
		w[++ m] = r = n / (n / l);
		if(r <= N) Smu[m] = mu[r] < 0 ? mu[r] + mod : mu[r];
	}

	int tot = 0;
	for(int i = 1; i <= m; i ++)
		if(w[i] > N) {
			Smu[i] = 1;
			for(ll L = 2, R; L <= w[i]; L = R + 1) {
				R = w[i] / (w[i] / L);
				Smu[i] += mod - Smu[id(w[i] / L)] * (R - L + 1) % mod;
				++ tot;
			}
			Smu[i] %= mod;
		}

	/* for(int i = 1; i <= m; i ++) */
	/* 	debug("%lld: %lld\n", w[i], Smu[i] % mod); */
	/* debug("%d\n", tot); */

	ll ans = 0;
	for(int i = 1; i <= m; i ++)
		(ans += (power(2, n / w[i]) - 1) * (Smu[i] - Smu[i - 1] + mod)) %= mod;
	printf("%lld\n", ans);
}
