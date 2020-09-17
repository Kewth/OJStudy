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
	printf("%lld\n", n * (n + 1) * n * (n + 1) / 4 - n * (n + 1) * (n * 2 + 1) / 6);
}

int main () {
#ifdef PE
	solve(100);
#else
	int T = read;
	while (T --) solve(read);
#endif
}
