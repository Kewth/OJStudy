#if 0
2019.08.27

考虑让 a[n] 作为背锅数，在前 n - 1 个数选好的情况下 a[n] 有唯一值使异或和为 0 。
枚举 b ： a[n] 与 k 第 b 位不同，所有 a[i] b 以上的位都与 k 相同。
由于要不大于 k ， k 的 b 为一定是 1 ，而 a[n] 的第 b 位是 0 。
枚举有多少数第 b 位为 0 ，那么这些数 b 以下的位都可以随便选，
若 n 为偶数，此时方案数为：

\sum{2|i} C(n, i) (2^b)^(i-1) ((k&(2^b-1))+1)^(n-i)

像二项式定理，考虑去掉偶数限制，有这样一个函数 f(x) = 1^x + (-1)^x 可供使用。
然后就可以用二项式定理，快速幂计算。
特别地，需要额外加上全选 0 的贡献。

对于 n 为奇数也类似，有函数 f(x) = (-1)^x - 1^x 。
但是一旦 k 的 highbit 被计算后就应该 break ，因为所有数之后该位全选 1 异或和一定非 0 。
#endif
#include <cstdio>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;

typedef long long lolong;

inline int input() { int x; scanf("%d", &x); return x; }

const int maxk = 32, mod = 998244353;

inline lolong power(lolong x, int k) {
	if(k < 0)
		k += mod - 1;
	x %= mod;
	lolong res = 1;
	while(k) {
		if(k & 1) (res *= x) %= mod;
		(x *= x) %= mod;
		k >>= 1;
	}
	return res;
}

int main() {
	int n = input(), K = input();

	lolong a = 0, b = 0;
	for(int k = maxk - 1; k >= 0; k --)
		if(K >> k & 1) {
			int x = (K & ((1 << k) - 1)) + 1;
			a += power(2, - k - 1) *
				(power(x + power(2, k), n) - power(x, n) + mod) % mod;
			b += power(2, - k - 1) *
				(power(x - power(2, k) + mod, n) - power(x, n) + mod) % mod;
			debug("%d %lld %lld\n", x, a, b);
			if(n & 1)
				break;
		}

	a %= mod;
	b %= mod;

	if(n & 1)
		printf("%lld\n", (power(K + 1, n) - a + b + mod) % mod);
	else
		printf("%lld\n", (power(K + 1, n) - a - b - 1 + mod * 2) % mod);
}
