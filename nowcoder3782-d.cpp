#if 0
2020.01.17

若排名为 k ，设选 m 个点都在其后面的概率为 p[k] ，不难得到 p[k] = ((n-k)/(n-1))^m 。
那么答案就是 sum(p[k] k) / sum(p[k]) 。
重点在于计算 sum((n-k)^m) ，这个就是前 n 个非负整数的 m 次幂和，设其为 f[m] 。

n^m - (n-1)^m = sum(C(m, i) (n-1)^i [i < m])
(n-1)^m - (n-2)^m = sum(C(m, i) (n-2)^i [i < m])
(n-2)^m - (n-3)^m = sum(C(m, i) (n-3)^i [i < m])
...

累加上式得到 n^m = sum(C(m, i) f[m] [i < m]) ，进一步可以得到 f 的递推式。
然后 sum((n-k)^m k) = sum((n-k)^m n) - sum((n-k)^m (n-k)) = n f[m] - f[m + 1] 。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
} read;

const int mod = 998244353;

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

const int maxn = 5050;
ll f[maxn];
ll fac[maxn], ifac[maxn];

inline ll C(int n, int m) {
	return fac[n] * ifac[m] % mod * ifac[n - m] % mod;
}

int main() {
	ll n = read;
	int m = read;

	int MAX = m + 2;
	fac[0] = 1;
	for(int i = 1; i <= MAX; i ++)
		fac[i] = fac[i - 1] * i % mod;
	ifac[MAX] = power(fac[MAX], -1);
	for(int i = MAX; i; i --)
		ifac[i - 1] = ifac[i] * i % mod;

	f[0] = n % mod;
	for(int i = 1; i <= m + 1; i ++) {
		f[i] = power(n % mod, i + 1);
		for(int j = 0; j < i; j ++)
			(f[i] += C(i + 1, j) * (mod - f[j])) %= mod;
		(f[i] *= power(i + 1, -1)) %= mod;
	}

	printf("%lld\n", (n % mod * f[m] % mod + mod - f[m + 1]) * power(f[m], -1) % mod);
}
