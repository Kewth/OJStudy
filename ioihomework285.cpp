/*
 * Author: Kewth

 * Date:
  2020.11.20

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

const int maxn = 200005;
bool pp[maxn], px[maxn], py[maxn];
int tot[2][2][2];

int main () {
	int n = read;
	for (int i = 1; i <= n; i ++) {
		px[i] = read & 1;
		py[i] = read & 1;
		pp[i] = pp[i - 1] ^ (px[i] & py[i - 1]) ^ (py[i] & px[i - 1]);
		++ tot[pp[i]][px[i]][py[i]];
	}
	if (pp[n] ^ (px[1] & py[n]) ^ (py[1] & px[n]))
		return puts("0"), 0;
	ll ans = 0;
	for (int s1 = 0; s1 < 8; s1 ++) {
		int p1 = s1 & 1, x1 = s1 >> 1 & 1, y1 = s1 >> 2 & 1;
		for (int s2 = 0; s2 < 8; s2 ++) {
			int p2 = s2 & 1, x2 = s2 >> 1 & 1, y2 = s2 >> 2 & 1;
			if ((p1 ^ p2 ^ (x1 & y2) ^ (y1 & x2)) == 0)
				ans += 1ll * tot[p1][x1][y1] * tot[p2][x2][y2];
		}
	}
	printf("%lld\n", (ans - n) / 2 - n);
}
