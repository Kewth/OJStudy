#if 0
2019.09.06

直接想法是 DP 设 f[u][i] 表示 u 子树内选 i 个伐木场的最小代价。
推转移就会发现转移依赖 u 的祖先伐木场，而这没有体现在状态中，是未知的。

设 f[u][p][i] 表示 u 子树内选 i 个伐木场，u 的最近祖先伐木场为 p 的最小代价。
转移时要特殊考虑是否选 u ，即将所有 f[u][p][i] 与 f[u][u][i] 取 min 。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 105;
int head[maxn], nxt[maxn], val[maxn];
int fa[maxn];
int w[maxn];
int f[maxn][maxn][maxn];

int n, m;
void dp(int u) {
	for(int v = head[u]; v; v = nxt[v])
		dp(v);

	for(int i = 0; i <= m; i ++)
		f[u][u][i] = 1000000000;
	f[u][u][1] = 0;

	for(int v = head[u]; v; v = nxt[v])
		for(int i = m; i >= 0; i --) {
			int min = 1000000000;
			for(int j = 0; j <= i; j ++)
				min = std::min(min, f[u][u][j] + f[v][u][i - j]);
			f[u][u][i] = min;
		}

	for(int p = fa[u], sum = val[u] * w[u]; ~p; sum += val[p] * w[u], p = fa[p]) {
		for(int i = 0; i <= m; i ++)
			f[u][p][i] = 1000000000;
		f[u][p][0] = sum;

		for(int v = head[u]; v; v = nxt[v])
			for(int i = m; i >= 0; i --) {
				int min = 1000000000;
				for(int j = 0; j <= i; j ++)
					min = std::min(min, f[u][p][j] + f[v][p][i - j]);
				f[u][p][i] = min;
			}

		for(int i = 0; i <= m; i ++)
			f[u][p][i] = std::min(f[u][p][i], f[u][u][i]);
	}

	/* for(int p = u; ~p; p = fa[p]) */
	/* 	for(int i = 0; i <= m; i ++) */
	/* 		debug("f[%d][%d][%d] = %d\n", u, p, i, f[u][p][i]); */
}

int main() {
	n = input(), m = input() + 1;

	for(int i = 1; i <= n; i ++) {
		w[i] = input();
		int p = input();
		fa[i] = p;
		nxt[i] = head[p];
		head[p] = i;
		val[i] = input();
	}

	fa[0] = -1;
	dp(0);

	printf("%d\n", f[0][0][m]);
}
