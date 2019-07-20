#if 0
2019.07.02

设 f[i][j] 表示考虑前 i 个商店，选 j 个物品的最小代价。
转移 f[i][j] = min(f[i - 1][k] + sum[j - k])，
其中 sum[i] 表示买 i 个的代价，
且除去 k = j 的点（由于有入场费）外 f[i][j] 的最优决策 k 随 j 单调不减。
可据此进行分治 DP 。

对每个商店的 sum[1] 进行排序，那么除了前 k 个外一定不会只买一个，
否则在前 k 个买会更优，把前 k 个删去，再对 s[2] 排序，
那么除了前 k / 2 个外一定不会只买两个，以此类推，
最后只考虑删去的 klogk 个点即可。

于是复杂度瓶颈到了排序。
对 s[i] 排序时，只需考虑商品数不小于 i 的商店，用桶 v[i] 存储这些商店。
其次只需要知道前 k / i 个，不需要知道具体顺序，不用 sort 而用 nth_element 。
#endif
#include <cstdio>
#include <vector>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;
inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 2000006, maxm = 1006;
const lolong inf = 10000000000000ll;
struct Shop {
	int len, choose;
	lolong *cost, *sum;
};
Shop in[maxn], sh[maxm * 20];
lolong f[maxm], tmp[maxn];
std::vector<int> sortv[maxm];

inline void dp(int i, int l, int r, int L, int R) {
	if(l > r) return;
	int mid = (l + r) >> 1, trans = mid;
	f[mid] = inf;
	for(int x = std::max(L, mid - sh[i].len + 1);
			x <= R and x < mid; x ++) {
		if(tmp[x] + sh[i].sum[mid - x] < f[mid]) {
			f[mid] = tmp[x] + sh[i].sum[mid - x];
			trans = x;
		}
	}
	/* debug("f[%d][%d] = f[%d][%d] + %lld = %lld (in %d-%d)\n", */
	/* 		i, mid, i - 1, trans, sh[i].s(mid - trans), f[mid], L, R); */
	dp(i, l, mid - 1, L, trans);
	dp(i, mid + 1, r, trans, R);
}

int sort_id;
inline bool cmp(int x, int y) {
	if(in[x].choose == in[y].choose)
		return in[x].sum[sort_id] < in[y].sum[sort_id];
	return in[x].choose < in[y].choose;
}

int main() {
	int n = input(), m = input();
	for(int i = 1; i <= n; i ++) {
		int k = input();
		in[i].len = k + 1;
		in[i].choose = 0;
		in[i].cost = new lolong[unsigned(k + 1)];
		in[i].sum = new lolong[unsigned(k + 1)];
		for(int j = 0; j <= k; j ++)
			in[i].cost[j] = input();
		in[i].sum[0] = in[i].cost[0];
		for(int j = 1; j <= k; j ++)
			in[i].sum[j] = in[i].sum[j - 1] + in[i].cost[j];
		in[i].sum[0] = 0;
		for(int j = 1; j <= k and j <= m; j ++)
			sortv[j].push_back(i);
	}
	for(int i = 1; i <= m; i ++) {
		sort_id = i;
		int len = std::min(m / i, int(sortv[i].size()));
		std::nth_element(sortv[i].begin(), sortv[i].begin() + len,
				sortv[i].end(), cmp);
		for(int j = 0; j < len; j ++)
			in[sortv[i][unsigned(j)]].choose = 1;
	}
	int p = 0;
	for(int i = 1; i <= n; i ++)
		if(in[i].choose)
			sh[++ p] = in[i];
	for(int j = m; j; j --)
		f[j] = inf;
	for(int i = 1; i <= p; i ++) {
		for(int j = 1; j <= m; j ++)
			tmp[j] = f[j];
		dp(i, 1, m, 0, m);
		for(int j = 1; j <= m; j ++)
			f[j] = std::min(f[j], tmp[j]);
	}
	for(int j = 1; j <= m; j ++)
		printf("%lld ", f[j]);
	puts("");
}
