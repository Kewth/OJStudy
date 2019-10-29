#if 0
2019.10.29

数列 x[i] = a x[i - 1] + b 可以化为 (x[i] - k) = a (x[i - 1] - k) 形式，
从而转换为等比数列，求出通项后就是个对数问题， BSGS 即可。
但是有很多细节需要考虑，例如 a = 0 ， a = 1 之类，此时不一定是个等比数列问题。
#endif
#include <cstdio>
#include <unordered_map>
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

ll inv(ll x, int mod) {
	ll res;
	exgcd(x, mod, res);
	return ((res % mod) + mod) % mod;
}


ll bsgs(ll a, ll b, int mod) {
	std::unordered_map<ll, int> map;
	int s = int(sqrt(mod) + 1);
	ll A = 1;

	for(int i = 1; i <= s; i ++) {
		(A *= a) %= mod;
		map[b * A % mod] = i;
	}

	b = 1;
	for(int i = 1; i <= s; i ++) {
		(b *= A) %= mod;
		if(map[b])
			return i * s - map[b];
	}

	return -1;
}

int main() {
	int T = read;
	while(T --) {
		int p = read, a = read, b = read, s = read, t = read;

		if(s == t) puts("1");

		else if(a == 0) {
			if(b == t) puts("2");
			else puts("-1");
		}

		else if(a == 1) {
			if(!b) puts("-1");
			else printf("%lld\n", 1 + (t + p - s) * inv(b, p) % p);
		}

		else {
			ll k = b * inv((p + 1 - a) % p, p) % p;
			/* debug("%lld\n", k); */
			s = (s + p - k) % p;
			t = (t + p - k) % p;
			ll ans = bsgs(a, t * inv(s, p) % p, p);
			/* debug("%lld\n", t * inv(s, p) % p); */
			if(ans == -1) puts("-1");
			else printf("%lld\n", ans + 1);
		}
	}
}
