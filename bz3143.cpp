#if 0
2019.04.04

如果知道每条边的期望经过次数，那么可以将其排序并贪心地编号得出答案。
但是边的期望经过次数并不好求，考虑求点的期望经过次数，易得：
f[u] = \sum_{u-v, v!=n} f[v] / d[v] ，
f[1] = 1 + \sum_{u-v, v!=n} f[v] / d[v] ，
其中 f[u] 表示 u 点的期望经过次数，d[u] 表示 u 点的度数。
高斯消元即可。

woc 我竟然一次打对了高斯消元！
#endif
#include <bits/stdc++.h>

typedef std::pair<int, int> par;
const int maxn = 505;
double M[maxn][maxn];
int d[maxn];
std::vector<int> G[maxn];
double f[maxn * maxn];

int main() {
	std::ios::sync_with_stdio(false);
	int n, m;
	std::cin >> n >> m;
	std::vector<par> edges;
	for(int i = 1; i <= m; i ++) {
		int u, v;
		std::cin >> u >> v;
		G[u].push_back(v);
		G[v].push_back(u);
		d[u] ++;
		d[v] ++;
		edges.push_back(par(u, v));
	}
	for(int u = 1; u < n; u ++) {
		M[u][u] = -1;
		for(int v : G[u])
			M[u][v] = double(1) / d[v];
		M[u][n] = 0;
	}
	M[1][n + 1] = -1;
	M[n][n] = 1;
	M[n][n + 1] = 1;
	for(int x = 1; x <= n; x ++) {
		double Mxx = M[x][x];
		for(int j = 1; j <= n + 1; j ++)
			M[x][j] /= Mxx;
		for(int i = 1; i <= n; i ++)
			if(i != x) {
				double Mix = M[i][x];
				for(int j = 1; j <= n + 1; j ++)
					M[i][j] -= M[x][j] * Mix;
			}
	}
	for(size_t i = 0; i < edges.size(); i ++) {
		int u = edges[i].first, v = edges[i].second;
		if(u != n)
			f[i] += M[u][n + 1] / d[u];
		if(v != n)
			f[i] += M[v][n + 1] / d[v];
	}
	std::sort(f, f + m);
	double ans = 0;
	/* for(int i = 0; i < m; i ++) */
	/* 	std::cerr << f[i] << ' '; */
	/* std::cerr << std::endl; */
	for(int i = 0; i < m; i ++)
		ans += f[i] * (m - i);
	std::cout << std::fixed << std::setprecision(3) << ans << std::endl;
}
