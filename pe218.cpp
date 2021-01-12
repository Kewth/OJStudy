/*
 * Author: Kewth

 * Date:
  2021.01.08

 * Solution:

  勾股数 (a, b, c) 总可以找到正整数对 (m, n) 使得

    a = m^2 - n^2
	b = 2mn
	c = m^2 + n^2

  (a, b, c) 互质的话当且仅当 (m, n) 互质且 (m, n) 一奇一偶。由于要求 c = t^2 ，
那么 (m, n, t) 也构成勾股数且互质。

    m = x^2 - y^2
	n = 2xy

  那么三角形面积 S = ab / 2 = (m + n) (m - n) mn = A B C D

    A = (x + y)^2 - 2xy
    B = (x - y)^2 - 2xy
    C = x^2 - y^2
    D = 2xy

  容易验证无论 x, y 取何值 S 总是 84 的倍数。

 * Digression:

  震撼震撼。打表大法好。

 * CopyRight:
   __  __                  __   __
  |  |/  |.-----.--.--.--.|  |_|  |--.
  |     < |  -__|  |  |  ||   _|     |
  |__|\__||_____|________||____|__|__|

 */

#include <cstdio>
#include <cmath>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef __int128 lll;

static struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
} read;

inline lll s2 (ll x) { return lll(x) * x; }

void solve (ll n, bool db = 0) {
	puts("0");
	if (db)
		for (int x = 1; x <= n / x; x ++) {
			ll c = 1ll * x * x;
			for (ll a = 1, b = c - 1; a < b; a ++)
				if (std::__gcd(a, c) == 1) {
					while (s2(a) + s2(b) > s2(c)) -- b;
					if (s2(a) + s2(b) == s2(c)) {
						debug("%lld %lld %lld\n", a, b, c);
						int A = a % 168, B = b % 168;
						if (A * B % 168 != 0)
							debug("^^^\n");
					}
				}
		}
}

int main () {
#ifdef PE
	solve(10000000000000000);
#else
	int q = read;
	while (q --)
		solve(read);
#endif
}
