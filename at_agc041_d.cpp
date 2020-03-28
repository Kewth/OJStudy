#if 0
2020.03.26

由于 a 是升序的，那么任意大小为 k + 1 的子集和大于任意大小为 k 的子集和等价于：
a[1] + a[2] + ... + a[k + 1] > a[n] + a[n - 1] + ... + a[n - k + 1]
而只要 k = floor((n - 1) / 2) 满足上述条件，任意 k 就能满足。

众所周知升序序列考虑差分，令 a[i] = 1 + x[1] + x[2] + ... + x[i] ，
那么上述限制等价于 x[1] >= x[2] * 0 + x[3] * 1 + ... + x[n - 1] * 2 + x[n] * 1 。
另外还要有 sum(x) < n 。
设 a = x[2] + x[3] + ... + x[n - 1] + x[n] ，
b = x[2] * 0 + x[3] * 1 + ... + x[n - 1] * 2 + x[n] * 1 。
那么有 b <= x[1] < n - a ，也就是说确定了 x[2] 到 x[n] 后 x[1] 有恰好 n - a - b 种选择。
不难发现需要关注的只是 a + b ，而 a + b 等于下式：
x[2] * 1 + x[3] * 2 + ... + x[n - 1] * 3 + x[n] * 2 。

DP 设 f[i][j] 表示考虑前 i 个 x 后 a + b = j 的方案数，前缀和优化即可。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 5050;
ll f[maxn][maxn];
int g[maxn];

int main () {
	int n = read, mod = read;

	for (int i = 1; i < n; i ++)
		g[i] = std::min(i, n - i + 1);

	f[0][0] = 1;
	for (int i = 1; i < n; i ++) {
		for (int j = 0; j < g[i]; j ++)
			f[i][j] = f[i - 1][j];
		for (int j = g[i]; j < n; j ++)
			f[i][j] = (f[i][j - g[i]] + f[i - 1][j]) % mod;
	}

	ll ans = 0;
	for (int j = 0; j < n; j ++)
		(ans += (n - j) * f[n - 1][j]) %= mod;
	printf("%lld\n", ans);
}
