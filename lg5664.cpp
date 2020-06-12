/*
 * Since g++10 is released, some characters is not valid inside #if 0 :(
 * So, why not using clang++? :D

 * Date:
    2020.06.12

 * Solution:
    注意到超过一半的食材至多只有一个，容易想到容斥，计算不合法的方案数，枚举超过一半的那
一个食材，然后设计 DP f[i][j][k] 表示前 i 行选了 j 个该食材和 k 个其他食材，但是复杂度是
O(mn^3) 的。一个注意到最后能贡献到答案的状态是 i = n, k > j ，每次转移的系数只与 i 有关，
那么对于 j, k 并不需要关心它们具体的值，只需要关心它们的差值，这样便可优化到 O(mn^2) 。

 * Digression:
    去年 CSP 完全没想到这个很自然很简单的状态优化，现在重新做了一遍，虽然是想到了，但还
是想了很久，讲道理这个优化实在是挺自然的，技不如人。

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

const int maxn = 105, maxm = 2005, mod = 998244353;
int a[maxn][maxm], b[maxn];
ll f[maxn][maxn << 1];

int main () {
	int n = read, m = read;
	for (int i = 1; i <= n; i ++)
		for (int j = 1; j <= m; j ++)
			if ((b[i] += a[i][j] = read) >= mod)
				b[i] -= mod;
	ll ans = 1;
	for (int i = 1; i <= n; i ++)
		(ans *= b[i] + 1) %= mod;
	-- ans;

	for (int x = 1; x <= m; x ++) {
		f[0][maxn] = 1;
		for (int i = 1; i <= n; i ++)
			for (int j = maxn - i; j <= maxn + i; j ++)
				f[i][j] = (f[i - 1][j] + f[i - 1][j - 1] * a[i][x] +
						f[i - 1][j + 1] * (b[i] + mod - a[i][x])) % mod;
		for (int j = maxn + 1; j <= maxn + n; j ++)
			ans -= f[n][j];
	}

	ans %= mod;
	if (ans < 0) ans += mod;
	printf("%lld\n", ans);
}
