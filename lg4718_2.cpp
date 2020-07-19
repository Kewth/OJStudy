/*
 * Since g++10 is released, some characters is not valid inside #if 0 :(
 * So, why not using clang++? :D

 * Date:
  2020.07.19

 * Solution:
  Miller-Rabin + Pollard-Rho 模板，数据很棒，卡掉了 gcd 带的 log 。
  由于复杂度瓶颈仅在于 Pollard-Rho 的 gcd ，只优化这个部分的复杂度即可，用多次采样
的方式可以减少 gcd 的调用次数。

 * Digression:

 * CopyRight:
          ▁▃▄▄▄▃▃▃▃▄▶
        ▗▇▀▔    ▔▔▔▔
       ▄▛   ▃▅━━■▄▂
      ▟▊   ▐▘     ▀▙
     ▟▜▌   ▐▖   ▋  ▐▍
    ▟▘ ▜   ▝▀▇▆●▘  ▐▌
  ▗▟▘   ▜▃       ▁▅▛
  ▔▀▼▅▄▃▃██▅▄▄▄▅■▀▔
        ▔▔▔▔▔▔
 */

#include <cstdio>
#include <algorithm>
#include <random>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
} read;

inline ll mul (ll a, ll b, ll c) {
	a %= c, b %= c;
	ll tmp = a * b - ll(ld(a) / c * b + 0.5L) * c;
	return tmp < 0 ? tmp + c : tmp;
}

inline ll power (ll x, ll k, ll mod) {
	if (k < 0) k += mod - 1;
	ll res = 1;
	while (k) {
		if (k & 1) res = mul(res, x, mod);
		x = mul(x, x, mod);
		k >>= 1;
	}
	return res;
}

bool check (ll n, int p) {
	ll k = n - 1, x = power(p, k, n);
	if (x != 1) return 0;
	while (x == 1 and !(k & 1)) {
		x = power(p, k >>= 1, n);
		if (x != n - 1 and x != 1) return 0;
	}
	return 1;
}

bool miller (ll n) {
	int pr[] = {2, 3, 5, 7, 11, 13, 17, 19, 21};
	for (int p : pr) if (n == p) return 1;
	for (int p : pr) if (!(n % p)) return 0;
	for (int p : pr) if (!check(n, p)) return 0;
	return 1;
}

inline ll nxt (ll a, ll c, ll n) {
	ll tmp = mul(a, a, n) + c;
	return tmp >= n ? tmp - n : tmp;
}

ll pollard (ll n) {
	if (n == 4) return 2;
	static std::mt19937 engine;
	std::uniform_int_distribution<ll> rand(0, n - 1);
	ll c = rand(engine);
	ll a = nxt(rand(engine), c, n), b = nxt(a, c, n);
	for (int lim = 1; a != b; lim = std::min(128, lim << 1)) {
		ll m = 1;
		for (int k = 0; k < lim; k ++) {
			ll tm = mul(m, std::abs(a - b), n);
			if (!tm) break;
			m = tm;
			a = nxt(a, c, n);
			b = nxt(b, c, n);
			b = nxt(b, c, n);
		}
		ll g = std::__gcd(n, m);
		if (g > 1) return g;
	}
	/* while (a != b) { */
	/* 	ll g = std::__gcd(n, std::abs(a - b)); */
	/* 	if (g > 1) return g; */
	/* 	a = nxt(a, c, n); */
	/* 	b = nxt(b, c, n); */
	/* 	b = nxt(b, c, n); */
	/* } */
	return pollard(n);
}

ll maxp (ll n) {
	if (n == 1 or miller(n)) return n;
	ll d = pollard(n);
	while (!(n % d)) n /= d;
	return std::max(maxp(d), maxp(n));
}

int main () {
	int T = read;
	while (T --) {
		ll n = read, p = maxp(n);
		if (p == n) puts("Prime");
		else printf("%lld\n", p);
	}
}
