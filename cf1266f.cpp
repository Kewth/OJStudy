/*
 * Since g++10 is released, some characters is not valid inside #if 0 :(
 * So, why not using clang++? :D

 * Date:
  2020.06.15

 * Solution:
 * 分类讨论，换根 DP ，双指针，去重枚举（总和一定）

  偶数奇数分别考虑，两者是分别单调不增的。

  对于权为 2x 的点集，相当于要找一条边 (u, v) ，然后在两边选尽可能多的以 u 或 v	为端点
的长度不小于 x 的不交链。对于权为 2x + 1 的点集，相当于要找一个点 u ，然后选尽可能多的
以 u 为端点的长度为 x + 1 的不交链和至多一个长为 x 的链。

  那么奇数的情况直接换根 DP 一波做贡献即可。对于偶数的情况，一个朴素的想法是枚举边，然
后在两边枚举儿子和奇数的情况同样的计算，容易发现这样最坏的复杂度是 O(n^2) 的，比如一个
菊花图。

  有一个看上去很 naive 的优化是对于每个点 u 用 map 存每个与 u 相连的点的最长的链长，把
长度相同的缩到一起记数量。然后还是同样枚举边，在两边的 map 上双指针算贡献，这样就避免
了多次枚举链长相同的点。事实上这是有效的，注意到对于一个点 u ，map 内存的链长的总和是
O(n) 的，也就意味着不同的链长数量是 O(n^0.5) 的，这样枚举边在两边暴力枚举 map 每个元素
的复杂度是 O(n^1.5) ，并且不满，足以通过。

 * Digression:
  去重后就可以直接枚举，我咋就没想到呢。

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
#include <map>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 500005;
int ans[maxn << 1];
std::vector<int> G[maxn];
int fa[maxn];
int flen[maxn], len[maxn];
/* std::vector<int> L[maxn], S[maxn]; */
std::map<int, int> map[maxn];

void dfs1 (int u) {
	len[u] = 0;
	for (int v : G[u])
		if (v != fa[u]) {
			fa[v] = u;
			dfs1(v);
			len[u] = std::max(len[u], len[v] + 1);
			/* L[u].push_back(len[v] + 1); */
			++ map[u][len[v] + 1];
		}
}

void dfs2 (int u) {
	/* S[u] = L[u]; */
	/* if (fa[u]) L[u].push_back(flen[u] + 1); */
	if (fa[u]) ++ map[u][flen[u] + 1];
	/* std::sort(L[u].begin(), L[u].end()); */
	/* std::sort(S[u].begin(), S[u].end()); */
	int max = flen[u], semax = -1;
	for (int v : G[u])
		if (v != fa[u]) {
			if (len[v] > max)
				semax = max, max = len[v];
			else if (len[v] > semax)
				semax = len[v];
		}
	for (int v : G[u])
		if (v != fa[u]) {
			flen[v] = len[v] == max ? semax + 1 : max + 1;
			dfs2(v);
		}
}

int main () {
	int n = read;
	for (int i = 1; i < n; i ++) {
		int u = read, v = read;
		G[u].push_back(v);
		G[v].push_back(u);
	}

	flen[1] = -1;
	dfs1(1);
	dfs2(1);

	for (int u = 1; u <= n; u ++) {
		int las = 0;
		for (auto it = map[u].rbegin(); it != map[u].rend(); ++ it) {
			it -> second += las;
			las = it -> second;
		}
		las = 0;
		for (auto p : map[u]) {
			int x = p.first, y = p.second;
			ans[x * 2] = std::max(ans[x * 2], y);
			ans[x * 2 - 1] = std::max(ans[x * 2 - 1], y);
			if (las < x)
				ans[las * 2 + 1] = std::max(ans[las * 2 + 1], y + 1);
			las = x;
		}
	}

	for (int u = 2; u <= n; u ++) {
		int f = fa[u];
		auto it1 = map[f].begin(), it2 = map[u].begin();
		while (it1 != map[f].end() and it2 != map[u].end()) {
			int x = std::min(it1 -> first, it2 -> first),
				y = it1 -> second + it2 -> second;
			if (it1 -> first <= len[u] + 1) -- y;
			if (it2 -> first <= flen[u] + 1) -- y;
			ans[x * 2] = std::max(ans[x * 2], y);
			if (it1 -> first == x) ++ it1;
			else ++ it2;
		}
	}

	ans[n + 1] = ans[n + 2] = 1;
	for (int i = n; i; i --)
		ans[i] = std::max(ans[i + 2], ans[i]);
	for (int i = 1; i <= n; i ++)
		printf("%d ", ans[i]);
	puts("");
}
