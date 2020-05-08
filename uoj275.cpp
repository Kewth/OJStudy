#if 0
2020.05.08

  Lucas 定理把 n, m 转成 k 进制数后数位 DP 即可。
#endif
#include <cstdio>
#include <cstring>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
} read;

const int maxk = 62, mod = 1000000007;
ll f[maxk][2][2][2];
int N[maxk], M[maxk];

int main () {
	int T = read, p = read;

	while (T --) {
		ll n = read, m = read;
		ll l = std::max(m - n, 0ll), r = m;
		ll ans = ((l + r) % mod) * ((r - l + 1) % mod) % mod;
		(ans *= (mod - 1) >> 1) %= mod;

		int lim = 0;
		while (n or m) {
			N[lim] = n % p;
			M[lim] = m % p;
			++ lim;
			n /= p;
			m /= p;
		}

		memset(f[lim], 0, sizeof f[lim]);
		f[lim][0][0][0] = 1;

		for (int k = lim - 1; k >= 0; k --) {
			memset(f[k], 0, sizeof f[k]);
			for (int nf = 0; nf < 2; nf ++)
				for (int mf = 0; mf < 2; mf ++)
					for (int s = 0; s < 2; s ++) {
						ll now = f[k + 1][nf][mf][s];
						for (int x = 0; x < (nf ? p : N[k] + 1); x ++)
							for (int y = 0; y < (mf ? p : M[k] + 1); y ++)
								f[k][nf | (x < N[k])][mf | (y < M[k])][s | (x < y)] +=
									now;
					}
			for (int nf = 0; nf < 2; nf ++)
				for (int mf = 0; mf < 2; mf ++)
					for (int s = 0; s < 2; s ++) {
						f[k][nf][mf][s] %= mod;
						/* if (f[k][nf][mf][s]) */
						/* 	debug("f[%d][%d%d%d] = %lld\n", */
						/* 			k, nf, mf, s, f[k][nf][mf][s]); */
					}
		}

		for (int nf = 0; nf < 2; nf ++)
			for (int mf = 0; mf < 2; mf ++)
				ans += f[0][nf][mf][1];
		ans %= mod;
		if (ans < 0) ans += mod;

		printf("%lld\n", ans);
	}
}
