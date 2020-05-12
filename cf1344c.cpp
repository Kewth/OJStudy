#if 0
2020.05.12

  把小于的关系连边，如果有环则不合法，否则可以建出一个 DAG 。
  按编号考虑每一个点 u ，可以发现无论 u 选择 A 或者 E ，编号大于 u 的能到达 u 的点和 u
能到达的点都只能选 E 。那么逐个贪心选 A ，然后暴力把 u 能到的和能到 u 的点标记一下即可。
每个点被标记的次数是 O(1) 的。
#endif
#include <cstdio>
#include <algorithm>
#include <vector>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 200005;
std::vector<int> G[maxn], iG[maxn];
int stack[maxn], sp;
int deg[maxn];
char ans[maxn];
bool vis[maxn], ivis[maxn];

void dfs (int u) {
	if (vis[u]) return;
	vis[u] = 1;
	for (int v : G[u])
		dfs(v);
}

void idfs (int u) {
	if (ivis[u]) return;
	ivis[u] = 1;
	for (int v : iG[u])
		idfs(v);
}

int main () {
	int n = read, m = read;
	for (int i = 1; i <= m; i ++) {
		int u = read, v = read;
		G[u].push_back(v);
		iG[v].push_back(u);
		++ deg[v];
	}

	for (int u = 1; u <= n; u ++)
		if (!deg[u])
			stack[++ sp] = u;

	int tot = 0;
	while (sp) {
		int u = stack[sp --];
		++ tot;
		for (int v : G[u])
			if (-- deg[v] == 0)
				stack[++ sp] = v;
	}

	if (tot != n)
		return puts("-1"), 0;

	tot = 0;
	for (int u = 1; u <= n; u ++) {
		if (!vis[u] and !ivis[u])
			ans[u] = 'A', ++ tot;
		else
			ans[u] = 'E';
		dfs(u);
		idfs(u);
	}

	printf("%d\n", tot);
	puts(ans + 1);
}
