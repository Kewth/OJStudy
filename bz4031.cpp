#if 0
2019.09.27

矩阵树定理模板，将每个格子看做一个节点即可。
麻烦的在于求行列式的时候不能像高斯消元那样直接除，而要辗转相除。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;

inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 12, mod = 1000000000;
char map[maxn][maxn];
int id[maxn][maxn];
lolong ma[maxn * maxn][maxn * maxn];

int main() {
	int n = input(), m = input();
	for(int i = 1; i <= n; i ++)
		scanf("%s", map[i] + 1);

	int p = 0;
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= m; j ++)
			if(map[i][j] == '.') {
				id[i][j] = ++ p;

				if(map[i - 1][j] == '.') {
					int tp = id[i - 1][j];
					ma[p][p] ++;
					ma[tp][tp] ++;
					ma[p][tp] --;
					ma[tp][p] --;
				}

				if(map[i][j - 1] == '.') {
					int tp = id[i][j - 1];
					ma[p][p] ++;
					ma[tp][tp] ++;
					ma[p][tp] --;
					ma[tp][p] --;
				}
			}

	p --;
	lolong ans = 1;

	/* for(int i = 1; i <= p; i ++) { */
	/* 	for(int j = 1; j <= p; j ++) */
	/* 		debug(" %d", ma[i][j]); */
	/* 	debug("\n"); */
	/* } */

	for(int i = 1; i <= p; i ++)
		for(int j = 1; j <= p; j ++)
			ma[i][j] += mod;

	for(int i = 1; i <= p; i ++) {
		for(int j = i + 1; j <= p; j ++) {
			while(ma[j][i]) {
				lolong d = ma[i][i] / ma[j][i];
				for(int k = i; k <= p; k ++)
					(ma[i][k] += mod - ma[j][k] * d % mod) %= mod;
				std::swap(ma[i], ma[j]);
				ans *= -1;
			}
		}
	}

	ans += mod;
	for(int i = 1; i <= p; i ++)
		(ans *= ma[i][i] % mod + mod) %= mod;

	printf("%lld\n", ans);
}
