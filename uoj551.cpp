/*
 * Author: Kewth

 * Date:
  2020.08.12

 * Solution:
  In blog.

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
#include <vector>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef unsigned long long ull;

static struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
} read;

const int maxl = 1 << 16, mod = 998244353;
const ll MM = 1ll * mod * mod;
typedef ll poly[maxl], *pit;
int R[maxl << 1];
ll G[maxl + 1];

inline void __a (ll &x) { x >= mod ? x -= mod : x; }
inline void __d (ll &x) { x < 0 ? x += mod : x; }
inline void __A (ll &x) { x >= MM ? x -= MM : x; }

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
	G[maxl >> 1] = 1;
	for (int i = maxl / 2 + 1; i <= maxl; i ++) G[i] = G[i - 1] * g % mod;
	for (int i = maxl / 2 - 1; i; i --) G[i] = G[i << 1];
}

void dft (pit a, int n) {
	// XXX: mod * mod * log 爆 long long 但不爆 unsigned long long
	static ull b[maxl];
	for (int i = 0; i < n; i ++)
		b[i] = ull(a[R[n + i]]);
	for (int m = 1; m < n; m <<= 1)
		for (int i = 0; i < n; i += m << 1)
			for (int k = i; k < i + m; k ++) {
				ull x = b[k], y = b[k + m] * ull(G[m + k - i]) % mod;
				b[k] = x + y;
				b[k + m] = x + mod - y;
				/* __a(a[k] = x + y); */
				/* __d(a[k + m] = x - y); */
			}
	for (int i = 0; i < n; i ++) a[i] = b[i] % mod;
}

void idft (pit a, int n) {
	std::reverse(a + 1, a + n);
	dft(a, n);
	ll inv = mod - (mod - 1) / n;
	for (int i = 0; i < n; i ++) (a[i] *= inv) %= mod;
}

const int maxn = 9;
poly f[maxn][maxn], g[maxn][maxn], h[maxn][maxn], t[maxn][maxn];
std::vector<int> e[maxn][maxn][20];

int N;
void solve (int k) {
	if (!k) {
		for (int a = 1; a <= N; a ++)
			f[a][a][0] = 1;
		return;
	}

	solve(k - 1);
	int len = 1 << k, hl = len >> 1;

	for (int a = 1; a <= N; a ++)
		for (int b = 1; b <= N; b ++) {
			std::fill(h[a][b], h[a][b] + hl, 0);
			std::fill(t[a][b], t[a][b] + hl, 0);
			std::copy(f[a][b], f[a][b] + hl, g[a][b]);
			for (int w : e[a][b][k])
				++ h[a][b][w];
			dft(g[a][b], len);
			dft(h[a][b], len);
		}

	for (int a = 1; a <= N; a ++)
		for (int b = 1; b <= N; b ++)
			for (int c = 1; c <= N; c ++)
				for (int i = 0; i < len; i ++)
					__A(t[a][b][i] += g[a][c][i] * h[c][b][i]);

	for (int a = 1; a <= N; a ++)
		for (int b = 1; b <= N; b ++) {
			for (int i = 0; i < len; i ++) t[a][b][i] %= mod;
			idft(t[a][b], len);
			for (int i = 0; i < hl; i ++)
				h[a][b][i] = t[a][b][i + hl];
			std::fill(t[a][b], t[a][b] + len, 0);
			std::fill(h[a][b] + hl, h[a][b] + len, 0);
			dft(h[a][b], len);
		}

	for (int a = 1; a <= N; a ++)
		for (int b = 1; b <= N; b ++)
			for (int c = 1; c <= N; c ++)
				for (int i = 0; i < len; i ++)
					__A(t[a][b][i] += h[a][c][i] * g[c][b][i]);

	for (int a = 1; a <= N; a ++)
		for (int b = 1; b <= N; b ++) {
			for (int i = 0; i < len; i ++) t[a][b][i] %= mod;
			idft(t[a][b], len);
			std::copy(t[a][b], t[a][b] + hl, f[a][b] + hl);
		}
}

int main () {
	init();

	/* ll p[8] = {1, 1, 0, 0, 0, 0, 0, 0}; */
	/* dft(p, 8); */
	/* for (ll &x : p) (x *= x) %= mod; */
	/* idft(p, 8); */
	/* for (ll x : p) debug("%lld\n", x); */
	/* return 0; */

	read(N);
	int m = read, q = read, V = read;

	int k = 0;
	while ((1 << k) < V + 1) ++ k;

	while (m --) {
		int a = read, b = read, w = read;
		for (int i = k; i and w < (1 << i); i --)
			e[a][b][i].push_back(w);
	}

	solve(k);

	while (q --) {
		int a = read, b = read, w = read;
		printf("%lld\n", f[a][b][w]);
	}
}
