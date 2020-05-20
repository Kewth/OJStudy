#if 0
2020.05.20

  把原串左右各加一个 0 ，一个朴素的 DP 是设 f[i] 表示第 i 个位置填 0 时前 i 个位置的填数
方案数，转移枚举上一个 0 的位置即可。这是个常系数齐次线性递推，可以简单优化到 O(m^2logn) 。
  考虑 f 的前缀和数组 s ，根据 f 的转移不难得出 s 的转移：s[i] = 2s[i - 1] + s[i - m - 1] 。
这个可以从组合意义来算，由于初值仅有 s[0] = 1 ，s[n] 可以看做在数轴上从 0 到 n 的路径数，
其中 i -> i + 1 有 2 条路径，i -> i + m + 1 有 1 条路径，枚举 i -> i + m + 1 的路径数用
组合数算即可，组合数用 lucas 定理，复杂度 O(mod + n / m) 。
  综上所述，对于 m 分类讨论，最坏复杂度 O(n^{2/3} log^{1/3}n) 。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
} read;

const int maxm = 4400, mod = 65537;
ll f[maxm], g[maxm], tmp[maxm << 1];
ll po[mod], fac[mod], ifac[mod];

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
	if (n < m) return 0;
	return fac[n] * ifac[m] % mod * ifac[n - m] % mod;
}

void combinator_init (int n) {
	fac[0] = 1;
	for (int i = 1; i <= n; i ++)
		fac[i] = fac[i - 1] * i % mod;
	ifac[n] = power(fac[n], -1);
	for (int i = n; i; i --)
		ifac[i - 1] = ifac[i] * i % mod;
	po[0] = 1;
	for (int i = 1; i <= n; i ++)
		if ((po[i] = po[i - 1] << 1) >= mod) po[i] -= mod;
}

void mul (ll *a, ll *b, int m) {
	std::fill(tmp, tmp + m * 2, 0);
	for (int i = 0; i < m; i ++)
		for (int j = 0; j < m; j ++)
			tmp[i + j] += a[i] * b[j];
	for (int i = 0; i < m * 2; i ++) tmp[i] %= mod;
}

void update (ll *a, int m) {
	for (int i = m * 2 - 1; i >= 0; i --) {
		tmp[i] %= mod;
		if (i >= m)
			for (int j = 1; j <= m; j ++)
				tmp[i - j] += tmp[i];
	}
	std::copy(tmp, tmp + m, a);
}

int calc1 (ll n, int m) {
	if (m == 1) return 1;
	f[0] = 1;
	g[1] = 1;
	while (n) {
		if (n & 1) {
			mul(f, g, m);
			update(f, m);
		}
		mul(g, g, m);
		update(g, m);
		n >>= 1;
	}
	ll res = f[0], coe = 1;
	for (int i = 1; i < m; i ++) {
		res += f[i] * coe;
		if ((coe <<= 1) >= mod) coe -= mod;
	}
	return res % mod;
}

ll lucas (ll n, ll m) {
	if (!n and !m) return 1;
	return C(n % mod, m % mod) * lucas(n / mod, m / mod) % mod;
}

int calc2 (ll n, ll m) {
	ll j = n, res = 0;
	for (int i = 0; j >= 0; i ++, j -= m + 1) {
		ll now = po[j % (mod - 1)] * lucas(i + j, j);
		if (i & 1) res += mod - now;
		else res += now;
	}
	return res % mod;
}

int main () {
	ll n = read, m = read;
	if (m < maxm)
		printf("%d\n", calc1(n + 1, int(m)));
	else {
		combinator_init(mod - 1);
		printf("%d\n", (calc2(n + 1, m) + mod - calc2(n, m)) % mod);
	}
}
