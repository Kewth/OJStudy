/*
 * Author: Kewth

 * Date:
  2020.11.30

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

const int maxn = 2000005, maxk = 20;
int f[maxk][maxn];

inline bool chkmax (int &x, int y) { return y > x ? x = y, 1 : 0; }

int main () {
	int n = read, m = read;
	for (int i = 1; i <= n * 2 + 1; i ++)
		f[0][i] = i;

	for (int i = 1; i <= m; i ++) {
		int l = read, r = read;
		if (r < l) {
			chkmax(f[0][1], r + 1);
			chkmax(f[0][l], r + n + 1);
			chkmax(f[0][l + n], n * 2 + 1);
		}
		else {
			chkmax(f[0][l], r + 1);
			chkmax(f[0][l + n], r + n + 1);
		}
	}

	for (int i = 2; i <= n * 2 + 1; i ++)
		f[0][i] = std::max(f[0][i - 1], f[0][i]);
	for (int k = 1; k < maxk; k ++)
		for (int i = n * 2 + 1; i; i --)
			f[k][i] = f[k - 1][f[k - 1][i]];

	if (f[maxk - 1][1] <= n)
		return puts("impossible"), 0;
	int ans = 1000000000;
	for (int i = 1; i <= n; i ++) {
		int x = i, now = 0;
		for (int k = maxk - 1; k >= 0; k --)
			if (f[k][x] < i + n)
				x = f[k][x], now += 1 << k;
		if (f[0][x] < i + n)
			return 1;
		ans = std::min(ans, now + 1);
	}
	printf("%d\n", ans);
}
