#if 0
2020.05.18

  考虑随着操作进行维护 f[i][j] 表示最终序列中 P[i] > P[j] 的概率。那么对于一次操作 (x, y) ，
其能影响的 f[i][j] 要满足 i = x, i = y, j = x, j = y 中的至少一个，这样的数量是 O(n) 的，暴
力修改每个值即可。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 3030, mod = 1000000007;
int a[maxn];
ll f[maxn][maxn];

int main () {
	int n = read, q = read;
	for (int i = 1; i <= n; i ++) a[i] = read;
	for (int i = 1; i <= n; i ++)
		for (int j = 1; j <= n; j ++)
			f[i][j] = a[i] > a[j];

	ll coe = 1, i2 = (mod + 1) >> 1;
	while (q --) {
		int x = read, y = read;
		for (int i = 1; i <= n; i ++)
			if (i != x and i != y)
				f[i][y] = f[i][x] = i2 * (f[i][x] + f[i][y]) % mod;
		for (int i = 1; i <= n; i ++)
			if (i != x and i != y)
				f[y][i] = f[x][i] = i2 * (f[x][i] + f[y][i]) % mod;
		f[y][x] = f[x][y] = i2 * (f[x][y] + f[y][x]) % mod;
		(coe <<= 1) %= mod;
	}

	/* for (int i = 1; i <= n; i ++) { */
	/* 	for (int j = 1; j <= n; j ++) */
	/* 		debug(" %lld", f[i][j]); */
	/* 	debug("\n"); */
	/* } */

	ll sum = 0;
	for (int i = 1; i <= n; i ++)
		for (int j = i + 1; j <= n; j ++)
			sum += f[i][j];
	sum %= mod;
	printf("%lld\n", sum * coe % mod);
}
