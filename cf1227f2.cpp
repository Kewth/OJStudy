#if 0
2020.03.25

不妨令 h[n + 1] = h[1] 。
对于第 i 个答案，如果选了 h[i] 则会使原分数加一，选 h[i + 1] 会使新分数加一。
最后的答案要满足新分数严格比原分数大，因此只需关心两者差值 dt 。
对于第 i 个答案，如果 h[i] = h[i + 1] ，它不会影响 dt ，但会对答案有 k 的乘积贡献。
否则它有三种取值，对应于三种影响（不妨设 k > 2）
1) dt - 1 : 有 1 种选择
2) dt 不变 : 有 (k - 2) 种选择
3) dt + 1 : 有 1 种选择
设这样的位置有 m 个，考虑计算这 m 个位置的贡献。

设 f[i] 表示最后 dt = i 的方案数，要求的是 sum(f[i] [i > 0]) 。
注意到 1) 3) 操作对称，有 f[i] = f[i - 1] 。
那么只需求出 f[0] 和 sum(f) ，则有 sum(f[i] [i > 0]) = (sum(f) - f[0]) / 2 。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator () (a...); }
} read;

const int maxn = 200005, mod = 998244353;
int a[maxn];
ll fac[maxn], ifac[maxn];
ll powk[maxn];

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

void combinator_init (int n) {
	fac[0] = 1;
	for (int i = 1; i <= n; i ++)
		fac[i] = fac[i - 1] * i % mod;
	ifac[n] = power(fac[n], -1);
	for (int i = n; i; i --)
		ifac[i - 1] = ifac[i] * i % mod;
}

int main () {
	int n = read, k = read;
	if (k == 1) return puts("0"), 0;
	for (int i = 1; i <= n; i ++)
		read(a[i]);
	a[n + 1] = a[1];

	combinator_init(n);

	int m = 0;
	for (int i = 1; i <= n; i ++)
		m += a[i] != a[i + 1];
	/* debug("%d\n", m); */

	powk[0] = 1;
	for (int i = 1; i <= m; i ++)
		powk[i] = powk[i - 1] * (k - 2) % mod;

	ll ans = 0;
	for (int x = 0; x * 2 <= m; x ++)
		(ans += fac[m] * ifac[x] % mod * ifac[x] % mod *
		 ifac[m - x - x] % mod * powk[m - x - x]) %= mod;

	ans = (power(k, m) + mod - ans) * (mod + 1) / 2 % mod;
	/* debug("%lld\n", ans); */
	(ans *= power(k, n - m)) %= mod;
	printf("%lld\n", ans);
}
