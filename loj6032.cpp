/*
 * Since g++10 is released, some characters is not valid inside #if 0 :(
 * So, why not using clang++? :D

 * Date:
    2020.06.10

 * Solution:
    类似于 Kruskal 重构树，相邻两个格子连权为隔板高度的边，建出一颗重构树，那么树上一个
节点代表水越过其子树的所有隔板的情况。在这颗重构树上 DP 即可，把限制放到对应的节点上排
个序在每个节点上枚举离散化的水位就可以简单转移。

 * Digression:
    注意到建树的同时也求出了拓扑序，因此 DP 没必要 dfs 。

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
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef std::pair<int, int> par;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 200005;
struct shit {
	int h, x, y, o;
} sh[maxn];
std::vector<int> lim[maxn];
int ls[maxn], rs[maxn];
int top[maxn];
int f[maxn], g[maxn];

int find (int x) {
	if (top[x] == x) return x;
	return top[x] = find(top[x]);
}

int main () {
	int T = read;
	while (T --) {
		int n = read, m = read;
		for (int i = 1; i < n; i ++)
			sh[m + i] = {read, i, i + 1, -1};

		for (int i = 1; i <= m; i ++) {
			int p = read, h = read, o = read;
			sh[i] = {h, p, p, o};
		}

		std::sort(sh + 1, sh + n + m, [] (shit a, shit b) {
					if (a.h == b.h) return a.o < b.o;
					return a.h < b.h;
				});

		for (int i = 1; i <= n; i ++)
			top[i] = i;
		int np = n;
		for (int i = 1; i < n + m; i ++)
			if (sh[i].o == -1) {
				int x = find(sh[i].x), y = find(sh[i].y);
				++ np;
				ls[np] = x;
				rs[np] = y;
				top[x] = top[y] = top[np] = np;
			}
			else {
				int x = find(sh[i].x);
				lim[x].push_back(sh[i].o);
				if (sh[i].o == 1)
					++ g[x];
			}

		for (int x = 1; x <= np; x ++) {
			f[x] = f[ls[x]] + f[rs[x]] + int(lim[x].size()) - g[x];
			int X = g[ls[x]] + g[rs[x]] + int(lim[x].size()) - g[x];
			for (int o : lim[x])
				if (o == 0) -- X;
				else f[x] = std::max(f[x], ++ X);
			g[x] += g[ls[x]] + g[rs[x]];
		}

		printf("%d\n", f[np]);

		for (int i = 1; i <= np; i ++) lim[i].clear(), ls[i] = rs[i] = f[i] = g[i] = 0;
	}
}
