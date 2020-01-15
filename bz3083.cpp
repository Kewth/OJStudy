#if 0
2020.01.15

不考虑换根操作的情况下可以用树剖 + 线段树维护一颗定根树。
事实上换根也很简单，仍然维护定根树，对询问点 u 与当前根 rt 的位置关系讨论一下，
有三种可能：
1) u = rt, 全局询问
2) rt 在 u 的子树内，找到 rt 的祖先 u 的儿子 x ，询问是 x 子树的补集
3) 其他，询问就是 x 子树
#endif
#include <cstdio>
#include <algorithm>
#include <vector>
#include <climits>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 100005;
int val[maxn << 2], lazy[maxn << 2];

inline void modi(int now, int x) {
	lazy[now] = val[now] = x;
}

inline void push_down(int now) {
	if(lazy[now]) {
		modi(now << 1, lazy[now]);
		modi(now << 1 | 1, lazy[now]);
		lazy[now] = 0;
	}
}

void modify(int now, int L, int R, int l, int r, int x) {
	if(r < L or l > R) return;
	if(l <= L and R <= r) return void(modi(now, x));
	push_down(now);
	int M = (L + R) >> 1;
	modify(now << 1, L, M, l, r, x);
	modify(now << 1 | 1, M + 1, R, l, r, x);
	val[now] = std::min(val[now << 1], val[now << 1 | 1]);
}

int query(int now, int L, int R, int l, int r) {
	if(l > r or r < L or l > R) return INT_MAX;
	if(l <= L and R <= r) return val[now];
	push_down(now);
	int M = (L + R) >> 1;
	return std::min(query(now << 1, L, M, l, r), query(now << 1 | 1, M + 1, R, l, r));
}

int fa[maxn], top[maxn], size[maxn], son[maxn], deep[maxn];
std::vector<int> G[maxn];
void dfs1(int u) {
	deep[u] = deep[fa[u]] + 1;
	size[u] = 1;
	for(int v : G[u])
		if(v != fa[u]) {
			fa[v] = u;
			dfs1(v);
			if(size[v] > size[son[u]])
				son[u] = v;
			size[u] += size[v];
		}
}

int id[maxn], ip;
void dfs2(int u) {
	if(!top[u])
		top[u] = u;
	id[u] = ++ ip;
	if(son[u]) {
		top[son[u]] = top[u];
		dfs2(son[u]);
		for(int v : G[u])
			if(v != son[u] and v != fa[u])
				dfs2(v);
	}
}

int find(int x, int y) {
	while(top[x] != top[y]) {
		x = top[x];
		if(fa[x] == y)
			return x;
		x = fa[x];
	}
	return son[y];
}

int main() {
	int n = read, q = read;
	for(int i = 1; i < n; i ++) {
		int u = read, v = read;
		G[u].push_back(v);
		G[v].push_back(u);
	}

	dfs1(1);
	dfs2(1);

	for(int i = 1; i <= n; i ++)
		modify(1, 1, n, id[i], id[i], read);

	int rt = read;
	while(q --) {
		int o = read;
		if(o == 1)
			rt = read;
		if(o == 2) {
			int x = read, y = read, w = read;
			while(top[x] != top[y]) {
				if(top[deep[x]] < top[deep[y]]) std::swap(x, y);
				modify(1, 1, n, id[top[x]], id[x], w);
				x = fa[top[x]];
			}
			if(deep[x] < deep[y]) std::swap(x, y);
			modify(1, 1, n, id[y], id[x], w);
		}
		if(o == 3) {
			int u = read;
			if(u == rt)
				printf("%d\n", query(1, 1, n, 1, n));
			else if(id[u] < id[rt] and id[rt] < id[u] + size[u]) {
				u = find(rt, u);
				printf("%d\n", std::min(query(1, 1, n, 1, id[u] - 1),
							query(1, 1, n, id[u] + size[u], n)));
			}
			else
				printf("%d\n", query(1, 1, n, id[u], id[u] + size[u] - 1));
		}
	}
}
