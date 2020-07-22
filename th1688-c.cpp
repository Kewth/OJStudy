/*
 * Author: Kewth

 * Date:
  2020.07.22

 * Solution:
 * 一般图最大匹配，优化建图

  不难发现问题可以转换为一般图最大匹配，一个组本质上就是给若干个点两两连边。这样一来
边数是 O(n^2) 级别，直接带花树跑不过。

  考虑到两两连边往往很有性质，不妨着手考虑如何对于一个组优化建图。

  也不知道怎么想到的，反正就是对于一个 k 个点的组，如果 k 是偶数，就新建 k 个辅助点，
这些辅助点连成一个环且有 k/2 个匹配，然后把组里的点连接到环上相邻两个点。这样一来，
组里的任意两个点都能通过这个辅助环找到一条増广路，效果等价于完全图中这两个点之间匹配。
至于 k 是奇数，建 k + 1 个辅助点即可。这样边数就是线性的，可以应用带花树。

 * Digression:

 * CopyRight:
          ▁▃▄▄▄▃▃▃▃▄▶
        ▗▇▀▔    ▔▔▔▔
       ▄▛   ▃▅━━■▄▂
      ▟▊   ▐▘     ▀▙
     ▟▜▌   ▐▖   ▋  ▐▍
    ▟▘ ▜   ▝▀▇▆●▘  ▐▌
  ▗▟▘   ▜▃       ▁▅▛
  ▔▀▼▅▄▃▃██▅▄▄▄▅■▀▔
        ▔▔▔▔▔▔
 */

#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

static struct {
    inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 9005;
std::vector<int> G[maxn];
int tmp[maxn];
int col[maxn], pre[maxn], bas[maxn];
int match[maxn];
std::queue<int> q;

inline void add (int u, int v) {
	G[u].push_back(v);
	G[v].push_back(u);
}

int find (int x) { return bas[x] == x ? x : bas[x] = find(bas[x]); }

int getbase (int x, int y) {
	static int mark[maxn], mp;
	++ mp;
	while (1) {
		if (!x) std::swap(x, y);
		x = find(x);
		if (mark[x] == mp) return x;
		mark[x] = mp;
		x = pre[x];
		std::swap(x, y);
	}
}

void blossom (int x, int z, int rt) {
	while (find(x) != rt) {
		int y = match[x];
		if (col[y] == 1) col[y] = 0, q.push(y);
		pre[y] = z;
		bas[x] = bas[y] = rt; // XXX: 第一次打漏掉了
		z = y;
		x = pre[x];
	}
}

bool bfs (int s, int n) {
	q = std::queue<int>();
	q.push(s);
	std::fill(col, col + n + 1, -1);
	std::fill(pre, pre + n + 1, 0);
	for (int i = 1; i <= n; i ++) bas[i] = i;
	col[s] = 0; // XXX: 第一次打漏掉了
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		for (int v : G[u])
			if (col[v] == -1) {
				if (!match[v]) {
					for (int x = u, y = v; x; x = pre[x]) {
						match[y] = x;
						std::swap(match[x], y);
					}
					return 1;
				}
				col[v] = 1;
				col[match[v]] = 0;
				pre[match[v]] = u;
				q.push(match[v]);
			} else if (col[v] == 0 and find(u) != find(v)) {
				int base = getbase(u, v);
				blossom(u, v, base);
				blossom(v, u, base);
			}
	}
	return 0;
}

int main () {
	while (1) {
		int n = read, m = read, np = n;
		if (n == 0 and m == 0) break;

		for (int u = 1; u <= n; u ++) G[u].clear();

		for (int i = 1; i <= m; i ++) {
			int tp = read;
			for (int j = 1; j <= tp; j ++) tmp[j] = read;
			if (tp <= 4) {
				for (int j = 1; j <= tp; j ++)
					for (int k = 1; k < j; k ++)
						add(tmp[j], tmp[k]);
				continue;
			}
			int p = tp + (tp & 1);
			for (int j = 1; j <= p; j ++) G[np + j].clear();
			for (int j = 2; j <= p; j ++) add(np + j, np + j - 1);
			add(np + 1, np + p);
			for (int j = 1; j <= tp; j ++) {
				add(tmp[j], np + j);
				add(tmp[j], j == p ? np + 1 : np + j + 1);
			}
			for (int j = 1; j <= p; j += 2) {
				match[np + j] = np + j + 1;
				match[np + j + 1] = np + j;
			}
			np += p;
		}

		std::fill(match, match + n + 1, 0);

		int ans = 0;
		for (int u = 1; u <= n; u ++)
			if (!match[u])
				ans += bfs(u, np);

		printf("%d\n", ans);
	}
}
