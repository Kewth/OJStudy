#if 0
date +%Y.%m.%d

树上带修莫队模板，用的皇室联邦分块，实现参考的 ouuan 。
#endif
#include <cstdio>
#include <algorithm>
#include <cmath>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;

inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 100005, maxk = 20;

struct Query {
	int u, v, t, id;
};

lolong ans[maxn];
int block[maxn], bp;
int fa[maxn][maxk];
int deep[maxn];
int head[maxn], nxt[maxn << 1], to[maxn << 1], hp;
int modi_x[maxn], modi_y[maxn];
int candy[maxn];
int V[maxn], W[maxn];
int times[maxn];
bool in_path[maxn];
Query qu[maxn];

inline void add(int u, int v) {
	nxt[++ hp] = head[u];
	head[u] = hp;
	to[hp] = v;
}

inline bool cmp(Query a, Query b) {
	if(block[a.u] == block[b.u])
		return block[a.v] == block[b.v] ?
			a.t < b.t : block[a.v] < block[b.v];
	return block[a.u] < block[b.u];
}

int stack[maxn], sp;
void dfs(int u, int b) {
	/* debug("dfs %d | %d | %d %d %d\n", u, deep[u], fa[u][0], fa[u][1], fa[u][2]); */

	int begin = sp;

	for(int i = head[u]; i; i = nxt[i])
		if(to[i] != fa[u][0]) {
			fa[to[i]][0] = u;
			for(int k = 1; k < maxk; k ++)
				fa[to[i]][k] = fa[fa[to[i]][k - 1]][k - 1];

			deep[to[i]] = deep[u] + 1;

			dfs(to[i], b);

			if(sp - begin >= b) {
				++ bp;
				while(sp > begin)
					block[stack[sp --]] = bp;
			}
		}

	stack[++ sp] = u;
}

int lca(int x, int y) {
	if(deep[x] < deep[y])
		std::swap(x, y);

	/* debug("%d %d\n", x, y); */

	for(int k = maxk - 1; k >= 0; k --)
		if(deep[fa[x][k]] >= deep[y])
			x = fa[x][k];

	for(int k = maxk - 1; k >= 0; k --)
		if(fa[x][k] != fa[y][k]) {
			x = fa[x][k];
			y = fa[y][k];
		}

	return x == y ? x : fa[x][0];
}

lolong now_ans;
void opp(int x) {
	if(not in_path[x])
		now_ans += 1ll * V[candy[x]] * W[++ times[candy[x]]];
	else
		now_ans -= 1ll * V[candy[x]] * W[times[candy[x]] --];
	in_path[x] ^= 1;

	/* debug("opp %d(%d) -> %lld\n", x, candy[x], now_ans); */
}

void path(int x, int y) { // not include lca
	if(deep[x] < deep[y])
		std::swap(x, y);

	while(deep[x] > deep[y]) {
		opp(x);
		x = fa[x][0];
	}

	while(x != y) {
		opp(x);
		opp(y);
		x = fa[x][0];
		y = fa[y][0];
	}
}

void modify(int t) {
	if(in_path[modi_x[t]]) {
		opp(modi_x[t]);
		std::swap(modi_y[t], candy[modi_x[t]]);
		opp(modi_x[t]);
	}
	else
		std::swap(modi_y[t], candy[modi_x[t]]);
}

int main() {
	int n = input(), m = input(), q = input();

	for(int i = 1; i <= m; i ++)
		V[i] = input();

	for(int i = 1; i <= n; i ++)
		W[i] = input();

	for(int i = 1; i < n; i ++) {
		int u = input(), v = input();
		add(u, v);
		add(v, u);
	}

	deep[1] = 1;
	dfs(1, 1 + int(pow(n, 0.66)));

	while(sp)
		block[stack[sp --]] = bp;

	/* for(int i = 1; i <= n; i ++) */
	/* 	debug(" %d", block[i]); */
	/* debug("\n"); */

	for(int i = 1; i <= n; i ++)
		candy[i] = input();

	int qup = 0, mop = 0;

	for(int i = 1; i <= q; i ++) {
		int typ = input(), x = input(), y = input();
		if(typ == 0) {
			mop ++;
			modi_x[mop] = x;
			modi_y[mop] = y;
		} else {
			qup ++;
			qu[qup].u = x;
			qu[qup].v = y;
			qu[qup].t = mop;
			qu[qup].id = qup;
		}
	}

	std::sort(qu + 1, qu + qup + 1, cmp);

	int t = 0;

	int u = 0, v = 0;
	for(int i = 1; i <= n; i ++)
		if(block[i] == 1)
			u = v = i;

	for(int i = 1; i <= qup; i ++) {
		/* debug("query %d %d %d(%d %d)\n", qu[i].u, qu[i].v, qu[i].t, u, v); */

		while(t < qu[i].t)
			modify(++ t);
		while(t > qu[i].t)
			modify(t --);

		path(qu[i].u, u);
		path(qu[i].v, v);

		u = qu[i].u;
		v = qu[i].v;
		int c = lca(u, v);

		opp(c);
		ans[qu[i].id] = now_ans;
		opp(c);
	}

	for(int i = 1; i <= qup; i ++)
		printf("%lld\n", ans[i]);
}
