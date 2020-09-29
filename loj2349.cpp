/*
 * Author: Kewth

 * Date:
  2020.09.19

 * Solution:
  把横着的可行串和竖着的可行串都看做点，把相斥的两个串连边，那么要求的就是最大独立集。
容易发现只有横竖有边，图是二分图。另外可以发现连边只在同一对角线上的点发生。
  根据二分图中最大独立集 = 点数 - 最大匹配，在每个对角线上求个最大匹配即可，图很特殊，
可以贪心求匹配。

 * Digression:

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

const int maxn = 3030;
char s[maxn][maxn];
bool a[maxn][maxn], b[maxn][maxn];

int main () {
	int n = read, m = read, ans = 0;
	for (int i = 1; i <= n; i ++)
		scanf("%s", s[i] + 1);

	for (int i = 1; i <= n; i ++)
		for (int j = 1; j <= m; j ++) {
			a[i][j] = s[i][j] == 'R' and s[i + 1][j] == 'G' and s[i + 2][j] == 'W';
			b[i][j] = s[i][j] == 'R' and s[i][j + 1] == 'G' and s[i][j + 2] == 'W';
			ans += a[i][j] + b[i][j];
		}

	for (int x = 2; x <= n + m; x ++)
		for (int i = std::max(1, x - m), j = x - i; i <= n and j >= 1; i ++, j --)
			if (b[i][j]) {
				if (i > 2 and a[i - 2][j + 2]) a[i - 2][j + 2] = 0, -- ans;
				else if (a[i - 1][j + 1]) a[i - 1][j + 1] = 0, -- ans;
				else if (a[i][j]) a[i][j] = 0, -- ans;
			}

	printf("%d\n", ans);
}
