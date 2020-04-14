#if 0
2020.04.14

归纳归纳找找规律，划分成若干段把一段转移到上一段即可。
每一段的长度是上一段的四倍，因此段数是 O(logN) 的。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
} read;

ll solve (ll x, ll y, ll len, ll prelen) {
	if (len == 1) return y;
	/* debug("%lld %lld %lld %lld\n", x, y, len, prelen); */
	ll nlen = len >> 2;
	if (x <= nlen) {
		ll k = solve(x, y, nlen, prelen - len) - nlen * y;
		return k + len * y;
	}
	if (x <= nlen * 2) {
		ll k = solve(x - nlen, y, nlen, prelen - len) - nlen * y;
		if (y == 1) return nlen * 1 + k + len * y;
		if (y == 2) return nlen * 2 + k + len * y;
		if (y == 3) return nlen * 3 + k + len * y;
	}
	if (x <= nlen * 3) {
		ll k = solve(x - nlen * 2, y, nlen, prelen - len) - nlen * y;
		if (y == 1) return nlen * 2 + k + len * y;
		if (y == 2) return nlen * 3 + k + len * y;
		if (y == 3) return nlen * 1 + k + len * y;
	}
	if (x <= nlen * 4) {
		ll k = solve(x - nlen * 3, y, nlen, prelen - len) - nlen * y;
		if (y == 1) return nlen * 3 + k + len * y;
		if (y == 2) return nlen * 1 + k + len * y;
		if (y == 3) return nlen * 2 + k + len * y;
	}
	return 0;
}

int main () {
	int T = read;
	while (T --) {
		ll n = read;
		ll len = 1, prelen = 1;
		ll x = (n - 1) / 3 + 1, y = (n - 1) % 3 + 1;
		while (x > prelen) prelen += (len *= 4);
		printf("%lld\n", solve(x - (prelen - len), y, len, prelen));
	}
}
