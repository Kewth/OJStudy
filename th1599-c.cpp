#if 0
2019.06.18

设 f[u][i][j] 表示从 u 点开始，s 匹配到 i ，t 匹配到 j 时的期望步数。
转移有环，但第三维的转移 j 只会到 j 或 j + 1 。
按 j 分层，同层有环高斯消元，不同层直接转移。

nm 高斯消元要判无解的题都 tm 毒瘤题，做你 mm。
操你大爷，挂题解上的那几个满分代码我随便拍几组 n=3 的随机数据都可以 hack ，
老子随机数据拍出来没错然后交上去就使劲 WA ，沃日那些个标程哪来这么牛逼？
50 分，再改这题我是孙子。
#endif
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#ifdef DEBUG
# define debug(...) fprintf(stderr, __VA_ARGS__)
#else
# define debug(...)
#endif

inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 21, maxk = 26, maxs = 11, maxt = 21;
const double eps = 1e-5;
double f[maxn][maxs][maxt];
int trans[maxn][maxk], du[maxn];
char s[10], t[50];
double matrix[maxn * maxs][maxn * maxs];

inline void clear(int x, int n) {
	for(int i = 1; i <= n; i ++)
		matrix[x][i] = 0;
}

inline void solve(int n) {
	debug("slove\n");
	for(int i = 0; i < n; i ++) {
		for(int j = 0; j <= n; j ++)
			debug(" % 2.2lf", matrix[i][j]);
		debug("\n");
	}
	for(int i = 0; i < n; i ++) {
		for(int j = 0; j <= n; j ++)
			if(std::isnan(matrix[i][j]) or std::isinf(matrix[i][j]))
				matrix[i][i] = 0;
		if(std::abs(matrix[i][i]) < eps) {
			clear(i, n);
			for(int k = 0; k < n; k ++)
				if(std::abs(matrix[k][i]) > eps)
					clear(k, n);
		}
		else {
			for(int j = 0; j <= n; j ++)
				if(i != j)
					matrix[i][j] /= matrix[i][i];
			matrix[i][i] /= matrix[i][i];
			for(int k = 0; k < n; k ++)
				if(k != i) {
					for(int j = 0; j <= n; j ++)
						if(j != i)
							matrix[k][j] -= matrix[i][j] * matrix[k][i];
					matrix[k][i] -= matrix[i][i] * matrix[k][i];
				}
		}
	}
	debug("to\n");
	for(int i = 0; i < n; i ++) {
		for(int j = 0; j <= n; j ++)
			debug(" % 2.2lf", matrix[i][j]);
		debug("\n");
	}
}

int main() {
	int n = input(), m = input();
	for(int u = 0; u < n; u ++)
		for(int c = 0; c < maxk; c ++)
			trans[u][c] = -1;
	for(int i = 1; i <= m; i ++) {
		int x = input() - 1, y = input() - 1, c = getchar();
		while(c == ' ') c = getchar();
		trans[x][c - 'a'] = y;
		du[x] ++;
	}
	scanf("%s%s", s, t);
	int lens = int(strlen(s)), lent = int(strlen(t));
	for(int j = lent - 1; j >= 0; j --) {
		// init matrix
		for(int i = 0; i <= n * lens; i ++)
			for(int k = 0; k <= n * lens; k ++)
				matrix[i][k] = 0;
		// get matrix
		for(int u = 0; u < n; u ++) {
			for(int i = 0; i < lens; i ++) {
				matrix[u * lens + i][n * lens] = du[u];
				matrix[u * lens + i][u * lens + i] = du[u];
				for(int c = 0; c < maxk; c ++)
					if(trans[u][c] != -1) {
						int v = trans[u][c];
						int toi = (c + 'a' == s[i]) ? i + 1 :
							(c + 'a' == s[0]);
						int toj = (c + 'a' == t[j]) ? j + 1 : j;
						debug("%d, %d -> %d, %d\n", i, j, toi, toj);
						if(toj == j + 1)
							matrix[u * lens + i][n * lens]
								+= f[v][toi][toj];
						else if(toi < lens and toj < lent)
							matrix[u * lens + i][v * lens + toi] --;
					}
			}
		}
		// solve matrix
		solve(n * lens);
		for(int u = 0; u < n; u ++)
			for(int i = 0; i < lens; i ++)
				f[u][i][j] = matrix[u * lens + i][n * lens]
					/ matrix[u * lens + i][u * lens + i];
	}
	if(std::isnan(f[0][0][0]) or std::isinf(f[0][0][0])
			or f[0][0][0] < eps or f[0][0][0] > 1e6)
		puts("-1");
	else
		printf("%.3lf\n", f[0][0][0]);
}
