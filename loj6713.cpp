#if 0
2020.05.27

* DGF 的应用

  对于数列的 DGF ，狄利克雷生成函数，可以通过快速实现 ln 和 exp 到达快速计算幂的目的。

  一个积性函数 f 的 DGF 为 sum(f(n)/n^x) ，可以验证这个幂级数的乘法对应于狄利克雷卷积，
那么对这个 DGF 求 ln, exp 即可，需要用到的一个关键的性质：若 e^A(x) = B(x) ，则有

    A'(x) B(x) = B'(x)

  注意到 DGF 求导就是第 k 项乘一个 lnk ，虽然 lnk 在模意义下没有定义，但是根据唯一分解
定理，所有质数的 ln 线性无关，那么 lnk 可以表示为 cnt[k] 个质数的 ln 的和，其中 cnt[k]
是 k 的质因子个数（相同算多次），为了方便，事实上对于每个质数 p ，将 lnp 看做 1 即可，
（其实似乎可以是任意数），这样 lnk 就对应于 cnt[k] 。

  那么根据上面的式子，既可以从 A 推到 B 又可以从 B 推到 A ，复杂度都是调和级数。
        ▁▃▄▄▄▃▃▃▃▄▶
      ▗▇▀▔    ▔▔▔▔
     ▄▛   ▃▅━━■▄▂
    ▟▊   ▐▘     ▀▙
   ▟▜▌   ▐▖   ▋  ▐▍
  ▟▘ ▜   ▝▀▇▆●▘  ▐▌
▗▟▘   ▜▃       ▁▅▛
▔▀▼▅▄▃▃██▅▄▄▄▅■▀▔   CopyRight :)
      ▔▔▔▔▔▔
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
} read;

const int maxn = 1000005, mod = 998244353;
int inv[maxn], cnt[maxn], minp[maxn];
ll tmp[maxn];

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

void ln (ll *a, int n) {
	for (int i = 1; i <= n; i ++)
		tmp[i] = a[i] * cnt[i] % mod;
	for (int i = 1; i <= n; i ++)
		for (int j = 2, k = i << 1; k <= n; j ++, k += i)
			(tmp[k] += (mod - tmp[i]) * a[j]) %= mod;
	for (int i = 1; i <= n; i ++)
		a[i] = tmp[i] * inv[cnt[i]] % mod;
	a[1] = 1;
}

void exp (ll *a, int n) {
	for (int i = 1; i <= n; i ++)
		tmp[i] = a[i] * cnt[i] % mod;
	std::fill(a, a + n + 1, 0);
	a[1] = 1;
	for (int i = 1; i <= n; i ++) {
		if (i > 1) (a[i] *= inv[cnt[i]]) %= mod;
		for (int j = 2, k = i << 1; k <= n; j ++, k += i)
			(a[k] += a[i] * tmp[j]) %= mod;
	}
}

ll f[maxn];
int main () {
	int n = read, k = read;

	inv[1] = minp[1] = 1;
	for (int i = 2; i <= n; i ++) {
		if (!minp[i]) {
			minp[i] = i;
			if (i <= n / i)
				for (int j = i * i; j <= n; j += i)
					if (!minp[j])
						minp[j] = i;
		}
		inv[i] = ll(mod - mod / i) * inv[mod % i] % mod;
		cnt[i] = cnt[i / minp[i]] + 1;
	}

	for (int i = 1; i <= n; i ++) read(f[i]);
	ln(f, n);
	ll ik = power(k, -1);
	for (int i = 1; i <= n; i ++) (f[i] *= ik) %= mod;
	exp(f, n);

	for (int i = 1; i <= n; i ++)
		printf("%lld ", f[i]);
	puts("");
}
