#if 0
2020.04.04

异或前缀和递增和数列递增这个两个限制很强，等价于二进制最高位递增。
统计每个二进制最高位的数的数量，就很容易求方案了。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxk = 32;
int tot[maxk];
int f[maxk];

int main() {
	int t = read;
	while (t --) {
		int lim = read, mod = read;
		int sum = 0, K = 0;
		std::fill(tot, tot + maxk, 0);
		for (; sum < lim; K ++) {
			int tmp = std::min(lim - sum, 1 << K);
			tot[K] += tmp;
			sum += tmp;
		}

		int ans = 1;
		for (int k = 0; k <= K; k ++)
			ans = 1ll * ans * (tot[k] + 1) % mod;
		printf("%d\n", (ans + mod - 1) % mod);
	}
}
