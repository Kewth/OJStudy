#if 0
2020.05.20

  类似《喂鸽子》。
  注意到每个燃料仓本质相同，不妨对于一个燃料仓 X 求出结束时该燃料仓加满的概率 p ，那么
答案就是 np 。而结 X 在束时是加满的，等价于 X 加满时还未结束，未结束也就是存在燃料仓还
没到最小要求。
  对于这个“存在”进行子集容斥，枚举非空子集 S ，钦定 S 内的点在 X 加满时还没到最小要求，
求出概率 f(S) ，那么其对 p 的贡献系数是 (-1)^{|S|+1} ，由于每个燃料仓本质相同，只需对
于每个 |S| 求 f 即可，求的方法还是统计操作序列，不难发现和《喂鸽子》一样，每种长度的操
作序列的出现概率的生成函数就是 G(x) 的幂，其中 G(x) = e^x mod x^b ，用同样的方法求导并
递推即可做到 O(n^3) 。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 255, mod = 998244353;
ll f[maxn * maxn], g[maxn * maxn];
ll fac[maxn * maxn], ifac[maxn * maxn], inv[maxn * maxn];
ll coe[maxn * maxn];

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
	int n = read, K = read, m = read;
	combinator_init(n * m);

	ll ans = 0;
	f[0] = 1;
	for (int i = 0, len = 0; i < n; i ++, len += m - 1) {
		g[0] = 1;
		for (int j = 0; j < len; j ++) {
			g[j + 1] = g[j];
			if (j - m + 1 >= 0)
				(g[j + 1] += (mod - ifac[m - 1]) * f[j - m + 1]) %= mod;
			(g[j + 1] *= i) %= mod;
			(g[j + 1] *= inv[j + 1]) %= mod;
		}
		std::copy(g, g + len + 1, f);
		if (!i) continue;

		coe[0] = 1;
		for (int k = 1; k <= len + K; k ++)
			coe[k] = coe[k - 1] * inv[i + 1] % mod;

		ll now = 0;
		for (int j = 0; j <= len; j ++)
			(now += f[j] * fac[j] % mod * C(j + K - 1, j) % mod * coe[j + K]) %= mod;

		/* debug("%lld\n", now); */
		(now *= C(n - 1, i)) %= mod;
		if (i & 1) ans += now;
		else ans += mod - now;
	}
	printf("%lld\n", ans * n % mod);
}
