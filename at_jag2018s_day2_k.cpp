#if 0
2020.04.01

不妨设 a <= b ，下标和值从一开始，限制是最长下降子序列不超过 2 。

LDS 不超过 2 意味着每个排列和其前缀 max 是一一对应的。

而前缀 max 要满足的要求只有：
1) max[i] >= i
2) max[n] = n

而 (a, b) 的限制只有：
1) max[a] = b
2) max[a - 1] < b

把 (i, max[i]) 放到平面上，考虑其折线，限制只有：
1) 不能越过 x = y + 1 。
2) 必须经过 (a, b) 。
3) 不能经过 (a - 1, b) 。
4) 不能经过 (a, b + 1) 。

对于第一个限制，翻折法即可。
后面三个限制把路径分为两段即可。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 1000005, mod = 1000000007;
ll fac[maxn << 1], ifac[maxn << 1];

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

void combinator_init (int n) {
	fac[0] = 1;
	for (int i = 1; i <= n; i ++)
		fac[i] = fac[i - 1] * i % mod;
	ifac[n] = power(fac[n], -1);
	for (int i = n; i; i --)
		ifac[i - 1] = ifac[i] * i % mod;
}

inline ll X (int a, int b) {
	if (a < 0 or b < 0) return 0;
	return C(a + b, a);
}

int main () {
	int n = read, a = read + 1, b = n - read;
	combinator_init(n << 1);

	if (b < a) std::swap(a, b);
	ll ans = 1;
	if (b > 1)
		(ans *= X(a - 1, b - 2) + mod - X(a - 3, b)) %= mod;
	if (a < n)
		(ans *= X(n - a - 1, n - b) + mod - X(n + 2 - a - 1, n - 2 - b)) %= mod;
	printf("%lld\n", ans);
}
