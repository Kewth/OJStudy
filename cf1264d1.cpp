#if 0
2020.03.23

考虑如何简单地求一个括号序列的权值。
首先端点的括号如果是向外的，肯定没有贡献，删除直到两个端点的括号向内，
此时将端点两个括号匹配，然后计算内部权值加一即为整个括号序列的权值，证明略。
那么一个 O(n^2) 的区间 DP 就呼之欲出了。
#endif
#include <cstdio>
#include <cstring>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

const int maxn = 2020, mod = 998244353;
char s[maxn];
ll f[maxn][maxn][2][2], g[maxn][maxn][2][2];

int main () {
	scanf("%s", s + 2);
	int n = int(strlen(s + 2));
	s[1] = ')';
	s[1 + n + 1] = '(';
	n += 2;
	char t[2] = {'(', ')'};
	for (int l = n; l; l --) {
		g[l][l - 1][0][0] = 1;
		for (int p = 0; p < 2; p ++)
			if (s[l] != t[!p])
				g[l][l][p][p] = 1;
		for (int r = l + 1; r <= n; r ++)
			for (int S = 0; S < 16; S ++) {
				int p = S >> 0 & 1, q = S >> 1 & 1;
				int x = S >> 2 & 1, y = S >> 3 & 1;
				int ld = p == 1 or q == 1;
				int rd = p == 0 or q == 0;
				if (s[l] != t[!p] and s[r] != t[!q] and
						(ld or x == p) and (rd or y == q)) {
					(f[l][r][p][q] += f[l + ld][r - rd][x][y] +
					 (p == 0 and q == 1) * g[l + ld][r - rd][x][y]) %= mod;
					(g[l][r][p][q] += g[l + ld][r - rd][x][y]) %= mod;
				}
			}
	}
	printf("%lld\n", f[1][n][1][0]);

/* 	for (int l = n; l; l --) */
/* 		for (int r = l + 1; r <= n; r ++) */
/* 			for (int p = 0; p < 2; p ++) */
/* 				for (int q = 0; q < 2; q ++) */
/* 					if (g[l][r][p][q]) */
/* 						debug("fg[%d-%d][%d,%d] = %lld %lld\n", */
/* 								l, r, p, q, f[l][r][p][q], g[l][r][p][q]); */
}
