/*
 * Author: Kewth

 * Date:
  2020.11.14

 * Solution:
  转换模型，该问题等价于随机选择一个点的排列，然后依次在排列上每次找到一个未被删除的点
并删除该点和该点能到达的点，求删除次数的期望。
  转换后就可以独立计算每个点的贡献，预处理个传递闭包就可以计算一个点在多少排列中是有贡
献的了。

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
typedef long double ld;

static struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 105;
char s[maxn];
bool to[maxn][maxn];

int main () {
	int n = read;
	for (int i = 1; i <= n; i ++) {
		scanf("%s", s + 1);
		for (int j = 1; j <= n; j ++)
			to[i][j] = s[j] == '1';
		to[i][i] = 1;
	}
	for (int k = 1; k <= n; k ++)
		for (int i = 1; i <= n; i ++)
			for (int j = 1; j <= n; j ++)
				to[i][j] |= to[i][k] & to[k][j];
	ld ans = 0;
	for (int i = 1; i <= n; i ++) {
		int x = 0;
		for (int j = 1; j <= n; j ++)
			x += to[j][i];
		for (int l = x; l <= n; l ++) {
			ld now = 1;
			for (int k = 1; k <= x; k ++) {
				now *= l - x + k;
				now /= n - x + k;
			}
			now /= l;
			ans += now;
		}
	}
	printf("%.10Lf\n", ans);
}
