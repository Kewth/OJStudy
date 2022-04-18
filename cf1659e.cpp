/*
 * Author: Kewth

 * Date:
  2022.04.18

 * Solution:
  显然由于前缀与的性质，1 和 2 不会同时出现，mex 只能是 0, 1, 2 三种。
  判断是否能取到 0 是简单的：检查是否有一个二进制位的边使得 u, v 连通即可。
  考虑判断是否能取到 1 。当我们走到第一条偶权边之前，我们的按位与不能有 1 ，
也就是说在走到第一条偶权边之前，经过的边必须有一个其他的二进制位一直保持是
1 ，同样用并查集判断即可。

 * Digression:

 * CopyRight:
   __  __                  __   __
  |  |/  |.-----.--.--.--.|  |_|  |--.
  |     < |  -__|  |  |  ||   _|     |
  |__|\__||_____|________||____|__|__|

 */

#include <cstdio>
#include <algorithm>
#include <vector>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef std::pair<int, int> par;

static struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 100005, maxc = 30;
/* std::vector<int> G[maxc][maxn]; */
struct dsu {
	int fa[maxn];
	int find (int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
	inline void link (int x, int y) { x = find(x), y = find(y), fa[x] = y; }
	inline void init (int n) { for (int i = 1; i <= n; i ++) fa[i] = i; }
} g[maxc], odd[maxc];
bool link_even[maxn], LinkEven[maxc][maxn];

int main () {
	int n = read, m = read;
	for (int k = 0; k < maxc; k ++)
		g[k].init(n), odd[k].init(n);
	std::fill(link_even, link_even + n + 1, 0);
	for (int k = 0; k < maxc; k ++)
		std::fill(LinkEven[k], LinkEven[k] + n + 1, 0);
	for (int i = 1; i <= m; i ++) {
		int u = read, v = read, w = read;
		for (int k = 0; k < maxc; k ++)
			if (w >> k & 1)
				g[k].link(u, v);
		if (w & 1) {
			for (int k = 1; k < maxc; k ++)
				if (w >> k & 1)
					odd[k].link(u, v);
		} else
			link_even[u] = link_even[v] = 1;
	}
	for (int i = 1; i <= n; i ++)
		if (link_even[i])
			for (int k = 1; k < maxc; k ++)
				LinkEven[k][odd[k].find(i)] = 1;
	int q = read;
	while (q --) {
		int u = read, v = read, get = 0;
		for (int k = 0; k < maxc; k ++)
			if (g[k].find(u) == g[k].find(v))
				++ get;
		if (get) puts("0");
		else {
			bool fuck = 0;
			for (int k = 1; k < maxc; k ++)
				fuck |= LinkEven[k][odd[k].find(u)];
			if (fuck) puts("1");
			else puts("2");
		}
	}
}
