#if 0
2020.05.13

* 问题转换，分离算贡献，设计 DP

  合法序列可以与排列一一对应，从序列转换为唯一的排列，只需要从小到大枚举 x ，然后把 x
出现的位置从大到小填入排列中，而把排列转换为唯一的序列，只需要划分成若干下降子段，每个
子段代表一个值，把值填入该子段的位置中即可。

  对于第 x 个答案，考虑枚举每个位置 p 对答案的贡献，把排列按位置分为两部分：[1, p] 和
[p + 1, n] ，对于前者，要满足其恰好有 i 个下降子段，对于后者，没有任何限制。那么这个贡
献自然就是 f[p][i] C(n, n - p) (n - p)! ，其中 f[i][j] 表示长度为 i 有恰好 j 个下降子段
的排列的数量。

  问题转换为求 f ，从小到大填数即可简单得到 f 的递推式。

  复杂度 O(n^2) ，递推 f 和统计答案都是 O(n^2) 的，事实上可以多项式进一步优化复杂度。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 5050, mod = 998244353;
ll f[maxn][maxn], g[maxn];
ll fac[maxn], ifac[maxn];

inline ll power (ll x, int k) {
	if (k < 0) k += mod - 1;
	ll res = 1;
	while (k) {
		if (k & 1) (res *= x) %= mod;
		(x *= x) %= mod;
		k >>= 1;
	}
	return res;
}

inline ll C (int n, int m) {
	return fac[n] * ifac[m] % mod * ifac[n - m] % mod;
}

inline ll A (int n, int m) {
	return fac[n] * ifac[n - m] % mod;
}

void combinator_init (int n) {
	fac[0] = 1;
	for (int i = 1; i <= n; i ++)
		fac[i] = fac[i - 1] * i % mod;
	ifac[n] = power(fac[n], -1);
	for (int i = n; i; i --)
		ifac[i - 1] = ifac[i] * i % mod;
}

int main () {
	int n = read;
	combinator_init(n);

	f[0][0] = 1;
	for (int i = 1; i <= n; i ++)
		for (int j = 1; j <= i; j ++)
			f[i][j] = (j * f[i - 1][j] + (i - j + 1) * f[i - 1][j - 1]) % mod;

	/* for (int i = 1; i <= n; i ++) { */
	/* 	for (int j = 1; j <= i; j ++) */
	/* 		debug(" %lld", f[i][j]); */
	/* 	debug("\n"); */
	/* } */

	for (int i = 1; i <= n; i ++) {
		ll ans = 0;
		for (int p = i; p <= n; p ++)
			(ans += A(n, n - p) * f[p][i]) %= mod;
		printf("%lld ", ans);
	}
	puts("");
}
