/*
 * Since g++10 is released, some characters is not valid inside #if 0 :(
 * So, why not using clang++? :D

 * Date:
  2020.06.16

 * Solution:
  对于一个二进制位，如果在该位上存在至少三个数为 1 ，那么这三个数就能构成一个三元环，
答案就是三。因此不妨假设每个二进制位都只有至多两个数为 1 ，那么那些有恰好两个数为 1
的二进制位可以看做一条边，这样建图，点数只有 2logV ，直接 floyd 求最小环即可。

 * Digression:

 * CopyRight:
          ▁▃▄▄▄▃▃▃▃▄▶
        ▗▇▀▔    ▔▔▔▔
       ▄▛   ▃▅━━■▄▂
      ▟▊   ▐▘     ▀▙
     ▟▜▌   ▐▖   ▋  ▐▍
    ▟▘ ▜   ▝▀▇▆●▘  ▐▌
  ▗▟▘   ▜▃       ▁▅▛
  ▔▀▼▅▄▃▃██▅▄▄▄▅■▀▔
        ▔▔▔▔▔▔
 */

#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
} read;

const int maxn = 100005, maxk = 60;
int ax[maxk], ay[maxk];
int id[maxn], ip;
int f[maxk << 1][maxk << 1], g[maxk << 1][maxk << 1];

int main () {
	int n = read;
	for (int i = 1; i <= n; i ++) {
		ll x = read;
		if (x == 0) continue;
		int u = ++ ip;
		for (int k = 0; k < maxk; k ++)
			if (x >> k & 1) {
				if (ay[k]) return puts("3"), 0;
				if (ax[k]) ay[k] = u;
				else ax[k] = u;
			}
	}

	for (int i = 1; i <= ip; i ++)
		for (int j = 1; j <= ip; j ++)
			f[i][j] = g[i][j] = 100000;

	for (int k = 0; k < maxk; k ++)
		if (ax[k] and ay[k]) {
			f[ax[k]][ay[k]] = f[ay[k]][ax[k]] = 1;
			g[ax[k]][ay[k]] = g[ay[k]][ax[k]] = 1;
		}

	int ans = 100000;
	for (int k = 1; k <= ip; k ++) {
		for (int i = 1; i < k; i ++)
			for (int j = 1; j < i; j ++)
				ans = std::min(ans, f[i][j] + g[i][k] + g[k][j]);
		for (int i = 1; i <= ip; i ++)
			for (int j = 1; j <= ip; j ++)
				f[i][j] = std::min(f[i][j], f[i][k] + f[k][j]);
	}

	if (ans == 100000) puts("-1");
	else printf("%d\n", ans);
}
