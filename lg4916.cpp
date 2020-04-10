#if 0
2020.04.10

把白球看做隔板，问题转换为把 m 个球放进 n - m 个盒子里，其中盒子形成了环。
通过 burnside 引理，可以简单地把问题转换为无环的情况。
那么现在问题就是 n 个盒子排成一排，放 m 个球，每个盒子不能超过 lim 个球。
注意到如果没有 lim 的限制是可以通过隔板法直接算的。
考虑容斥，枚举有至少 k 个盒子有超过 lim 个球，然后把 m - k(lim + 1) 个球放进盒子，
再选出 k 个盒子每个再放 lim + 1 个球，可以归纳出容斥系数是 (-1)^(k+1) 。
#endif
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct Inputer {
	static char buffer[64 * 1024 * 1024], *p;
	inline operator int () { return int(strtol(p, &p, 10)); }
	inline operator ll () { return strtoll(p, &p, 10); }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
	Inputer() { fread(buffer, 1, sizeof buffer, stdin); }
} read;
char *Inputer::p = Inputer::buffer;
char Inputer::buffer[] = {};

const int maxn = 100005, mod = 998244353;
int f[maxn];
ll fac[maxn << 1], ifac[maxn << 1];

inline ll power (ll x, int k) {
	if (k < 0) k += mod - 1;
	ll res = 1;
	while (k) {
		if (k & 1) (res *= x) %= mod;
		(x *= x) %= mod;
		k >>= 1;
	}
	return res;
}

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

ll g[maxn];
ll solve (int n, int m, int lim) {
	ll res = 0;
	for (int k = 0, M = m; M >= 0; k ++, M -= lim + 1) {
		ll now = C(n + M - 1, M) * C(n, k) % mod;
		res += k & 1 ? mod - now : now;
	}
	return res % mod;
}

int main () {
	combinator_init(200000);
	int n = read, m = read, lim = read;
	n -= m;
	if (n <= 1 or m == 0)
		return printf("%d\n", m <= lim), 0;

	for (int k = 1; k <= n; k ++)
		if (!(n % k)) {
			int x = m % (n / k) ? 0 : int(solve(k, m / (n / k), lim));
			for (int i = k; i <= n; i += k)
				f[i] = x;
		}

	ll sum = 0;
	for (int k = 1; k <= n; k ++)
		sum += f[k];
	printf("%lld\n", sum % mod * power(n, -1) % mod);
}
