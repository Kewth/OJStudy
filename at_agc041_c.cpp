#if 0
2020.03.25

首先可以构造 3 的方案。
那么对于所有 n = 3k 的倍数的矩阵，只需要在对角线上的 k 个子矩阵放 3x3 的方案即可。
其次可以构造 4, 5, 6, 7 的方案，并且满足最后每行每列有 3 个不同的牌。
那么对于 n > 7 ，一定可以表示成 4, 5, 6, 7 的和，同样在对角线上放这些矩阵即可。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 1010;
char s[maxn][maxn];

void solve3 (int i, int j) {
	s[i][j] = s[i][j + 1] = s[i + 1][j + 2] = s[i + 2][j + 2] = 'e';
}

void solve2_a (int i, int j) {
	s[i][j] = s[i][j + 1] = 'a';
	s[i + 1][j] = s[i + 1][j + 1] = 'b';
}

void solve2_b (int i, int j) {
	s[i][j] = s[i + 1][j] = 'c';
	s[i][j + 1] = s[i + 1][j + 1] = 'd';
}

void solve_even (int i, int j, int k) {
	for (int l = 0; l < k; l ++)
		solve2_a(i + l * 2, j + l * 2);
	for (int l = 0; l < k - 1; l ++)
		solve2_b(i + l * 2 + 2, j + l * 2);
	solve2_b(i, j + k * 2 - 2);
}

void solve5 (int i, int j) {
	char t[10][10] = {
		".ijjl",
		"fi..l",
		"f.ppm",
		"hho.m",
		"ggonn",
	};
	for (int x = 0; x < 5; x ++)
		for (int y = 0; y < 5; y ++)
			s[i + x][j + y] = t[x][y];
}

void solve7 (int i, int j) {
	char t[10][10] = {
		"a...lmm",
		"a.nnl..",
		".b..jkk",
		".b..ji.",
		"ccd..i.",
		"..dgg.h",
		"eeff..h",
	};
	for (int x = 0; x < 7; x ++)
		for (int y = 0; y < 7; y ++)
			s[i + x][j + y] = t[x][y];
}

int main () {
	int n = read;
	for (int i = 1; i <= n; i ++)
		std::fill(s[i] + 1, s[i] + n + 1, '.');

	if (n == 2) return puts("-1"), 0;

	if (n == 5)
		solve5(1, 1);
	else if (n == 7)
		solve7(1, 1);
	else if (n % 3 == 0)
		for (int i = 1; i <= n; i += 3)
			solve3(i, i);
	else if (n % 2 == 0)
		solve_even(1, 1, n / 2);
	else {
		solve5(1, 1);
		solve_even(6, 6, (n - 5) / 2);
	}

	for (int i = 1; i <= n; i ++)
		puts(s[i] + 1);
}
