#if 0
2019.08.02

大力数位 DP ，设 f[i][2][2][2] 表示考虑后 i 位，
是否分别需要满足：x 小于 n 、y 小于 m 、(x ^ y) 大于 k 的所有异或和，
g[i][2][2][2] 表示该情况下的方案数。
注意细节取模。
#endif
#include <cstdio>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;
inline lolong input() { lolong x; scanf("%lld", &x); return x; }

const int maxn = 64;
lolong f[maxn][2][2][2], g[maxn][2][2][2];

int main() {
	int t = input();
	// for(int a = 0; a < 2; a ++)
		// for(int b = 0; b < 2; b ++)
			// for(int c = 0; c < 2; c ++)
				// g[0][a][b][c] = 1;
	g[0][0][0][0] = 1;
	while(t --) {
		lolong n = input(), m = input(), k = input(), p = input();
		for(int i = 1; i < maxn; i ++)
			for(int a = 0; a < 2; a ++)
				for(int b = 0; b < 2; b ++)
					for(int c = 0; c < 2; c ++)
						f[i][a][b][c] = g[i][a][b][c] = 0;
		for(int i = 0; i < maxn - 1; i ++) {
			for(int x = 0; x < 2; x ++)
				for(int y = 0; y < 2; y ++) {
					int aa = x <= (n >> i & 1), bb = y <= (m >> i & 1),
						cc = (x ^ y) >= (k >> i & 1);
					for(int a = 0; a <= aa; a ++)
						for(int b = 0; b <= bb; b ++)
							for(int c = 0; c <= cc; c ++) {
								int toa = a && x == (n >> i & 1);
								int tob = b && y == (m >> i & 1);
								int toc = c && (x ^ y) == (k >> i & 1);
								f[i + 1][a][b][c] +=
									(lolong(x ^ y) << i) % p * g[i][toa][tob][toc]
									+ f[i][toa][tob][toc];
								g[i + 1][a][b][c] += g[i][toa][tob][toc];
							}
				}
			for(int a = 0; a < 2; a ++)
				for(int b = 0; b < 2; b ++)
					for(int c = 0; c < 2; c ++) {
						f[i + 1][a][b][c] %= p;
						g[i + 1][a][b][c] %= p;
					}
		}
#if 0
		for(int i = 1; i < maxn; i ++)
			debug("%lld\n", (f[i][1][1][1] - k % p * g[maxn - 1][1][1][1] % p + p) % p);
		for(int i = 1; i < maxn; i ++)
			for(int a = 0; a < 2; a ++)
				for(int b = 0; b < 2; b ++)
					for(int c = 0; c < 2; c ++)
						debug("%d, %d, %d, %d: %lld, %lld\n",
								i, a, b, c, f[i][a][b][c], g[i][a][b][c]);
#endif
		printf("%lld\n", (f[maxn - 1][1][1][1] - k % p * g[maxn - 1][1][1][1] % p + p) % p);
	}
}

