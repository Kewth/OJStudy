#if 0
2019.08.19

要求满足条件的三元组 (x, y, z) 数量，
假设 x, y, z 之间的割点为 l ，x, y, z 之间的 lca 为 r ，
由于三元组无序，不妨设 lca(x, y) = l ，那么 x 和 y 的深度相等。
那么把这个三元组的贡献记在 r 上，考虑 DP 统计。
设 f[u][i] 表示 u 作为 r 子树内 (x, y) 的数量，满足 x 到 l 的距离比 l 到 r 的距离多 i 。
设 g[u][i] 表示 u 作为 r 子树内 (z) 的数量，满足 z 到 r 的距离为 i 。
那么 u 的两个儿子 v1, v2 的 f[v1][i] 与 g[v2][i] 相乘即可得到贡献。
#endif
#include <cstdio>
#include <vector>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;
inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 100005;
std::vector<int> G[maxn];
int len[maxn], son[maxn];
lolong *f[maxn], *g[maxn];
lolong memory_pool[maxn << 1];

void dfs(int u, int fa) {
	for(int v : G[u])
		if(v != fa) {
			dfs(v, u);
			if(len[v] > len[son[u]])
				son[u] = v;
		}
	len[u] = len[son[u]] + 1;
}

lolong ans = 0;
void dp(int u, int fa) {
	f[u][0] = 1;
	if(son[u]) {
		f[son[u]] = f[u] + 1;
		g[son[u]] = g[u] - 1;
		g[u][-1] = 0;
		dp(son[u], u);
		ans += g[son[u]][1];
		for(int v : G[u])
			if(v != fa and v != son[u]) {
				f[v] = f[u] + len[u];
				g[v] = g[u] - len[v];
				for(int i = 0; i < len[v]; i ++)
					g[v][i] = 0;
				dp(v, u);
				for(int i = 0; i < len[v]; i ++) {
					if(i) ans += g[v][i] * f[u][i - 1];
					ans += f[v][i] * g[u][i + 1];
				}
				for(int i = 0; i < len[v]; i ++) {
					g[u][i + 1] += f[v][i] * f[u][i + 1];
					if(i) g[u][i - 1] += g[v][i];
					f[u][i + 1] += f[v][i];
				}
			}
	}
}

int main() {
	int n = input();
	for(int i = 1; i < n; i ++) {
		int u = input(), v = input();
		G[u].push_back(v);
		G[v].push_back(u);
	}
	dfs(1, 0);
	f[1] = memory_pool;
	g[1] = memory_pool + (maxn << 1) - len[1];
	dp(1, 0);
	printf("%lld\n", ans);
}
