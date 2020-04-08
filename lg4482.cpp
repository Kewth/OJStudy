#if 0
2020.04.07

字符串的又一神题，parent 树上链分治套线段树二分及 right 集合启发式合并。

对于区间 [l, r] ，要求的就是最大的 i 满足 lcs(i, r) >= i - l + 1 且 i < r 。

一个暴力的想法就是找到前缀 r 在 parent 树上的节点 u 。
然后枚举 u 的祖先 s ，实际上是枚举 lcs(i, r) 。
对于每个 s ，在 right 集合中查询满足 len[s] >= i - l + 1 且 i < r 的点即可。

这样的复杂度与树高有关，考虑链分治，对 parent 树进行重链剖分。
那么可以将 u 到根的路径分为若干条链，可以对于每条链单独计算答案，讨论任意一条链。
每条链都一定是重链的一段前缀，设链底为 u 。
还是在 u 的 right 集合中查询，这样 u 的子树就处理完了，
剩下的需要处理的是在同一条重链的 u 的祖先和它们的轻子树。
对于这些点，从链顶向下维护线段树，线段树第 i 个点的值是 i - lcs(i, r) + 1 ，维护区间最小值。
查询只需要线段树二分，至此，问题以 O(nlog^2n) 的时空复杂度解决。
而如果每条重链的线段树处理完后就清理掉，空间复杂度可以做到 O(nlogn) 。

ps: 那个线段树二分处理的问题本质上是满足二维偏序的前提下最大化某一维。
#endif
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <set>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 400005, maxk = 26;
char s[maxn];
int ch[maxn][maxk], len[maxn], fa[maxn];
int sam[maxn], bl[maxn];
int cp = 1;
std::vector<int> G[maxn];

int insert (int pre, int x) {
	int now = ++ cp;
	len[now] = len[pre] + 1;
	while (pre and !ch[pre][x]) {
		ch[pre][x] = now;
		pre = fa[pre];
	}
	if (pre) {
		int preto = ch[pre][x];
		if (len[preto] == len[pre] + 1)
			fa[now] = preto;
		else {
			int sp = ++ cp;
			len[sp] = len[pre] + 1;
			fa[sp] = fa[preto];
			for (int i = 0; i < maxk; i ++)
				ch[sp][i] = ch[preto][i];
			while (pre and ch[pre][x] == preto) {
				ch[pre][x] = sp;
				pre = fa[pre];
			}
			fa[now] = fa[preto] = sp;
		}
	} else
		fa[now] = 1;
	return now;
}

int top[maxn], son[maxn], size[maxn], deep[maxn];

void dfs1 (int u) {
	deep[u] = deep[fa[u]] + 1;
	size[u] = 1;
	for (int v : G[u]) {
		dfs1(v);
		size[u] += size[v];
		if (size[v] > size[son[u]])
			son[u] = v;
	}
}

void dfs2 (int u) {
	if (!top[u]) top[u] = u;
	if (son[u]) {
		top[son[u]] = top[u];
		dfs2(son[u]);
		for (int v : G[u])
			if (v != son[u])
				dfs2(v);
	}
}

void rebuild () {
	for (int i = 2; i <= cp; i ++)
		G[fa[i]].push_back(i);
	dfs1(1);
	dfs2(1);
}

struct Query {
	int l, r, id;
};
std::set<int> set[maxn];
std::vector<Query> qv[maxn];
int ans[maxn];
struct Tree {
	int lti, rti;
	int min;
} pool[maxn * 400];
int seg[maxn], pp;
#define self pool[now]
#define lt pool[self.lti]
#define rt pool[self.rti]

void insert (int &now, int L, int R, int p, int x) {
	/* debug("%d %d\n", p, x); */
	if (!now) now = ++ pp, self.min = 1000000000;
	self.min = std::min(self.min, x);
	if (L == R) return;
	int M = (L + R) >> 1;
	if (p <= M) insert(self.lti, L, M, p, x);
	else insert(self.rti, M + 1, R, p, x);
}

int query (int now, int L, int R, int p, int x) {
	if (!now or p < L or self.min > x) return -1;
	if (L == R) return L;
	int M = (L + R) >> 1;
	int k = query(self.rti, M + 1, R, p, x);
	if (k != -1) return k;
	return query(self.lti, L, M, p, x);
}

int n;
void force (int u, int x, int &se) {
	if (bl[u])
		insert(se, 1, n, bl[u], bl[u] + x);
	for (int v : G[u])
		force(v, x, se);
}

void solve (int u) {
	if (top[u] != u) {
		seg[u] = seg[fa[u]];
		for (Query q : qv[u])
			ans[q.id] = std::max(ans[q.id], query(seg[u], 1, n, q.r - 1, q.l) - q.l + 1);
	}

	for (int v : G[u])
		if (v != son[u])
			force(v, 1 - len[u], seg[u]);
	if (bl[u])
		insert(seg[u], 1, n, bl[u], bl[u] - len[u] + 1);

	if (bl[u]) set[u].insert(bl[u]);
	for (int v : G[u]) {
		solve(v);
		if (set[v].size() > set[u].size())
			std::swap(set[u], set[v]);
		for (int x : set[v]) set[u].insert(x);
	}

	for (Query q : qv[u]) {
		auto it = set[u].lower_bound(std::min(q.r, q.l + len[u]));
		if (it != set[u].begin())
			ans[q.id] = std::max(ans[q.id], *(-- it) - q.l + 1);
	}
}

int main () {
	scanf("%s", s + 1);
	n = int(strlen(s + 1));

	sam[0] = 1;
	for (int i = 1; i <= n; i ++)
		bl[sam[i] = insert(sam[i - 1], s[i] - 'a')] = i;
	rebuild();

	int q = read;
	for (int i = 1; i <= q; i ++) {
		int l = read, r = read;
		for (int u = sam[r]; u; u = fa[top[u]])
			qv[u].push_back({l, r, i});
	}

	solve(1);

	for (int i = 1; i <= q; i ++)
		printf("%d\n", ans[i]);
}
