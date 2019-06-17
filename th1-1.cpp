#if 0
2019.06.17

题意： 求所有 n(400) 个点的无向连通图的 1-2 最短路的和。

求 1-2 最短路和求任意 1-x 最短路是一样的，
因此求出 1 到所有点的最短路和后除以 n - 1 即答案。
把图按 1 的距离分层，那么同层随便连边，每个点必须向上一层连边。
设 f[i][j] 表示选 i 个点，最后一层 j 个点的所有图的 1 到所有点的最短路和。
转移枚举上一层的点数 k ，设 g[i][j] 表示...所有的图的数量辅助转移即可。
中间还要预处理 h[k][j] 表示上一层 k 个这一层 j 个时这层与上层的连边方案。
但是由于状态内没有层数，无法得知最后一层的深度，
但是当前这一层会让后面所有点的深度加 1 ，把这个算进去即可。
#endif
#include <cstdio>

typedef long long lolong;
inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 404;
lolong f[maxn][maxn], g[maxn][maxn], h[maxn][maxn], c[maxn][maxn];

inline lolong power(lolong x, int k, int mod) {
	lolong res = 1;
	if(k < 0) k += mod - 1;
	while(k) {
		if(k & 1) (res *= x) %= mod;
		(x *= x) %= mod;
		k >>= 1;
	}
	return res;
}

int main() {
	int n = input(), mod = input();
	for(int i = 0; i <= n; i ++) {
		c[i][0] = 1;
		for(int j = 1; j <= i; j ++)
			c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % mod;
	}
	f[1][1] = n - 1;
	g[1][1] = 1;
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= n; j ++)
			h[i][j] = power(2, j * (j - 1) >> 1, mod)
					* power(power(2, i, mod) - 1, j, mod) % mod;
	for(int i = 1; i <= n; i ++) {
		for(int j = 1; j <= i; j ++) {
			for(int k = 1; k <= i - j; k ++) {
				lolong now = h[k][j] * c[n - i + j][j] % mod;
				(g[i][j] += g[i - j][k] * now) %= mod;
				(f[i][j] +=
				 (f[i - j][k] + (n - i) * g[i - j][k] % mod) * now) %= mod;
			}
		}
	}
	/* for(int i = 1; i <= n; i ++) { */
	/* 	for(int j = 1; j <= i; j ++) */
	/* 		printf(" %d", f[i][j]); */
	/* 	puts(""); */
	/* } */
	/* for(int i = 1; i <= n; i ++) { */
	/* 	for(int j = 1; j <= i; j ++) */
	/* 		printf(" %d", g[i][j]); */
	/* 	puts(""); */
	/* } */
	lolong ans = 0;
	for(int i = 1; i <= n; i ++)
		(ans += f[n][i]) %= mod;
	(ans *= power(n - 1, -1, mod)) %= mod;
	printf("%lld\n", ans);
}
