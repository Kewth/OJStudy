#if 0
2019.12.11

设 x[u] 表示 u 子树内和 u 颜色相同的点权和，对应的 y[u] 表示颜色不同的点权和。
那么 x[u] 是确定的，简单的贪心策略可知要在此基础上最小化 y[u] 的值。
对于点 u ，假设已经计算出所有儿子 v 的最小 y[u] 。
那么每个儿子 v 有两种可能，分别是 v 与 u 颜色相同与否。
设所有与 u 颜色相同/不同的儿子集合为 S/T ，
记 X = sum_x(S) + sum_y(T), Y = sum_y(S) + sum_x(T) ，
那么只要 X <= x[u] 就可以将 u 附一个非负权值使得 u 子树颜色相同的点权和恰为 x[u] ，
自然有 y[u] = Y ，由于 X + Y 是常量，最小化 Y 等价于最大化 X ，
最大化 X 可以用 01 背包处理出所有可能的 X 值，取个最大的即可，
如果没有合法的 X ，全局无解。
#endif
#include <cstdio>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
} read;

const int maxn = 1010, maxv = 5050;
int head[maxn], nxt[maxn];
int fa[maxn];
int a[maxn];
bool f[maxn][maxv];

bool dfs(int u, int &x, int &y) {
	int sum = 0;
	f[u][0] = 1;

	for(int v = head[u]; v; v = nxt[v]) {
		int vx, vy;
		if(!dfs(v, vx, vy)) return 0;
		sum += vx + vy;

		for(int k = a[u]; k >= 0; k --)
			f[u][k] = (k >= vx ? f[u][k - vx] : 0) | (k >= vy ? f[u][k - vy] : 0);
	}

/* 	for(int k = 0; k <= a[u]; k ++) */
/* 		debug("%d", f[u][k]); */
/* 	debug("\n"); */

	int use = a[u];
	while(use >= 0 and !f[u][use]) -- use;
	if(use < 0) return 0;

	x = a[u];
	y = sum - use;

	/* debug("%d: use=%d x=%d y=%d\n", u, use, x, y); */
	return 1;
}

int main() {
	int n = read;
	for(int i = 2; i <= n; i ++) {
		read(fa[i]);
		nxt[i] = head[fa[i]];
		head[fa[i]] = i;
	}

	for(int i = 1; i <= n; i ++)
		read(a[i]);

	int x, y;
	if(dfs(1, x, y)) puts("POSSIBLE");
	else puts("IMPOSSIBLE");
}
