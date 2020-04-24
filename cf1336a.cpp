#if 0
2020.04.23

  一个点如果被选了，那么它的所有子树都一定要被选。据此可以单独算出选择每个点新产生的贡献，
按贡献从大到小选择即可。
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
int size[maxn];
int a[maxn];

void dfs (int u, int fa, int d) {
	size[u] = 1;
	for (int v : G[u])
		if (v != fa) {
			dfs(v, u, d + 1);
			size[u] += size[v];
		}
	a[u] = d - size[u];
}

int main () {
	int n = read, m = read;
	for (int i = 1; i < n; i ++) {
		int u = read, v = read;
		G[u].push_back(v);
		G[v].push_back(u);
	}

	dfs(1, 0, 1);
	std::sort(a + 1, a + n + 1);
	ll ans = 0;
	for (int i = 0; i < m; i ++)
		ans += a[n - i];
	printf("%lld\n", ans);
}
