#if 0
2020.04.16

设 F[k] 表示答案。
一个 naive 的想法是钦定 k 个位置作为交集，然后其他随便，
这样算出来的方案数就是 C(n, k) * 2^(2^(n-k)) 。
但这样显然会把一些实际上不合法的方案算进去，不妨记这个值为 G[k] 。

考虑 G 和 F 的关系，对于 G[k] ，枚举 i 求 G[k] 中实际上交集为 i 的方案数，
那不难发现这个贡献就是 C(i, k) F[i] ，通过二项式反演就能得到 F 关于 G 的式子。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

inline ll power (ll x, int k, int mod) {
	if (k < 0) k += mod - 1;
	ll res = 1;
	while (k) {
		if (k & 1) (res *= x) %= mod;
		(x *= x) %= mod;
		k >>= 1;
	}
	return res;
}

const int maxn = 1000005, mod = 1000000007;
ll G[maxn];
ll fac[maxn], ifac[maxn];

inline ll C (int n, int m) {
	return fac[n] * ifac[m] % mod * ifac[n - m] % mod;
}

void combinator_init (int n) {
	fac[0] = 1;
	for (int i = 1; i <= n; i ++)
		fac[i] = fac[i - 1] * i % mod;
	ifac[n] = power(fac[n], -1, mod);
	for (int i = n; i; i --)
		ifac[i - 1] = ifac[i] * i % mod;
}

int main () {
	int n = read, k = read;
	combinator_init(n);
	for (int i = 0; i <= n; i ++)
		G[i] = C(n, i) * power(2, int(power(2, n - i, mod - 1)), mod) % mod;

	ll Fk = 0;
	for (int i = k; i <= n; i ++)
		if ((i - k) & 1)
			(Fk -= C(i, k) * G[i]) %= mod;
		else
			(Fk += C(i, k) * G[i]) %= mod;
	if (Fk < 0) Fk += mod;
	printf("%lld\n", Fk);
}
