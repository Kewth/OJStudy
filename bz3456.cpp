/*
 * Since g++10 is released, some characters is not valid inside #if 0 :(
 * So, why not using clang++? :D

 * Date:
  2020.06.07

 * Solution:
  设 f[n] 表示答案，显然联通这个限制不好直接处理，不妨设 g[n] 表示 n 个点的图的数量，也
就是忽略联通的限制，考虑 f 与 g 的关系，对于 g[n] ，枚举 1 所在的联通块大小，即可得到 g
与 f 的关系式，把组合数拆开后就是阶乘，多项式求逆即可。

 * Digression:
  自从把常用代码模板化后就再也没手打过 NTT 和多项式求逆了，今天试着不用板子打了打，果然
各种不熟练各种错误。

 * CopyRight:
          ▁▃▄▄▄▃▃▃▃▄▶
        ▗▇▀▔    ▔▔▔▔
       ▄▛   ▃▅━━■▄▂
      ▟▊   ▐▘     ▀▙
     ▟▜▌   ▐▖   ▋  ▐▍
    ▟▘ ▜   ▝▀▇▆●▘  ▐▌
  ▗▟▘   ▜▃       ▁▅▛
  ▔▀▼▅▄▃▃██▅▄▄▄▅■▀▔
        ▔▔▔▔▔▔
 */

#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxl = 1 << 18, mod = 1004535809;
typedef ll *pit;
typedef ll poly[maxl];
ll G[maxl + 1];
int R[maxl];

inline void __a (ll &x) { if (x >= mod) x -= mod; }
inline void __d (ll &x) { if (x < 0) x += mod; }

ll power (ll x, int k) {
	if (k < 0) k += mod - 1;
	ll res = 1;
	while (k) {
		if (k & 1) (res *= x) %= mod;
		(x *= x) %= mod;
		k >>= 1;
	}
	return res;
}

void nttinit () {
	ll g = power(3, (mod - 1) / maxl);
	G[maxl >> 1] = 1;
	for (int i = maxl / 2 + 1; i <= maxl; i ++)
		G[i] = G[i - 1] * g % mod;
	for (int i = maxl / 2 - 1; i; i --)
		G[i] = G[i << 1];
	for (int i = 1; i < maxl; i ++)
		R[i] = R[i >> 1] >> 1 | (maxl >> 1) * (i & 1);
}

void DFT (pit a, int n) {
	int nk = __builtin_ctz(maxl) - __builtin_ctz(unsigned(n));
	for (int i = 0; i < n; i ++)
		if (i < (R[i] >> nk))
			std::swap(a[i], a[R[i] >> nk]);
	for (int m = 1; m < n; m <<= 1)
		for (int i = 0; i < n; i += m << 1)
			for (int k = i; k < i + m; k ++) {
				ll a0 = a[k], a1 = a[k + m] * G[m + k - i] % mod;
				__a(a[k] = a0 + a1);
				__d(a[k + m] = a0 - a1);
			}
}

void IDFT (pit a, int n) {
	std::reverse(a + 1, a + n);
	DFT(a, n);
	int in = mod - (mod - 1) / n;
	for (int i = 0; i < n; i ++)
		(a[i] *= in) %= mod;
}

void polyinv (pit a, int n) {
	static poly res, tmp;
	std::fill(res, res + n * 2, 0);
	res[0] = power(a[0], -1);
	for (int m = 2; m <= n; m <<= 1) {
		std::copy(a, a + m, tmp);
		std::fill(tmp + m, tmp + m * 2, 0);
		DFT(tmp, m << 1);
		DFT(res, m << 1);
		for (int i = 0; i < m * 2; i ++)
			(res[i] *= mod + 2 - res[i] * tmp[i] % mod) %= mod;
		IDFT(res, m << 1);
		std::fill(res + m, res + m * 2, 0);
	}
	std::copy(res, res + n, a);
}

poly a, b, fac, ifac;

int main () {
	nttinit();
	int n = read;

	fac[0] = 1;
	for (int i = 1; i <= n; i ++)
		fac[i] = fac[i - 1] * i % mod;
	ifac[n] = power(fac[n], -1);
	for (int i = n; i; i --)
		ifac[i - 1] = ifac[i] * i % mod;

	for (int i = 0; i <= n; i ++)
		b[i] = power(2, (i * ll(i - 1) >> 1) % (mod - 1)) * ifac[i] % mod;
	for (int i = 0; i <= n; i ++)
		a[i] = b[i] * i % mod;

	int len = 1;
	while (len < n) len <<= 1;
	polyinv(b, len);
	len <<= 1;
	DFT(a, len);
	DFT(b, len);
	for (int i = 0; i < len; i ++)
		(a[i] *= b[i]) %= mod;
	IDFT(a, len);

	printf("%lld\n", a[n] * fac[n - 1] % mod);
}
