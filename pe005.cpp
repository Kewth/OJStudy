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
} read;

void solve (int n) {
	ll res = 1;
	for (int i = 1; i <= n; i ++)
		res = res / std::__gcd<ll>(res, i) * i;
	printf("%lld\n", res);
}

int main () {
#ifdef PE
	solve(20);
#else
	int T = read;
	while (T --) solve(read);
#endif
}
