/*
 * Author: Kewth

 * Date:
  2020.08.12

 * Solution:
  In blog.

 * Digression:

 * CopyRight:
          ▁▃▄▄▄▃▃▃▃▄▶
        ▗▇▀▔    ▔▔▔▔
       ▄▛   ▃▅━━■▄▂
      ▟▊   ▐▘     ▀▙
     ▟▜▌   ▐▖   ▋  ▐▍
    ▟▘ ▜   ▝▀▇▆■▘  ▐▌
  ▗▟▘   ▜▃       ▁▅▛
  ▔▀▼▅▄▃▃██▅▄▄▄▅■▀▔
        ▔▔▔▔▔▔
 */

#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

static struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 60005, maxm = 10, inf = 1000000000;
int a[maxn], tmp[maxm];
int f[maxm][1 << 8][1 << 8];

int query (int o, int x) {
	int y = x >> 8;
	x &= (1 << 8) - 1;
	int res = inf;
	for (int s = 0; s < (1 << 8); s ++)
		res = std::min(res, f[o][s][y] + (x ^ s));
	return res;
}

void update (int o, int x, int v) {
	int y = x >> 8;
	x &= (1 << 8) - 1;
	for (int s = 0; s < (1 << 8); s ++)
		f[o][x][s] = std::min(f[o][x][s], v + ((y ^ s) << 8));
}

int main () {
	int n = read, m = read;
	for (int i = 1; i <= n; i ++) a[i] = a[i - 1] ^ read;
	for (int i = 1; i <= m; i ++)
		for (int x = 0; x < (1 << 8); x ++)
			for (int y = 0; y < (1 << 8); y ++)
				f[i][x][y] = inf;
	for (int i = 1; i <= n; i ++) {
		tmp[1] = a[i];
		for (int j = 2; j <= m and j <= i; j ++)
			tmp[j] = query(j - 1, a[i]);
		for (int j = 1; j <= m and j <= i; j ++)
			update(j, a[i], tmp[j]);
		if (i >= m) printf("%d ", tmp[m]);
	}
	puts("");
}
