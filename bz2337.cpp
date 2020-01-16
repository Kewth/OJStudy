#if 0
2020.01.16

拆位考虑，然后设 X[i] 表示从 i 出发到 n 的路径异或为 1 的概率。
可以根据边列出 X 的方程，高斯消元即可。
（一开始设的是 X[i] 表示从 1 出发到 i 的概率，然而发现这样路径根本不会结束）
#endif
#include <cstdio>
#include <algorithm>
#include <vector>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef long double ld;
typedef std::pair<int, int> par;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 105, maxk = 30;
ld ma[maxn << 1][maxn << 1];
std::vector<par> G[maxn];

void guass(int n) {
	for(int i = 1; i <= n; i ++)
		for(int j = i + 1; j <= n; j ++) {
			ld x = ma[j][i] / ma[i][i];
			for(int k = i; k <= n + 1; k ++)
				ma[j][k] -= ma[i][k] * x;
		}
	for(int i = n; i; i --)
		for(int j = 1; j < i; j ++) {
			ld x = ma[j][i] / ma[i][i];
			ma[j][i] -= ma[i][i] * x;
			ma[j][n + 1] -= ma[i][n + 1] * x;
		}
}

int main() {
	int n = read, m = read;
	while(m --) {
		int u = read, v = read, w = read;
		G[u].push_back(par(v, w));
		if(u != v)
			G[v].push_back(par(u, w));
	}

	ld ans = 0;
	for(int k = 0; k < maxk; k ++) {
		for(int i = 1; i <= n; i ++)
			for(int j = 1; j <= n + 1; j ++)
				ma[i][j] = 0;

		for(int u = 1; u < n; u ++) {
			ma[u][u] = - int(G[u].size());
			for(par e : G[u])
				if(e.second >> k & 1) {
					ma[u][n + 1] -= 1;
					ma[u][e.first] -= 1;
				}
				else
					ma[u][e.first] += 1;
		}
		ma[n][n] = 1;

		guass(n);
		/* debug("%Lf\n", ma[1][n + 1] / ma[1][1]); */

		ans += (1 << k) * ma[1][n + 1] / ma[1][1];
	}

	printf("%.3Lf\n", ans);
}
