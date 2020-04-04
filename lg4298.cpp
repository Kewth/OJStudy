#if 0
2020.02.27

构造最长反链方案：

对于最长反链建的二分图，先考虑求出这个二分图的最小点覆盖。
先构造一组可行的点覆盖：选择左边所有点。
在二分图最大匹配的基础上，在左边从所有未匹配点开始 dfs 走增广路。
当然实际上不存在增广路，因此在未匹配边 - 匹配边的交替选择后，最后会到同一边。
那么每条路径经过的点中右边的点数总比左边的点数小 1 。
而这些点覆盖的边是相同的。
因此对于所有这样的路径，
把经过的左边的带你在点覆盖中删掉，加入所有经过的右边的点。
最后就得到了一组最小点覆盖。
而最小点覆盖的补集就是最大独立集。

通过二分图的一组最大独立集可以得出原图的一组最长反链：
对于每个点，如果它对应在二分图的两个点都在最大独立集中，
这个点就在原图对应的最长反链中。

判断一个点是否存在于某个最长反链：

强制该点存在于最长反链中，那么它以及它能到的点以及能到它的点都不能被选。
把这些点删掉再求最长反链，如果最长反链的大小恰好减少一，
就说明这个点存在于某个最长反链。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	inline operator char () { char x[3]; return scanf("%s", x), *x; }
} read;

const int maxn = 105;
bool to[maxn][maxn];
int match[maxn];
bool matched[maxn];
bool ban[maxn];

int n;
bool vis[maxn];
bool find(int x) {
	for(int y = 1; y <= n; y ++)
		if(!vis[y] and !ban[y] and to[x][y]) {
			vis[y] = 1;
			if(!match[y] or find(match[y])) {
				match[y] = x;
				matched[x] = 1;
				return 1;
			}
		}
	return 0;
}

bool visa[maxn], visb[maxn];
void dfs(int x) {
	visa[x] = 1;
	for(int y = 1; y <= n; y ++)
		if(to[x][y] and match[y] != x and !visb[y] and !visa[match[y]]) {
			visb[y] = 1;
			dfs(match[y]);
		}
}

int main() {
	n = read;

	int m = read;
	while(m --) {
		int u = read, v = read;
		to[u][v] = 1;
	}

	for(int k = 1; k <= n; k ++)
		for(int i = 1; i <= n; i ++)
			for(int j = 1; j <= n; j ++)
				to[i][j] |= to[i][k] & to[k][j];

	int tot = 0;
	for(int x = 1; x <= n; x ++) {
		std::fill(vis, vis + n + 1, 0);
		tot += find(x);
	}

	printf("%d\n", n - tot);

	for(int x = 1; x <= n; x ++)
		if(!matched[x])
			dfs(x);

	for(int i = 1; i <= n; i ++)
		printf("%d", visa[i] and !visb[i]);
	puts("");

	for(int i = 1; i <= n; i ++) {
		std::fill(ban, ban + n + 1, 0);
		std::fill(match, match + n + 1, 0);
		int t = 0;
		for(int j = 1; j <= n; j ++)
			if(i == j or to[i][j] or to[j][i]) {
				++ t;
				ban[j] = 1;
			}
		for(int x = 1; x <= n; x ++)
			if(!ban[x]) {
				std::fill(vis, vis + n + 1, 0);
				t += find(x);
			}
		printf("%d", t == tot + 1);
	}
	puts("");
}
