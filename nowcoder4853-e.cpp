#if 0
2020.03.27

长链剖分板子？
用长链剖分求出 f[u][i], g[u][i] 表示 u 子树内与 u 距离为 i 的点权和和数量，
更新 f, g 的时候统计答案即可。
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
	{ x = *this; this -> operator () (a...); }
} read;

const int maxn = 100005;
int head[maxn], nxt[maxn << 1], to[maxn << 1], hp = 1;
ll fpool[maxn << 1];
ll *f[maxn];
int gpool[maxn << 1];
int *g[maxn];
int deep[maxn], len[maxn];
int son[maxn];
int a[maxn];
ll ans[maxn];

inline void add(int u, int v) {
	nxt[++ hp] = head[u];
	head[u] = hp;
	to[hp] = v;
}

void dfs(int u, int fa) {
	deep[u] = deep[fa] + 1;
	for(int i = head[u]; i; i = nxt[i])
		if(to[i] != fa) {
			dfs(to[i], u);
			if(len[to[i]] > len[son[u]])
				son[u] = to[i];
		}
	len[u] = len[son[u]] + 1;
}

int k;

void dp(int u, int fa) {
	f[u][0] = a[u];
	g[u][0] = 1;
	if(son[u]) {
		f[son[u]] = f[u] + 1;
		g[son[u]] = g[u] + 1;
		dp(son[u], u);
	}

	for(int i = head[u]; i; i = nxt[i])
		if(to[i] != fa and to[i] != son[u]) {
			int v = to[i];
			f[v] = f[u] + len[u];
			g[v] = g[u] + len[u];
			dp(v, u);
			/* f[u][0] += f[v][0]; */
			/* debug("%d %d\n", u, v); */
			/* debug("%d %d\n", len[u], len[v]); */
			for(int j = 0; j < len[v]; j ++)
				if (1 <= k - j - 1 and k - j - 1 < len[u])
					/* debug("%d %d\n", k - j - 1, j), */
					ans[u] += (f[v][j] * g[u][k - j - 1] + g[v][j] * f[u][k - j - 1]);
			for(int j = 0; j < len[v]; j ++)
				f[u][j + 1] += f[v][j];
			for(int j = 0; j < len[v]; j ++)
				g[u][j + 1] += g[v][j];
		}

	/* for (int i = 0; i < len[u]; i ++) */
	/* 	debug(" %lld(%d)", f[u][i], g[u][i]); */
	/* debug(" of %d\n", u); */
}

int main () {
	int n = read;
	read(k);
	for (int i = 1; i <= n; i ++)
		read(a[i]);
	for (int i = 1; i < n; i ++) {
		int u = read, v = read;
		add(u, v);
		add(v, u);
	}
	dfs(1, 0);
	f[1] = fpool;
	g[1] = gpool;
	dp(1, 0);
	for (int i = 1; i <= n; i ++) printf("%lld ", ans[i]);
	puts("");
}
