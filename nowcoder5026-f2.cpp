#if 0
2020.04.13

被动态点分治爆踩。。。

一个朴素的想法是对于每个修改和询问都暴力跳父亲，每个节点用线段树维护子树内每种苹果的最小距离。
这样的复杂度是 O(hlog) 的，可以简单地推广到点分树上，每个联通块用线段树维护到重心的信息即可。
并且这里查询最小值不会有算重复的问题，实现起来十分清爽，没有恶心细节。
#endif
#include <cstdio>
#include <algorithm>
#include <vector>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
} read;

const int maxn = 100005;
struct Edge { int v, w; };
std::vector<Edge> G[maxn];
int st[20][maxn << 1], hb[maxn << 1], first[maxn], stp;
int dist[maxn];
bool ban[maxn];
int size[maxn], son[maxn];
int dfa[maxn], dsize[maxn];

struct Tree {
	int lti, rti;
	int val;
} pool[maxn * 400];
int pp;
#define self pool[now]
#define lt pool[self.lti]
#define rt pool[self.rti]

int query (int now, int L, int R, int l, int r) {
	if (!now or r < L or l > R) return 1000000000;
	if (l <= L and R <= r) return self.val;
	int M = (L + R) >> 1;
	return std::min(query(self.lti, L, M, l, r), query(self.rti, M + 1, R, l, r));
}

void modify (int &now, int L, int R, int p, int x) {
	if (!now) now = ++ pp, self.val = x;
	else self.val = std::min(self.val, x);
	if (L == R) return;
	int M = (L + R) >> 1;
	if (p <= M) modify(self.lti, L, M, p, x);
	else modify(self.rti, M + 1, R, p, x);
}

void stinit () {
	for (int i = 2; i <= stp; i ++)
		hb[i] = hb[i >> 1] + 1;
	for (int i = stp; i; i --)
		for (int k = 1; i + (1 << k) - 1 <= stp; k ++)
			st[k][i] = std::min(st[k - 1][i], st[k - 1][i + (1 << k >> 1)]);
}

void dfs (int u, int f) {
	st[0][first[u] = ++ stp] = dist[u];
	for (Edge e : G[u])
		if (e.v != f) {
			dist[e.v] = dist[u] + e.w;
			dfs(e.v, u);
			st[0][++ stp] = dist[u];
		}
}

inline int dis (int x, int y) {
	int l = first[x], r = first[y];
	if (l > r) std::swap(l, r);
	int k = hb[r - l + 1];
	return dist[x] + dist[y] - std::min(st[k][l], st[k][r - (1 << k) + 1]) * 2;
}

void getsize (int u, int f) {
	size[u] = 1, son[u] = 0;
	for (Edge e : G[u])
		if (!ban[e.v] and e.v != f) {
			getsize(e.v, u);
			size[u] += size[e.v];
			if (size[e.v] > size[son[u]])
				son[u] = e.v;
		}
}

int divide (int s) {
	getsize(s, 0);
	int n = size[s], r = s;
	while (size[son[r]] * 2 > n)
		r = son[r];
	dsize[r] = n;
	ban[r] = 1;
	for (Edge e : G[r])
		if (!ban[e.v]) {
			int vv = divide(e.v);
			dfa[vv] = r;
		}

	return r;
}

int seg[maxn];

void vmodify (int u, int p) {
	for (int f = u; f; f = dfa[f])
		modify(seg[f], 1, 10000, p, dis(f, u));
}

int vquery (int u, int l, int r) {
	int res = 1000000000;
	for (int f = u; f; f = dfa[f])
		res = std::min(res, query(seg[f], 1, 10000, l, r) + dis(f, u));
	return res;
}

int val[maxn];
int main () {
	int n = read, q = read;
	for (int i = 1; i <= n; i ++) read(val[i]);
	for (int i = 1; i < n; i ++) {
		int u = read, v = read, w = read;
		G[u].push_back({v, w});
		G[v].push_back({u, w});
	}

	dfs(1, 0);
	stinit();
	divide(1);

	for (int i = 1; i <= n; i ++) vmodify(i, val[i]);

	while (q --) {
		int o = read;
		if (o == 1) {
			int u = read, x = read;
			vmodify(u, x);
		}
		if (o == 2) {
			int u = read, l = read, r = read;
			int ans = vquery(u, l, r);
			printf("%d\n", ans == 1000000000 ? -1 : ans << 1);
		}
	}
}
