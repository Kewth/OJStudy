/*
 * Author: Kewth

 * Date:
  2021.05.29

 * Solution:
  耳分解后用 splay 维护高度即可。

 * Digression:
  难度：9 / 12
  小题大作，愚蠢至极，多此一举，匪夷所思，不可理喻。

 * CopyRight:
   __  __                  __   __
  |  |/  |.-----.--.--.--.|  |_|  |--.
  |     < |  -__|  |  |  ||   _|     |
  |__|\__||_____|________||____|__|__|

 */

#include <cstdio>
#include <algorithm>
#include <vector>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef double ld;

static struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 100005, maxm = 300005;
struct Edge { int v, i; };
std::vector<Edge> G[maxn];
int ex[maxm], ey[maxm];
int dfn[maxn], low[maxn], map[maxn], clk;

// Tree {{{
struct Tree {
	int fai, lti, rti;
	Tree (): fai(0), lti(0), rti(0) { }
} T[maxn];
#define self T[now]
#define lt T[self.lti]
#define rt T[self.rti]
#define fa T[self.fai]

inline bool from (int now) { return fa.rti == now; }

void rotate (int now) {
	int p = fa.fai, f = self.fai, fr = from(now), s = fr ? self.lti : self.rti;
	if (p) (from(f) ? T[p].rti : T[p].lti) = now;
	(fr ? T[f].rti : T[f].lti) = s;
	(fr ? self.lti : self.rti) = f;
	T[s].fai = f;
	T[f].fai = now;
	self.fai = p;
	/* update(f), update(now); */
}

void splay (int now, int top = 0) {
	while (self.fai != top) {
		if (fa.fai != top)
			rotate(from(now) == from(self.fai) ? self.fai : now);
		rotate(now);
	}
}

void insertL (int now, int an) {
	/* debug("insertL %d %d\n", now, an); */
	if (!self.lti) self.lti = an;
	else {
		now = self.lti;
		while (self.rti) now = self.rti;
		self.rti = an;
	}
	T[an].fai = now;
	splay(an);
}
void insertR (int now, int an) {
	/* debug("insertR %d %d\n", now, an); */
	if (!self.rti) self.rti = an;
	else {
		now = self.rti;
		while (self.lti) now = self.lti;
		self.lti = an;
	}
	T[an].fai = now;
	splay(an);
}

bool cmprank (int now, int an) {
	/* debug("cmp %d %d\n", now, an); */
	splay(now);
	splay(an, now);
	return from(an);
}
#undef fa
// }}}

// dfs1 {{{
int vstack[maxn], vsp;
int estack[maxm << 1], esp;
std::vector<int> V[maxn], E[maxn];
int bp;
void dfs1 (int u) {
	low[u] = dfn[u] = ++ clk;
	vstack[++ vsp] = u;
	for (Edge e : G[u]) {
		int v = e.v;
		if (!dfn[v]) {
			int tmp = esp;
			/* estack[++ esp] = e.i; */
			dfs1(v);
			low[u] = std::min(low[u], low[v]);
			if (low[v] == dfn[u]) {
				++ bp;
				while (vstack[vsp + 1] != v)
					V[bp].push_back(vstack[vsp --]);
				V[bp].push_back(u);
				while (esp > tmp)
					E[bp].push_back(estack[esp --]);
				/* debug("========\n"); */
				/* for (int i : E[bp]) */
				/* 	debug("%d %d\n", ex[i], ey[i]); */
				/* debug("========\n"); */
			}
		} else if (dfn[v] < dfn[u]) {
			low[u] = std::min(low[u], dfn[v]);
			estack[++ esp] = e.i;
		}
	}
}
// }}}

// dfs2 and dfs3 {{{
Edge fa[maxn];
Edge to[maxn];
void dfs2 (int u) {
	/* debug("d2 %d\n", u); */
	low[u] = dfn[u] = ++ clk;
	map[clk] = u;
	for (Edge e : G[u]) {
		int v = e.v;
		if (!dfn[v]) {
			fa[v] = {u, e.i};
			dfs2(v);
			if (low[v] < low[u])
				low[u] = low[v], to[u] = e;
		} else if (dfn[v] < low[u])
			low[u] = dfn[v], to[u] = e;
	}
}

