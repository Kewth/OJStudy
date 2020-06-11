/*
 * Since g++10 is released, some characters is not valid inside #if 0 :(
 * So, why not using clang++? :D

 * Date:
  2020.06.10

 * Solution:
  《反回文串》的弱化版，不需要用 porllard-rho 分解。
  但是为了去写《反回文串》，还是写了 porllard-rho ，题解就见《反回文串》。

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
#include <map>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef std::pair<ll, int> par;

struct {
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
} read;

inline ll mul (ll a, ll b, ll c) {
	return __int128(a) * b % c;
}

ll power (ll x, ll k, ll mod) {
	ll res = 1;
	while (k) {
		if (k & 1) res = mul(res, x, mod);
		x = mul(x, x, mod);
		k >>= 1;
	}
	return res;
}

bool miller (ll n, int p) {
	ll x = n - 1, test = power(p, x, n);
	if (test != 1) return 0;
	while (!(x & 1) and test == 1) {
		x >>= 1;
		test = power(p, x, n);
		if (test != 1 and test != n - 1) return 0;
	}
	return 1;
}

bool is_prime (ll n) {
	int prime[] = {2, 3, 5, 7, 11, 13, 17, 19, 23};
	for (int p : prime) if (n == p) return 1;
	for (int p : prime) if (n % p == 0) return 0;
	for (int p : prime) if (!miller(n, p)) return 0;
	return 1;
}

ll gcd (ll a, ll b) {
	if (!b) return a;
	return gcd(b, a % b);
}

ll nxt (ll x, ll c, ll n) {
	ll res = mul(x, x, n) + c;
	return res >= n ? res - n : res;
}

ll porllard (ll n) {
	if (n == 4) return 2;
	ll c = (rand() * (ll(RAND_MAX) + 1) + rand()) % n;
	ll a = nxt(rand(), c, n), b = nxt(a, c, n);
	while (a != b) {
		ll g = gcd(n, std::abs(a - b));
		if (g > 1 and g < n) return g;
		a = nxt(a, c, n);
		b = nxt(b, c, n);
		b = nxt(b, c, n);
	}
	return porllard(n);
}

std::map<ll, int> get;
void factor (ll n, int coe) {
	if (n == 1) return;
	if (is_prime(n)) return get[n] += coe, void();
	ll d = porllard(n);
	int k = 0;
	while (n % d == 0) n /= d, ++ k;
	factor(n, coe);
	factor(d, coe * k);
}

par pr[100];
ll ans;
void dfs (int i, ll d, ll c, ll n, ll K, ll mod) {
	if (!i) {
		if (d & 1 and !(n / d & 1)) return;
		ll g = power(K, (d + 1) >> 1, mod);
		ll h = d & 1 ? d : d >> 1;
		ans += mul(mul(g, h, mod), c, mod);
		return;
	}
	for (int k = 0; k <= pr[i].second; k ++) {
		dfs(i - 1, d, k == pr[i].second ? c : c * (1 - pr[i].first), n, K, mod);
		d *= pr[i].first;
	}
}

int main () {
	ll n = read, K = read, mod = 1000000007;
	get.clear();
	factor(n, 1);
	int pp = 0;
	for (par p : get)
		pr[++ pp] = p;
	ans = 0;
	dfs(pp, 1, 1, n, K, mod);
	ans %= mod;
	if (ans < 0) ans += mod;
	printf("%lld\n", ans);
}
