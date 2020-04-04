#pragma GCC optimize(2)
#if 0
2020.02.25

暴力枚举路径上第 2, 4, 6, 8 个点。
然后对于第 i 个和第 i + 2 个点，需要计算走恰好两条边的最短路。
朴素的想法是再枚举合法的第 i + 1 个点将最短路取 min 。
这样的复杂度是 O(n^5) ，难以接受。
事实上可以发现如果第 i 个点是 x ，第 i + 2 个点是 y ，
其他点对 x 到 y 之间最短路的影响很小，
预先将 x 到 y 所有可能的中间点排序，然后再找最短路。
这样的复杂度是 O(n^4 m) 。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef std::pair<int, int> par;
struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	inline operator char () { char x[3]; return scanf("%s", x), *x; }
} read;

const int maxn = 85, maxm = 12, inf = 1000000005;
bool color[maxn];
int path[maxm];
int dis[maxn][maxn];
par d[maxn][maxn][maxn];

int ans = inf;
void fuck(int y, int n, int m) {
	if(y == m) {
		for(int i = 0; i < m; i += 2)
			color[path[i]] = 1;

		int sum = 0;
		for(int i = 2; i <= m; i += 2) {
			int x = path[i - 2], y = path[i];
			int p = 1;
			while(color[d[x][y][p].second])
				++ p;
			sum += d[x][y][p].first;
			if(sum >= inf) break;
		}
		ans = std::min(ans, sum);

		for(int i = 0; i < m; i += 2)
			color[path[i]] = 0;
		return;
	}

	for(int i = 1; i <= n; i ++) {
		path[y] = i;
		fuck(y + 2, n, m);
	}
}

int main() {
	int n = read, m = read;
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= n; j ++)
			dis[i][j] = read;

	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= n; j ++) {
			for(int k = 1; k <= n; k ++)
				d[i][j][k] = par(dis[i][k] + dis[k][j], k);
			d[i][j][n + 1] = par(inf, 0);
			std::sort(d[i][j] + 1, d[i][j] + n + 1);
		}

	path[0] = path[m] = 1;
	fuck(2, n, m);
	printf("%d\n", ans);
}
