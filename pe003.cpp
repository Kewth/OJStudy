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
	ll ans = 0;
	for (ll d = 2; d * d <= n; d ++)
		while (n % d == 0)
			ans = d, n /= d;
	printf("%lld\n", std::max(ans, n));
}

int main () {
#ifdef PE
	solve(600851475143);
#else
	int T = read;
	while (T --) solve(read);
#endif
}
