/*
 * Author: Kewth

 * Date:
  2020.07.23

 * Solution:
 * 数学归纳，高维差分，拉格朗日插值

  设 S(m) = sum(f(i) q^i [0<=i<m]) 。

  引理：存在 k 次多项式 G 满足 S(m) = q^m G(m) - G(0) 。

  证明：对于 k = 0 显然成立，对于 k > 1 把 S(m) 和 q S(m) 作差，设 g(i) = f(i) - f(i - 1) ，
那么 g 是个 k - 1 次多项式，根据归纳假设，存在 k - 1 次多项式 P 满足 q^m P(m) - P(0) =
sum(g(i) q^i [0<=i<m]) ，稍加整理不难得到对于 k 的命题成立。

  有了这个引理，问题可以转换到求多项式 G ，将 S(m + 1) 和 S(m) 作差，可以得到 G(m + 1)
和 G(m) 的递推式，迭代递推可以得到 G(m) 和 G(0) 的线性关系。

  然而只有递推式是不够的，至少要求出一个位置的点值，注意到引理给出了 G 是 k 次多项式，这
意味着 G 做 k + 1 次差分后得到的结果是 0 。那么可以用一个方程把 G(0) 到 G(k + 1) 联系起
来，然后通过递推式转换为关于 G(0) 的线性方程，就可以解出 G(0) 到 G(k + 1) 。

  最后拉格朗日插值求出 G(n + 1) 即可。

 * Digression:

 * CopyRight:
          ▁▃▄▄▄▃▃▃▃▄▶
        ▗▇▀▔    ▔▔▔▔
       ▄▛   ▃▅━━■▄▂
      ▟▊   ▐▘     ▀▙
     ▟▜▌   ▐▖   ▋  ▐▍
    ▟▘ ▜   ▝▀▇▆■▘  ▐▌
  ▗▟▘   ▜▃       ▁▅▛
  ▔▀▼▅▄▃▃██▅▄▄▄▅■▀▔
        ▔▔▔▔▔▔
 */

#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

static struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
} read;

const int maxn = 500005, mod = 1000000007;
ll f[maxn], g[maxn];
ll fac[maxn], ifac[maxn], inv[maxn];
ll ga[maxn], gb[maxn];

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
	inv[1] = 1;
	for (int i = 2; i <= n; i ++)
		inv[i] = (mod - mod / i) * inv[mod % i] % mod;
}

ll G (ll x, int k) {
	if (x <= k) return g[x];
	x %= mod;
	ll res = 0;
	ll coe = ifac[k];
	for (int i = k; i >= 0; i --) {
		(res += coe * g[i] % mod * power(x + mod - i, -1)) %= mod;
		(coe *= i) %= mod;
		(coe *= mod - inv[k + 1 - i]) %= mod;
	}
	for (int i = k; i >= 0; i --)
		(res *= x - i) %= mod;
	return res;
}

int main () {
	ll N = read;
	int k = read, q = read;
	for (int i = 0; i <= k; i ++) read(f[i]);

	combinator_init(k + 1);

	ga[k + 1] = 1, gb[k + 1] = 0;
	for (int i = k + 1; i; i --) {
		ga[i - 1] = ga[i] * q % mod;
		gb[i - 1] = (gb[i] * q + mod - f[i - 1]) % mod;
	}

	ll a = 0, b = 0;
	for (int i = 0, c = 1; i <= k + 1; i ++, c = -c) {
		(a += C(k + 1, i) * ga[k + 1 - i] * c) %= mod;
		(b += C(k + 1, i) * gb[k + 1 - i] * c) %= mod;
	}

	g[k + 1] = (mod - b) * power(mod + a, -1) % mod; // ax + b = 0
	for (int i = k + 1; i; i --)
		g[i - 1] = (q * g[i] + mod - f[i - 1]) % mod;

	ll S = power(q, (N + 1) % (mod - 1)) * G(N + 1, k) - g[0];
	S %= mod;
	if (S < 0) S += mod;
	printf("%lld\n", S);

	/* for (int i = 0; i <= k + 1; i ++) */
	/* 	debug("%lld\n", g[i]); */
}