// 忽略仅有一条边的耳朵
int list[maxm << 1], lp = 0;
int pos[maxn], pp;
void dfs3 (int u) {
	low[u] = dfn[u] = ++ clk;
	for (Edge e : G[u]) {
		int v = e.v;
		if (!dfn[v]) {
			fa[v] = {u, e.i};
			dfs3(v);
			if (low[v] < low[u])
				low[u] = low[v], to[u] = e;
		} else if (dfn[v] < low[u] and v != fa[u].v)
			low[u] = dfn[v], to[u] = e;
	}
	for (Edge e : G[u]) {
		int v = e.v;
		if (fa[v].v == u and v != to[u].v) {
			list[++ lp] = u;
			pos[++ pp] = lp;
			list[++ lp] = v;
			for (int k = v; dfn[k] != low[v]; k = to[k].v)
				list[++ lp] = to[k].v;
		}
	}
}
// }}}

// solve {{{
ld h[maxn];
bool key[maxm];
void solve (int b, int s, int t) {
	/* debug("s->t : %d %d\n", s, t); */
	bool check = 0;
	for (int u : V[b])
		check |= u == t;
	if (!check) { puts("No"); exit(0); }
	if (V[b].size() == 2)
		return insertR(s, t);

	for (int u : V[b]) {
		G[u].clear();
		low[u] = dfn[u] = 0;
		fa[u] = to[u] = {0, 0};
	}
	clk = 0;
	for (int i : E[b]) {
		int u = ex[i], v = ey[i];
		G[u].push_back({v, i});
		G[v].push_back({u, i});
		key[i] = 0;
	}
	dfs2(s);

	for (int x = t, z, ly = t; x != s; x = z) {
		int y = map[low[x]];
		for (int k = x; k != y; k = to[k].v)
			/* debug("y %d %d\n", k, to[k].v), */
			key[to[k].i] = 1;
		if (y == s)
			z = s;
		else {
			z = x;
			for (int k = x; k != y; k = fa[k].v)
				if (low[k] < low[z])
					z = k;
		}
		for (int k = ly; k != z; k = fa[k].v)
			/* debug("z %d %d\n", k, fa[k].v), */
			key[fa[k].i] = 1;
		ly = y;
	}

	for (int u : V[b]) {
		std::sort(G[u].begin(), G[u].end(), [] (Edge e1, Edge e2) {
					return key[e1.i] > key[e2.i];
				});
		low[u] = dfn[u] = 0;
		fa[u] = to[u] = {0, 0};
	}
	lp = pp = clk = 0;
	dfs3(s);
	pos[pp + 1] = lp + 1;

	int k = pos[pp];
	while (list[k] != t) ++ k;
	for (int j = pos[pp]; j < k; j ++)
		insertR(list[j], list[j + 1]);
	for (int j = k; j + 1 < pos[pp + 1] - 1; j ++)
		insertL(list[j], list[j + 1]);

	for (int i = pp - 1; i; i --) {
		/* for (int j = pos[i]; j < pos[i + 1]; j ++) */
		/* 	debug(" %d", list[j]); */
		/* debug(" !!\n"); */
		/* debug(" %d %d\n", rank(list[pos[i]]), rank(list[pos[i + 1] - 1])); */
		if (cmprank(list[pos[i]], list[pos[i + 1] - 1]))
			for (int j = pos[i]; j + 1 < pos[i + 1] - 1; j ++)
				insertR(list[j], list[j + 1]);
		else
			for (int j = pos[i]; j + 1 < pos[i + 1] - 1; j ++)
				insertL(list[j], list[j + 1]);
	}
}
// }}}

int H[maxn], hp;
void treedfs (int now) {
	if (!now) return;
	treedfs(self.lti);
	/* debug("t %d\n", now); */
	H[now] = ++ hp;
	treedfs(self.rti);
}

int main () {
	int n = read, m = read;
	for (int i = 1; i <= m; i ++) {
		int u = ex[i] = read, v = ey[i] = read;
		G[u].push_back({v, i});
		G[v].push_back({u, i});
	}
	dfs1(1);
	for (int b = bp; b; b --)
		solve(b, V[b].back(), b == 1 ? n : V[b - 1].back());
	splay(1);
	treedfs(1);
	puts("Yes");
	for (int i = 1; i <= m; i ++) {
		int u = ex[i], v = ey[i];
		if (H[u] > H[v]) std::swap(u, v);
		printf("%d %d\n", u, v);
	}
}
