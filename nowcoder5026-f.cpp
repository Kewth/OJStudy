#pragma GCC optimize(2)
#if 0
2020.04.10

把苹果颜色建线段树，然后把加苹果和查苹果操作插入到线段树对应的节点。
然后对于每个节点单独考虑里面的操作，这时候苹果就没有了颜色属性，而总的操作数是 qlogV 的。
对于每个节点的操作，cdq 分治，那么就只需要计算前面一半对后面一半的贡献。
对于前面一半建出虚树，然后暴力 DP 出每个节点最近的苹果，后面一半直接查询即可。
复杂度 O(qlog(V)log^2(q)) ，如果严格线性建虚树的话复杂度 O(qlog(V)log(q)) 。
在 cdq 内部剪枝，如果左边一半没有修改或者右边一半没有询问的时候退出。
#endif
#include <cstdio>
#include <algorithm>
#include <vector>
/* #define debug(...) fprintf(stderr, __VA_ARGS__) */
inline void foo() { }
#define debug(...) foo()

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	/* inline operator ll () { ll x; return scanf("%lld", &x), x; } */
	/* template<class T> inline void operator () (T &x) { x = *this; } */
	/* template<class T, class ...A> inline void operator () (T &x, A &...a) */
	/* { x = *this; this -> operator () (a...); } */
} read;

const int maxn = 200005, maxw = 10005, inf = 1000000000;
struct Edge { int v, w; };
std::vector<Edge> G[maxn], T[maxn];
struct oper {
	int u, id;
};
std::vector<oper> op[maxw << 2];
int ans[maxn], ap;

void add_modify (int now, int L, int R, int x, int u) {
	op[now].push_back({u, 0});
	if (L == R) return;
	int M = (L + R) >> 1;
	if (x <= M) add_modify(now << 1, L, M, x, u);
	else add_modify(now << 1 | 1, M + 1, R, x, u);
}

void add_query (int now, int L, int R, int x, int y, int u, int id) {
	if (R < x or L > y) return;
	if (x <= L and R <= y) return op[now].push_back({u, id}), void();
	int M = (L + R) >> 1;
	add_query(now << 1, L, M, x, y, u, id);
	add_query(now << 1 | 1, M + 1, R, x, y, u, id);
}

int deep[maxn], top[maxn], fa[maxn], son[maxn], size[maxn];
int dist[maxn];
int id[maxn], iid[maxn], ip;
void dfs1(int u) {
	deep[u] = deep[fa[u]] + 1;
	size[u] = 1;
	for (Edge e : G[u])
		if (e.v != fa[u]) {
			fa[e.v] = u;
			dist[e.v] = dist[u] + e.w;
			dfs1(e.v);
			size[u] += size[e.v];
			if(size[e.v] > size[son[u]])
				son[u] = e.v;
		}
}

void dfs2(int u) {
	iid[id[u] = ++ ip] = u;
	if(son[u]) {
		top[son[u]] = top[u];
		dfs2(son[u]);
		for (Edge e : G[u])
			if(e.v != fa[u] and e.v != son[u]) {
				top[e.v] = e.v;
				dfs2(e.v);
			}
	}
}

int lca(int x, int y) {
	while(top[x] != top[y])
		if(deep[top[x]] < deep[top[y]])
			y = fa[top[y]];
		else
			x = fa[top[x]];
	return deep[x] < deep[y] ? x : y;
}

int key[maxn], ikey[maxn], kp;
int stack[maxn], sp;
oper otmp[maxn];

