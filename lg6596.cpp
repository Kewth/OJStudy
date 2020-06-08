/*
 * Since g++10 is released, some characters is not valid inside #if 0 :(
 * So, why not using clang++? :D

 * Date:
  2020.06.07

 * Solution:
  不妨计算 a[i] 表示恰好 i 条割边的联通图数量。可以发现如果钦定 i 条割边，图被划分为
i + 1 个边双，但是保证每个部分都是边双来计数比较困难，不妨降低限制为联通，也就是另外
设 b[i] 表示钦定 i 条割边，分成 i + 1 个联通块的连通图数量，那么 b 和 a 的关系显然是
可以用二项式反演表示的。
  如果把图划分为 k 个联通块，设它们的大小构成序列 {a} ，那么在这些联通块之间连割边的
方案数就是 n^{k-2} a[1] a[2] ... a[k] ，那么求 b[i] 就是把 n 个点划分为 i + 1 个联通
块的带权贡献和，设 h[i] 表示 i 个点的连通图个数，用个 O(n^3) 的 DP 不难求出 b 。
  而求 h 根据《城市规划》的式子直接 O(n^2) 求即可。

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
} read;

const int maxn = 305, mod = 1000000007;
ll C[maxn][maxn];
ll g[maxn], h[maxn];
ll f[maxn][maxn];
ll b[maxn];

inline ll power (ll x, int k) {
	if (k < 0) k += mod - 1;
	ll res = 1;
	while (k) {
		if (k & 1) (res *= x) %= mod;
		(x *= x) %= mod;
		k >>= 1;
	}
	return res;
}

int main () {
	int n = read, m = read;
	if (m >= n) m = n - 1;

	for (int i = 0; i <= n; i ++) {
		C[i][0] = 1;
		for (int j = 1; j <= i; j ++)
			C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod;
	}

	for (int i = 0; i <= n; i ++)
		g[i] = power(2, i * (i - 1) >> 1);
	for (int i = 1; i <= n; i ++) {
		h[i] = g[i];
		for (int j = 1; j < i; j ++)
			(h[i] += (mod - h[j]) * C[i - 1][j - 1] % mod * g[i - j]) %= mod;
	}

	f[0][0] = 1;
	for (int i = 1; i <= n; i ++)
		for (int j = 1; j <= i; j ++)
			for (int k = 1; k <= i; k ++)
				(f[i][j] += f[i - k][j - 1] * C[i - 1][k - 1] % mod *
				 h[k] % mod * k) %= mod;

	ll po = power(n, -1);
	for (int i = 1; i <= n; i ++) {
		b[i - 1] = f[n][i] * po % mod;
		(po *= n) %= mod;
	}

	/* for (int i = 0; i < n; i ++) */
	/* 	debug(" %lld", b[i]); */
	/* debug("\n"); */

	ll ans = 0;
	for (int i = 0; i <= m; i ++) {
		ll now = 0;
		for (int j = i; j < n; j ++)
			if ((j - i) & 1)
				(now += (mod - b[j]) * C[j][i]) %= mod;
			else
				(now += b[j] * C[j][i]) %= mod;
		/* debug("%lld\n", now); */
		ans += now;
	}
	ans %= mod;
	printf("%lld\n", ans);
}
