/*
 * Since g++10 is released, some characters is not valid inside #if 0 :(
 * So, why not using clang++? :D

 * Date:
  2020.07.19

 * Solution:
  杨表钩长公式模板。

 * Digression:
  直接算 n! 会爆，要同时维护分子分母不断约分。

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
typedef long long ll;

struct {
	inline operator int () { int x = 0; return scanf("%d", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
} read;

ll gcd (ll a, ll b) { return b ? gcd(b, a % b) : a; }

int main () {
	int a[10];
	while (1) {
		int n = read, tot = 0;
		if (n == 0) break;
		for (int i = 1; i <= n; i ++) read(a[i]);
		ll ans = 1, shit = 1;
		for (int i = 1; i <= n; i ++) {
			for (int j = 1; j <= a[i]; j ++) {
				int hook = a[i] - j + 1;
				for (int k = i + 1; k <= n and j <= a[k]; k ++)
					++ hook;
				ans *= ++ tot;
				shit *= hook;
				ll g = gcd(ans, shit);
				ans /= g;
				shit /= g;
			}
		}
		printf("%lld\n", ans);
	}
}
