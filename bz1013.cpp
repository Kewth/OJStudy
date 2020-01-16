#if 0
2020.01.15

设 n 个变量 x[i] 表示球心第 i 维坐标。
令设 y = sum(x[i]^2) - R^2 ，那么球上每个点就是关于这 n + 1 个变量的线性方程。
高斯消元即可。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator double () { double x; return scanf("%lf", &x), x; }
} read;

const int maxn = 15;
const double eps = 1e-10;
double ma[maxn][maxn];

int main() {
	int n = int(read) + 1;

	for(int i = 1; i <= n; i ++) {
		for(int j = 1; j < n; j ++) {
			double x = read;
			ma[i][j] = 2 * x;
			ma[i][n + 1] += x * x;
		}
		ma[i][n] = -1;
	}

	for(int i = 1; i <= n; i ++) {
		if(-eps < ma[i][i] and ma[i][i] < eps) {
			for(int j = i + 1; j <= n; j ++)
				if(ma[j][i] < -eps or ma[j][i] > eps) {
					std::swap(ma[i], ma[j]);
					break;
				}
		}
		for(int j = i + 1; j <= n; j ++) {
			double x = ma[j][i] / ma[i][i];
			for(int k = i; k <= n + 1; k ++)
				ma[j][k] -= ma[i][k] * x;
		}
	}

	for(int i = n; i; i --)
		for(int j = 1; j < i; j ++) {
			double x = ma[j][i] / ma[i][i];
			ma[j][i] -= ma[i][i] * x;
			ma[j][n + 1] -= ma[i][n + 1] * x;
		}

	for(int i = 1; i < n; i ++)
		printf("%.3lf ", ma[i][n + 1] / ma[i][i]);
	puts("");
}
