#if 0
2019.07.14

先随便定向所有边，考虑那些边需要反向。
反向的结果两端的点的出度奇偶取反。
如果有一条环被反向，是不会造成任何影响的，
而反向环上一条边等价于反向环上除了这条边的所有边。
因此可以割掉所有环，最后只剩一颗生成树。
在生成树上 dfs 考虑即可。
#endif
#include <cstdio>
#include <vector>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef std::pair<int, int> par;
inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 100005;
std::vector<par> G[maxn];
bool a[maxn], vis[maxn];
par edge[maxn];
bool ans[maxn];

void dfs(int u) {
	vis[u] = true;
	for(par p : G[u])
		if(not vis[p.first]) {
			dfs(p.first);
			if(a[p.first]) {
				a[u] ^= 1;
				a[p.first] ^= 1;
				ans[p.second] ^= 1;
			}
		}
}

int main() {
	int n = input(), m = input();
	for(int i = 1; i <= m; i ++) {
		int u = input(), v = input();
		G[u].push_back(par(v, i));
		G[v].push_back(par(u, i));
		edge[i] = par(u, v);
		a[u] ^= 1;
	}
	dfs(1);
	if(a[1])
		puts("-1");
	else {
		for(int i = 1; i <= m; i ++) {
			if(ans[i]) std::swap(edge[i].first, edge[i].second);
			printf("%d %d\n", edge[i].first, edge[i].second);
		}
	}
}
