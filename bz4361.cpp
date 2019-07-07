#if 0
2019.07.07

计算长度为 i 的不降序列，
考虑多算的序列，当且仅当是从 i + 1 的不降序列（不一定合法）转过来时不合法。
因为一个不降序列之后随便怎么删数都会是不降序列。
那么 ans[i] = f[i] * (n - i)! - f[i + 1] * (n - i - 1)! * (i + 1) ，
其中 ans[i] 表示长度为 i 的合法序列数，f[i] 表示长度为 i 的所有不降序列数。
问题转换为求上述 f ，DP 设 g[i][j] 表示以 i 结尾长度为 j 的不降序列数。
用树状数组 + 离散化处理前缀和优化转移。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;
inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 2020, mod = 1000000007;
int a[maxn], tmp[maxn];
int f[maxn], g[maxn][maxn];
int bit[maxn][maxn];
lolong jie[maxn];

inline int lowbit(int k) { return k & -k; }

int main() {
	int n = input();
	for(int i = 1; i <= n; i ++)
		tmp[i] = a[i] = input();
	std::sort(tmp + 1, tmp + n + 1);
	for(int i = 1; i <= n; i ++)
		a[i] = int(std::lower_bound(tmp + 1, tmp + n + 1, a[i]) - tmp);
	/* for(int i = 1; i <= n; i ++) */
	/* 	debug(" %d", a[i]); */
	/* debug("\n"); */
	for(int k = 1; k <= n; k += lowbit(k))
		bit[k][0] ++;
	for(int i = 1; i <= n; i ++) {
		for(int j = 1; j <= i; j ++)
			for(int k = a[i]; k; k -= lowbit(k))
				(g[i][j] += bit[k][j - 1]) %= mod;
		for(int j = 1; j <= i; j ++)
			for(int k = a[i]; k <= n; k += lowbit(k))
				(bit[k][j] += g[i][j]) %= mod;
	}
	for(int j = 1; j <= n; j ++)
		for(int i = 1; i <= n; i ++)
			(f[j] += g[i][j]) %= mod;
	lolong ans = 0;
	jie[0] = 1;
	for(int i = 1; i <= n; i ++)
		jie[i] = jie[i - 1] * i % mod;
	/* for(int i = 1; i <= n; i ++) */
	/* 	debug("%d ", f[i]); */
	/* debug("\n"); */
	for(int i = 1; i <= n; i ++)
		(ans += f[i] * jie[n - i]
		 - f[i + 1] * jie[n - i - 1] % mod * (i + 1)) %= mod;
	(ans += mod) %= mod;
	printf("%lld\n", ans);
}
