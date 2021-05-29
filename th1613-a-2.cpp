/*
 * Author: Kewth

 * Date:
  2021.05.29

 * Solution:
  In blog.

 * Digression:
  难度：8 / 12

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

static struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 100005, maxm = 300005;

struct Splay { // {{{
	int fai, lti, rti;
} T[maxn];
#define _l T[now].lti
#define _r T[now].rti
#define _f T[now].fai

inline bool from (int now) { return T[_f].rti == now; }

void rotate (int now) {
	int p = T[_f].fai, f = _f, fr = from(now), s = fr ? _l : _r;
	if (p) (from(f) ? T[p].rti : T[p].lti) = now;
	(fr ? T[f].rti : T[f].lti) = s;
	(fr ? _l : _r) = f;
	T[s].fai = f;
	T[f].fai = now;
	_f = p;
	/* update(f), update(now); */
}

void splay (int now, int top = 0) {
	while (_f != top) {
		if (T[_f].fai != top)
			rotate(from(now) == from(_f) ? _f : now);
		rotate(now);
	}
}

void insertL (int now, int an) {
	/* debug("insertL %d %d\n", now, an); */
	if (!_l) _l = an;
	else {
		now = _l;
		while (_r) now = _r;
		_r = an;
	}
	T[an].fai = now;
	splay(an);
}
void insertR (int now, int an) {
	/* debug("insertR %d %d\n", now, an); */
	if (!_r) _r = an;
	else {
		now = _r;
		while (_l) now = _l;
		_l = an;
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
// }}}

std::vector<int> G[maxn];
int ex[maxm], ey[maxm];
int dfn[maxn], low[maxn], map[maxn], clk;
bool mark[maxn];
int fa[maxn], to[maxn];
int tmp[maxn], tp;

void dfs (int u) {
	map[low[u] = dfn[u] = ++ clk] = u;
	/* debug("dfs %d\n", u); */
	for (int v : G[u])
		if (!dfn[v]) {
			fa[v] = u;
			dfs(v);
			if (low[v] < low[u])
				low[u] = low[v], to[u] = v;
		} else if (dfn[v] < low[u])
			low[u] = dfn[v], to[u] = v;
}

void solve (int u) {
	for (int v : G[u])
		if (fa[v] == u and !mark[v]) {
			if (low[v] == dfn[u])
				puts("No"), exit(0);
			tp = 0;
			int x = v;
			while (dfn[x] != low[v])
				tmp[++ tp] = x, mark[x] = 1, x = to[x];
			tmp[0] = u;
			if (cmprank(u, x))
				for (int i = 1; i <= tp; i ++)
					insertR(tmp[i - 1], tmp[i]);
			else
				for (int i = 1; i <= tp; i ++)
					insertL(tmp[i - 1], tmp[i]);
			solve(v);
		}
}

int H[maxn], hp;
void treedfs (int now) {
	if (!now) return;
	treedfs(_l);
	/* debug("t %d\n", now); */
	H[now] = ++ hp;
	treedfs(_r);
}

int main () {
	int n = read, m = read;
	for (int i = 1; i <= m; i ++) {
		int u = ex[i] = read, v = ey[i] = read;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	dfs(1);
	tp = 0;
	for (int x = n; x; x = fa[x])
		tmp[++ tp] = x, mark[x] = 1;
	for (int i = tp - 1; i; i --)
		insertR(tmp[i + 1], tmp[i]);
	for (int i = 1; i <= clk; i ++)
		solve(map[i]);
	splay(1);
	treedfs(1);
	puts("Yes");
	for (int i = 1; i <= m; i ++) {
		int u = ex[i], v = ey[i];
		if (H[u] > H[v]) std::swap(u, v);
		printf("%d %d\n", u, v);
	}
}
