#if 0
2019.07.19

朴素 DP 设 f[u][d] 表示 u 的子树每个叶子到 u 有 d 个黑点的最大黑点数。
转移有两种：
1) u 点染黑，f[u][d] = sum(f[v][d - 1]) + 1
2) u 点不染，f[u][d] = sum(f[v][d])
若一个黑点的儿子全是白点，那么把他和儿子的颜色全部翻转一定合法且答案不会减少。
由此可知 2) 合法的情况下一定不小于 1) 。
先 dfs 出 mindeep[u] 表示 u 的子树的叶子到 u 的最小深度，
用 mindeep 可以直接判断 2) 是否合法，如果 2) 合法直接转移 2) ，否则转移 1) 。
这样一来转移的方向固定，可以线性求出 f[u][mindeep[u]] 。
#endif
#include <cstdio>
#include <vector>
#include <queue>
#define debug(...) fprintf(stderr, __VA_ARGS__)

inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 100005;
std::vector<int> G[maxn];
int mindeep[maxn];

void dfs(int u, int fa) {
	mindeep[u] = maxn;
	for(int v : G[u])
		if(v != fa) {
			dfs(v, u);
			mindeep[u] = std::min(mindeep[u], mindeep[v] + 1);
		}
	if(mindeep[u] == maxn)
		mindeep[u] = 1;
}

int dp(int u, int d, int fa) {
	debug("dp %d %d\n", u, d);
	if(mindeep[u] == 1) return 1; // d must equal to 1
	bool ok = true;
	for(int v : G[u])
		if(v != fa)
			if(mindeep[v] < d)
				ok = false;
	int res = ! ok;
	for(int v : G[u])
		if(v != fa) {
			if(ok) res += dp(v, d, u);
			else res += dp(v, d - 1, u);
		}
	return res;
}

int main() {
	int n = input();
	for(int i = 1; i < n; i ++) {
		int u = input(), v = input();
		G[u].push_back(v);
		G[v].push_back(u);
	}
	dfs(1, 0);
	printf("%d\n", dp(1, mindeep[1], 0));
}
