#if 0
2020.03.27

首先 a 的使用次数 x 如果超过 b ，可以把 b 个 a 换成 a 个 b 。
那么可以认为 x < b ，枚举所有 x ，然后得到方程 by + cz = k - ax ，
用 exgcd 解这个不定方程即可。
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
	{ x = *this; this -> operator () (a...); }
} read;

int gcd (int a, int b) {
	if (!b) return a;
	return gcd(b, a % b);
}

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

int main () {
	ll a = read, b = read, c = read, k = read;

	ll y, z;
	ll g = exgcd(b, c, y, z);
	/* debug("%lld %lld\n", y, z); */

	for (int i = 0; i < b; i ++) {
		ll s = k - 1ll * i * a;
		if (s % g) continue;
		s /= g;
		ll Y = y * s, Z = z * s;
		ll d = Y / (c / g);
		Y -= c / g * d;
		Z += b / g * d;
		if (Y < 0) Y += c / g, Z -= b / g;
		/* debug("%lld %lld\n", Y, Z); */
		if (Z >= 0) {
			printf("%d %lld %lld\n", i, Y, Z);
			break;
		}
	}
}
