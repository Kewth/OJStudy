#if 0
2019.06.27

一个位置 i 不满足条件当且仅当 a[i] | a[i - 1] 且 a[i] < a[i - 1] 。
那么连续的不满足条件的点最大是 log 个。
根据容斥原理，钦定一些点不满足条件，每个放点方案对答案的贡献是 -1^|S| ，
其中 S 是钦定的不满足条件的点的集合，其他点的合法性随意。
设 f[i][0/1] 表示 n = i 时，所有 |S| 为奇/偶的方案，
枚举最后一段连续的不满足条件的点的长度钦定之，预处理转移即可。

至于预处理转移，设 g[i][j] 表示转移的长度为 i （i - 1 个点被钦定） ，
这长度为 i 的区间中最大的数为 j 的系数（该数的合法性随意）。
那么枚举 j 的因子 k, g[i][j] += g[i - 1][k] 即可。
由于枚举因子的复杂度是根号，需要换成从 k 贡献到 j 的方式。
#endif
#include <cstdio>

typedef long long lolong;
inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 100005, maxl = 18, mod = 998244353;
lolong f[maxn][2];
lolong g[maxl][maxn];
lolong h[maxl];

int main() {
	int n = input(), m = input();
	for(int j = 1; j <= m; j ++)
		g[1][j] = 1;
	for(int i = 2; i < maxl; i ++)
		for(int k = 1; k <= m; k ++)
			for(int j = k + k; j <= m; j += k)
				(g[i][j] += g[i - 1][k]) %= mod;
	for(int i = 1; i < maxl; i ++)
		for(int j = 1; j <= m; j ++)
			(h[i] += g[i][j]) %= mod;
	f[0][0] = 1;
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= i and j < maxl; j ++) {
			(f[i][0] += h[j] * f[i - j][1 - (j & 1)] % mod) %= mod;
			(f[i][1] += h[j] * f[i - j][0 + (j & 1)] % mod) %= mod;
		}
	printf("%lld\n", (f[n][0] - f[n][1] + mod) % mod);
}
