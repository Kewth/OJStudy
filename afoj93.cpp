#if 0
2019.08.19

一个 Naive 的 DP 想法是设 f[i][j] 表示 i 个点深度为 j 的概率，
这个转移依赖每个深度的点数，复杂度会退化到 O(n!) 。

考虑差分掉，设 f[i][j] 表示 i 个点深度不超过 j 的概率。
转移的话枚举根的第一个子树的大小 k ，f[i][j] += f[k][j - 1] * f[i - k][j] * g[i][k] 。
其中需要 g 辅助转移，g[i][k] 代表 i 个点有 k 个点在根的第一个子树的概率。
g 的转移则枚举最后一个点有没有被加进根的第一个子树。
#endif
#include <cstdio>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;

inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 202;
lolong f[maxn][maxn], g[maxn][maxn];
int mod;

lolong power(lolong x, int k) {
	if(k < 0) k += mod - 1;
	lolong res = 1;
	while(k) {
		if(k & 1) (res *= x) %= mod;
		(x *= x) %= mod;
		k >>= 1;
	}
	return res;
}

int main() {
	int n = input();
	mod = input();

	g[1][0] = 1;
	g[2][1] = 1;

	for(int i = 3; i <= n; i ++)
		for(int j = 1; j < n; j ++)
			g[i][j] =
				(g[i - 1][j - 1] * (j - 1) + g[i - 1][j] * (i - j - 1)) % mod *
				power(i - 1, -1) % mod;

	/* debug("%lld %lld\n", g[3][2], g[3][1]); */

	for(int i = 0; i <= n; i ++)
		f[1][i] = 1;

	for(int i = 2; i <= n; i ++) {
		for(int j = 1; j <= i; j ++) {
			for(int k = 1; k < i; k ++)
				f[i][j] += f[k][j - 1] * f[i - k][j] % mod * g[i][k] % mod;
			f[i][j] %= mod;
		}
		for(int j = i + 1; j <= n; j ++)
			f[i][j] = f[i][j - 1];
	}

	lolong ans = 0;
	for(int i = 1; i <= n; i ++)
		ans += i * (f[n][i] - f[n][i - 1] + mod) % mod;
	ans %= mod;

	printf("%lld\n", ans);
}
