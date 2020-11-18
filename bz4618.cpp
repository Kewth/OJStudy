/*
 * Author: Kewth

 * Date:
  2020.11.18

 * Solution:
  In blog.

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

const int maxs = 10005;
int bl[maxs];

int main () {
	int n = read, p = 0;
	for (int i = 1; i <= n; i ++) {
		int x = read;
		for (int j = 0; j < x; j ++)
			bl[++ p] = i;
	}
	int ans = p == 2 ? 1 : 0;
	if (p % 2 == 0)
		for (int k = 2; k * (k + 1) <= p; k ++) {
			bool ok = 1;
			for (int i = k, las = 0; i; i --)
				ok &= bl[las + 1] == bl[las + i], las += i;
			for (int i = k, las = p + 1; i; i --)
				ok &= bl[las - 1] == bl[las - i], las -= i;
			if (ok) ans = k;
		}
	if (ans) printf("%d\n", ans);
	else puts("no quotation");
}
