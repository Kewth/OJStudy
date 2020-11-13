/*
 * Author: Kewth

 * Date:
  2020.11.05

 * Solution:
  In blog.

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

const int maxn = 303;
bool map[maxn][maxn], tmp[maxn], tar[maxn][maxn];
char s[maxn];

bool solve (int n, int m) {
	if (n <= 2 or m <= 2) return 0;
	int R = 0, C = 0;

	for (int i = 1; i <= n; i ++)
		for (int j = 1; j <= m; j ++) {
			bool t = tar[i][j] ^ map[i][j];
			for (int x = 0; x < 3 and x < i; x ++)
				for (int y = 0; y < 3 and y < j; y ++)
					t ^= tar[i - x][j - y];
			tar[i][j] = t;
		}

	for (int i = n; i; i --)
		if (tar[i][m - 1] or tar[i][m])
			R = i;
	for (int j = m; j; j --)
		if (tar[n - 1][j] or tar[n][j])
			C = j;

	/* for (int i = 1; i <= n; i ++) { */
	/* 	for (int j = 1; j <= m; j ++) */
	/* 		debug("%d", tar[i][j]); */
	/* 	debug("\n"); */
	/* } */
	/* debug("%d %d\n", R, C); */

	if ((R and !C) or (!R and C)) return 0;
	if (R and C) map[R][C] ^= 1;

	for (int i = 1; i <= n; i ++)
		for (int j = 1; j <= m; j ++) {
			bool t = tar[i][j] ^ map[i][j];
			for (int x = 0; x < 3 and x < i; x ++)
				for (int y = 0; y < 3 and y < j; y ++)
					t ^= tar[i - x][j - y];
			tar[i][j] = t;
		}

	for (int i = 1; i <= n; i ++)
		for (int j = 1; j <= m; j ++)
			if (tar[i][j] and (i > n - 2 or j > m - 2))
				return map[R][C] ^= 1, 0;

	return 1;
}

int main () {
	int m = read, n = read;
	for (int i = 1; i <= n; i ++) {
		scanf("%s", s + 1);
		for (int j = 1; j <= m; j ++)
			map[i][j] = s[j] == '#';
	}

	while (solve(n, m)) {
		/* for (int i = 1; i <= n; i ++) { */
		/* 	for (int j = 1; j <= m; j ++) */
		/* 		debug("%d", tar[i][j]); */
		/* 	debug("\n"); */
		/* } */
		int lx = n, rx = 1, ly = m, ry = 1;
		for (int i = 1; i <= n; i ++)
			for (int j = 1; j <= m; j ++)
				if (tar[i][j]) {
					lx = std::min(lx, i);
					rx = std::max(rx, i);
					ly = std::min(ly, j);
					ry = std::max(ry, j);
				}
		n = rx - lx + 1, m = ry - ly + 1;
		for (int i = 1; i <= n; i ++)
			for (int j = 1; j <= m; j ++)
				map[i][j] = tar[lx + i - 1][ly + j - 1];
	}

	/* printf("%d %d\n", n, m); */
	for (int i = 1; i <= n; i ++) {
		for (int j = 1; j <= m; j ++)
			putchar(map[i][j] ? '#' : '.');
		puts("");
	}
}
