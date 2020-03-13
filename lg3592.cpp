#if 0
2020.03.11

首先可以将 c 离散化，因为最后每个点的价格一定是取某个 c 。
区间 DP 设 f[l][r][x] 表示只考虑区间 [l, r] 内，价格的最小值为 x 的最大收益。
转移枚举最小值的位置 k ，然后后缀和优化一下即可。
由于要输出方案，需要记录转移方向。
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

const int maxn = 53, maxm = 4040;
int f[maxn][maxn][maxm], g[maxn][maxn][maxm];
int fp[maxn][maxn][maxm], gp[maxn][maxn][maxm];
int tot[maxn];
struct Car {
	int l, r, c;
} ca[maxm];

int ans[maxn];
int tmp[maxm], tp;

void solve(int l, int r, int min) {
	if(l > r) return;
	int x = gp[l][r][min];
	int k = fp[l][r][x];
	ans[k] = tmp[x];
	solve(l, k - 1, x);
	solve(k + 1, r, x);
}

int main() {
	int n = read, m = read;
	for(int i = 1; i <= m; i ++) {
		ca[i].l = read;
		ca[i].r = read;
		ca[i].c = read;
	}

	std::sort(ca + 1, ca + m + 1, [](Car a, Car b) {
				return a.c < b.c;
			});

	for(int i = 1; i <= m; i ++)
		if(ca[i].c > ca[i - 1].c)
			tmp[++ tp] = ca[i].c;

	for(int l = n; l; l --)
		for(int r = l; r <= n; r ++) {
			for(int k = l; k <= r; k ++)
				tot[k] = 0;
			int p = m;
			for(int x = tp; x; x --) {
				while(ca[p].c >= tmp[x]) {
					if(l <= ca[p].l and ca[p].r <= r)
						for(int k = ca[p].l; k <= ca[p].r; k ++)
							++ tot[k];
					-- p;
				}
				int &F = f[l][r][x];
				for(int k = l; k <= r; k ++) {
					int G = tmp[x] * tot[k] +
						g[l][k - 1][x] + g[k + 1][r][x];
					if(G >= F) {
						F = G;
						fp[l][r][x] = k;
					}
				}
				int G = g[l][r][x + 1];
				g[l][r][x] = F >= G ? F : g[l][r][x + 1];
				gp[l][r][x] = F >= G ? x :gp[l][r][x + 1];
			}
		}

	printf("%d\n", g[1][n][1]);
	solve(1, n, 1);
	for(int i = 1; i <= n; i ++)
		printf("%d ", ans[i]);
	puts("");
}
