#if 0
2020.05.27

  有意思的是狄利克雷卷积有类似的费马小定理：F^p = e (mod p) ，其中 e 是单位函数，那么把
F 开 k 次方根就是求 F^{1/k} ，指数可以等价于在模 p 意义下 k 的逆元。
  当然有更优秀的做法，见 loj6713 。
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

const int maxn = 100005, mod = 998244353;

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

void mul (ll *a, ll *b, ll *c, int n) {
	static ll tmp[maxn];
	std::fill(tmp, tmp + n + 1, 0);
	for (int i = 1; i <= n; i ++)
		for (int j = 1, k = i; k <= n; j ++, k += i)
			(tmp[k] += a[i] * b[j]) %= mod;
	std::copy(tmp, tmp + n + 1, c);
}

ll f[maxn], g[maxn];

int main () {
	int n = read, k = int(power(read, -1));
	for (int i = 1; i <= n; i ++) read(g[i]);
	f[1] = 1;

	while (k) {
		if (k & 1) mul(f, g, f, n);
		mul(g, g, g, n);
		k >>= 1;
	}

	for (int i = 1; i <= n; i ++) printf("%lld ", f[i]);
	puts("");
}
