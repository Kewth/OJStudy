#if 0
2019.08.27

建 Kruskal 重构树，每次询问倍增调到最高能到的祖先，
那么问题转换为求某个子树内权值第 k 大的叶子节点，主席树维护即可。
#endif
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cassert>
#define debug(...) fprintf(stderr, __VA_ARGS__)

inline int input() { int x; scanf("%d", &x); return x; }

struct Edge {
	int u, v, w;
};

struct Tree;
Tree *null;

struct Tree {
	Tree *lt, *rt;
	int val, fuck;

	void update() {
		val = lt -> val + rt -> val;
	}

	Tree *lain(int l, int r, int p) {
		Tree *T = new Tree(*this);
		if(l == r) {
			T -> val ++;
			return T;
		}

		int mid = (l + r) >> 1;

		if(p <= mid)
			T -> lt = lt -> lain(l, mid, p);
		else
			T -> rt = rt -> lain(mid + 1, r, p);

		T -> update();
		return T;
	}

	Tree(): lt(null), rt(null), val(0) { }
};

const int maxn = 100005, maxd = 1000005, maxk = 23;
int h[maxn];
Edge e[maxd];
Tree *T[maxn];
int fa[maxd][maxk];
int idl[maxd], idr[maxd];
int top[maxd];
int dis[maxd];
int nh[maxn];
std::vector<int> G[maxd];
int tmp[maxn];

int get_top(int x) {
	if(top[x] == x) return x;
	return top[x] = get_top(top[x]);
}

inline bool cmp(Edge a, Edge b) {
	return a.w < b.w;
}

int dfn, N;
void dfs(int u) {
	/* debug("dfs %d\n", u); */
	idl[u] = dfn + 1;

	if(G[u].empty())
		/* nh[++ dfn] = h[u]; */
		nh[++ dfn] = int(std::lower_bound(tmp + 1, tmp + N + 1, h[u]) - tmp);
	else
		for(int v : G[u]) {
			fa[v][0] = u;
			for(int k = 1; k < maxk; k ++)
				fa[v][k] = fa[fa[v][k - 1]][k - 1];
			dfs(v);
		}

	idr[u] = dfn;
}

int kth(Tree *L, Tree *R, int l, int r, int k) {
	if(l == r)
		return k <= R -> val - L -> val ? l : 0;

	int mid = (l + r) >> 1;
	int rsize = R -> rt -> val - L -> rt -> val;
	if(k <= rsize)
		return kth(L -> rt, R -> rt, mid + 1, r, k);
	return kth(L -> lt, R -> lt, l, mid, k - rsize);
}

int main() {
	null = new Tree();
	null -> lt = null -> rt = null;

	int n = input(), m = input(), q = input();

	for(int i = 1; i <= n; i ++)
		tmp[i] = h[i] = input();

	for(int i = 1; i <= m; i ++) {
		e[i].u = input();
		e[i].v = input();
		e[i].w = input();
	}

	std::sort(e + 1, e + m + 1, cmp);
	std::sort(tmp + 1, tmp + n + 1);

	for(int i = 1; i <= n; i ++)
		top[i] = i;

	int d = N = n;
	for(int i = 1; i <= m; i ++) {
		int u = e[i].u, v = e[i].v;
		if(get_top(u) == get_top(v))
			continue;

		dis[++ d] = e[i].w;
		G[d].push_back(top[u]);
		G[d].push_back(top[v]);
		top[top[u]] = top[top[v]] = top[d] = d;
	}

	for(int i = 1; i <= d; i ++)
		if(top[i] == i)
			dfs(i);

	T[0] = new Tree();
	for(int i = 1; i <= n; i ++)
		T[i] = T[i - 1] -> lain(1, n, nh[i]);

	assert(dfn == n);

	/* for(int i = 1; i <= n; i ++) */
	/* 	debug(" %d", nh[i]); */
	/* debug("\n"); */

	tmp[0] = -1;

	int ans = 0;
	while(q --) {
		int u = input() ^ ans, x = input() ^ ans, K = input() ^ ans;

		/* debug("query %d %d %d\n", u, x, K); */

		for(int k = maxk - 1; k >= 0; k --)
			if(fa[u][k] and dis[fa[u][k]] <= x)
				u = fa[u][k];

		/* debug("to %d (%d-%d)\n", u, idl[u], idr[u]); */
		ans = tmp[kth(T[idl[u] - 1], T[idr[u]], 1, n, K)];
		printf("%d\n", ans);

		// 在线离线一念之间
		/* if(ans == -1) */
			ans = 0;
	}
}
