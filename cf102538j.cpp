/*
 * Author: Kewth

 * Date:
  2020.11.07

 * Solution:
  注意到树的答案始终是一，因为可以从叶子向上唯一确定每条边的边权。考虑随意求一个生成树，
然后把边分类，朴素的想法是先随意选非树边的边权，然后唯一确定树边的边权。
  但是这样不一定是对的，因为树边可能没有合法的边权分配。因此我们需要直到非树边边权满足
什么条件的时候树边有合法的边权分配。
  不妨设一个点的点权为其相邻的非树边的边权和，那么容易发现树边有合法的边权分配当且仅当
奇数深度的点和偶数深度的点的点权和相等。
  那么对于一条连接深度奇偶性不同的两点的非树边，它是可以任意选的，然后如果有 k (k > 0)
条连接深度奇偶性不同的非树边，它们的边权选取方案是 5^{k-1} 。
  由此可以得到更精简的结论：二分图的答案是 5^{n-m+1} ，有奇环的答案是 5^{n-m} 。

 * Digression:

 * CopyRight:
   __  __                  __   __
  |  |/  |.-----.--.--.--.|  |_|  |--.
  |     < |  -__|  |  |  ||   _|     |
  |__|\__||_____|________||____|__|__|

 */

#include <cstdio>
#include <algorithm>
#include <vector>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

static struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 200005, mod = 998244353;
std::vector<int> G[maxn];
int col[maxn], fuck;

void dfs (int u) {
	for (int v : G[u])
		if (!col[v])
			col[v] = 3 - col[u], dfs(v);
		else if (col[v] + col[u] != 3)
			fuck = 1;
}

int main () {
	int T = read;
	while (T --) {
		int n = read, m = read, k = m - n;
		std::fill(col, col + n + 1, 0);
		std::fill(G, G + n + 1, G[0]);
		for (int i = 1; i <= m; i ++) {
			int u = read, v = read;
			G[u].push_back(v);
			G[v].push_back(u);
		}
		for (int u = 1; u <= n; u ++)
			if (!col[u] and (fuck = 0, col[u] = 1, dfs(u), fuck) == 0)
				++ k;
		ll ans = 1;
		while (k --) (ans *= 5) %= mod;
		printf("%lld\n", ans);
	}
}
