#if 0
2020.04.14

考虑最小化，如果所有叶子之间的距离都是偶数，所有边填一个数即可。
否则可以简单归纳，用 1, 2, 3 三个数即可。

考虑最大化，DP ，以非叶子节点为根，对于每个点 u ，其子树内所有叶子到其的边权异或和都要相等。
那么如果 u 直接连向一些叶子，这些边的权必须一样，其他边可以两两不同。
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
int f[maxn], g[maxn], shit[2];

void dp (int u, int fa, int d) {
	bool leaf = 0;
	for (int v : G[u])
		if (v != fa) {
			dp(v, u, d + 1);
			g[u] += g[v] + 1;
			if (G[v].size() == 1)
				-- g[u], leaf = 1;
		}
	g[u] += leaf;
	shit[d & 1] |= G[u].size() == 1;
}

int main () {
	int n = read;
	for (int i = 1; i < n; i ++) {
		int u = read, v = read;
		G[u].push_back(v);
		G[v].push_back(u);
	}

	int rt = 1;
	for (int i = 2; i <= n; i ++)
		if (G[i].size() > 1)
			rt = i;
	dp(rt, 0, 0);

	printf("%d %d\n", shit[0] and shit[1] ? 3 : 1, g[rt]);
}
