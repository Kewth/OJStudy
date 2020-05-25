#if 0
2020.05.24

  维护每个点的最短路 dis ，每次询问并删除一个点，就从该点开始 bfs 增广，遍历所有 dis 减小
的点，注意到 dis 的和初始是 O(n^3) 的，因此 dis 减小的次数是有保证的。
        ▁▃▄▄▄▃▃▃▃▄▶
      ▗▇▀▔    ▔▔▔▔
     ▄▛   ▃▅━━■▄▂
    ▟▊   ▐▘     ▀▙
   ▟▜▌   ▐▖   ▋  ▐▍
  ▟▘ ▜   ▝▀▇▆●▘  ▐▌
▗▟▘   ▜▃       ▁▅▛
▔▀▼▅▄▃▃██▅▄▄▄▅■▀▔   CopyRight :)
      ▔▔▔▔▔▔
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 505;
int val[maxn][maxn];
int dis[maxn][maxn];

void update (int x, int y, int d) {
	d += val[x][y];
	if (d >= dis[x][y]) return;
	dis[x][y] = d;
	update(x - 1, y, d);
	update(x + 1, y, d);
	update(x, y - 1, d);
	update(x, y + 1, d);
}

int main () {
	int n = read;

	for (int i = 1; i <= n; i ++)
		for (int j = 1; j <= n; j ++) {
			val[i][j] = 1;
			dis[i][j] = std::min({i, j, n - i + 1, n - j + 1});
		}

	int ans = 0;
	for (int i = 1; i <= n * n; i ++) {
		int p = read;
		int x = (p - 1) / n + 1, y = (p - 1) % n + 1;
		val[x][y] = 0;
		update(x, y, dis[x][y] - 1);
		ans += dis[x][y];
	}

	printf("%d\n", ans);
}
