#if 0
2019.07.28

这种最小边最大之类的玩意，算是个套路，路径一定是在最大生成树上的。
考虑最大的 f(i, j) ，i 到 j 一定有 f(i, j) 的边，
证明的话，反证法，因为没有其他边比它更大， i 到 j 的权值小于 f(i, j) ，
那么 i 到 j 的其他路径有一条权值全是 f(i, j) ，发现。。。并没有矛盾。。
但是这样的话事实上 i 到 j 是没用的，因为其他点经过 i, j 总会走上述的路径，
那么把 i 到 j 的权值提升到 f(i, j) 也是对的。

那么这样搞出来最大生成树，枚举根节点 u ， dfs 出所有 f[u][i] 验证是不是对的即可。
#endif
#include <cstdio>
#include <vector>
#include <algorithm>
#include <climits>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef std::pair<int, int> Par;
inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 1010, maxm = 300005;
int f[maxn][maxn];
Par edge[maxm];
int fa[maxn];
int min[maxn];
std::vector<int> G[maxn];

int find(int x) {
	if(fa[x] == x) return x;
	return fa[x] = find(fa[x]);
}

inline bool cmp(Par a, Par b) {
	return f[a.first][a.second] > f[b.first][b.second];
}

bool dfs(int u, int fa) {
	for(int v : G[u])
		if(v != fa) {
			min[v] = std::min(min[u], f[u][v]);
			dfs(v, u);
		}
}

int main() {
	int T = input();
	for(int t = 1; t <= T; t ++) {
		debug("FUCK\n");
		int n = input(), m = input();
		for(int i = 1; i <= n; i ++) {
			G[i].clear();
			fa[i] = i;
		}
		for(int i = 1; i <= m; i ++)
			edge[i] = Par(input(), input());
		for(int i = 1; i <= n; i ++)
			for(int j = 1; j <= n; j ++)
				f[i][j] = input();
		std::sort(edge + 1, edge + m + 1, cmp);
		for(int i = 1; i <= m; i ++) {
			int u = edge[i].first, v = edge[i].second;
			if(find(u) != find(v)) {
				fa[find(u)] = find(v);
				G[u].push_back(v);
				G[v].push_back(u);
				// debug("add %d %d %d\n", u, v, f[u][v]);
			}
		}
		bool ans = true;
		for(int i = 1; i <= n and ans; i ++) {
			for(int j = 1; j <= n; j ++)
				min[j] = INT_MAX;
			dfs(i, 0);
			for(int j = 1; j <= n; j ++)
				if((min[j] == INT_MAX and f[i][j] > 0)
						or (min[j] != INT_MAX and min[j] != f[i][j]))
					ans = false;
			// debug("%d ->\n", i);
			// for(int j = 1; j <= n; j ++)
				// debug(" %d", min[j] == INT_MAX ? 0 : min[j]);
			// debug("\n");
			// debug("should ->\n");
			// for(int j = 1; j <= n; j ++)
				// debug(" %d", f[i][j]);
			// debug("\n");
		}
		char s[2][4] = {"No", "Yes"};
		printf("Case #%d: %s\n", t,	s[ans]);
	}
}
