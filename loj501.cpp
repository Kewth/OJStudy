#if 0
2019.09.25

把序列中相邻且相同的数缩到一起，
考虑每相邻的三个值 (x, y, z) ，
如果 x, y, z 单调，那么 y 中的数都是可选可不选的，方案数为 2^k ， k 为这段 y 的数量。
否则 y 为峰，那么 y 至少要选一个，方案数为 2^k - 1 。
而处于最边上的两个值 x1, x2 ，自然也是必须选的，方案数为 2^k - 1 。

综上，如果 n 可以分解成若干 2^k 和 2^k-1 的积，那么就可以通过上述方法构造数列，
否则一定无解。
#endif
#include <cstdio>
#include <climits>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;
inline lolong linput() { lolong x; scanf("%lld", &x); return x; }

int ans[1000], ap;
lolong F[64];

bool dfs(lolong n, int d) {
	if(n == 1) return 1;
	for(int k = d; k <= 60; k ++)
		if(!(n % F[k]) and dfs(n / F[k], d)) {
			int tmp = k;
			while(tmp --)
				ans[++ ap] = 2;
			ans[++ ap] = 3;
			return 1;
		}
	return 0;
}

int main() {
	lolong n = linput();

	ans[++ ap] = 1;

	while(!(n & 1)) {
		ans[++ ap] = 2;
		n >>= 1;
	}

	ans[++ ap] = 3;

	for(int k = 2; k <= 60; k ++)
		F[k] = (1ll << k) - 1;

	if(dfs(n, 2)) {
		printf("%d\n", ap);
		for(int i = 1; i <= ap; i ++)
			printf("%d ", ans[i]);
		puts("");
	} else
		puts("qnq");
}
