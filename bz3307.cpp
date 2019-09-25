#if 0
2019.09.25

将操作进行树上差分放在点上，问题转换为统计子树内出现次数最多的标记。
这种子树问题 Dsu On Tree 统计即可，
注意到有的标记表示删除，而删掉一个标记并不能 O(1) 维护出现次数最多的标记，
需要对每个出现次数开 set 维护。
#endif
#include <cstdio>
#include <set>
#define debug(...) fprintf(stderr, __VA_ARGS__)

inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 100005, maxk = 20; int head[maxn], nxt[maxn << 1], to[maxn << 1], hp = 1;
int size[maxn], son[maxn], top[maxn];
int deep[maxn], fa[maxn];
int id[maxn], iid[maxn], ip;
int ans[maxn];
int sadd[maxn], snxt[maxn * 6], sval[maxn * 6], sp;
bool sdel[maxn * 6];
int tot[maxn];
std::set<int> set[maxn << 1];

inline void add(int u, int v) {
	nxt[++ hp] = head[u];
	head[u] = hp;
	to[hp] = v;
}

void dfs1(int u) {
	iid[id[u] = ++ ip] = u;
	size[u] = 1;
	deep[u] = deep[fa[u]] + 1;
	for(int i = head[u]; i; i = nxt[i])
		if(to[i] != fa[u]) {
			fa[to[i]] = u;
			dfs1(to[i]);
			size[u] += size[to[i]];
			if(size[to[i]] > size[son[u]])
				son[u] = to[i];
		}
}

void dfs2(int u) {
	if(!top[u])
		top[u] = u;
	top[son[u]] = top[u];
	if(son[u]) {
		dfs2(son[u]);
		for(int i = head[u]; i; i = nxt[i])
			if(to[i] != fa[u] and to[i] != son[u])
				dfs2(to[i]);
	}
}

int lca(int x, int y) {
	while(top[x] != top[y]) {
		if(deep[top[x]] < deep[top[y]])
			y = fa[top[y]];
		else
			x = fa[top[x]];
	}
	return deep[x] < deep[y] ? x : y;
}

int max;
void update(int u, int typ) {
	for(int i = sadd[u]; i; i = snxt[i]) {
		set[tot[sval[i]]].erase(sval[i]);
		/* debug("erase %d\n", tot[sval[i]]); */
		if(set[max].empty())
			max --;

		if(sdel[i])
			tot[sval[i]] -= typ;
		else
			tot[sval[i]] += typ;

		set[tot[sval[i]]].insert(sval[i]);
		/* debug("insert %d\n", tot[sval[i]]); */
		if(!set[max + 1].empty())
			max ++;
		if(!set[max + 2].empty())
			max += 2;
		/* debug("max %d\n", max); */
	}
}

void dsu(int u, int typ) {
	for(int x = id[u]; x < id[u] + size[u]; x ++)
		update(iid[x], typ);
}

void dfs(int u) {
	max = maxn;
	if(son[u]) {
		for(int i = head[u]; i; i = nxt[i])
			if(to[i] != fa[u] and to[i] != son[u]) {
				dfs(to[i]);
				dsu(to[i], -1);
			}
		dfs(son[u]);
	}

	update(u, 1);
	for(int i = head[u]; i; i = nxt[i])
		if(to[i] != fa[u] and to[i] != son[u])
			dsu(to[i], 1);
	ans[u] = *set[max].begin();

	/* debug("%d: %d %d (%d)\n", u, tot[1], tot[2], max); */
	/* for(int i = sadd[u]; i; i = snxt[i]) */
	/* 	debug("%c%d\n", "+-"[sdel[i]], sval[i]); */
}

inline void adds(int u, int z, bool del) {
	snxt[++ sp] = sadd[u];
	sadd[u] = sp;
	sval[sp] = z;
	sdel[sp] = del;
}

int main() {
	for(int i = 0; i < maxn; i ++) {
		tot[i] = maxn;
		set[maxn].insert(i);
	}

	int n = input(), m = input();

	for(int i = 1; i < n; i ++) {
		int u = input(), v = input();
		add(u, v);
		add(v, u);
	}

	dfs1(1);
	dfs2(1);

	for(int i = 1; i <= m; i ++) {
		int x = input(), y = input(), l = lca(x, y), z = input();
		/* debug("%d %d %d\n", x, y, l); */
		adds(x, z, 0);
		adds(y, z, 0);
		adds(l, z, 1);
		if(fa[l])
			adds(fa[l], z, 1);
	}

	dfs(1);

	for(int i = 1; i <= n; i ++)
		printf("%d\n", ans[i]);
}
