#if 0
2019.10.17

首先有一个十分优秀的性质就是最终每种局面的发生概率相等。
其中两个局面不同当且仅当存在一个人在两种局面中获得的宝石不等。
那么只需要统计所有本质不同的局面的前 r 大的和以及所有本质不同的局面数量即可。
设前者为 F[n][m] 后者为 G[n][m] ，转移枚举有 k 个人至少有一颗宝石即可。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;

inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 505;
double C[maxn][maxn], F[maxn][maxn], G[maxn][maxn];

int main() {
	int n = input(), m = input(), r = input();

	for(int i = 0; i <= n; i ++) {
		C[i][0] = 1;
		for(int j = 1; j <= i; j ++)
			C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
	}

	for(int i = 0; i <= n; i ++) {
		G[i][0] = 1;
		for(int j = 1; j <= m; j ++)
			for(int k = 0; k <= i and k <= j; k ++)
				G[i][j] += C[i][k] * G[k][j - k];
	}

	for(int i = 0; i <= n; i ++) {
		for(int j = 1; j <= m; j ++)
			for(int k = 0; k <= i and k <= j; k ++)
				F[i][j] += C[i][k] * (F[k][j - k] + std::min(r, k) * G[k][j - k]);
	}

	printf("%lf\n", F[n][m] / G[n][m] + r);
}
