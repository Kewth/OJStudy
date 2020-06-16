/*
 * Since g++10 is released, some characters is not valid inside #if 0 :(
 * So, why not using clang++? :D

 * Date:
  2020.06.16

 * Solution:
  类似国际象棋一样把格子分为黑白两色，角落所在格子为黑。注意到用一个曼哈顿距离恰为 2
的询问就可以得到两个同色的格子的值是否相同，那么通过若干次询问就可以求出所有黑格子的
值。对于白格子，不妨钦定 a[1][2] = 0 ，然后通过询问求出所有白格子的值，一共 n^2 - 3
次询问，但是白格子的值不一定对，考虑通过不超过 3 次询问检验正确性。

  注意到主对角线上一定存在 i 满足 a[i][i] = 1 且 a[i + 2][i + 2] = 0 ，它们构成的 3x3
的子矩阵拿出来考虑，问题转换为 n = 3 ，那么只需要能对于 n = 3 确定任何一个白格子的值
就能最终得到答案。

  列出这个 3x3 的矩阵：

    1 a b
	c d e
	f g 0

  可以发现，如果 b != d 或者 a != c ，询问 (1, e) 就可以得到 e 的值，同理如果 d != f
或者 e != g ，询问 (c, 0) 就可以得到 c 的值，否则，矩阵可以简化为：

    1 x z
	x z y
	z y 0

  这个矩阵本质不同的询问实在不多，询问 (1, y) 和 (x, 0) ，有任意一个返回 1 就可以确定
y 或者 x ，否则，对于两个串 1xzy 和 xzy0 ，它们都不能是回文串，也就是说要满足：

    (x != z || y != 1) && (x != 0 || y != z)

  对 z 分类讨论，一定可以解出 x 或者 y 。

 * Digression:
  想偏了很久，缕清思路的话想法其实很自然。

 * CopyRight:
          ▁▃▄▄▄▃▃▃▃▄▶
        ▗▇▀▔    ▔▔▔▔
       ▄▛   ▃▅━━■▄▂
      ▟▊   ▐▘     ▀▙
     ▟▜▌   ▐▖   ▋  ▐▍
    ▟▘ ▜   ▝▀▇▆●▘  ▐▌
  ▗▟▘   ▜▃       ▁▅▛
  ▔▀▼▅▄▃▃██▅▄▄▄▅■▀▔
        ▔▔▔▔▔▔
 */

#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 55;
int a[maxn][maxn];

int query (int x1, int y1, int x2, int y2) {
	printf("? %d %d %d %d\n", x1, y1, x2, y2);
	fflush(stdout);
	return read;
}

bool check (int n) {
	for (int i = 3; i <= n; i ++)
		if (a[i][i] == 0 and a[i - 2][i - 2] == 1) {
			auto A = [i] (int x, int y) {
				return a[i - 3 + x][i - 3 + y];
			};
			auto q = [i] (int x1, int y1, int x2, int y2) {
				return query(i - 3 + x1, i - 3 + y1,
						i - 3 + x2, i - 3 + y2);
			};
			if (A(1, 2) != A(2, 1) or A(1, 3) != A(2, 2))
				return (A(1, 1) ^ q(1, 1, 2, 3) ^ 1) == A(2, 3);
			if (A(2, 2) != A(3, 1) or A(2, 3) != A(3, 2))
				return (A(3, 3) ^ q(2, 1, 3, 3) ^ 1) == A(2, 1);
			int x = q(1, 1, 2, 3), y = q(2, 1, 3, 3);
			if (x) return A(1, 1) == A(2, 3);
			if (y) return A(2, 1) == A(3, 3);
			if (A(2, 2) == 0) return A(1, 2) == 1;
			else return A(2, 3) == 0;
		}
	return 1; // impossible
}

int main () {
	int n = read;

	for (int i = 1; i <= n; i ++)
		for (int j = 1; j <= n; j ++)
		a[i][j] = -1;

	a[1][1] = 1;
	a[n][n] = 0;

	a[1][2] = 0; // a guess
	a[2][3] = a[1][2] ^ query(1, 2, 2, 3) ^ 1;
	a[2][1] = a[2][3] ^ query(2, 1, 2, 3) ^ 1;

	for (int j = 3; j <= n; j ++)
		a[1][j] = a[1][j - 2] ^ query(1, j - 2, 1, j) ^ 1;
	for (int i = 3; i <= n; i ++)
		a[i][1] = a[i - 2][1] ^ query(i - 2, 1, i, 1) ^ 1;
	for (int i = 2; i <= n; i ++)
		for (int j = 2; j <= n; j ++)
			if (a[i][j] == -1)
			a[i][j] = a[i - 1][j - 1] ^ query(i - 1, j - 1, i, j) ^ 1;

	if (!check(n))
		for (int i = 1; i <= n; i ++)
			for (int j = 1; j <= n; j ++)
				if ((i & 1) != (j & 1))
					a[i][j] ^= 1;

	puts("!");
	for (int i = 1; i <= n; i ++) {
		for (int j = 1; j <= n; j ++)
			putchar('0' + a[i][j]);
		puts("");
	}
	fflush(stdout);
}