void build (int l, int r) {
	bool has1 = 0;
	/* for (int i = l; i <= r; i ++) */
	/* 	debug(" %d", otmp[i].u); */
	/* debug(" in build\n"); */
	int m = 0;
	for (int i = l; i <= r; i ++)
		ikey[++ m] = id[otmp[i].u], has1 |= otmp[i].u == 1;
	if (!has1) ikey[++ m] = id[1];
	std::sort(ikey + 1, ikey + m + 1);
	m = int(std::unique(ikey + 1, ikey + m + 1) - ikey - 1);
	for (int i = 1; i <= m; i ++)
		ikey[i] = iid[ikey[i]];
	/* for (int i = 1; i <= m; i ++) */
	/* 	debug(" %d", ikey[i]); */
	/* debug(" in build\n"); */

	sp = kp = 0;
	for (int i = 1; i <= m; i ++)
		key[ikey[i]] = ++ kp;
	stack[++ sp] = ikey[1]; // ikey[1] = 1

	for(int i = 2; i <= m; i ++) {
		int u = ikey[i];
		if(u == 1) continue;
		int x = stack[sp];
		int c = lca(u, x);

		while(deep[c] < deep[x]) {
			int y = x;
			x = stack[-- sp];
			if(deep[c] < deep[x])
				debug("%d -> %d\n", x, y),
				T[x].push_back({y, dist[y] - dist[x]});
			else
				debug("%d -> %d\n", c, y),
				T[c].push_back({y, dist[y] - dist[c]});
		}

		if(deep[c] > deep[x]) {
			ikey[key[c] = ++ kp] = c;
			stack[++ sp] = c;
		}

		stack[++ sp] = u;
	}

	for(int i = 2; i <= sp; i ++)
		debug("%d -> %d\n", stack[i - 1], stack[i]),
		T[stack[i - 1]].push_back({stack[i], dist[stack[i]] - dist[stack[i - 1]]});
}

int f[maxn], h[maxn];
void dp1 (int u) {
	for (Edge e : T[u]) {
		dp1(e.v);
		f[u] = std::min(f[u], f[e.v] + e.w);
	}
}
void dp2 (int u) {
	for (Edge e : T[u]) {
		h[e.v] = std::min(f[u], h[u]) + e.w;
		dp2(e.v);
	}
}

void solve (int l, int r) {
	if (l >= r) return;
	int mid = (l + r) >> 1;
	solve(l, mid);
	solve(mid + 1, r);

	bool shit1 = 0, shit2 = 0;
	for (int i = l; i <= mid; i ++)
		shit1 |= bool(!otmp[i].id);
	for (int i = mid + 1; i <= r; i ++)
		shit2 |= bool(otmp[i].id);
	if (!shit1 or !shit2) return;

	/* debug("solve %d %d\n", l, r); */
	build(l, r);
	for (int i = l; i <= mid; i ++)
		if (!otmp[i].id)
			f[otmp[i].u] = 0;
	/* debug("%d %d %d %d\n", f[1], f[2], f[3], f[4]); */
	dp1(1);
	dp2(1);
	for (int i = mid + 1; i <= r; i ++)
		if (otmp[i].id)
			ans[otmp[i].id] = std::min({ans[otmp[i].id], f[otmp[i].u], h[otmp[i].u]});

	for(int i = 1; i <= kp; i ++) {
		int u = ikey[i];
		key[u] = 0;
		f[u] = h[u] = 1000000000;
		T[u].clear();
	}
}

void shit (int now, int L, int R) {
	int p = 0;
	for (oper o : op[now]) otmp[++ p] = o;
	solve(1, p);
	if (L == R) return;
	int M = (L + R) >> 1;
	shit(now << 1, L, M);
	shit(now << 1 | 1, M + 1, R);
}

int main () {
	int n = read, q = read;
	int c = 10000;
	for (int i = 1; i <= n; i ++)
		add_modify(1, 1, c, read, i);
	for (int i = 1; i < n; i ++) {
		int u = read, v = read, w = read;
		G[u].push_back({v, w});
		G[v].push_back({u, w});
	}
	for (int i = 1; i <= q; i ++) {
		int o = read;
		if (o == 1) {
			int u = read, x = read;
			add_modify(1, 1, c, x, u);
		}
		if (o == 2) {
			int u = read, x = read, y = read;
			add_query(1, 1, c, x, y, u, ++ ap);
		}
	}
	std::fill(ans, ans + ap + 1, inf);
	std::fill(f, f + n + 1, inf);
	std::fill(h, h + n + 1, inf);
	dfs1(1);
	dfs2(1);
	shit(1, 1, c);
	for (int i = 1; i <= ap; i ++)
		printf("%d\n", ans[i] == inf ? -1 : ans[i] << 1);
}
