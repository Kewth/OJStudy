#if 0
2019.11.14

要求修改后最大的路径最小，二分 mid ，check 是否能删一条边使得所有路径长不超过 mid 。
那么对于所有长度超过 mid 的路径，必须从中删一条 x - mid 的边，其中 x 是该路径的长度。
由于只能删一条边使得所有路径满足要求，那么实际上就是要删掉一条长度超过 max(x) - mid 的边。
只需要求出所有路径的交，并判断是否存在一条长度满足要求的边在其中即可。
求路径交可以树上差分对路径所有边进行标记，被标记恰好 m 次的边就在交中。

luogu(2s) 随便过，然而 loj(1.5s)/uoj(1s) 有一个点十分卡常，需要一些高超的技巧。
比如二分后 check 的 dfs 可以通过预先处理 dfs 序从而改成一个 for 循环。
再比如用树剖求 lca （事实证明树剖在实践中远远比倍增快）。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
} read;

const int maxn = 300005, maxk = 20;
int head[maxn], nxt[maxn << 1], to[maxn << 1], val[maxn << 1], hp = 1;

inline void add(int u, int v, int w) {
	nxt[++ hp] = head[u];
	head[u] = hp;
	to[hp] = v;
	val[hp] = w;
}

int fa[maxn], top[maxn], size[maxn], son[maxn];
int deep[maxn];
int dis[maxn];
int id[maxn], iid[maxn], ip;

void dfs1(int u) {
	deep[u] = deep[fa[u]] + 1;
	size[u] = 1;
	for(int i = head[u]; i; i = nxt[i])
		if(to[i] != fa[u]) {
			fa[to[i]] = u;
			dis[to[i]] = dis[u] + val[i];
			dfs1(to[i]);
			size[u] += size[to[i]];
			if(size[to[i]] > size[son[u]])
				son[u] = to[i];
		}
}

void dfs2(int u) {
	iid[id[u] = ++ ip] = u;
	if(!top[u]) top[u] = u;
	if(son[u]) {
		top[son[u]] = top[u];
		dfs2(son[u]);
		for(int i = head[u]; i; i = nxt[i])
			if(to[i] != fa[u] and to[i] != son[u])
				dfs2(to[i]);
	}
}

int lca(int x, int y) {
	while(top[x] != top[y]) {
		if(deep[top[x]] > deep[top[y]]) x = fa[top[x]];
		else y = fa[top[y]];
	}
	return deep[x] > deep[y] ? y : x;
}

int mark[maxn];
bool check(int need, int tot) {
	for(int i = ip; i; i --) {
		int u = iid[i];
		if(mark[u] == tot and dis[u] - dis[fa[u]] >= need) return 1;
		mark[fa[u]] += mark[u];
	}
	return 0;
}

int mu[maxn], mv[maxn], mlca[maxn], mlen[maxn];

int main() {
	int n = read, m = read;
	for(int i = 1; i < n; i ++) {
		int u = read, v = read, w = read;
		add(u, v, w);
		add(v, u, w);
	}

	dfs1(1);
	dfs2(1);

	int maxlen = 0;
	for(int i = 1; i <= m; i ++) {
		read(mu[i], mv[i]);
		mlca[i] = lca(mu[i], mv[i]);
		mlen[i] = dis[mu[i]] + dis[mv[i]] - (dis[mlca[i]] << 1);
		maxlen = std::max(maxlen, mlen[i]);
		/* debug("%d %d\n", mlca[i], mlen[i]); */
	}

	int l = 0, r = maxlen;
	while(l < r) {
		int mid = (l + r) >> 1;

		for(int i = 1; i <= n; i ++)
			mark[i] = 0;

		int tot = 0;
		for(int i = 1; i <= m; i ++)
			if(mlen[i] > mid) {
				++ tot;
				++ mark[mu[i]];
				++ mark[mv[i]];
				mark[mlca[i]] -= 2;
			}

		if(check(maxlen - mid, tot))
			r = mid;
		else
			l = mid + 1;
	}

	printf("%d\n", l);
}
