/*
 * Author: Kewth

 * Date:
  2020.07.20

 * Solution:
 * 设计 DP ，前缀和优化，双折线法

  如果没有 K 的限制答案就是卡特兰数，这启发我们把问题放在二维平面上，于是可以发现 K 的限制
竟然就是一条直线，加上卡特兰数本来就有的限制直线，就是双折线法的问题。

  好吧，具体来说，设计一个 DP f[i][j] 表示 i 个叶子左链长为 j 的合法二叉树数量，转移在左边
加点，枚举加点位置，一波前缀和优化后可以发现有 f[i][j] = f[i][j + 1] + f[i - 1][j - 1] 。

  这个转移就很明显了，把 f[i][j] 映射到平面上的点 (i, i - j) 就是个路径计数，有一条折线，
而 K 对这个 DP 的限制就是 j 这一维不能超过 K - 1 ，也就是不能触碰 y = x - K 。

 * Digression:

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

#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

static struct {
    inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int mod = 10007;
int fac[mod], ifac[mod];

int power (int x, int k) {
	if (k < 0) k += mod - 1;
	int res = 1;
	while (k) {
		if (k & 1) (res *= x) %= mod;
		(x *= x) %= mod;
		k >>= 1;
	}
	return res;
}

int C (int n, int m) {
	int n0 = n / mod, m0 = m / mod;
	int n1 = n % mod, m1 = m % mod;
	if (m0 > n0 or m1 > n1) return 0;
	int a0 = 1ll * fac[n0] * ifac[m0] * ifac[n0 - m0] % mod;
	int a1 = 1ll * fac[n1] * ifac[m1] * ifac[n1 - m1] % mod;
	return a0 * a1 % mod;
}

int lucas (int n, int m) {
	if (!n and !m) return 1;
	int n0 = n % mod, m0 = m % mod;
	if (m0 > n0) return 0;
	int tmp = 1ll * fac[n0] * ifac[m0] * ifac[n0 - m0] % mod;
	return lucas(n / mod, m / mod) * tmp % mod;
}

int path (int x, int y) {
	if (y > x or y < -x) return 0;
	return lucas(x, (x - y) >> 1);
}

int main () {
	int n = read, m = read;
	int up = m - 1, down = - 1;
	int X = (n - 1) << 1, Y = 0;

	fac[0] = 1;
	for (int i = 1; i < mod; i ++) fac[i] = fac[i - 1] * i % mod;
	ifac[mod - 1] = power(fac[mod - 1], -1);
	for (int i = mod - 1; i; i --) ifac[i - 1] = ifac[i] * i % mod;

	ll ans = path(X, Y);

	for (int x = X, y = Y, coe = 1; std::abs(y) <= X; ) {
		y = coe == 1 ? up * 2 - y : down * 2 - y;
		coe = - coe;
		ans += coe * path(x, y);
		// debug("%d %d %d %d\n", x, y, coe, path(x, y));
	}

	for (int x = X, y = Y, coe = 1; std::abs(y) <= X; ) {
		y = coe == 1 ? down * 2 - y : up * 2 - y;
		coe = - coe;
		ans += coe * path(x, y);
	}

	ans %= mod;
	if (ans < 0) ans += mod;
	printf("%lld\n", ans);
}
