#if 0
2019.07.27

点对的贡献不好处理，考虑把贡献放点上。
观察收费系数，发现 nB <= nA 时系数就是 B 的数量，反之是 A 的数量。
那么点对 (i, j) 的代价可以分开，在两个点分别计算后求和。
然后考虑计算每个点的代价。

点 u 的代价在点 v 上的值与 lca(u, v) 的 nA, nB 有关，不是独立的，
但 u 的祖先是 O(n) 的，每个只需关注 nB <= nA 或 nB > nA 两种，可以 O(2^n) 状压 u 点的祖先的状态。
但需要考虑不合法的情况，即 u 的某个祖先选了 nB <= nA 但是最后 nB > nA ，这是不行的。

考虑 dfs 从上至下，维护当前的状压集合，那么到了每个叶子时其祖先的状态是已知的。
每个点记 f[i] 表示管辖的叶子里有 i 个选 B 的最小代价，
若为非叶子结点，枚举当前点状态后向下 dfs ，然后更新 f 的时候可以剔除不合法的情况。
若为叶子节点，通过状压集合可以 O(logN) 求出该点选 A, B 分别产生的代价，即 f[0], f[1] 。
#endif
#include <cstdio>
#include <algorithm>
#include <climits>
#define debug(...) fprintf(stderr, __VA_ARGS__)

inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 1030;
int L[maxn], R[maxn];
int cost[maxn][maxn];
int color[maxn];
int leaf[maxn];

void dfs(int l, int r, int S, int deep, int *f) {
	if(l == r) {
		f[! color[l]] = leaf[l];
		f[color[l]] = 0;
		while(deep --) {
			int mid = (L[deep] + R[deep]) >> 1;
			if(l <= mid)
				f[! (S >> deep & 1)] += cost[l][R[deep]] - cost[l][mid];
			else
				f[! (S >> deep & 1)] += cost[l][mid] - cost[l][L[deep] - 1];
		}
		// debug("leaf %d, S=%d, A=%d, B=%d\n", l, S, f[0], f[1]);
	} else {
		int mid = (l + r) >> 1, len = r - l + 1;
		int *lf = new int[(len >> 1) + 5], *rf = new int[(len >> 1) + 5];
		L[deep] = l;
		R[deep] = r;
		dfs(l, mid, S, deep + 1, lf);
		dfs(mid + 1, r, S, deep + 1, rf);
		for(int i = 0; i <= len; i ++)
			f[i] = INT_MAX;
		for(int i = 0; i <= (len >> 1); i ++)
			for(int j = 0; j <= i; j ++)
				if(j <= (len >> 1) and i - j <= (len >> 1))
					f[i] = std::min(f[i], lf[j] + rf[i - j]);
		// debug("%d-%d, S=%d, len=%d:\n", l, r, S, len);
		// debug(">%d %d %d %d\n", lf[0], lf[1], rf[0], rf[1]);
		// for(int i = 0; i <= len; i ++)
			// debug(" %d", f[i]);
		// debug("\n");
		dfs(l, mid, S | (1 << deep), deep + 1, lf);
		dfs(mid + 1, r, S | (1 << deep), deep + 1, rf);
		for(int i = (len >> 1) + 1; i <= len; i ++)
			for(int j = 0; j <= i; j ++)
				if(j <= (len >> 1) and i - j <= (len >> 1))
					f[i] = std::min(f[i], lf[j] + rf[i - j]);
		delete [] lf;
		delete [] rf;
		// debug("%d-%d, S=%d:\n", l, r, S);
		// for(int i = 0; i <= len; i ++)
			// debug(" %d", f[i]);
		// debug("\n");
	}
}

int f[maxn];
int main() {
	int n = 1 << input();
	for(int i = 1; i <= n; i ++)
		color[i] = input();
	for(int i = 1; i <= n; i ++)
		leaf[i] = input();
	for(int i = 1; i <= n; i ++)
		for(int j = i + 1; j <= n; j ++) {
			cost[i][j] = cost[j][i] = input();
			cost[i][j] += cost[i][j - 1];
			cost[j][i] += cost[j][i - 1];
		}
	dfs(1, n, 0, 0, f);
	int ans = INT_MAX;
	for(int i = 0; i <= n; i ++)
		ans = std::min(ans, f[i]);
	printf("%d\n", ans);
}
