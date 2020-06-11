/*
 * Since g++10 is released, some characters is not valid inside #if 0 :(
 * So, why not using clang++? :D

 * Date:
  2020.06.10

 * Solution:
  由于有绝对值，不难发现 |x| 选 0 和非零的贡献不一样，容易想到枚举 0 的个数，然后剩
下的就是隔板法的问题，递推一行的组合数即可，可以解决 p <= 10^9 的情形。

 * Digression:
  淼题。

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

const int maxn = 1000005, mod = 1000000007;
ll inv[maxn];

int main () {
	int n = read, p = read;
	ll ans = 0, x = 1;
	inv[1] = 1;
	for (int i = 2; i <= n; i ++)
		inv[i] = (mod - mod / i) * inv[mod % i] % mod;
	for (int m = 0; m <= n; m ++) {
		ans += x;
		(x *= p - m) %= mod;
		(x *= inv[m + 1]) %= mod;
		(x *= n - m) %= mod;
		(x *= inv[m + 1]) %= mod;
		x <<= 1;
	}
	ans %= mod;
	printf("%lld\n", ans);
}
