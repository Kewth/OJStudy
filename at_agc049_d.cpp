/*
 * Author: Kewth

 * Date:
  2020.11.15

 * Solution:
 * 背包，前缀和优化

  先考虑如果限制 a 单调不减且 a[1] = 0 如何统计。差分后得到数组 b ，限制转换为 b 单调不
减且非负。二次差分得到数组 c ，c 的限制就仅仅是非负。c 的每一项对应一个数量无限物品，相
当于求把物品装满体积为 m 的背包的方案数。

  注意到物品的体积形如 1 + 2 + ... + s ，那么事实上有用的物品只有 O(m^0.5) 中，直接背包
DP 处理 f[i][j] 表示用前 i 种物品体积和为 j 的方案数。上述问题的答案就是 f[max][m] 。

  现在考虑原问题，注意到 a 可能先降后减，不妨枚举 a 最小的最小值位置 p 计算贡献。那么数
列划分为左右独立的两部分背包。O(m) 枚举一边背包的大小即可。注意到 p 也是不超过 O(m^0.5)
的，因此复杂度是有保证的。

 * Digression:
  怎么人均计数带师啊。。。

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

const int maxn = 100005, maxs = 450, mod = 1000000007;
const ll M = 1ll * mod * mod;
ll f[maxs][maxn], g[maxs][maxn];
int sum[maxs];

int main () {
	int n = read, m = read, s = 0;
	while (sum[s] + s + 1 <= m)
		++ s, sum[s] = sum[s - 1] + s;

	f[0][0] = 1;
	for (int i = 1; i <= s; i ++) {
		std::copy(f[i - 1], f[i - 1] + m + 1, f[i]);
		for (int j = sum[i]; j <= m; j ++)
			if ((f[i][j] += f[i][j - sum[i]]) >= mod)
				f[i][j] -= mod;
	}

	for (int i = 0; i <= s; i ++) {
		std::copy(f[i], f[i] + m + 1, g[i]);
		for (int j = n; j <= m; j ++)
			if ((g[i][j] += g[i][j - n]) >= mod)
				g[i][j] -= mod;
	}

	ll ans = 0;
	for (int p = 1; p <= n and p - 1 <= s; p ++)
		for (int x = sum[p - 1]; x <= m; x ++)
			if ((ans += f[p - 1][x - sum[p - 1]] *
						g[std::min(s, n - p)][m - x]) >= M)
				ans -= M;
	printf("%lld\n", ans % mod);
}
