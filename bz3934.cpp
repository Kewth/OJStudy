#if 0
2019.09.11

轮廓线 DP 真的是打一下玩一年。

设 f[i][j][a][b][c][e] 表示当前考虑到 (i, j) 中，
轮廓线上三个向下的插头的位置分别为 a, b, c ，
已经完成了已经正在做的 L 有 e 个，的方案数。
实际上还有向右的插头，设 g[i][j][a][b][c][e] 表示上述情况的基础上，
(i, j) 的位置还有一个向右的插头，的方案数。
转移的话枚举插头位置考虑是否接上去，在考虑是否在当前位置开始做一个 L 。
另外，为了防止算重，规定 a <= b <= c 。

踩了两个坑：
1) 从 (i, m) 转移到 (i + 1, 1) 的时候有些特殊，下一个点的坐标打错。
2) n, m 搞混，a, b, c 应该枚举到 m 而不是 n 。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;

inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 32;
lolong f[2][maxn][maxn][maxn][4];
lolong g[2][maxn][maxn][maxn][4];
bool shit[maxn][maxn];

inline lolong &F(int o, int a, int b, int c, int e) {
	if(a > b)
		std::swap(a, b);
	if(b > c)
		std::swap(b, c);
	if(a > b)
		std::swap(a, b);
	/* debug("%d %d %d\n", a, b, c); */
	return f[o][a][b][c][e];
}

int main() {
	int n = input(), m = input();

	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= m; j ++) {
			int c = getchar();
			while(c != '.' and c != '#')
				c = getchar();
			shit[i][j] = c == '.';
		}

	int o = 0;

	if(shit[1][1])
		f[0][0][0][1][1] = 1;
	f[0][0][0][0][0] = 1;

	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= m; j ++) {
			if(i == n and j == m)
				break;

			int nj = 1 + (j % m);
			int ni = nj == 1 ? i + 1 : i;

			for(int a = 0; a <= m; a ++)
				for(int b = a; b <= m; b ++)
					for(int c = b; c <= m; c ++)
						for(int e = bool(a) + bool(b) + bool(c); e <= 3; e ++) {
							if(not f[o][a][b][c][e] and not g[o][a][b][c][e])
								continue;

							if(nj == a) {
								if(shit[ni][nj]) {
									f[o ^ 1][a][b][c][e] +=
										f[o][a][b][c][e];
									g[o ^ 1][0][b][c][e] +=
										f[o][a][b][c][e];
								}
							}

							else if(nj == b) {
								if(shit[ni][nj]) {
									f[o ^ 1][a][b][c][e] +=
										f[o][a][b][c][e];
									g[o ^ 1][0][a][c][e] +=
										f[o][a][b][c][e];
								}
							}

							else if(nj == c) {
								if(shit[ni][nj]) {
									f[o ^ 1][a][b][c][e] +=
										f[o][a][b][c][e];
									g[o ^ 1][0][a][b][e] +=
										f[o][a][b][c][e];
								}
							}

							else {
								if(shit[ni][nj]) {
									if(j < m) {
										g[o ^ 1][a][b][c][e] +=
											g[o][a][b][c][e];
										f[o ^ 1][a][b][c][e] +=
											g[o][a][b][c][e];
									}

									if(e < 3) {
										if(not a) {
											F(o ^ 1, nj, b, c, e + 1) +=
												f[o][a][b][c][e];
										}
									}
								}

								f[o ^ 1][a][b][c][e] +=
									f[o][a][b][c][e];
							}
						}

			for(int a = 0; a <= m; a ++)
				for(int b = a; b <= m; b ++)
					for(int c = b; c <= m; c ++)
						for(int e = bool(a) + bool(b) + bool(c); e <= 3; e ++) {
							/* if(f[o][a][b][c][e]) */
							/* 	debug("f(%d,%d|%d.%d.%d|%d)=%lld\n", */
							/* 			i, j, a, b, c, e, f[o][a][b][c][e]); */
							/* if(g[o][a][b][c][e]) */
							/* 	debug("g(%d,%d|%d.%d.%d|%d)=%lld\n", */
							/* 			i, j, a, b, c, e, g[o][a][b][c][e]); */
							f[o][a][b][c][e] = 0;
							g[o][a][b][c][e] = 0;
						}
			o ^= 1;
		}

	printf("%lld\n", f[o][0][0][0][3]);
}
