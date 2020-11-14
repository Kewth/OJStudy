/*
 * Author: Kewth

 * Date:
  2020.11.13

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

const int maxn = 100005 * 30;
int a[maxn], p;

int main () {
	int n = read, k = read;
	ll ans = 0;
	for (int i = 1; i <= n; i ++) {
		int x = read;
		ans += x;
		while (!(x & 1))
			a[++ p] = x >> 1, x >>= 1;
	}
	std::sort(a + 1, a + p + 1);
	for (int i = 0; i < k and i < p; i ++)
		ans -= a[p - i];
	printf("%lld\n", ans);
}
