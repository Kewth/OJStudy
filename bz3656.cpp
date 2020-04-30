#if 0
2020.04.29

  可以发现无论怎么操作，这个序列都构成一个线性基，那么在线性基里选 k 个数异或出来的数一定
两两不同，因此答案就是 C(n, k) % p ，扩展卢卡斯即可。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
} read;

ll __tmp1, __tmp2;
ll exgcd(ll a, ll b, ll &x = __tmp1, ll &y = __tmp2) {
	if(!b) {
		x = 1;
		y = 0;
		return a;
	}
	ll x0, y0;
	ll res = exgcd(b, a % b, x0, y0);
	x = y0;
	y = x0 - a / b * y0;
	return res;
}

ll inv(ll x, int Mod) {
	ll res;
	exgcd(x, Mod, res);
	return ((res % Mod) + Mod) % Mod;
}

inline ll power (ll x, ll k, int mod = (1ll << 31) - 1) {
	if (k < 0) k += mod - 1;
	ll res = 1;
	while (k) {
		if (k & 1) (res *= x) %= mod;
		(x *= x) %= mod;
		k >>= 1;
	}
	return res;
}

ll fucksum;
ll fact (ll n, int p, int k, int flag) {
	if (!n) return 1;
	int mod = int(power(p, k));
	ll t = n / p;
	ll res = 1;
	fucksum += t * flag;
	for (int i = 1; i <= mod; i ++)
		if (i % p)
			(res *= i) %= mod;
	res = power(res, n / mod, mod);
	for (int i = 1; i <= n % mod; i ++)
		if (i % p)
			(res *= i) %= mod;
	(res *= fact(t, p, k, flag)) %= mod;
	return res;
}

ll ca[100], cm[100], cp;
ll excrt () {
	ll a = 0, m = 1;
	for (int i = 1; i <= cp; i ++) {
		ll x, y, A = ca[i], M = cm[i];
		exgcd(m, M, x, y);
		m = m * M;
		if (!m) return -1;
		a = (A - M * y % m * (A - a)) % m;
		if (a < 0) a += m;
	}
	return a;
}

ll exlucas (ll n, ll m, int p) {
	for (int x = 2; x <= p; x ++)
		if (p % x == 0) {
			int k = 0;
			while (p % x == 0) p /= x, ++ k;
			fucksum = 0;
			int mod = int(power(x, k));
			ll a = fact(n, x, k, 1) * inv(fact(m, x, k, -1), mod) % mod *
				inv(fact(n - m, x, k, -1), mod) % mod;
			(a *= power(x, fucksum, mod)) %= mod;
			++ cp;
			ca[cp] = a;
			cm[cp] = mod;
		}
	return excrt();
}

int main () {
	ll n = read, m = read;
	int p = read;
	printf("%lld\n", exlucas(n, m, p));
}
