#if 0
2020.04.01

假设第一排确定了，可以发现只要第一排不是黑白相间第二排就必须是与第一排完全相反。
那么每个第一排不黑白相间的方案都会对答案贡献 1 。
而如果第一排黑白相间，那么后一排就可以与之完全相同或者完全相反，但是不能有连续三排完全相同。
那么这就可以直接对第一列做。

DP 设 f[N] 表示 1xN 矩阵的答案，NxM 的矩阵的答案就是 f[N] + f[M] - 2 ，
减 2 是因为整个矩阵黑白相间的情况会算重。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 100005, mod = 1000000007;
ll f[maxn][2];

int main () {
	int n = read, m = read;
	f[1][0] = 2;
	for (int i = 2; i <= n or i <= m; i ++) {
		f[i][0] = (f[i - 1][0] + f[i - 1][1]) % mod;
		f[i][1] = f[i - 1][0];
	}
	printf("%lld\n", (f[n][0] + f[n][1] + f[m][0] + f[m][1] + mod - 2) % mod);
}
