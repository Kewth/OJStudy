/*
 * Author: Kewth

 * Date:
  2020.11.17

 * Solution:
 * DP 设计，维护凸包，问题转换，分离贡献计数

  In blog.

 * Digression:
  大师，我悟了！

 * CopyRight:
   __  __                  __   __
  |  |/  |.-----.--.--.--.|  |_|  |--.
  |     < |  -__|  |  |  ||   _|     |
  |__|\__||_____|________||____|__|__|

 */

#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

static struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 55, mod = 1000000007;
int B[maxn][maxn];
int tmp[maxn * maxn], tp;
ll po[maxn], f[maxn][maxn * maxn], tot[maxn * maxn];

int main () {
	int N = read, C = read, K = read;
	for (int i = 1; i <= N; i ++) {
		for (int j = 1; j <= K; j ++)
			tmp[++ tp] = B[i][j] = read;
		std::sort(B[i] + 1, B[i] + K + 1);
	}
	std::sort(tmp + 1, tmp + tp + 1);
	tp = int(std::unique(tmp + 1, tmp + tp + 1) - tmp - 1);

	po[0] = 1;
	for (int i = 1; i <= N; i ++)
		po[i] = po[i - 1] * K % mod;

	for (int x = 1; x <= tp; x ++) {
		for (int i = 1; i <= N; i ++)
			for (int j = 0; j <= C; j ++)
				f[i][j] = 0;
		f[0][0] = 1;
		for (int i = 1; i <= N; i ++) {
			int sm = int(std::lower_bound(B[i] + 1, B[i] + K + 1, tmp[x]) - B[i] - 1);
			for (int j = 0; j <= C; j ++) {
				int k = std::max(0, j - 1);
				(f[i][k] += f[i - 1][j] * sm) %= mod;
				(tot[x] += f[i - 1][j] * sm % mod * po[N - i]) %= mod;
				k = j + 1;
				if (k <= C)
					(tot[x] += f[i - 1][j] * (K - sm) % mod * po[N - i]) %= mod;
				else
					k = C;
				(f[i][k] += f[i - 1][j] * (K - sm)) %= mod;
			}
			/* for (int j = 0; j <= C; j ++) */
			/* 	debug(" %lld", f[i][j]); */
			/* debug("\n"); */
		}
		/* debug("%d : %lld\n", tmp[x], tot[x]); */
	}

	ll ans = 0;
	for (int i = 1; i <= N; i ++)
		for (int j = 1; j <= K; j ++)
			ans += B[i][j];
	ans = ans % mod * po[N - 1] % mod;
	tot[tp + 1] = po[N] * N % mod;
	for (int x = 1; x <= tp; x ++)
		(ans += (mod - tmp[x]) * (tot[x + 1] + mod - tot[x])) %= mod;
	printf("%lld\n", ans);
}
