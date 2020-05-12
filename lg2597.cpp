#if 0
2020.05.11

  将 DAG 拓扑排序，建出一颗树，树的拓扑序与 DAG 拓扑序相同，每个点在树上的父亲就是在 DAG
上最近的消失可以导致灭绝的点。
  这个树似乎叫支配树，那么一个点的答案就是其在树上的子树大小减 1 。
  另外需要在 DAG 中建一个虚拟节点连接向所有点，以确保能建出来一颗树。
#endif
#include <cstdio>
#include <algorithm>
#include <vector>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 65535, maxk = 20;
std::vector<int> G[maxn], iG[maxn], T[maxn];
int deg[maxn];
int stack[maxn], sp;
int fa[maxn][maxk], deep[maxn];
int size[maxn], topsort[maxn], tp;

int lca (int x, int y) {
	if (deep[x] < deep[y]) std::swap(x, y);
	for (int k = maxk - 1; k >= 0; k --)
		if (deep[fa[x][k]] >= deep[y])
			x = fa[x][k];
	for (int k = maxk - 1; k >= 0; k --)
		if (fa[x][k] != fa[y][k])
			x = fa[x][k], y = fa[y][k];
	return x == y ? x : *fa[x];
}

int main () {
	int n = read;
	for (int i = 1; i <= n; i ++) {
		int x = read;
		while (x) {
			G[x].push_back(i);
			iG[i].push_back(x);
			++ deg[i];
			x = read;
		}
		if (!deg[i]) stack[++ sp] = i;
	}

	while (sp) {
		int u = stack[sp --];
		for (int v : G[u])
			if (-- deg[v] == 0)
				stack[++ sp] = v;
		if (!iG[u].empty()) {
			*fa[u] = iG[u].front();
			for (int f : iG[u])
				*fa[u] = lca(*fa[u], f);
		}
		deep[u] = deep[*fa[u]] + 1;
		for (int k = 1; k < maxk; k ++)
			fa[u][k] = fa[fa[u][k - 1]][k - 1];
		T[*fa[u]].push_back(u);
		topsort[++ tp] = u;
	}

	for (int i = tp; i; i --) {
		int u = topsort[i];
		size[u] = 1;
		for (int v : T[u])
			size[u] += size[v];
	}

	for (int i = 1; i <= n; i ++)
		printf("%d\n", size[i] - 1);
}
