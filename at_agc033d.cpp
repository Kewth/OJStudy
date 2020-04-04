#if 0
2020.02.14

每次对半分，直到区域只剩 1x1 ，可以知道答案的上界是 O(logNM) 。

DP 设 f[k][x][l][r] 表示以 (x, l), (x, r) 为左上角和右上角，
区域的值不超过 k 最多能向下延伸几行。
转移有两种，一种是按行划分的情况，可以直接转移。
按列划分的情况比较棘手，暴力转移需要枚举划分方式，
也就是枚举 p : f[k][x][l][r] <- min(f[k-1][x][l][p], f[k-1][x][p+1][r])
但是不难发现后面的值随 p 的变化是个单峰函数，
并且最优的 p 随 r 的变化是个单调函数。
因此固定 k, x, l 时只需维护一个 p 即可。
#endif
#include <cstdio>
#include <algorithm>
#include <cstring>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	inline operator char () { char x[3]; return scanf("%s", x), *x; }
} read;

const int maxn = 190;
char s[maxn][maxn];
int f[maxn][maxn][maxn], g[maxn][maxn][maxn];

void chkmax(int &x, int y) {
	if(y > x) x = y;
}

int main() {
	int n = read, m = read;
	for(int i = 1; i <= n; i ++)
		scanf("%s", s[i] + 1);

	for(int x = n; x; x --)
		for(int l = 1; l <= m; l ++)
			for(int r = l; s[x][l] == s[x][r]; r ++)
				f[x][l][r] = 1 + (s[x][l] == s[x + 1][l] ?
						f[x + 1][l][r] : 0);

	int ans = 0;
	while(f[1][1][m] < n) {
		++ ans;
		std::swap(f, g);
		for(int x = 1; x <= n; x ++)
			for(int l = 1; l <= m; l ++) {
				int p = l;
				for(int r = l; r <= m; r ++) {
					int d = g[x][l][r];
					chkmax(f[x][l][r], d + g[x + d][l][r]);
					int now = std::min(g[x][l][p], g[x][p + 1][r]);
					int nxt = std::min(g[x][l][p + 1], g[x][p + 2][r]);
					while(p + 1 < r and now <= nxt) {
						++ p;
						now = nxt;
						nxt = std::min(g[x][l][p + 1], g[x][p + 2][r]);
					}
					chkmax(f[x][l][r], now);
				}
			}
	}

	printf("%d\n", ans);
}
