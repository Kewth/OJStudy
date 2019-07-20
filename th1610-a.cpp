#if 0
2019.07.06

直接 DP ，设 f[u][k][0/1/2] 表示 u 的子树选 k 条链的最大收益，
0/1/2 表示随意/有链的起点为 u /有链的 lca 为 u 。
似乎在转移中优化枚举上下界就可以了。

DP 时记录 pre[v][k][b] 表示 f[fa[v]][k][b] 在 v 上的转移方向，
输出方案就模拟一遍 DP 过程，在递归中返回链的一端。
#endif
#include <cstdio>
#include <vector>
#include <stack>
#include <cassert>
#define debug(...) // fprintf(stderr, __VA_ARGS__)

inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 10005, maxm = 505;
std::vector<int> G[maxn];
int f[maxn][maxm][3], g[maxm][3], fmax[maxn][maxm];
int size[maxn];
int prex[maxn][maxm][3], prey[maxn][maxm][3];

inline void update(int u, int i, int b, int v, int j, int c, int val) {
	if(i and g[j][c] + val > f[u][i][b]) {
		f[u][i][b] = g[j][c] + val;
		prex[v][i][b] = j;
		prey[v][i][b] = c;
	}
}

void dp(int u, int fa, int m) {
	f[u][1][0] = f[u][0][1] = f[u][0][2] = - 100000000;
	f[u][1][1] = f[u][1][2] = 1;
	size[u] = 1;
	for(int v : G[u])
		if(v != fa) {
			dp(v, u, m);
			debug("trans %d -> %d\n", v, u);
			for(int i = 0; i <= size[u] + size[v] and i <= m; i ++)
				for(int b = 0; b < 3; b ++)
					prex[v][i][b] = prey[v][i][b] = -1;
			for(int i = 0; i <= size[u] and i <= m; i ++)
				for(int b = 0; b < 3; b ++)
					g[i][b] = f[u][i][b];
			for(int i = 0; i <= size[u] and i <= m; i ++)
				for(int j = 0; j <= size[v] and i + j <= m; j ++) {
					update(u, i + j, 0, v, i, 0, fmax[v][j]);
					update(u, i + j, 1, v, i, 0, f[v][j][1] + 1);
					update(u, i + j, 1, v, i, 1, fmax[v][j]);
					if(j + 1 <= size[v] and j + 1 <= m)
						update(u, i + j, 2, v, i, 1, f[v][j + 1][1]);
					update(u, i + j, 2, v, i, 2, fmax[v][j]);
				}
			size[u] += size[v];
		}
	for(int i = 1; i <= size[u] and i <= m; i ++) {
		fmax[u][i] = 0;
		for(int b = 0; b < 3; b ++)
			fmax[u][i] = std::max(fmax[u][i], f[u][i][b]);
		debug("f[%d][%d]: %d %d %d -> %d\n",
				u, i, f[u][i][0], f[u][i][1], f[u][i][2], fmax[u][i]);
	}
}

int print(int u, int fa, int k, int b) {
	if(b == -1) {
		debug("print %d %d max\n", u, k);
		for(int c = 0; c < 3; c ++)
			if(f[u][k][c] == fmax[u][k]) {
				int s = print(u, fa, k, c);
				if(s) {
					assert(c == 1);
					printf("%d %d\n", u, s);
				}
				return s;
			}
		return 0;
	}
	int s = 0;
	debug("print %d %d %d, %d\n", u, k, b, s);
	std::stack<int> st;
	for(int v : G[u])
		if(v != fa)
			st.push(v);
	while(not st.empty()) {
		int v = st.top();
		st.pop();
		int x = prex[v][k][b], y = prey[v][k][b];
		if(x == -1) {
			assert(y == -1);
			continue;
		}
		if(y == b)
			print(v, u, k - x, -1);
		else if(b == 2) {
			assert(y == 1);
			s = print(v, u, k - x + 1, 1);
		} else {
			assert(b == 1);
			assert(y == 0);
			int t = print(v, u, k - x, 1);
			if(s) {
				printf("%d %d\n", s, t);
				s = 0;
			} else
				s = t;
		}
		k = x;
		b = y;
		debug("print %d %d %d, %d\n", u, k, b, s);
	}
	if(k == 1 and b == 1) {
		if(s) {
			printf("%d %d\n", u, s);
			s = 0;
		} else
			s = u;
	} else if(k == 1 and b == 2)
		printf("%d %d\n", u, u);
	debug("print %d 0 x, %d\n", u, s);
	return s;
}

int main() {
	while(true) {
		int n = input(), m = input();
		if(not n and not m) break;
		for(int u = 1; u <= n; u ++)
			G[u].clear();
		for(int u = 1; u <= n; u ++)
			for(int i = 1; i <= m; i ++)
				for(int b = 0; b < 3; b ++) {
					fmax[u][i] = g[i][b] = f[u][i][b] = 0;
					size[u] = 0;
					prex[u][i][b] = prey[u][i][b] = 0;
				}
		for(int i = 1; i < n; i ++) {
			int u = input(), v = input();
			G[u].push_back(v);
			G[v].push_back(u);
		}
		dp(1, 0, m);
		printf("%d\n%d\n", fmax[1][m], m);
		print(1, 0, m, -1);
	}
}
