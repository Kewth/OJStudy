/*
 * Since g++10 is released, some characters is not valid inside #if 0 :(
 * So, why not using clang++? :D

 * Date:
  2020.06.15

 * Solution:
  不妨假设 n, m >= 2 ，直接令 b[i] = i, a[i][j] = lcm(i, n + j) 即可，由于相邻两个数
的 gcd 为 1 ，这样构造显然是正确且最优的。

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

ll gcd (ll a, ll b) {
	if (!b) return a;
	return gcd(b, a % b);
}

int main () {
	int n = read, m = read;
	if (n == 1 and m == 1) return puts("0"), 0;
	for (int i = 1; i <= n; i ++) {
		for (int j = 1; j <= m; j ++) {
			ll x = i, y = n + j;
			if (m == 1) x = m + i, y = j;
			printf("%lld ", x * y / gcd(x, y));
		}
		puts("");
	}
}
