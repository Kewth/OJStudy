#if 0
2019.08.27

考虑计算每个数 x 对最终答案的贡献，枚举出现次数 y ，若 x 出现 y 次的方案数为 z ，
那么贡献： x^m * y * z 。
考虑求出每个 g[x][y] = z ，
利用简单容斥，求出 x 出现至少 y 次的方案数减去至少 y + 1 次的方案数。

设 f[i][j] 表示用 i 个数凑出和为 j 的方案数。
比较清奇的 O(1) 转移是考虑对当前集合新加一个 1 或者给所有数加 1 。
那么对应的 x 出现至少 y 次的方案数就是 f[K - y][n - x * y] 。
#endif
#include <cstdio>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;

inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 5050, mod = 1000000007;
lolong f[maxn][maxn];
lolong tmp[maxn];

lolong power(lolong x, int k) {
	if(k < 0)
		k += mod - 1;
	lolong res = 1;
	while(k) {
		if(k & 1) (res *= x) %= mod;
		(x *= x) %= mod;
		k >>= 1;
	}
	return res;
}

int main() {
	int n = input(), K = input(), m = input();

	f[0][0] = 1;
	for(int i = 1; i <= K; i ++)
		for(int j = 1; j <= n; j ++) {
			f[i][j] = f[i - 1][j - 1];
			if(j - i >= 0)
				f[i][j] += f[i][j - i];
			f[i][j] %= mod;
			/* debug("%d %d : %lld\n", i, j, f[i][j]); */
		}

	lolong ans = 0;
	for(int i = 1; i <= n; i ++) {
		lolong now = 0;
		/* debug("%d : %lld\n", i, now), fflush(stderr); */
		for(int j = 1; j <= n / i; j ++)
			tmp[j] = j <= K ? f[K - j][n - i * j] : 0;
		tmp[n / i + 1] = 0;
		for(int j = 1; j <= n / i; j ++)
			now += j * (tmp[j] - tmp[j + 1] + mod) % mod;
		now %= mod;
		(ans += now * power(i, m)) %= mod;
		/* debug("%d : %lld\n", i, now); */
	}

	printf("%lld\n", ans);
}
