#if 0
2019.07.20

数位 DP ，设 f[i][j][k] 表示从大到小考虑前 i 位，数位和与乘积数位和的差为 j ，
i 位以后向 i 位进位 k 的方案数。
对于 R 的限制典型地一位一位判断是否到最高位统计方案即可。

但是看了看最短代码，学到了新操作。
因为要保证 x 小于等于 R ，
f 加一维 0/1 表示是否 i 位之后的值小于等于 R i 位之后的值，这样可以直接输出答案。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;
inline lolong input() { lolong x; scanf("%lld", &x); return x; }

const int maxlen = 23, maxv = maxlen * 9, maxm = 1005;
lolong f[maxlen][maxv << 1][maxm][2];
int a[maxlen], ap = 0;

int main() {
	lolong n = input();
	int m = int(input());
	while(n) {
		a[ap ++] = n % 10;
		n /= 10;
	}
	for(int i = 0; i * 2 < maxlen; i ++)
		std::swap(a[i], a[maxlen - i - 1]);
	/* for(int i = 0; i < maxlen; i ++) */
	/* 	debug(" %d", a[i]); */
	/* debug("\n"); */
	f[maxlen - 1][maxv][0][0] = 1;
	f[maxlen - 1][maxv][0][1] = 1;
	for(int i = maxlen - 1; i; i --)
		for(int j = 0; j < maxv * 2; j ++)
			for(int k = 0; k <= m; k ++)
				for(int l = 0; l <= 9; l ++) {
					int nj = j - (l * m + k) % 10 + l;
					if(nj >= 0 and nj < maxv * 2) {
						/* if(l < a[i] and f[i][j][k][0]) */
						/* 	debug("%d %d %d 0 -%d-> %d %d %d 1\n", */
						/* 			i, j, k, l, i - 1, nj, (l * m + k) / 10); */
						f[i - 1][nj][(l * m + k) / 10][1]
							+= f[i][j][k][0] * (l < a[i]);
						/* if(f[i][j][k][0]) */
						/* 	debug("%d %d %d 0 -%d-> %d %d %d 0\n", */
						/* 			i, j, k, l, i - 1, nj, (l * m + k) / 10); */
						f[i - 1][nj][(l * m + k) / 10][0]
							+= f[i][j][k][0];
						/* if(l == a[i] and f[i][j][k][1]) */
						/* 	debug("%d %d %d 1 -%d-> %d %d %d 1\n", */
						/* 			i, j, k, l, i - 1, nj, (l * m + k) / 10); */
						f[i - 1][nj][(l * m + k) / 10][1]
							+= f[i][j][k][1] * (l == a[i]);
					}
				}
	printf("%lld\n", f[0][maxv][0][1] - 1);
}
