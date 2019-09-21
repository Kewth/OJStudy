#if 0
2019.09.20

朴素 DP 设 f[l][r][len][x] 表示区间 l, r 内选长度为 len 的子序列模 101 为 x 的方案数。
朴素转移枚举左右的端点 O(n) 转移。

101 这个数不是随便选的，由于 101 * 99 = 9999 = 10000 - 1 ，
使得 10000 在模 101 意义下为 1 ，也就有 10000k 同余于 k 。

状态里要有长度的原因是确定在两边加数对值产生的影响，
具体地，在值为 x 的数两边加 y ，值会变成 (10^len)y + 10x + y ，
根据上面 101 的性质，该值模 101 同余于 (10^(len % 4))y + 10x + y ，
那么长度这一维只需维护模 4 意义下的值即可。

优化转移，区间 [l, r] 中的数如果没同时用到 l, r ，就一定在 [l, r) 和 (l, r] 之一中。
但是直接加起来会算重，可以简单容斥： [l, r] = [l, r) + (l, r] - (l, r) ，
那么只需再处理同时用到 l, r 的转移即可。
#endif
#include <cstdio>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;
inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 202, mod = 1000000007;
char s[maxn];
lolong f[maxn][maxn][4][101];
lolong g[maxn][4][101];
int power10[10];

int main() {
	power10[0] = 1;
	for(int i = 1; i < 10; i ++)
		power10[i] = power10[i - 1] * 10 % 101;

	int n = input();
	scanf("%s", s + 1);

	for(int l = n; l; l --) {
		f[l][l - 1][0][0] = 1;
		f[l][l][0][0] = 1;
		f[l][l][1][s[l] - '0'] = 1;

		for(int r = l + 1; r <= n; r ++) {
			for(int le = 0; le < 4; le ++)
				for(int x = 0; x < 101; x ++)
					f[l][r][le][x] =
						f[l][r - 1][le][x] + f[l + 1][r][le][x] -
						f[l + 1][r - 1][le][x] + mod;

			int y = s[r] - '0';
			if(s[l] == s[r])
				for(int le = 0; le < 4; le ++)
					for(int x = 0; x < 101; x ++)
						f[l][r][(le + 2) % 4]
							[(10 * x + y + y * power10[le + 1]) % 101] +=
							f[l + 1][r - 1][le][x];

			for(int le = 0; le < 4; le ++)
				for(int x = 0; x < 101; x ++) {
					f[l][r][le][x] %= mod;
					/* if(f[l][r][le][x]) */
					/* 	debug("f[%d][%d][%d][%d] = %lld\n", */
					/* 			l, r, le, x, f[l][r][le][x]); */
				}
		}
	}

	lolong ans = mod - 1;
	for(int le = 0; le < 4; le ++)
		ans += f[1][n][le][0];

	printf("%lld\n", ans % mod);
}
