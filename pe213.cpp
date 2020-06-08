/*
 * Since g++10 is released, some characters is not valid inside #if 0 :(
 * So, why not using clang++? :D

 * Date:
  2020.06.08

 * Solution:
  直接 DP 即可。

 * Digression:
  妈的，我单方面宣布 hackerrank 是天下第一卡常 OJ 。

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

#pragma GCC optimize(3)
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 45, mod = 1000000007;
const ll i2 = (mod + 1) / 2, i3 = (mod + 1) / 3, i4 = (mod + 1) / 4;
ll f[maxn][maxn];
ll g[maxn][maxn];
ll p[maxn][maxn];

void trans (int n) {
	/* if (n == 2) { */
	/* 	ll a = f[1][1], b = f[1][2], c = f[2][1], d = f[2][2]; */
	/* 	f[1][1] = (b + c) * i2 % mod; */
	/* 	f[1][2] = (a + d) * i2 % mod; */
	/* 	f[2][1] = (a + d) * i2 % mod; */
	/* 	f[2][2] = (b + c) * i2 % mod; */
	/* 	return; */
	/* } */

	for (int i = 1; i <= n; i ++)
		for (int j = 1; j <= n; j ++)
			g[i][j] = 0;

	g[2][1] += f[1][1] * i2;
	g[1][2] += f[1][1] * i2;
	g[2][n] += f[1][n] * i2;
	g[1][n - 1] += f[1][n] * i2;
	g[n - 1][1] += f[n][1] * i2;
	g[n][2] += f[n][1] * i2;
	g[n - 1][n] += f[n][n] * i2;
	g[n][n - 1] += f[n][n] * i2;

	for (int i = 2; i < n; i ++) {
		g[2][i] += f[1][i] * i3;
		g[1][i - 1] += f[1][i] * i3;
		g[1][i + 1] += f[1][i] * i3;
		g[n - 1][i] += f[n][i] * i3;
		g[n][i - 1] += f[n][i] * i3;
		g[n][i + 1] += f[n][i] * i3;
		g[i][2] += f[i][1] * i3;
		g[i - 1][1] += f[i][1] * i3;
		g[i + 1][1] += f[i][1] * i3;
		g[i][n - 1] += f[i][n] * i3;
		g[i - 1][n] += f[i][n] * i3;
		g[i + 1][n] += f[i][n] * i3;
	}

	for (int i = 2; i < n; i ++)
		for (int j = 2; j < n; j ++) {
			g[i - 1][j] += f[i][j] * i4;
			g[i + 1][j] += f[i][j] * i4;
			g[i][j - 1] += f[i][j] * i4;
			g[i][j + 1] += f[i][j] * i4;
		}

	for (int i = 1; i <= n; i ++)
		for (int j = 1; j <= n; j ++)
			f[i][j] = g[i][j] % mod;
}

void solve (int n, int m) {
	if (n == 1)
		return puts("0"), void();

	for (int i = 1; i <= n; i ++)
		for (int j = 1; j <= n; j ++)
			p[i][j] = 1;

	for (int x = 1; x <= n; x ++)
		for (int y = 1; y <= n; y ++) {
			for (int i = 1; i <= n; i ++)
				for (int j = 1; j <= n; j ++)
					f[i][j] = 0;
			f[x][y] = 1;
			for (int t = 1; t <= m; t ++) trans(n);
			for (int i = 1; i <= n; i ++)
				for (int j = 1; j <= n; j ++)
					(p[i][j] *= mod + 1 - f[i][j]) %= mod;
		}

	ll ans = 0;
	for (int i = 1; i <= n; i ++)
		for (int j = 1; j <= n; j ++)
			ans += p[i][j];
	printf("%lld\n", ans % mod);
}

int main () {
#ifdef PE
	solve(30, 50);
	// 330.721154
#else
	int T = read;
	while (T --) {
		int n = read, m = read;
		solve(n, m);
	}
#endif
}
