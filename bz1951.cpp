#if 0
2020.01.13

答案就是 g^sum(C(n, d) [d | n]) ，上面的组合数对 p - 1 取模。
将 p - 1 分解，得到 p - 1 = 2 * 3 * 4679 * 35617 。
每个质数都很小，可以卢卡斯定理算出 C(n, d) 在每个质数取模意义下的值，
然后用 CRT 合并即可得到模 p - 1 的值。
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

const int Mod = 2 * 3 * 4679 * 35617 + 1, maxn = 35617;

inline ll power(ll x, int k, int mod) {
	if(k < 0) k += mod - 1;
	ll res = 1;
	while(k) {
		if(k & 1) (res *= x) %= mod;
		(x *= x) %= mod;
		k >>= 1;
	}
	return res;
}

struct Shit {
	int mod, test;
	ll fac[maxn], ifac[maxn];

	Shit(int mod): mod(mod) {
		int n = mod - 1;
		fac[0] = 1;
		for(int i = 1; i <= n; i ++)
			fac[i] = fac[i - 1] * i % mod;
		ifac[n] = power(fac[n], -1, mod);
		for(int i = n; i; i --)
			ifac[i - 1] = ifac[i] * i % mod;
	}

	inline ll C(int n, int m) {
		if(n < m) return 0;
		return fac[n] * ifac[n - m] % mod * ifac[m] % mod;
	}

	ll lucas(int n, int m) {
		if(!n and !m) return 1;
		return lucas(n / mod, m / mod) * C(n % mod, m % mod) % mod;
	}
};

Shit shi[4] = {2, 3, 4679, 35617};
ll solve(int n, int d) {
	ll res = 0;
	int p[4] = {2, 3, 4679, 35617}, mod = Mod - 1;
	for(int i = 0; i < 4; i ++) {
		int m = (Mod - 1) / p[i];
		(res += m * power(m, -1, p[i]) % mod * shi[i].lucas(n, d)) %= mod;
	}
	return res;
}

int main() {
	int n = read, g = read;
	if(g % Mod == 0) return puts("0"), 0;
	ll ans = 0;
	for(int d = 1; d * d <= n; d ++)
		if(n % d == 0) {
			ans += solve(n, d);
			if(d * d < n)
				ans += solve(n, n / d);
		}
	ans = power(g, ans % (Mod - 1), Mod);
	printf("%lld\n", ans);
}
