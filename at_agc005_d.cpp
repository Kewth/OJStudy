#if 0
2019.08.18

搞两排排列 a[i] = i 的排列，上下如果相差恰好为 k 则连 A 边，反之 B 边，连成一个完全二分图。
那么答案就是求在该二分图上选 B 边的最大匹配的方案数。
但是 B 边很多难以统计，如果能够转换为统计具有特殊性质的 A 边，问题就可能简化。
考虑容斥，设 g[i] 表示二分图上选最大匹配，其中至少 i 条 A 边的方案数。
那么只要能求出恰好 i 条 A 匹配的方案数，剩下的可以随便选，方案为 (n - i)! 。
A 边构成的子图是由若干条链组成的，把链拉出来排成一排，DP 统计。
设 f[i][j] 表示前 i 条边选 j 条匹配的方案数即可转移。
#endif
#include <cstdio>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;

inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 2020, mod = 924844033;

bool real[maxn << 1];
int f[maxn << 1][maxn];
lolong fac[maxn];

int main() {
	int n = input(), k = input();

	int p = 0;
	for(int i = 1; i <= k; i ++)
		for(int t = 0; t < 2; t ++)
			for(int j = i; j <= n; j += k)
				real[++ p] = j > i;

	/* for(int i = 1; i <= n * 2; i ++) */
	/* 	debug(" %d", real[i]); */
	/* debug("\n"); */

	f[0][0] = 1;
	for(int i = 1; i <= p; i ++) {
		for(int j = 0; j <= n; j ++)
			f[i][j] = f[i - 1][j];
		if(real[i])
			for(int j = 1; j <= n; j ++)
				(f[i][j] += f[i - 2][j - 1]) %= mod;
	}

	/* for(int i = 0; i <= n; i ++) */
	/* 	debug(" %d", f[n << 1][i]); */
	/* debug("\n"); */

	fac[0] = 1;
	for(int i = 1; i <= n; i ++)
		fac[i] = fac[i - 1] * i % mod;

	lolong ans = 0;
	for(int i = 0; i <= n; i ++)
		ans += fac[n - i] * f[n << 1][i] % mod * ((i & 1) ? -1 : 1);
	((ans %= mod) += mod) %= mod;

	printf("%lld\n", ans);
}
