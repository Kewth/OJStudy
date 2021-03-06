#if 0
2019.08.29

Dsu on tree
轻重链剖分后，每个点继承重儿子信息再暴力 dfs 每个轻儿子子树。
由于每个点到根经过的链数是 log 的，所以每个点被暴力 dfs 的次数也是 log 。
#endif
#include <cstdio>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;
inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 100005;
int head[maxn], nxt[maxn << 1], to[maxn << 1], hp;
int c[maxn];
int size[maxn], son[maxn];
int tot[maxn], max;
lolong sum[maxn];
lolong ans[maxn];

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

void update(int u, int typ) {
	sum[tot[c[u]]] -= c[u];
	tot[c[u]] += typ;
	sum[tot[c[u]]] += c[u];

	if(sum[max + 1])
		max ++;
	else if(not sum[max])
		max --;
}

void dfs2(int u, int fa, int typ) {
	update(u, typ);
	for(int i = head[u]; i; i = nxt[i])
		if(to[i] != fa)
			dfs2(to[i], u, typ);
}

void dfs3(int u, int fa) {
	for(int i = head[u]; i; i = nxt[i])
		if(to[i] != fa and to[i] != son[u]) {
			dfs3(to[i], u);
			dfs2(to[i], u, -1);
		}

	if(son[u])
		dfs3(son[u], u);

	update(u, 1);
	for(int i = head[u]; i; i = nxt[i])
		if(to[i] != fa and to[i] != son[u])
			dfs2(to[i], u, 1);

	ans[u] = sum[max];
}

int main() {
	int n = input();
	for(int i = 1; i <= n; i ++)
		c[i] = input();

	for(int i = 1; i < n; i ++) {
		int u = input(), v = input();
		add(u, v);
		add(v, u);
	}

	dfs1(1, 0);

	dfs3(1, 0);

	for(int i = 1; i <= n; i ++)
		printf("%lld ", ans[i]);
	puts("");
}
