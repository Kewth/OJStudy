#if 0
2020.05.20

  显然一波 min-max 容斥后问题可以转换为对于所有 n <= N ，求出在 n 个鸽子中投喂，有一只
被喂饱的期望时间。
  类似《百鸽笼》，定义一个操作序列，每个操作序列出现的概率只与其长度有关，可以背包 DP
求出 f[n][i] 表示长度为 i 的合法操作序列数量，而 f[n] 就是在 f[n - 1] 的基础上加一个元
素，同样用组合数算贡献系数。
  但是复杂度分析下来是 O(N^2 K^2) 的，因为每次加入的元素大小为 O(K) ，要加 O(N) 次。
  把转移的组合数拆开，设 f[n] 的 EGF 为 F_{n}(x) 不难得到 F_{n}(x) = F_{n-1}(x) G(x) ，
其中 G(x) = e^x mod x^m ，直接多项式卷积可以优化复杂度，但不在讨论重点。
  由于 F_{n+1}(x) = G^n(x) 而 G^n(x) 的形式很优秀，不妨对 F_{n}(x) 求导，用复合函数求导
列出一个多项式等式，从每一项系数的等式中可以得到 f[n + 1][i + 1] 关于 f[n + 1][i] 和
f[n][i - m + 1] 的递推式，至此复杂度优化至 O(N^2 K) 。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 55, maxm = 1005, mod = 998244353;
ll f[maxn * maxm], g[maxm * maxm];
ll fac[maxn * maxm], ifac[maxn * maxm], inv[maxn * maxm];
ll coe[maxn * maxm];

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
	inv[1] = 1;
	for (int i = 2; i <= n; i ++)
		inv[i] = (mod - mod / i) * inv[mod % i] % mod;
}

int main () {
	int n = read, m = read;
	combinator_init(n * m);

	ll ans = 0;
	f[0] = 1;
	for (int i = 1, len = 0; i <= n; i ++, len += m - 1) {
		g[0] = 1;
		for (int j = 0; j < len; j ++) {
			g[j + 1] = g[j];
			if (j - m + 1 >= 0)
				(g[j + 1] += (mod - ifac[m - 1]) * f[j - m + 1]) %= mod;
			(g[j + 1] *= i - 1) %= mod;
			(g[j + 1] *= inv[j + 1]) %= mod;
		}
		std::copy(g, g + len + 1, f);

		coe[0] = 1;
		for (int k = 1; k <= len + m; k ++)
			coe[k] = coe[k - 1] * inv[i] % mod;
		for (int k = 0; k <= len + m; k ++)
			(coe[k] *= k) %= mod;

		ll now = 0;
		for (int j = 0; j <= len; j ++)
			(now += f[j] * fac[j] % mod * C(j + m - 1, j) % mod * coe[j + m]) %= mod;

		/* debug("%lld\n", now); */
		(now *= C(n, i)) %= mod;
		if (i & 1) ans += now;
		else ans += mod - now;
	}
	printf("%lld\n", ans * n % mod);
}
