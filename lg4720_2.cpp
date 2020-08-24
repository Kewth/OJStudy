/*
 * Author: Kewth

 * Date:
  2020.08.11

 * Solution:

 * Digression:
  刷板题，用时 13min 。

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
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

static struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
} read;

ll power (ll x, ll k, int mod) {
	ll res = 1;
	while (k) {
		if (k & 1) (res *= x) %= mod;
		(x *= x) %= mod;
		k >>= 1;
	}
	return res;
}

ll exgcd (ll a, ll b, ll &x, ll &y) {
	if (!b) return x = 1, y = 0, a;
	ll g = exgcd(b, a % b, y, x);
	y -= a / b * x;
	return g;
}

ll inv (ll a, ll mod) {
	ll x, y;
	exgcd(a, mod, x, y);
	x %= mod;
	return x < 0 ? x + mod : x;
}

struct shit { ll x, y; };
const int maxn = 1000005;
ll pre[maxn];

shit fact (ll n, int p, int k) {
	if (!n) return {1, 0};
	int mod = int(power(p, k, maxn));
	shit res = fact(n / p, p, k);
	res.y += n / p;
	(res.x *= power(pre[mod], n / mod, mod)) %= mod;
	(res.x *= pre[n % mod]) %= mod;
	return res;
}

ll C (ll n, ll m, int p, int k) {
	int mod = int(power(p, k, maxn));
	pre[0] = 1;
	for (int i = 1; i <= mod; i ++)
		pre[i] = i % p ? pre[i - 1] * i % mod : pre[i - 1];
	shit a = fact(n, p, k), b = fact(m, p, k), c = fact(n - m, p, k);
	(a.x *= inv(b.x * c.x % mod, mod)) %= mod;
	a.y -= b.y + c.y;
	return a.x * power(p, a.y, mod);
}

int A[100], M[100], p;
int main () {
	ll n = read, m = read;
	int mod = read;
	for (int i = 2, x = mod; i <= x; i ++)
		if (x % i == 0) {
			M[++ p] = 1;
			int k = 0;
			while (x % i == 0) x /= i, ++ k, M[p] *= i;
			A[p] = int(C(n, m, i, k));
		}
	ll ans = 0;
	for (int i = 1; i <= p; i ++) {
		ll t = mod / M[i];
		(ans += t * inv(t, M[i]) % mod * A[i]) %= mod;
	}
	printf("%lld\n", ans);
}
