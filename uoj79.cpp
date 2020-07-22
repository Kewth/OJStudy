/*
 * Author: Kewth

 * Date:
  2020.07.21

 * Solution:
  带花树模板。

 * Digression:
  感觉有不少细节，虽然不长但很难打，也可能只是我不太熟练。。。

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

const int maxn = 1005;
std::vector<int> G[maxn];
std::queue<int> q;
int col[maxn];
int match[maxn];
int pre[maxn];
int bas[maxn];

int find (int x) { return bas[x] == x ? x : bas[x] = find(bas[x]); }

int getbase (int x, int y) { // 学到许多，原来有不维护 deep 的暴力求 lca 方法。。。
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
		// XXX: 不能跳并查集？
		/* x = find(x); */
		int y = match[x];
		if (col[y] == 1) {
			col[y] = 0;
			q.push(y);
		}
		// XXX:
		// 这里 pre 可能已经有值，但在新的花中值会改变？
		// 相当于一个大花覆盖了一个小花，小花的一些点的 pre 本来只在小花内，但是要改成连大
		// 花的节点？
		pre[y] = z;
		/* debug(" pre %d -> %d\n", y, z); */
		bas[x] = bas[y] = rt;
		x = pre[x];
		z = y;
	}
}

int stack[maxn];
bool bfs (int s, int n) {
	std::fill(col, col + n + 1, -1);
	std::fill(pre, pre + n + 1, 0);
	for (int i = 1; i <= n; i ++) bas[i] = i;
	q = std::queue<int>();
	q.push(s);
	col[s] = 0;
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		for (int v : G[u])
			if (col[v] == -1) {
				if (!match[v]) {
					int sp = 0;
					for (int x = u, y = v; x; x = pre[x]) {
						stack[++ sp] = y, stack[++ sp] = x;
						match[y] = x;
						std::swap(match[x], y);
					}
					/* debug("find path:"); */
					/* while (sp) debug(" %d", stack[sp --]); */
					/* debug("\n"); */
					return 1;
				}
				/* debug("%d -> %d -> %d\n", u, v, match[v]); */
				pre[match[v]] = u;
				col[v] = 1;
				col[match[v]] = 0; // 一条匹配边的两个端点一定同时有色或同时无色
				q.push(match[v]);
			} else if (col[v] == 0 and find(u) != find(v)) {
				int base = getbase(u, v);
				/* debug("merge %d(%d) %d(%d) -> %d\n", u, find(u), v, find(v), base); */
				blossom(u, v, base);
				blossom(v, u, base);
			}
	}
	return 0;
}

int main () {
	int n = read, m = read;
	for (int i = 1; i <= m; i ++) {
		int u = read, v = read;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	int ans = 0;
	for (int u = 1; u <= n; u ++)
		if (!match[u])
			ans += bfs(u, n);
	printf("%d\n", ans);
	for (int u = 1; u <= n; u ++)
		printf("%d ", match[u]);
	puts("");
}
