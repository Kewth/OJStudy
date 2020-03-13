#if 0
2020.03.12

维护一个扫描线，计算折线在扫描线以下的长度和。
DP 设 f[i][j][k][c] 表示：
扫描线扫完了第 i 个数（排序后），当前扫描线以下的折线分成了 j 段，
这些段的折线长度和为 k ，最后的折线端点已经扫过了 c 个，这样的排列数。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	inline operator char () { char x[3]; return scanf("%s", x), *x; }
} read;

const int maxn = 105, maxm = 1005, mod = 1000000007;
int a[maxn];
ll f[2][maxn][maxm][4];

int main() {
	int n = read, m = read;
	for(int i = 1; i <= n; i ++)
		a[i] = read;
	std::sort(a + 1, a + n + 1);

	f[1][1][0][0] = 1;
	f[1][1][0][1] = 2;
	f[1][1][0][2] = 1;

	for(int i = 2; i <= n; i ++) {
		int o = i & 1, h = a[i] - a[i - 1];

		for(int j = 1; j <= i; j ++)
			for(int x = 0; x <= m; x ++)
				for(int c = 0; c < 3; c ++)
					f[o][j][x][c] = 0;

		for(int j = 1; j < i; j ++)
			for(int x = 0; x <= m; x ++)
				for(int c = 0; c < 3; c ++) {
					int y = x + (j * 2 - c) * h;
					ll F = f[!o][j][x][c];
					if(y <= m) {
						(f[o][j + 1][y][c] += F * (j + 1 - c)) %= mod;
						(f[o][j + 1][y][c + 1] += F * (2 - c)) %= mod;
						(f[o][j][y][c] += F * (j * 2 - c)) %= mod;
						(f[o][j][y][c + 1] += F * (2 - c)) %= mod;
						(f[o][j - 1][y][c] += F * (j - 1)) %= mod;
					}
				}

#if 0
		for(int j = 1; j <= i; j ++)
			for(int x = 0; x <= m; x ++)
				for(int c = 0; c < 3; c ++)
					if(f[o][j][x][c])
						debug("f[%d][%d][%d][%d] = %d\n",
								i, j, x, c, f[o][j][x][c]);
#endif
	}

	ll ans = 0;
	for(int x = 0; x <= m; x ++)
		ans += f[n & 1][1][x][2];
	ans %= mod;
	printf("%lld\n", ans);

}
