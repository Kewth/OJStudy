#if 0
2020.03.24

假设所有 a[i] = 0 ，考虑从根开始一个个加点，每次加点都会使得当前答案乘上加的点的度数。
那么可以归纳出这种情况的答案就是所有点的度数阶乘乘积。

如果 a[i] = x ，那么 x 上的标记就要逐步移动到 i 上，
把 x 到 i 路径上的所有边按顺序设为序列 e[1], e[2], ... e[p] ，
那么这条路经相当于加上如下几条限制：
1) 设 y 是 e[j - 1] 和 e[j] 的交点，那么在 y 的所有连边中，e[j] 必须在 e[j - 1] 之后紧跟着被选。
2) 在 x 的所有连边中，e[1] 必须是第一条被选的。
3) 在 i 的所有连边中，e[p] 必须是最后一条被选的。

对于第一条限制，将 e[j - 1], e[j] 看作点并连边。
那么对于每个点单独统计，考虑其所连的边构成的导出子图，这个图必须由若干链构成。
那么这个点的贡献就是选联通块的方案数。

细节颇多。
#endif
#include <cstdio>
#include <algorithm>
#include <vector>
#include <stack>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 500005, mod = 1000000007;
int head[maxn], nxt[maxn << 1], to[maxn << 1], hp = 1;
int fa[maxn], fe[maxn], deep[maxn];
std::vector<int> G[maxn];
int tmp[maxn], tp, tmp2[maxn];
int first[maxn], last[maxn];
int deg[maxn];

inline void add(int u, int v) {
	nxt[++ hp] = head[u];
	head[u] = hp;
	to[hp] = v;
}

void dfs (int u) {
	deep[u] = deep[fa[u]] + 1;
	for (int i = head[u]; i; i = nxt[i])
		if (to[i] != fa[u]) {
			fe[to[i]] = i >> 1;
			fa[to[i]] = u;
			dfs(to[i]);
		}
}

void force (int x, int y) {
	int p = 0;
	while (deep[x] > deep[y]) {
		tmp[++ tp] = fe[x];
		x = fa[x];
	}
	while (deep[y] > deep[x]) {
		tmp2[++ p] = fe[y];
		y = fa[y];
	}
	while (x != y) {
		tmp[++ tp] = fe[x];
		x = fa[x];
		tmp2[++ p] = fe[y];
		y = fa[y];
	}
	while (p) tmp[++ tp] = tmp2[p --];
}

bool inv[maxn];
int enxt[maxn];

ll solve (std::vector<int> v, int fir, int las) {
	/* for (int x : v) debug(" %d", x); debug("\n"); */

	for (int x : v) inv[x] = 1, deg[x] = 0, enxt[x] = 0;
	for (int x : v)
		for (int y : G[x])
			if (inv[y]) {
				if (enxt[x])
					puts("0"), exit(0);
				enxt[x] = y;
				if (++ deg[y] > 1)
					puts("0"), exit(0);
			}
	for (int x : v) inv[x] = 0;

	if (enxt[las] or deg[fir] == 1)
		puts("0"), exit(0);

	int tot = 0, F = 0;
	for (int x : v)
		if (deg[x] == 0) {
			bool f = x == fir;
			++ tot;
			while (enxt[x])
				deg[x = enxt[x]] = -1;
			f &= x == las;
			F |= f;
		}

	if (F and tot > 1)
		puts("0"), exit(0);
	if (F) return 1;
	if (fir) -- tot;
	if (las) -- tot;

	for (int x : v)
		if (deg[x] == 1)
			puts("0"), exit(0);

	ll res = 1;
	for (int i = 1; i <= tot; i ++)
		(res *= i) %= mod;
	/* debug(" res = %lld\n", res); */
	return res;
}

int main () {
	int n = read;
	for (int i = 1; i < n; i ++) {
		int u = read, v = read;
		add(u, v);
		add(v, u);
	}

	dfs(1);

	int tot = 0;
	for (int u = 1; u <= n; u ++) {
		int x = read;
		if (u == x)
			puts("0"), exit(0);
		if (x) {
			/* debug("%d -> %d\n", x, u); */
			tp = 0;
			force(x, u);
			if ((tot += tp) > 2 * n - 2)
				puts("0"), exit(0);
			for (int i = 2; i <= tp; i ++)
				G[tmp[i - 1]].push_back(tmp[i]);
			if (first[x] or last[u])
				puts("0"), exit(0);
			first[x] = tmp[1];
			last[u] = tmp[tp];
		}
	}

	ll ans = 1;
	for (int u = 1; u <= n; u ++) {
		std::vector<int> v;
		for (int i = head[u]; i; i = nxt[i])
			v.push_back(i >> 1);
		/* debug("solve %d\n", u); */
		(ans *= solve(v, first[u], last[u])) %= mod;
	}

	printf("%lld\n", ans);
}
