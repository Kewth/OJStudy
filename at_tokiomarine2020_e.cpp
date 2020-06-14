/*
 * Since g++10 is released, some characters is not valid inside #if 0 :(
 * So, why not using clang++? :D

 * Date:
  2020.06.13

 * Solution:
  对于 s 和 t 的每一位进行讨论，不妨假设 s = 0 而 t = 2^k - 1 ，那么就是要选集合满足每
一位有 0 有 1 求方案数。
  直接子集容斥，枚举全部相同的二进制位的集合，然后用组合数算贡献即可。

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

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 55, maxk = 18;
int c[maxn];
ll C[maxn][maxn];

int main () {
	int n = read, m = read, a = read, b = read, ab = a ^ b;
	for (int k = 0; k < maxk; k ++)
		if (!(b >> k & 1) and a >> k & 1)
			return puts("0"), 0;

	int p = 0;
	for (int i = 1; i <= n; i ++) {
		int x = read;
		for (int k = 0; k < maxk; k ++)
			if (!(ab >> k & 1) and (x >> k & 1) != (a >> k & 1))
				goto fail;
		c[++ p] = x;
fail:;
	}
	n = p;
	if (m > n) m = n;

	for (int i = 0; i <= n; i ++) {
		C[i][0] = 1;
		for (int j = 1; j <= i; j ++)
			C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
	}

	ll ans = 0;
	for (int S = ab; S >= 0; S --) {
		S &= ab;
		ll now = 0;
		for (int i = 1; i <= n; i ++) {
			int x = 0;
			for (int j = i + 1; j <= n; j ++)
				if ((c[i] & S) == (c[j] & S))
					++ x;
			/* debug("%d\n", x); */
			for (int j = 0; j < m; j ++)
				now += C[x][j];
		}
		for (int k = 0; k < maxk; k ++)
			if (S >> k & 1)
				now = -now;
		/* debug("%d : %lld\n", S, now); */
		ans += now;
	}

	printf("%lld\n", ans);
}
