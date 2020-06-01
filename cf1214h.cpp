#if 0
2020.05.31

  不妨假设 k > 2 ，那么对于一个点 u ，有三个分支交于 u 且任意两个分支的长度和都不小于
k - 1 ，那么一定不存在合法的染色方案。进一步的，可以发现逆命题同样成立，那么只需要换根
DP 求出每个点 u 最长的三个分支就可以判断是否有解。
  考虑如何构造一组解，找到一条直径，不妨在直径上逐个染色 1, 2, 3, ... ，那对于连到直径
上的每颗子树，看根离哪个直径端点较近就往哪个方向染色，按深度分层逐个染色即可。不难证明
如果该构造不合法，则一定不存在合法的解，换言之只要有合法解该构造就是合法的。
        ▁▃▄▄▄▃▃▃▃▄▶
      ▗▇▀▔    ▔▔▔▔
     ▄▛   ▃▅━━■▄▂
    ▟▊   ▐▘     ▀▙
   ▟▜▌   ▐▖   ▋  ▐▍
  ▟▘ ▜   ▝▀▇▆●▘  ▐▌
▗▟▘   ▜▃       ▁▅▛
▔▀▼▅▄▃▃██▅▄▄▄▅■▀▔   CopyRight :)
      ▔▔▔▔▔▔
#endif
#include <cstdio>
#include <algorithm>
#include <vector>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 200005;
std::vector<int> G[maxn];
int f[maxn], g[maxn], h[maxn];

void update (int u, int x) {
	if (x > f[u]) h[u] = g[u], g[u] = f[u], f[u] = x;
	else if (x > g[u]) h[u] = g[u], g[u] = x;
	else if (x > h[u]) h[u] = x;
}

void dp (int u, int fa) {
	for (int v : G[u])
		if (v != fa) {
			dp(v, u);
			int x = f[v] + 1;
			update(u, x);
		}
}

void dp2 (int u, int fa, int x) {
	update(u, x);
	for (int v : G[u])
		if (v != fa)
			dp2(v, u, (f[v] + 1 == f[u] ? g[u] : f[u]) + 1);
}

int pre[maxn];
int pos, max;
void find (int u, int fa, int d) {
	if (d >= max) max = d, pos = u;
	for (int v : G[u])
		if (v != fa)
			pre[v] = u, find(v, u, d + 1);
}

int tmp[maxn], ans[maxn];

void force (int u, int fa, int x, int d, int m) {
	if (x > m) x -= m;
	ans[u] = x;
	for (int v : G[u])
		if (v != fa)
			force(v, u, x + d, d, m);
}

int main () {
	int n = read, m = read;
	for (int i = 1; i < n; i ++) {
		int u = read, v = read;
		G[u].push_back(v);
		G[v].push_back(u);
	}

	if (m > 2) {
		dp(1, 0);
		dp2(1, 0, 0);
		for (int u = 1; u <= n; u ++)
			if (f[u] and g[u] and h[u] and g[u] + h[u] >= m - 1)
				return puts("No"), 0;
	}

	find(1, 0, 1);
	find(pos, 0, 1);
	for (int i = 1, x = pos; i <= max; i ++, x = pre[x])
		tmp[i] = x;

	for (int i = 1; i <= max; i ++) {
		int u = tmp[i], x = ans[tmp[i]] = (i - 1) % m + 1;
		for (int v : G[u])
			if (v != tmp[i - 1] and v != tmp[i + 1]) {
				if (i * 2 <= max)
					force(v, u, x + m - 1, m - 1, m);
				else
					force(v, u, x + 1, 1, m);
			}
	}

	puts("Yes");
	for (int u = 1; u <= n; u ++)
		printf("%d ", ans[u]);
}
