#if 0
2020.04.29

  设 p(i, j) 表示走到了第 i 个位置，绿灯过了 j 秒这个状态。那么一个状态可以转移的其他状
态只有最多两个，即向左或者向右走碰到的第一个状态。
  在这些状态中跑最短路即可，边权只有 0 和 1 （绿灯是否结束） ，可以 bfs 求最短路。
#endif
#include <cstdio>
#include <algorithm>
#include <queue>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef std::pair<int, int> par;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
} read;

const int maxn = 10005, maxt = 1005;
int f[maxn][maxt];
bool vis[maxn][maxt];
int pos[maxn];

int main () {
	int len = read, n = read;
	for (int i = 1; i <= n; i ++)
		read(pos[i]);
	std::sort(pos + 1, pos + n + 1); // what fuck weak pretests
	int g = read, r = read;

	std::queue<par> q, qq;
	q.push(par(1, 0));
	vis[1][0] = 1;

	while (!q.empty() or !qq.empty()) {
		if (q.empty())
			/* debug("---\n"), */
			std::swap(q, qq);
		int p = q.front().first, x = q.front().second;
		q.pop();
		if (x == g) {
			if (!vis[p][0]) {
				vis[p][0] = 1;
				f[p][0] = f[p][x] + 1;
				qq.push(par(p, 0));
			}
			continue;
		}
		/* debug("%d %d %d\n", p, x, f[p][x]); */
		if (p > 1 and x + pos[p] - pos[p - 1] <= g) {
			int y = x + pos[p] - pos[p - 1];
			if (!vis[p - 1][y]) {
				/* debug("-> %d %d\n", p - 1, y); */
				f[p - 1][y] = f[p][x];
				vis[p - 1][y] = 1;
				q.push(par(p - 1, y));
			}
		}
		if (p < n and x + pos[p + 1] - pos[p] <= g) {
			int y = x + pos[p + 1] - pos[p];
			if (!vis[p + 1][y]) {
				/* debug("-> %d %d\n", p + 1, y); */
				f[p + 1][y] = f[p][x];
				vis[p + 1][y] = 1;
				q.push(par(p + 1, y));
			}
		}
	}

	ll ans = 1000000000000000000;
	for (int i = 1; i <= n; i ++)
		for (int j = 0; j < g; j ++)
			if (vis[i][j]) {
				/* debug("%d %d %d\n", i, j, f[i][j]); */
				int k = j + len - pos[i];
				if (k <= g)
					ans = std::min(ans, 1ll * f[i][j] * (g + r) + k);
			}

	printf("%lld\n", ans == 1000000000000000000 ? -1 : ans);
}
