/*
 * Author: Kewth

 * Date:
  2020.11.14

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
	template<class T> inline void operator () (T &x) { x = *this; }
} read;

const int maxn = 305, maxt = 605;
int f[maxt][maxt], mx[maxt][maxt];
struct rival { int l, r, w; } ri[maxn];
int tmp[maxt], tp;

inline bool chkmax (int &x, int y) { return y > x ? x = y, 1 : 0; }
inline bool chkmin (int &x, int y) { return y < x ? x = y, 1 : 0; }

int main () {
	int T = read;
	while (T --) {
		int n = read;
		tp = 0;
		for (int i = 1; i <= n; i ++) {
			tmp[++ tp] = ri[i].l = read;
			tmp[++ tp] = ri[i].r = read;
			read(ri[i].w);
		}
		std::sort(tmp + 1, tmp + tp + 1);
		tp = int(std::unique(tmp + 1, tmp + tp + 1) - tmp - 1);
		for (int l = 1; l <= tp; l ++)
			for (int r = l; r <= tp; r ++)
				mx[l][r] = 0;
		for (int i = 1; i <= n; i ++) {
			ri[i].l = int(std::lower_bound(tmp + 1, tmp + tp + 1, ri[i].l) - tmp);
			ri[i].r = int(std::lower_bound(tmp + 1, tmp + tp + 1, ri[i].r) - tmp);
			for (int l = 1; l <= ri[i].l; l ++)
				chkmax(mx[l][ri[i].r], ri[i].w);
			/* debug("%d %d\n", ri[i].l, ri[i].r); */
		}
		for (int l = 1; l <= tp; l ++)
			for (int r = l; r <= tp; r ++)
				chkmax(mx[l][r], mx[l][r - 1]);
		for (int l = tp; l; l --)
			for (int r = l; r <= tp; r ++) {
				f[l][r] = 1000000000;
				for (int i = l; i <= r; i ++)
					chkmin(f[l][r], f[l][i - 1] + f[i + 1][r]);
				f[l][r] += mx[l][r];
			}
		printf("%d\n", f[1][tp]);
	}
}
