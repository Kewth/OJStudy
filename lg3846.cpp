#if 0
2019.10.27

BSGS 模板。
#endif
#include <cstdio>
#include <unordered_map>
#include <cmath>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

inline int input() { int x; scanf("%d", &x); return x; }

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

/* ll tmp1, tmp2; */
/* ll exgcd(ll a, ll b, ll &x = tmp1, ll &y = tmp2) { */
/* 	if(!b) { */
/* 		x = 1; */
/* 		y = 0; */
/* 		return a; */
/* 	} */
/* 	ll x0, y0; */
/* 	ll res = exgcd(b, a % b, x0, y0); */
/* 	x = y0; */
/* 	y = x0 - a / b * y0; */
/* 	return res; */
/* } */

/* ll inv(ll x, int mod) { */
/* 	ll res; */
/* 	exgcd(x, mod, res); */
/* 	return ((res % mod) + mod) % mod; */
/* } */

/* ll log(ll a, ll b, int mod) { */
/* 	a %= mod; */
/* 	b %= mod; */
/* 	if(!a) return !b ? 0 : -1; */
/* 	if(b == 1) return 0; */
/* 	if(a == b) return 1; */
/* 	/1* debug("%lld %lld %d\n", a, b, mod); *1/ */
/* 	ll g = exgcd(a, mod); */
/* 	if(g == 1) return bsgs(a, b, mod); */

/* 	if(b % g) return -1; */

/* 	a /= g; */
/* 	b /= g; */
/* 	mod /= g; */

/* 	ll res = log(a * g, b * inv(a, mod), mod); */
/* 	if(res == -1) return res; */
/* 	return res + 1; */
/* } */

int main() {
	int mod = input(), a = input(), b = input();

	ll ans = bsgs(a, b, mod);
	if(ans == -1) puts("no solution");
	else printf("%lld\n", ans);
}
