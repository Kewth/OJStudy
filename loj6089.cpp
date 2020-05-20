#if 0
2020.05.20

  设一个阈值 n^0.5 ，称不超过该值的物品为小物品，反之为大物品，考虑对于两种物品分别背包。
  对于小物品，由于数量较少，暴力背包，复杂度 O(n^1.5) 。
  对于大物品，由于大小较大，在背包中出现的个数不超过 n^0.5 ，此时每个物品实际上可以认为
没有数量限制。设 f[i][j] 表示背包里放了 i 个物品且大小为 j 的方案数，考虑对背包的物品序
列排序后差分，如果最小的物品超过 n^0.5 ，那么把所有物品大小减一，如果最小的物品大小恰为
n^0.5 ，就把这个物品去掉，得到转移 f[i][j] = f[i][j - i] + f[i - 1][j - n^0.5] 。
  两边综合统计答案即可，总复杂度 O(n^1.5) 。
#endif
#include <cstdio>
#include <cmath>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 100005, mod = 23333333;
int f[maxn], g[maxn];

inline void __a (int &x) { if (x >= mod) x -= mod; }
inline void __d (int &x) { if (x < 0) x += mod; }

int main () {
	int n = read, B = int(sqrt(n));
	f[0] = g[0] = 1;
	for (int i = 1; i <= B; i ++) {
		for (int j = i; j <= n; j ++)
			__a(f[j] += f[j - i]);
		int d = i * (i + 1);
		for (int j = n; j >= d; j --)
			__d(f[j] -= f[j - d]);
	}
	ll ans = f[n];
	for (int i = 1; i * (B + 1) <= n; i ++) {
		for (int j = n; j >= B + 1; j --)
			g[j] = g[j - B - 1];
		std::fill(g, g + B + 1, 0);
		for (int j = i; j <= n; j ++)
			__a(g[j] += g[j - i]);
		for (int j = 0; j <= n; j ++)
			(ans += 1ll * g[j] * f[n - j]) %= mod;
	}
	printf("%lld\n", ans);
}
