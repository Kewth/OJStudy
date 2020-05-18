#if 0
2020.05.18

  如果只有一维，显然是可以线性消元的。
  推广到二维也是一样，把上面两行以及左边一列作为自由元，然后对于每个方程，把 (+2, +1) 的
位置看做主元，如果没有这个位置就是 0 。这样就能将所有位置用自由元和 1 的线性表示，同时还
能得到自由元的若干个方程，高斯消元解出自由元再代入到每个位置即可。
#endif
#include <cstdio>
#include <algorithm>
#include <valarray>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef size_t si;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
} read;

const int maxn = 202, mod = 998244353;
ll p[8];
std::valarray<ll> f[maxn][maxn], g;
ll ma[maxn << 2][maxn << 2];
ll ans[maxn][maxn];

inline void __d (ll &x) { if (x < 0) x += mod; }

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

ll num (ll x) {
	ll y = mod - x;
	return x < y ? x : - y;
}

int dx[8] = {-2, -1, +1, +2, +2, +1, -1, -2};
int dy[8] = {-1, -2, -2, -1, +1, +2, +2, +1};

int main () {
	int n = read, m = read;
	ll sum = 0;
	for (int i = 0; i < 8; i ++)
		sum += p[i] = read;

	int lim = m * 2 + n - 2;
	for (int i = 0; i < n; i ++)
		for (int j = 0; j < m; j ++)
			f[i][j].resize(si(lim + 1));

	for (int j = 0; j < m; j ++)
		f[0][j][si(j + 1)] = 1;
	for (int j = 0; j < m; j ++)
		f[1][j][si(j + 1 + m)] = 1;
	for (int i = 2; i < n; i ++)
		f[i][0][si(m * 2 + i - 1)] = 1;

	int mp = 0;
	for (int i = 0; i < n; i ++)
		for (int j = 0; j < m; j ++) {
			g = f[i][j] * sum;
			g[0] += mod - sum;
			for (int d = 0, r, c; d < 8; d ++)
				if (d != 4 and si(r = i + dx[d]) < si(n) and si(c = j + dy[d]) < si(m))
					g += (- f[r][c] + mod) * p[d];
			g %= mod;
			int r = i + dx[4], c = j + dy[4];
			if (r < n and c < m)
				f[r][c] = g * power(p[4], -1) % mod;
			else {
				/* debug("%d %d\n", i, j); */
				++ mp;
				for (int k = 1; k <= lim; k ++)
					ma[mp][k] = g[si(k)];
				ma[mp][lim + 1] = mod - g[0];
			}
		}

	if (mp != lim) return 1;

	/* for (int i = 1; i <= lim; i ++) { */
	/* 	for (int j = 1; j <= lim; j ++) */
	/* 		debug("%2lld ", num(ma[i][j])); */
	/* 	debug("-> %lld\n", num(ma[i][lim + 1])); */
	/* } */

	for (int i = 1; i <= lim; i ++) {
		for (int j = i + 1; j <= lim and !ma[i][i]; j ++)
			if (ma[j][i])
				std::swap(ma[i], ma[j]);
		ll mii = power(ma[i][i], -1);
		for (int j = i + 1; j <= lim; j ++) {
			ll x = ma[j][i] * mii % mod;
			for (int k = i; k <= lim + 1; k ++)
				(ma[j][k] += (mod - x) * ma[i][k]) %= mod;
		}
	}

	for (int i = lim; i; i --) {
		ll mii = power(ma[i][i], -1);
		for (int j = 1; j < i; j ++) {
			ll x = ma[j][i] * mii % mod;
			ma[j][i] = 0;
			(ma[j][lim + 1] += (mod - x) * ma[i][lim + 1]) %= mod;
		}
		ma[i][0] = ma[i][lim + 1] * mii % mod;
	}

	for (int i = 0; i < n; i ++)
		for (int j = 0; j < m; j ++) {
			ans[i][j] = f[i][j][0];
			for (int k = 1; k <= lim; k ++)
				(ans[i][j] += ma[k][0] * f[i][j][si(k)]) %= mod;
		}


	int q = read;
	while (q --) {
		int x = read, y = read;
		printf("%lld\n", ans[x - 1][y - 1]);
	}
}
