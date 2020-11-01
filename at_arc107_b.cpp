/*
 * Author: Kewth

 * Date:
  2020.11.01

 * Solution:

 * Digression:
  我是傻逼，因为爆 int 被这题耗了十几分钟。

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

ll a (int n, int i) {
	if (i < 2 or i > n * 2) return 0;
	return i <= n + 1 ? i - 1 : n * 2 - i + 1;
}

int main () {
	int n = read, k = read;
	ll ans = 0;
	for (int i = 2; i <= n * 2; i ++)
		ans += a(n, i) * a(n, i + k);
	printf("%lld\n", ans);
}
