#if 0
2019.09.17

分两种情况： a 是 b 的祖先，或者 b 是 a 的祖先。
b 是 a 的祖先很好算，此时 a 的子树都可以做 c 。
接下来考虑统计 a 是 b 祖先的情况。

此时 a 的子树中与 a 距离大于 1 的都可以做 c ，但是每个 c 对应的 b 的方案不同。
具体地，对于 ac 距离在 d = [2, k] 的 c ，对应的 b 有 d - 1 种方案。
对于 ac 距离大于 k 的 c ，对应的 b 都恰有 k 种方案。

ac 距离大于 k 的 c 的贡献总共是 f[u][k + 1] * k ，
其中 f[u][x] 表示 u 子树距离至少为 x 的点数，这可以用长链剖分 O(n) 处理。

ac 距离在 [2, k] 的 c 的贡献有点麻烦，因为不同深度的点贡献不同，
但是贡献系数差等于深度差，据此考虑把贡献系数改为 deep[c] ，
那么算出来后再减去 (点数 * (deep[u] + 1)) 即可，即 (f[u][1] - f[u][k + 1]) * (deep[u] + 1) 。
设 g[u][x] 表示 u 子树距离至少为 x 的点做 c 在这种情况下的贡献。
那么这部分的贡献就是 g[u][1] - g[u][k + 1] ，再减去上述部分。
同样 g[u][x] 可以用长链剖分 O(n) 处理。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;
inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 300005;
int head[maxn], nxt[maxn << 1], to[maxn << 1], hp;
int fpool[maxn << 1];
int *f[maxn];
lolong gpool[maxn << 1];
lolong *g[maxn];
int Q[maxn], qn[maxn], K[maxn];
lolong ans[maxn];
int deep[maxn], len[maxn];
int son[maxn];

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

void dp(int u, int fa) {
	f[u][0] = 1;
	g[u][0] = deep[u];
	if(son[u]) {
		f[son[u]] = f[u] + 1;
		g[son[u]] = g[u] + 1;
		dp(son[u], u);
		f[u][0] += f[son[u]][0];
		g[u][0] += g[son[u]][0];
	}

	for(int i = head[u]; i; i = nxt[i])
		if(to[i] != fa and to[i] != son[u]) {
			int v = to[i];
			f[v] = f[u] + len[u];
			g[v] = g[u] + len[u];
			dp(v, u);
			f[u][0] += f[v][0];
			g[u][0] += g[v][0];
			for(int j = 0; j < len[v]; j ++) {
				f[u][j + 1] += f[v][j];
				g[u][j + 1] += g[v][j];
			}
		}

	auto F = [=](int x) {
		return x >= len[u] ? 0 : f[u][x];
	};
	auto G = [=](int x) {
		return x >= len[u] ? 0 : g[u][x];
	};

	for(int i = Q[u]; i; i = qn[i]) {
		int k = K[i];
		ans[i] = 1ll * std::min(deep[u], k) * F(1) +
				1ll * k * F(k + 1) +
				(G(1) - G(k + 1)) -
				1ll * (F(1) - F(k + 1)) * (deep[u] + 1);
		/* debug("%d: %lld+%lld+%lld-%lld\n", i, */
		/* 		1ll * std::min(deep[u], k) * F(1), */
		/* 		1ll * k * F(k + 1), */
		/* 		(G(1) - G(k + 1)), */
		/* 		1ll * (F(1) - F(k + 1)) * (deep[u] + 1)); */
	}

	/* for(int i = 0; i < len[u]; i ++) */
	/* 	debug(" %d", f[u][i]); */
	/* debug(" in f[%d]\n", u); */
	/* for(int i = 0; i < len[u]; i ++) */
	/* 	debug(" %lld", g[u][i]); */
	/* debug(" in g[%d]\n", u); */
}

int main() {
	int n = input(), q = input();

	for(int i = 1; i < n; i ++) {
		int u = input(), v = input();
		add(u, v);
		add(v, u);
	}

	for(int i = 1; i <= q; i ++) {
		int u = input();
		qn[i] = Q[u];
		Q[u] = i;
		K[i] = input();
	}

	deep[0] = -1;
	dfs(1, 0);
	f[1] = fpool;
	g[1] = gpool;
	dp(1, 0);

	for(int i = 1; i <= q; i ++)
		printf("%lld\n", ans[i]);
}
