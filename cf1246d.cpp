#if 0
2020.03.31

考虑倒推，用最少的操作次数把一颗树变成一条链。
贪心，把所有点的儿子按最大深度排序，将深度最大的儿子缩成链后接到倒数第二大的儿子上，
重复操作直到只剩下一个儿子，把该儿子也缩成一条链即可。
#endif
#include <cstdio>
#include <algorithm>
#include <vector>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef std::pair<int, int> par;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 100005;
int fa[maxn];
int len[maxn];
bool f[maxn];
std::vector<int> G[maxn];
int ans[maxn], ap;

void dp (int u) {
	for (int v : G[u])
		dp(v);
	std::sort(G[u].begin(), G[u].end(), [] (int x, int y) {
				return len[x] < len[y];
			});
	len[u] = G[u].empty() ? 1 : len[G[u].back()] + 1;
}

void dfs (int u) {
	if (f[u]) return;
	/* debug("dfs %d\n", u); */
	if (G[u].empty()) return;
	for (size_t i = G[u].size() - 1; i; i --) {
		dfs(G[u][i]);
		ans[++ ap] = G[u][i];
		G[G[u][i - 1]].push_back(G[u][i]);
	}
	while (G[u].size() > 1) G[u].pop_back();
	if (!G[u].empty())
		dfs(G[u][0]);
	f[u] = 1;
}

int main () {
	int n = read;
	for (int i = 2; i <= n; i ++) {
		fa[i] = read + 1;
		G[fa[i]].push_back(i);
	}

	dp(1);
	dfs(1);
	for (int x = 1; x; x = G[x].empty() ? 0 : G[x][0])
		printf("%d ", x - 1);
	puts("");
	printf("%d\n", ap);
	for (int i = ap; i; i --)
		printf("%d ", ans[i] - 1);
	puts("");
}
