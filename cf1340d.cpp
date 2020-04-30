#if 0
2020.04.29

  设 m 是所有点的度数最大值，那么答案一定不会小于 m 。考虑构造答案恰好为 m 的方案。
  考虑当前走到了 u ，时间为 t ，目标是在回到父亲的时候 u 的时间为 t - 1 。归纳地证明这是
可行的：首先如果 u 是叶子直接时间倒流一次即可，否则对于每个儿子 v ，走到 v 的时候时间为 x
，走回来的时候时间就一定是 x + 1 。如果始终满足 x + 1 <= m ，那么在最后把时间回退到 t - 1
即可。否则，在 x = m 的时候把时间回退到一个值 y ，使得处理完所有儿子后时间恰好为 x + 1 即
可，由于度数不超过 m ，那么不同的时间数也不会超过 m ，所以这样的 y 是一定存在的。
#endif
#include <cstdio>
#include <algorithm>
#include <vector>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef std::pair<int, int> par;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 100005;
std::vector<int> G[maxn];
std::vector<par> ans;

void dfs (int u, int fa, int x, int m) {
	int f = x;
	ans.push_back(par(u, x));
	int tot = int(G[u].size() - 1);
	for (int v : G[u])
		if (v != fa) {
			if (x == m)
				ans.push_back(par(u, x = f - tot - 1));
			dfs(v, u, ++ x, m);
			-- tot;
		}
	if (u > 1) {
		if (x >= f)
			ans.push_back(par(u, x = f - 1));
		if (x < f - 1) debug("ERROR\n");
		ans.push_back(par(fa, ++ x));
	}
}

int main () {
	int n = read;
	for (int i = 1; i < n; i ++) {
		int u = read, v = read;
		G[u].push_back(v);
		G[v].push_back(u);
	}

	int m = 0;
	for (int i = 1; i <= n; i ++)
		m = std::max(m, int(G[i].size()));
	dfs(1, 0, 0, m);
	printf("%lu\n", ans.size());
	for (par p : ans)
		printf("%d %d\n", p.first, p.second);
}
