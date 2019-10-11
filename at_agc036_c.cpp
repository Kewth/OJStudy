#if 0
2019.10.11

问题等价于求长为 n 的满足一下三个条件的数列的个数：

1. 所有值的和为 s1 = 3m
2. 奇数的个数不超过 s2 = m
3. 最大的数不超过 s3 = 2m

先考虑第一个限制，相当于把 s1 个球放进 n 个盒子，方案数为 f1(s1, n) = C(n + s1, s1)。

再考虑第二个限制，设 f2(n, m, k) 为长度为 n ，和为 m ，奇数不超过 k 个的方案数，
枚举奇数个数 i ，然后把这 i 个奇数减 1 弄成偶数，
那么 i 的贡献就是 C(n, i) * f1((m - i) / 2, n - 1) 。

最后考虑第三个限制，由于和为 3m ，超过 2m 的数最多只有一个，
简单容斥，钦定一个数大于 2m ，那么贡献就是 - n * f2(n, m, m) ，
但事实上这也算进去了该数恰好为 2m 的情况，继续容斥，贡献为 n * f2(n - 1, m, m) ，
那么答案 f3(n, m) = f2(n, 3m, m) - n * (f2(n, m, m) - f2(n - 1, m, m)) 。
#endif
#include <cstdio>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;

inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 3000005, mod = 998244353;
lolong fac[maxn];
lolong inv[maxn];
lolong ifac[maxn];

inline lolong c(int n, int m) {
	return fac[n] * ifac[m] % mod * ifac[n - m] % mod;
}

lolong f(int n, int m, int k) {
	lolong res = 0;
	for(int i = 0; i <= k and i <= n; i ++)
		if(!((m - i) & 1))
			res += c(n, i) * c((m - i) / 2 + n - 1, (m - i) >> 1) % mod;
	return res % mod;
}

int main() {
	fac[0] = 1;
	for(int i = 1; i < maxn; i ++)
		fac[i] = fac[i - 1] * i % mod;

	inv[1] = 1;
	for(int i = 2; i < maxn; i ++)
		inv[i] = (mod - mod / i) * inv[mod % i] % mod;

	ifac[0] = 1;
	for(int i = 1; i < maxn; i ++)
		ifac[i] = ifac[i - 1] * inv[i] % mod;

	int n = input(), m = input();
	printf("%lld\n",
			(f(n, m * 3, m) + mod -
			 n * (f(n, m, m) + mod -
				 f(n - 1, m, m)) % mod) % mod);
}
