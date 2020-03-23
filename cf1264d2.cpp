#if 0
2020.03.23

考虑一个括号序列的权值，一定有一个代表子序列满足 ((((((....)))))) 的形式，
这个代表子序列的最大左括号数量就是序列权值。
既然存在这样的代表子序列，就一定存在一个划分点，
满足划分点左边恰好有 p 个左括号，右边恰好有 p 个右括号。
这个 p 就是序列权值，并且可以发现一个序列的划分点有且仅有一个。

那么枚举划分点，设左边有 l 个左括号，x 个问号，右边有 r 个右括号，y 个问号。
枚举左边多少个问号变成了左括号，然后对于问号的分配方案通过组合数即可列出式子。
然后通过 sum(C(a, i) * C(b, c - i)) = C(a + b, c) 化简，消掉这个枚举即可。
#endif
#include <cstdio>
#include <cstring>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

const int maxn = 1000005, mod = 998244353;
char s[maxn];
ll fac[maxn], ifac[maxn];

inline ll power(ll x, int k) {
	if(k < 0) k += mod - 1;
	ll res = 1;
	while(k) {
		if(k & 1) (res *= x) %= mod;
		(x *= x) %= mod;
		k >>= 1;
	}
	return res;
}

inline ll C(int n, int m) {
	if (m < 0 or m > n) return 0;
	return fac[n] * ifac[m] % mod * ifac[n - m] % mod;
}

int X[maxn], Y[maxn], L[maxn], R[maxn];

int main () {
	scanf("%s", s + 1);
	int n = int(strlen(s + 1));

	fac[0] = 1;
	for (int i = 1; i <= n; i ++)
		fac[i] = fac[i - 1] * i % mod;
	ifac[n] = power(fac[n], -1);
	for (int i = n; i; i --)
		ifac[i - 1] = ifac[i] * i % mod;

	for (int i = 1; i < n; i ++) X[i] = X[i - 1] + (s[i] == '?');
	for (int i = 1; i < n; i ++) L[i] = L[i - 1] + (s[i] == '(');
	for (int i = n; i > 1; i --) Y[i - 1] = Y[i] + (s[i] == '?');
	for (int i = n; i > 1; i --) R[i - 1] = R[i] + (s[i] == ')');

	ll ans = 0;
	for (int i = 1; i < n; i ++)
		(ans += L[i] * C(X[i] + Y[i], Y[i] + R[i] - L[i]) +
			X[i] * C(X[i] + Y[i] - 1, Y[i] + R[i] - L[i] - 1)) %= mod;
	printf("%lld\n", ans);
}
