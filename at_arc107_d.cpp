/*
 * Author: Kewth

 * Date:
  2020.11.01

 * Solution:
  直接 DP 设 f[i][j] 表示 i 个数和为 j 的方案数。朴素转移枚举 1 的个数，前缀和优化
一波即可。

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

const int maxn = 3030, mod = 998244353;
ll f[maxn][maxn << 1];

int main () {
	int n = read, m = read;
	f[0][0] = 1;
	for (int i = 1; i <= n; i ++)
		for (int j = i; j; j --)
			f[i][j] = (f[i - 1][j - 1] + f[i][j << 1]) % mod;
	printf("%lld\n", f[n][m]);
}
