/*
 * Author: Kewth

 * Date:
  2020.08.07

 * Solution:
  In blog.

 * Digression:

 * CopyRight:
          ▁▃▄▄▄▃▃▃▃▄▶
        ▗▇▀▔    ▔▔▔▔
       ▄▛   ▃▅━━■▄▂
      ▟▊   ▐▘     ▀▙
     ▟▜▌   ▐▖   ▋  ▐▍
    ▟▘ ▜   ▝▀▇▆■▘  ▐▌
  ▗▟▘   ▜▃       ▁▅▛
  ▔▀▼▅▄▃▃██▅▄▄▄▅■▀▔
        ▔▔▔▔▔▔
 */

#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>
#include <map>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

static struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
} read;

ll mul (ll x, ll y, ll mod) {
	return __int128(x) * y % mod;
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

ll minp (ll n) {
	for (ll d = 2; d * d <= n; d ++)
		if (n % d == 0)
			return d;
	return n;
}

ll phi;
int sq;
std::vector<ll> v, V;
std::map<ll, int> S;
const int maxs = 20000005;
int G[maxs], GS[maxs];

void getd (ll n) {
	sq = int(std::sqrt(n));
	for (int d = 1; d <= sq; d ++)
		if (n % d == 0)
			V.push_back(n / d);
	for (int d = 1ll * sq * sq == n ? sq - 1 : sq; d; d --)
		if (n % d == 0)
			V.push_back(d);
	for (int d = 2; d <= n / d; d ++)
		if (n % d == 0) {
			v.push_back(d);
			while (n % d == 0) n /= d;
		}
	if (n > 1)
		v.push_back(n);
}

inline int id (ll x) {
	return int(x <= sq ? x : sq + phi / x);
}

const int maxn = 100005;
ll po[maxn];

int main () {
	int n = read;
	ll p = read, q = minp(p);
	phi = p / q * (q - 1);
	getd(phi);

	for (int i = 1; i <= n; i ++) {
		ll x = read, y = phi;
		if (x % q == 0) S[x] = 0;
		else {
			for (ll d : v)
			while (y % d == 0 and power(x, y / d, p) == 1)
				y /= d;
			++ G[id(y)];
			++ GS[id(y)];
		}
	}

	for (auto P : S) {
		ll x = P.first;
		while (x) {
			if (S.count(x)) ++ S[x];
			x = mul(x, P.first, p);
		}
	}

	for (ll d : v)
		for (ll x : V)
			if (phi / x % d == 0)
				GS[id(x)] += GS[id(x * d)];

	/* for (auto P : S) */
	/* 	debug("%lld %d\n", P.first, P.second); */
	/* for (ll x : V) */
	/* 	debug("%lld : %d %d\n", x, G[id(x)], GS[id(x)]); */

	const int mod = 998244353;
	po[0] = 1;
	for (int i = 1; i <= n; i ++) po[i] = (po[i - 1] << 1) % mod;
	ll ans = 0;
	for (auto P : S)
		ans += po[n - P.second];
	ans %= mod;
	for (ll x : V)
		(ans += (po[G[id(x)]] - 1) * po[n - GS[id(x)]]) %= mod;
	printf("%lld\n", ans);
}
