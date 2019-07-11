#if 0
2019.07.11

朴素的背包 DP 为 f[i][j] 表示考虑前 i 个，价格和为 j 的最大价值和。
加点可以直接对新加节点转移，但是删点则要重构整个背包。
考虑定期重构，设当前物品区间为 [l, r] ，记录参数 x ，以 x 拆分背包，
维护 [l, x) 的从右向左的背包和 [x, r] 的从左向右的背包。
那么 r ++ 还是直接在 [x, r] 的背包上加点，l ++ 时直接在 [l, x) 上去掉一个点。
另外，当 l > x 时，令 x = r + 1 重构上述背包。
这样，每个物品只被加入到背包常数次，复杂度 O(nm) 。

计算答案时要合并背包，问题转换为已知两个定义域为 [0, m) 的函数 f, g ，
求 f(a) + g(b) 的最大值使得 (a + b) % m 在 [l, r] 内。
固定 a ，可行的 b 是一段区间，a ++ 时 b 的取值区间整个 -1 。
那么枚举 a 的同时维护 g(b) 的最大值，可以用优先队列，但是会带一个 log ，
利用区间移动的性质，也就是加一个点再删一个端点，
事实上用单调双端队列维护以 l 开头的单调递增的点可以代替优先队列。

空间似乎卡的紧，右边的背包可以滚动掉一维。
#endif
#include <cstdio>
#include <vector>
#include <queue>
#include <cassert>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;
inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 100005, maxm = 505, mod = 1000000007;
lolong f[maxn][maxm], g[2][maxm];
int w[maxn], v[maxn];
lolong que[maxm << 1];

int main() {
	int q = input(), m = input(), online = input();
	int x = 1, ans = 0, begin = 1, end = 0;
	for(int k = 0; k < m; k ++)
		f[end + 1][k] = k ? - 100000000000000000 : 0;
	for(int k = 0; k < m; k ++)
		g[end & 1][k] = k ? - 100000000000000000 : 0;
	while(q --) {
		if(input() == 1) {
			end ++;
			w[end] = input() ^ ans * online;
			v[end] = input() ^ ans * online;
			/* debug("new %d, %d\n", w[end], v[end]); */
			for(int k = 0; k < m; k ++)
				g[end & 1][k] = std::max(g[(end - 1) & 1][k],
						g[(end - 1) & 1][(k - w[end] + m) % m] + v[end]);
		} else {
			/* debug("delete\n"); */
			begin ++;
			if(begin > x) {
				for(int k = 0; k < m; k ++)
					f[end + 1][k] = k ? - 100000000000000000 : 0;
				for(int j = end; j >= x; j --) {
					for(int k = 0; k < m; k ++)
						f[j][k] = std::max(f[j + 1][k],
								f[j + 1][(k - w[j] + m) % m] + v[j]);
				}
				x = end + 1;
				for(int k = 0; k < m; k ++)
					g[end & 1][k] = k ? - 100000000000000000 : 0;
			}
		}
		assert(begin <= end + 1);
		int l = input() ^ ans * online, r = input() ^ ans * online;
		/* debug("%d - %d - %d\n", begin, x, end); */
		/* debug("ask %d-%d\n", l, r); */
		lolong fuckans = -1;
		int L = 1, R = 0;
		for(int b = r; b >= l; b --) {
			while(L <= R and g[end & 1][b] > que[R])
				R --;
			que[++ R] = g[end & 1][b];
		}
		for(int a = 0; a < m; a ++) {
			fuckans = std::max(fuckans, f[begin][a] + que[L]);
			while(L <= R and g[end & 1][(l - a - 1 + m) % m] > que[R])
				R --;
			que[++ R] = g[end & 1][(l - a - 1 + m) % m];
			if(L <= R and g[end & 1][(r - a + m) % m] == que[L])
				L ++;
		}
		printf("%lld\n", fuckans);
		if(fuckans != -1)
			ans = fuckans % mod;
	}
}
