#if 0
2019.08.29

暴力的背包设 f[u][i] 表示 u 子树中大小为 i 的最大收益，可以 O(n^3) 得出答案。
然而这是一个没有修改的子树问题，单点的对 f[u] 的贡献是 O(n) 的。
Dsu on tree 即可做到 O(n^2 logn) 。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;
inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 5050;
int head[maxn], nxt[maxn << 1], to[maxn << 1], hp;
int size[maxn], son[maxn];
int w[maxn], a[maxn];
lolong ans[maxn][maxn];
lolong f[maxn];

inline void add(int u, int v) {
	nxt[++ hp] = head[u];
	head[u] = hp;
	to[hp] = v;
}

void dfs1(int u, int fa) {
	size[u] = 1;
	for(int i = head[u]; i; i = nxt[i])
		if(to[i] != fa) {
			dfs1(to[i], u);
			if(size[to[i]] > size[son[u]])
				son[u] = to[i];
			size[u] += size[to[i]];
		}
}

void update(int u) {
	for(int i = maxn - 1; i >= a[u]; i --)
		f[i] = std::max(f[i - a[u]] + w[u], f[i]);
}

void clear() {
	std::fill(f, f + maxn, 0);
}

void dfs2(int u, int fa) {
	update(u);
	for(int i = head[u]; i; i = nxt[i])
		if(to[i] != fa)
			dfs2(to[i], u);
}

void dfs3(int u, int fa) {
	clear();

	for(int i = head[u]; i; i = nxt[i])
		if(to[i] != fa and to[i] != son[u])
			dfs3(to[i], u);

	if(son[u])
		dfs3(son[u], u);

	update(u);
	for(int i = head[u]; i; i = nxt[i])
		if(to[i] != fa and to[i] != son[u])
			dfs2(to[i], u);

	for(int i = 1; i < maxn; i ++)
		ans[u][i] = std::max(ans[u][i - 1], f[i]);
}

int main() {
	/* freopen("A.in", "r", stdin); */
	/* freopen("A.out", "w", stdout); */

	int n = input();

	for(int i = 1; i < n; i ++) {
		int u = input(), v = input();
		add(u, v);
		add(v, u);
	}

	for(int i = 1; i <= n; i ++) {
		w[i] = input();
		a[i] = input();
	}

	dfs1(1, 0);

	dfs3(1, 0);

	int q = input();
	while(q --) {
		int u = input(), x = input();
		printf("%lld\n", ans[u][x]);
	}
}
