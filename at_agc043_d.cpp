#if 0
2020.03.22

如果已知 A ，考虑 P 会长什么样。
对于一个 A[i] ，划分为若干极大的以左端点为最大值的区间，称为块。
一个显而易见的性质是一个块一定连续出现在 P 中。
进一步可以得到把所有块按左端点升序后拼接起来就能得到 P 。

那么问题就是统计有多少排列 P 能够被划分为若干块，这些块能够构成 A 。
首先块长不能超过 3 ，其次块长为 2 的块数不能超过块长为 1 的块数，
后者保证了这些块能够组成长为 3 的序列 A 。

接着考虑确定了 P 是由什么样的块构成的，统计 P 的方案数。
具体地，设 P 由 k 个块组成，第 i 个块的大小为 b[i] ，b 的前缀和为 s 。
那么满足这个分块方式的 P 有 n!/prod(s) 。

证明：
考虑从左到右确定排列 P 的相对权值，把块的最大值定在块的右端点。
不考虑块限制时第 i 个位置有 i 种选数方案，考虑块限制，事实上块限制只会影响到块的右端点，
这些点在选数时必须选当前最大值，那么用 n! 除掉这些点的位置乘积即可。

于是可以对于分母进行 DP ，设 f[i][j] 表示当前块长和为 i ，块长为 1 与块长为 2 的块数差为 j ，
这种情况下的分母的和，转移枚举最后一个块的大小即可。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 6005;
ll f[maxn][maxn << 1];
ll inv[maxn];

int main () {
	int n = read * 3, mod = read;

	inv[1] = 1;
	for (int i = 2; i <= n; i ++)
		inv[i] = (mod - mod / i) * inv[mod % i] % mod;

	f[0][maxn + 0] = 1;
	f[1][maxn + 1] = inv[1];
	f[2][maxn + 2] = inv[2];
	f[2][maxn - 1] = inv[2];
	for (int s = 3; s <= n; s ++)
		for (int i = maxn - s; i <= maxn + s; i ++)
			f[s][i] = (f[s - 1][i - 1] + f[s - 3][i] + f[s - 2][i + 1]) * inv[s] % mod;

	ll ans = 0;
	for (int i = maxn; i <= maxn + n; i ++)
		ans += f[n][i];
	ans %= mod;
	for (int i = 1; i <= n; i ++)
		(ans *= i) %= mod;
	printf("%lld\n", ans);
}
