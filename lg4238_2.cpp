/*
 * Author: Kewth

 * Date:
  2020.08.02

 * Solution:
  试了试分治 FFT 版本的多项式乘法逆，居然比牛顿迭代快。

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

const int maxl = 1 << 17, mod = 998244353;
typedef ll poly[maxl];
typedef ll *pit;
int R[maxl], G[maxl + 1];

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

struct initer { initer () {
	for (int i = 1; i < maxl; i ++) R[i] = R[i >> 1] >> 1 | (i & 1) * (maxl >> 1);
	ll g = power(3, (mod - 1) / maxl);
	G[maxl >> 1] = 1;
	for (int i = maxl / 2 + 1; i <= maxl; i ++) G[i] = 1ll * G[i - 1] * g % mod;
	for (int i = maxl / 2 - 1; i; i --) G[i] = G[i << 1];
} } initer;

inline void __a (ll &x) { if (x >= mod) x -= mod; }
inline void __d (ll &x) { if (x < 0) x += mod; }

void DFT (pit a, int n) {
	int nk = __builtin_ctz(maxl) - __builtin_ctz(unsigned(n));
	for (int i = 0; i < n; i ++)
		if (i < (R[i] >> nk))
			std::swap(a[i], a[R[i] >> nk]); // XXX: 啊这，这里把 >> nk 漏掉还行
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
	int inv = mod - (mod - 1) / n;
	for (int i = 0; i < n; i ++) (a[i] *= inv) %= mod;
}

// template
const int force_n = 8;
void solve (pit a, pit b, int *coe, int n) {
	static poly c;
	if (n <= force_n) {
		for (int i = 0; i < n; i ++) {
			for (int j = 0; j < i; j ++)
				(b[i] += b[j] * a[i - j]) %= mod;
			(b[i] *= coe[i]) %= mod;
		}
		return;
	}
	int m = n >> 1;
	solve(a, b, coe, m);
	std::copy(b, b + m, c);
	std::fill(c + m, c + n, 0);
	DFT(c, n);
	for (int i = 0; i < n; i ++) (c[i] *= a[n + i]) %= mod;
	IDFT(c, n);
	/* for (int i = 0; i < n; i ++) debug(" %lld", c[i]); debug("\n"); */
	for (int i = m; i < n; i ++) __a(b[i] += c[i]);
	solve(a, b + m, coe + m, m);
}
void Solve (pit a, int *coe, int n) {
	static ll b[maxl << 1]; // XXX: 2n
	std::copy(a, a + force_n, b);
	for (int m = force_n << 1; m <= n; m <<= 1)
		std::copy(a, a + m, b + m), DFT(b + m, m);
	std::fill(a, a + n, 0), a[0] = 1;
	solve(b, a, coe, n);
}

void polyinv (pit a, int n) {
	static int coe[maxl];
	coe[0] = int(power(a[0], -1));
	std::fill(coe + 1, coe + n, mod - coe[0]);
	Solve(a, coe, n);
}

poly a;
int main () {
	int n = read, len = 1;
	while (len < n) len <<= 1;
	for (int i = 0; i < n; i ++) read(a[i]);
	polyinv(a, len);
	for (int i = 0; i < n; i ++) printf("%lld ", a[i]);
	puts("");
}
