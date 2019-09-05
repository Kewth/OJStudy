#if 0
2019.09.05

树上背包优化。

f[u][i] 表示 u 子树以及集合 S[u] 中必须选 u ，选 i 的最大收益。
S[u] 同样需要转移，稍后会提到。

转移枚举儿子 v ，考虑 v 选或不选，如果不选对 f[u] 没有影响，
否则令 S[v] = S[u] | T ，其中 T 是 u 已经 dp 的其他子树的点，
DP v ，得到 f[v] 贡献到 f[u] 。

实现上不需要记 S ，只需在 DP v 前把 f[v] 的初始状态设为当前的 f[u] 即可。
#endif
#include <cstdio>
#include <vector>
#define debug(...) fprintf(stderr, __VA_ARGS__)

inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 100005;
std::vector<int> G[maxn];
int *f[maxn];
int val[maxn];

int n, m;
void dp(int u) {
	/* for(int i = 1; i <= m; i ++) */
	/* 	debug(" %d", f[u][i]); */
	/* debug(" -> %d\n", u); */

	for(int v : G[u]) {
		for(int i = 0; i <= m; i ++)
			f[v][i] = f[u][i];
		dp(v);
		for(int i = 1; i <= m; i ++)
			f[u][i] = std::max(f[u][i], f[v][i]);
	}

	for(int i = m; i; i --)
		f[u][i] = f[u][i - 1] + val[u];

	/* for(int i = 1; i <= m; i ++) */
	/* 	debug(" %d", f[u][i]); */
	/* debug(" <- %d\n", u); */
}

int main() {
	n = input(), m = input() + 1;

	for(int i = 1; i <= n; i ++) {
		G[input()].push_back(i);
		val[i] = input();
	}
	for(int i = 0; i <= n; i ++)
		f[i] = new int[unsigned(m + 1)];

	dp(0);

	printf("%d\n", f[0][m]);
}
