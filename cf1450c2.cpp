/*
 * Author: Kewth

 * Date:
  2020.12.19

 * Solution:
  考虑把格点三染色，使得每连续三个格点都恰好有三种颜色，这样一来只需要把颜色 a 全部换成 X ，
颜色 b 全部换成 O ，颜色 c 的格点无论如何整张网格都是合法的。于是相当于把 k 个有效格点放入
三个不同的盒子里，只需用一个盒子的代价就能使整张网格合法，那必然有一个盒子的大小不超过 k/3 。
  染色方案容易想到把 (i, j) 的颜色定义为 (i + j) mod 3 。

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

const int maxn = 305;
char s[maxn][maxn];

int main () {
	int T = read;
	while (T --) {
		int n = read;
		for (int i = 1; i <= n; i ++)
			scanf("%s", s[i] + 1);
		int t[3] = {0, 0, 0};
		for (int i = 1; i <= n; i ++)
			for (int j = 1; j <= n; j ++)
				if (s[i][j] == 'X')
					++ t[(i + j) % 3];
				else if (s[i][j] == 'O')
					++ t[(i + j + 1) % 3];
		int min = std::min({t[0], t[1], t[2]});
		for (int x = 0; x < 3; x ++)
			if (t[x] == min) {
				for (int i = 1; i <= n; i ++) {
					for (int j = 1; j <= n; j ++)
						if (s[i][j] == 'X' and (i + j) % 3 == x)
							s[i][j] = 'O';
						else if (s[i][j] == 'O' and (i + j + 1) % 3 == x)
							s[i][j] = 'X';
					s[i][n + 1] = 0;
					puts(s[i] + 1);
				}
				break;
			}
	}
}
