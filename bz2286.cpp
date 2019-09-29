#if 0
2019.09.28

虚树经典题，虚树建立后 DP 设 f[u] 表示 u 到根的链没有断的情况下 u 子树的最小代价。
采用 dfs 序栈式建虚树，需要注意的是只有点出栈的时候才能连边，
入栈的点连边是不确定的，因为之后可能会有点插入栈的任何位置。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;

inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 250005;
int head[maxn], nxt[maxn << 1], to[maxn << 1], val[maxn << 1], hp = 1;
/* int vhead[maxn], vnxt[maxn], vto[maxn], vval[maxn], vhp; */
int mindis[maxn];
int id[maxn], iid[maxn], ip;
int stack[maxn], sp;
int key[maxn], ikey[maxn], kp;
int son[maxn], size[maxn], top[maxn], deep[maxn], fa[maxn];

inline void add(int u, int v, int w) {
	nxt[++ hp] = head[u];
	head[u] = hp;
	to[hp] = v;
	val[hp] = w;
}

void dfs1(int u) {
	/* debug("%d: %d\n", u, mindis[u]); */
	deep[u] = deep[fa[u]] + 1;
	size[u] = 1;
	for(int i = head[u]; i; i = nxt[i])
		if(to[i] != fa[u]) {
			fa[to[i]] = u;
			mindis[to[i]] = std::min(mindis[u], val[i]);
			dfs1(to[i]);
			size[u] += size[to[i]];
			if(size[to[i]] > size[son[u]])
				son[u] = to[i];
		}
}

void dfs2(int u) {
	iid[id[u] = ++ ip] = u;
	if(son[u]) {
		top[son[u]] = top[u];
		dfs2(son[u]);
		for(int i = head[u]; i; i = nxt[i])
			if(to[i] != fa[u] and to[i] != son[u]) {
				top[to[i]] = to[i];
				dfs2(to[i]);
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

bool cmp(int x, int y) {
	return id[x] < id[y];
}

lolong dp(int u, int m) {
	/* debug("dp %d\n", u); */
	/* for(int i = head[u]; i; i = nxt[i]) */
	/* 	debug("%d -> %d\n", u, to[i]); */
	if(key[u] <= m)
		return mindis[u];
	lolong sum = 0;
	for(int i = head[u]; i; i = nxt[i])
		sum += dp(to[i], m);
	if(u == 1) return sum;
	return std::min(lolong(mindis[u]), sum);
}

int main() {
	int n = input();
	for(int i = 1; i < n; i ++) {
		int u = input(), v = input(), w = input();
		add(u, v, w);
		add(v, u, w);
	}

	mindis[1] = 1000000000;
	dfs1(1);
	top[1] = 1;
	dfs2(1);

	for(int i = 1; i <= n; i ++)
		head[i] = 0;

	int q = input();
	while(q --) {
		int m = input();
		hp = kp = sp = 0;

		for(int i = 1; i <= m; i ++)
			ikey[i] = input();
		std::sort(ikey + 1, ikey + m + 1, cmp);

		for(int i = 1; i <= m; i ++)
			key[ikey[i]] = ++ kp;
		stack[++ sp] = 1;
		ikey[key[1] = ++ kp] = 1;

		for(int i = 1; i <= m; i ++) {
			int u = ikey[i];
			int x = stack[sp];
			int l = lca(u, x);
			/* debug("%d %d %d\n", u, x, l); */
			while(deep[l] < deep[x]) {
				int y = stack[sp];
				x = stack[-- sp];
				if(deep[l] < deep[x])
					add(x, y, 0);
				else
					add(l, y, 0);
			}
			if(deep[l] > deep[x]) {
				stack[++ sp] = l;
				ikey[key[l] = ++ kp] = l;
			}
			stack[++ sp] = u;
		}
		for(int i = 2; i <= sp; i ++)
			add(stack[i - 1], stack[i], 0);

		/* for(int i = 1; i <= kp; i ++) */
		/* 	debug(" %d", ikey[i]); */
		/* debug("\n"); */

		printf("%lld\n", dp(1, m));

		for(int i = 1; i <= kp; i ++)
			head[ikey[i]] = 0;
	}
}
