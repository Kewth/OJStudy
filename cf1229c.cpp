#if 0
2020.05.05

  很巧妙，相当漂亮。
  每个点对答案的贡献就是入度和出度乘积，对于每个点维护其入边集合，每次修改一个点就暴力
扫描其出边集合的每个点更新所有信息。
  一次修改的最坏复杂度自然是 O(n) 的，但是这种修改不会出现很多次，分析其总复杂度。
  考虑将所有点按度数大小降序，每个点的入度由左右两边构成，其中左边部分不会超过 sqrt(2m) 。
可以反证，如果左边部分超过 sqrt(2m) ，那么这些点的度数都不小于 sqrt(2m) ，而总度数不超
过 2m ，得到一个矛盾。所以从左向右的边这部分暴力扫的复杂度是 O(sqrt(2m)) 的。而从右向左
的边虽然可能很多，但是每次一条从右向左的边被扫到后都会转变为从左向右的边。而每次修改
最多访问 sqrt(2m) 条从左到右的边，因而每次询问最多增加 sqrt(2m) 条从右向左的边，因此复
杂度均摊下来就是 O(sqrt(2m)) 。
#endif
#include <cstdio>
#include <algorithm>
#include <vector>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 100005;
std::vector<int> G[maxn];
int deg[maxn];

ll ans = 0;
void update (int u, int t) {
	ans += (deg[u] - ll(G[u].size())) * ll(G[u].size()) * t;
}

int main () {
	int n = read, m = read;
	for (int i = 1; i <= m; i ++) {
		int u = read, v = read;
		if (u > v) std::swap(u, v);
		G[u].push_back(v);
		++ deg[u];
		++ deg[v];
	}

	for (int u = 1; u <= n; u ++)
		update(u, 1);
	printf("%lld\n", ans);

	int q = read;
	while (q --) {
		int u = read;
		for (int x : G[u]) {
			update(x, -1);
			G[x].push_back(u);
			update(x, 1);
		}
		update(u, -1);
		G[u].clear();
		printf("%lld\n", ans);
	}
}
