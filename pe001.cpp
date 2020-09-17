/*
 * Author: Kewth

 * Date:
  2020.08.24

 * Solution:
  简单容斥。

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
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

static struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

inline ll sum (int n) { return 1ll * n * (n + 1) >> 1; }

void solve (int n) {
	-- n;
	printf("%lld\n", sum(n / 3) * 3 + sum(n / 5) * 5 - sum(n / 15) * 15);
}

int main () {
#ifdef PE
	solve(1000);
#else
	int T = read;
	while (T --) solve(read);
#endif
}
