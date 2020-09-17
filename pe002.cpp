/*
 * Author: Kewth

 * Date:
  2020.08.24

 * Solution:

 * Digression:

 * CopyRight:
   __  __                  __   __
  |  |/  |.-----.--.--.--.|  |_|  |--.
  |     < |  -__|  |  |  ||   _|     |
  |__|\__||_____|________||____|__|__|

 */

#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

static struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
} read;

void solve (ll n) {
	ll a = 1, b = 1, ans = 0;
	while (a + b < n) {
		ll c = a + b;
		if (!(c & 1)) ans += c;
		a = b, b = c;
	}
	printf("%lld\n", ans);
}

int main () {
#ifdef PE
	solve(4000000);
#else
	int T = read;
	while (T --) solve(read);
#endif
}
