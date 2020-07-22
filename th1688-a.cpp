/*
 * Author: Kewth

 * Date:
  2020.07.21

 * Solution:
 * 常系数齐次线性递推，组合意义

  看着就很像 loj 《匹配字符串》，m 小的时候直接常系数齐次线性递推，m 大的时候，不妨
求出 1 到 n 的所有答案，对于超过 n 的答案可以放一起算哈希值。

  不难得到递推式 f[n] = a f[n - 1] + (1 - a) f[n - m - 1] ，由于 1 到 m 的初始值恰好
满足这个递推式，可以用同样的 trick 做组合意义。

  但是这个递推式对 n = m + 1 却不成立，会少算一个 -a ，单独算这个 -a 的贡献，用同样
的组合意义方法即可。

 * Digression:
  loj 那题是用前缀和数组做的组合意义，所以我这题也想着用 f 的前缀和 g 来算，能得出同
样的递推式，但是 g 在 1 到 m 并不能满足该递推式，导致没能得出正解。
  意识到自己是个傻逼后，一切都解释得通了。

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

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

static struct {
    inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int bas = 19260817, mod = 998244353;

ll power (ll x, int k) {
	x %= mod;
	k %= mod - 1;
	if (k < 0) k += mod - 1;
	ll res = 1;
	while (k) {
		if (k & 1) (res *= x) %= mod;
		(x *= x) %= mod;
		k >>= 1;
	}
	return res;
}

const int maxm = 205;
ll p1[maxm], p2[maxm];
ll tmp[maxm << 1];

void mul (ll *a, ll *b, int m, int x) {
	std::fill(tmp, tmp + m * 2, 0);
	for (int i = 0; i < m; i ++)
		for (int j = 0; j < m; j ++)
			(tmp[i + j] += a[i] * b[j]) %= mod;
	for (int i = m * 2 - 2; i >= m; i --)
		for (int j = 1; j <= m; j ++)
			(tmp[i - j] += tmp[i] * (x - 1)) %= mod;
	std::copy(tmp, tmp + m, a);
}

ll force (int n, int m, int x) {
	if (m == 1) return x * power(x - 1, n - 1) % mod;
	int k = n - m;
	std::fill(p1, p1 + m, 0);
	std::fill(p2, p2 + m, 0);
	p1[m - 1] = 1;
	p2[1] = 1;
	while (k) {
		if (k & 1) mul(p1, p2, m, x);
		mul(p2, p2, m, x);
		k >>= 1;
	}
	ll res = 0, coe = 1;
	for (int i = 0; i < m; i ++) {
		(coe *= x) %= mod;
		(res += coe * p1[i]) %= mod;
	}
	return res;
}

const int maxn = 3000005;
ll fac[maxn], ifac[maxn];
ll poa[maxn], pob[maxn];

inline ll C (int n, int m) {
	return fac[n] * ifac[m] % mod * ifac[n - m] % mod;
}

const ll O = 1ll * mod * mod;
inline void __a (ll &x) { if (x >= O) x -= O; }
inline void __d (ll &x) { if (x < 0) x += O; }

int main () {
	int m = read, a = read, n = read;
	a %= mod;

	if (m < n) {
		ll ans = 0, coe = 1;
		for (int i = 1; i <= m; i ++) {
			(coe *= bas) %= mod;
			(ans += coe * force(n, i, a)) %= mod;
		}
		printf("%lld\n", ans);
	}

	else {
		fac[0] = 1;
		for (int i = 1; i <= n; i ++) fac[i] = fac[i - 1] * i % mod;
		ifac[n] = power(fac[n], -1);
		for (int i = n; i; i --) ifac[i - 1] = ifac[i] * i % mod;
		int b = mod + 1 - a;

		poa[0] = pob[0] = 1;
		for (int i = 1; i <= n; i ++) {
			poa[i] = poa[i - 1] * a % mod;
			pob[i] = pob[i - 1] * b % mod;
		}
		for (int i = 0; i <= n; i ++) {
			(poa[i] *= ifac[i]) %= mod;
			(pob[i] *= ifac[i]) %= mod;
		}

		ll ans = 0, coe = 1;
		for (int M = 1; M <= n; M ++) {
			(coe *= bas) %= mod;
			ll now = 0;
			int L1 = n - 1, L2 = n - M - 1;
			for (int i = 0; i <= L2 / (M + 1); i ++)
				__a(now += (fac[L1 - M * i] * poa[L1 - (M + 1) * i] +
						(mod - fac[L2 - M * i]) * poa[L2 - (M + 1) * i]) % mod *
					pob[i]);
			for (int i = L2 / (M + 1) + 1; i <= L1 / (M + 1); i ++)
				__a(now += fac[L1 - M * i] * pob[i] % mod *
						poa[L1 - (M + 1) * i]);
			/* int L = n - 1; */
			/* for (int i = 0; (M + 1) * i <= L; i ++) */
			/* 	__a(now += fac[L - M * i] * pob[i] % mod * */
			/* 		poa[L - (M + 1) * i]); */
			/* L = n - M - 1; */
			/* for (int i = 0; (M + 1) * i <= L; i ++) */
			/* 	__d(now -= fac[L - M * i] * pob[i] % mod * */
			/* 		poa[L - (M + 1) * i]); */
			now %= mod;
			(ans += coe * now) %= mod;
		}
		(ans *= a) %= mod;

		(coe *= power(a, n)) %= mod;
		(ans += (bas + mod - power(bas, m - n + 1)) *
		 power(mod + 1 - bas, -1) % mod * coe) %= mod;

		printf("%lld\n", ans);
	}
}
