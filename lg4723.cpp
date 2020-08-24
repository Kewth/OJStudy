/*
 * Author: Kewth

 * Date:
  2020.08.12

 * Solution:

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
typedef unsigned long long ull;

using std::copy;
using std::fill;
using std::reverse;

static struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxl = 1 << 17, mod = 998244353;
int R[maxl << 1], G[maxl + 1];

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

void init () {
	for (int n = 1; n <= maxl; n <<= 1) {
		int *r = R + n;
		for (int i = 1; i < n; i ++)
			r[i] = r[i >> 1] >> 1 | (i & 1) * (n >> 1);
	}
	ll g = power(3, (mod - 1) / maxl);
	G[maxl / 2] = 1;
	for (int i = maxl / 2 + 1; i <= maxl; i ++) G[i] = g * G[i - 1] % mod;
	for (int i = maxl / 2 - 1; i; i --) G[i] = G[i << 1];
}

void dft (int *b, int n) {
	static ull a[maxl];
	for (int i = 0; i < n; i ++) a[i] = ull(b[R[n + i]]);
	for (int m = 1; m < n; m <<= 1)
		for (int i = 0; i < n; i += m << 1)
			for (int k = i; k < i + m; k ++) {
				ull x = a[k], y = a[k + m] * ull(G[m + k - i]) % mod;
				a[k] = x + y, a[k + m] = x + mod - y;
			}
	for (int i = 0; i < n; i ++) b[i] = a[i] % mod;
}

void idft (int *a, int n) {
	reverse(a + 1, a + n), dft(a, n);
	ll inv = mod - (mod - 1) / n;
	for (int i = 0; i < n; i ++) a[i] = inv * a[i] % mod;
}

void polyinv (int *a, int n) {
	static int b[maxl], t[maxl];
	b[0] = int(power(a[0], -1));
	for (int m = 2; m <= n; m <<= 1) {
		copy(a, a + m, t);
		fill(t + m, t + (m << 1), 0);
		fill(b + (m >> 1), b + (m << 1), 0);
		dft(t, m << 1), dft(b, m << 1);
		for (int i = 0; i < (m << 1); i ++)
			b[i] = ll(2 + t[i] * ll(mod - b[i])) % mod * b[i] % mod;
		idft(b, m << 1);
	}
	copy(b, b + n, a);
}

void pre (int *b, int *c, int *db, int n, int m) {
	copy(b, b + m, c), reverse(c, c + m);
	if (m > n - m + 1) fill(c + n - m + 1, c + m, 0);
	int l = 1; while (l < n - m + 1) l <<= 1; l <<= 1;
	polyinv(c, l), fill(c + n - m + 1, c + l, 0);
	dft(c, l);
	copy(b, b + m, db);
	l = 1; while (l < n + 1) l <<= 1; l <<= 1;
	dft(db, l);
}

void polydiv (int *A, int *c, int *a, int n, int m) {
	copy(A, A + n, a), reverse(a, a + n);
	int l = 1; while (l < n - m + 1) l <<= 1; l <<= 1;
	fill(a + n - m + 1, a + n, 0);
	dft(a, l);
	for (int i = 0; i < l; i ++) a[i] = 1ll * a[i] * c[i] % mod;
	idft(a, l), fill(a + n - m + 1, a + l, 0);
	reverse(a, a + n - m + 1); // XXX: 这都能忘？ // XXX: 这还能写成 n
}

void polymod (int *a, int *db, int *c, int n, int m) {
	static int t[maxl];
	polydiv(a, c, t, n, m);
	int l = 1; while (l < n + 1) l <<= 1; l <<= 1;
	dft(t, l);
	for (int i = 0; i < l; i ++) t[i] = 1ll * t[i] * db[i] % mod;
	idft(t, l);
	for (int i = 0; i < n; i ++) a[i] = (a[i] + mod - t[i]) % mod;
	fill(t, t + l, 0);
}

void PolyMod (int *a, int *b, int n, int m) {
	static int db[maxl], c[maxl];
	pre(b, c, db, n, m);
	polymod(a, db, c, n, m);
}
[[ noreturn ]] void test () {
	int a[8] = {0, 0, 1, 1, 0, 0, 0, 0};
	/* polyinv(a, 4); */
	/* polyinv(a, 4); */
	/* for (int x : a) debug(" %d", x); debug("\n"); */
	int b[8] = {1, 1, mod - 1, 0, 0, 0, 0, 0};
	PolyMod(a, b, 4, 3);
	for (int x : a) debug(" %d", x); debug("\n");
	exit(0);
}

int a[maxl], aa[maxl], b[maxl], c[maxl], db[maxl];

int main () {
	init();
	/* test(); */
	int k = read, m = read;
	for (int i = 1; i <= m; i ++) b[m - i] = (read % mod + mod) % mod;
	b[m ++] = mod - 1;
	pre(b, c, db, m << 1, m);

	int l = 1; while (l < m) l <<= 1; l <<= 1;
	a[0] = 1;
	aa[1] = 1;
	while (k) {
		if (k & 1) {
			dft(a, l), dft(aa, l);
			for (int i = 0; i < l; i ++) a[i] = 1ll * a[i] * aa[i] % mod;
			idft(a, l), idft(aa, l);
			polymod(a, db, c, m << 1, m);
		}
		dft(aa, l);
		for (int i = 0; i < l; i ++) aa[i] = 1ll * aa[i] * aa[i] % mod;
		idft(aa, l);
		polymod(aa, db, c, m << 1, m);
		k >>= 1;
	}

	ll ans = 0;
	for (int i = 0; i < m; i ++)
		(ans += a[i] * ll(read % mod + mod)) %= mod;
	printf("%lld\n", ans);
}
