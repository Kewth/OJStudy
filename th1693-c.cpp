/*
 * Author: Kewth

 * Date:
  2020.08.02

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
#include <cmath>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

static struct {
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
} read;

const int maxs = 200000;
const int Maxw = 8000000, mod = 1000000007;
ll A[Maxw + 1], B[Maxw + 1], C[Maxw + 1];
int minp[Maxw + 1];

inline ll Sa (ll n) { return n % mod; }
inline ll Sb (ll n) {
	return n & 1 ? (n + 1) / 2 % mod * n % mod : n / 2 % mod * (n + 1) % mod;
}
inline ll Sc (ll n) {
	static const int inv6 = (mod + 1) / 6;
	n %= mod;
	return n * (n + 1) % mod * (n + n + 1) % mod * inv6 % mod;
}

struct sieve {
	ll n, s, m;
	ll A[maxs], B[maxs], C[maxs], w[maxs];
	inline int id (ll x) {
		return int(x <= s ? x : m - n / x + 1);
	}
	void init (ll _n) {
		n = _n;
		s = ll(std::sqrt(n));
		for (ll l = 1, r; l <= n; l = r + 1)
			w[++ m] = r = n / (n / l);
		for (int i = 1; i <= m; i ++)
			if (w[i] <= Maxw)
				A[i] = ::A[w[i]], B[i] = ::B[w[i]], C[i] = ::C[w[i]];
			else {
				A[i] = B[i] = C[i] = 1;
				for (ll l = 2, r; l <= w[i]; l = r + 1) {
					r = w[i] / (w[i] / l);
					int j = id(w[i] / l);
					(A[i] += (mod - A[j]) * (Sa(r) - Sa(l - 1) + mod)) %= mod;
					(B[i] += (mod - B[j]) * (Sb(r) - Sb(l - 1) + mod)) %= mod;
					(C[i] += (mod - C[j]) * (Sc(r) - Sc(l - 1) + mod)) %= mod;
				}
			}

	}
} ns, ms;

int main () {
	A[1] = B[1] = C[1] = 1;
	for (int i = 2; i <= Maxw; i ++) {
		int &p = minp[i];
		if (!p) {
			p = i;
			if (i <= Maxw / i)
				for (int j = i * i; j <= Maxw; j += i)
					if (!minp[j])
						minp[j] = i;
		}
		if (minp[i / p] != p) {
			A[i] = -A[i / p];
			B[i] = -B[i / p] * p % mod;
			C[i] = -C[i / p] * p % mod * p % mod;
		}
	}

	for (int i = 1; i <= Maxw; i ++) {
		A[i] = (A[i] + mod + A[i - 1]) % mod;
		B[i] = (B[i] + mod + B[i - 1]) % mod;
		C[i] = (C[i] + mod + C[i - 1]) % mod;
	}

	ll n = read, m = read;
	ns.init(n), ms.init(m);

	ll ans = 0;
	for (ll l = 1, r, sa = 0, sb = 0, sc = 0; l <= n and l <= m; l = r + 1) {
		ll _sa = sa, _sb = sb, _sc = sc;
		ll n0 = n / l, m0 = m / l;
		if (n / n0 < m / m0) {
			r = n / n0;
			sa = ns.A[ns.id(r)];
			sb = ns.B[ns.id(r)];
			sc = ns.C[ns.id(r)];
		} else {
			r = m / m0;
			sa = ms.A[ms.id(r)];
			sb = ms.B[ms.id(r)];
			sc = ms.C[ms.id(r)];
		}
		_sa = sa + mod - _sa;
		_sb = sb + mod - _sb;
		_sc = sc + mod - _sc;
		/* debug("%lld %lld | %lld %lld | %lld %lld %lld\n", */
		/* 		l, r, n0, m0, _sa % mod, _sb % mod, _sc % mod); */
		ll n1 = Sb(n0), m1 = Sb(m0);
		n0 = n0 % mod * n % mod;
		m0 = m0 % mod * m % mod;
		(ans += n0 * m0 % mod * _sa) %= mod;
		(ans += (n0 * m1 + n1 * m0) % mod * (mod - _sb)) %= mod;
		(ans += n1 * m1 % mod * _sc) %= mod;
	}
	printf("%lld\n", ans * 4 % mod);
}
