#if 0
2019.09.27

矩阵树定理另一种形式，统计有向图的叶向生成树。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 255, mod = 10007;
int M[maxn][maxn];

int main() {
	int n = input(), m = input();

	while(m --) {
		int b = input(), a = input();
		M[b][b] ++;
		M[a][b] --;
	}

	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= n; j ++)
			M[i][j] += mod;

	int ans = 1;

	for(int i = 2; i <= n; i ++)
		for(int j = i + 1; j <= n; j ++) {
			while(M[j][i]) {
				int d = M[i][i] / M[j][i];
				for(int k = i; k <= n; k ++)
					(M[i][k] += mod - d * M[j][k] % mod) %= mod;
				std::swap(M[i], M[j]);
				ans *= -1;
			}
		}

	ans += mod;
	for(int i = 2; i <= n; i ++)
		(ans *= M[i][i]) %= mod;

	printf("%d\n", ans);
}
