#if 0
2020.05.12

  对于一个点，如果存在相邻同色的点，那么它就会一直交替变换颜色。而一个不存在相邻同色的
点，如果其相邻的点在某一时刻 t 颜色改变，那么从时刻 t + 1 开始该点就会一直有相邻同色的
点，进而一直交替变换颜色。
  设 f[x][y] 表示 (x, y) 开始交替变换颜色的时间，可以发现 f 实际上就是最短路的模型，bfs
求解即可。
#endif
#include <cstdio>
#include <queue>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef std::pair<int, int> par;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
} read;

const int maxn = 1010;
char map[maxn][maxn];
ll cg[maxn][maxn];

int main () {
	int n = read, m = read, q = read;
	for (int i = 1; i <= n; i ++)
		scanf("%s", map[i] + 1);

	bool get = 0;
	for (int i = 2; i <= n; i ++)
		for (int j = 1; j <= m; j ++)
			if (map[i][j] == map[i - 1][j])
				get = cg[i][j] = cg[i - 1][j] = 1;
	for (int i = 1; i <= n; i ++)
		for (int j = 2; j <= m; j ++)
			if (map[i][j] == map[i][j - 1])
				get = cg[i][j] = cg[i][j - 1] = 1;

	if (get) {
		std::queue<par> qu;
		for (int i = 1; i <= n; i ++)
			for (int j = 1; j <= m; j ++)
				if (cg[i][j])
					qu.push(par(i, j));
		int di[] = {-1, 0, 1, 0}, dj[] = {0, -1, 0, 1};
		while (!qu.empty()) {
			int i = qu.front().first, j = qu.front().second;
			qu.pop();
			if (i == 0 or j == 0 or i > n or j > m) continue;
			for (int k = 0; k < 4; k ++) {
				int ni = i + di[k], nj = j + dj[k];
				if (!cg[ni][nj]) {
					cg[ni][nj] = cg[i][j] + 1;
					qu.push(par(ni, nj));
				}
			}
		}
	}
	else
		for (int i = 1; i <= n; i ++)
			for (int j = 1; j <= m; j ++)
				cg[i][j] = 2000000000000000000;

	while (q --) {
		int i = read, j = read;
		ll t = read;
		if (t < cg[i][j] or (t - cg[i][j]) % 2)
			printf("%c\n", map[i][j]);
		else
			printf("%c\n", '0' + '1' - map[i][j]);
	}
	return 0;
}
