#if 0
2020.01.07

考虑每个数 a[i] 对答案的贡献，一定是 ka[i] ，其中 k 是贡献系数。
不难想到这个 k 是与 i 无关的，因此答案就是 k * sum(a) 。

对于 a[i] 计算 k ，就是所有划分中 i 所在集合的大小的和。
考虑每个 a[j] 对 k 的贡献 p ，不难想到 j != i 时 p 与 k 无关。

而这个 p 就是所有划分中 a[j] 与 a[i] 被划分在一块的方案数，
把 a[i] 和 a[j] 绑在一起，方案数 p = S(n - 1, m) 。
而 a[i] 本身对 k 的贡献自然就是所有划分的方案数，即 S(n, m) 。
那么 k = (n - 1)S(n - 1, m) + S(n, m) 。
#endif
#include <cstdio>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
} read;

const int maxn = 200005, mod = 1000000007;
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
	return fac[n] * ifac[m] % mod * ifac[n - m] % mod;
}

inline ll S(int n, int m) {
	ll res = 0;
	for(int k = 0; k <= m; k ++)
		res += power(mod - 1, m - k) * C(m, k) % mod * power(k, n) % mod;
	res %= mod;
	return res * ifac[m] % mod;
}

int main() {
	int n = read, m = read;
	ll sum = 0;
	for(int i = 1; i <= n; i ++) sum += read;
	sum %= mod;

	fac[0] = 1;
	for(int i = 1; i <= m; i ++) fac[i] = fac[i - 1] * i % mod;
	ifac[m] = power(fac[m], -1);
	for(int i = m; i; i --) ifac[i - 1] = ifac[i] * i % mod;

	printf("%lld\n", ((n - 1) * S(n - 1, m) % mod + S(n, m)) * sum % mod);
}
