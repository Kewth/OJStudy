/*
 * Since g++10 is released, some characters is not valid inside #if 0 :(
 * So, why not using clang++? :D

 * Date:
  2020.06.08

 * Solution:
  讨论钝角的位置不难发现满足条件的点构成的区域是一个圆与两个半平面，统计圆内的个数和半平
面的个数即可，圆的统计只需枚举一个维度，半平面的斜率是 -1 ，可以直接 O(1) 推导。

 * Digression:
  妈的自闭了，统计圆内点的个数是 O(R) 的，其中 R 是圆的半径，有 3e8 ，不知道有没有什么更
好的做法。

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

#pragma GCC optimize(3)
#include <cstdio>
#include <cmath>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef long double ld;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const ld eps = ld(1e-10);

int main () {
#ifdef PE
	int r = 1000000000, a = 0, b = 1, n = r / 8;
#else
	int r = read, a = read, b = read, n = read;
#endif

	ld p = ld(a) / b;
	ld R = std::sqrt((n - p) * (n - p) * 2);
	ll ans = 0;

	if (R <= 100000000)
		for (int dx = 0; dx < R; dx ++) {
			ll sqr = ll(std::sqrt(R * R - 1ll * dx * dx) - eps);
			ans += sqr + sqr + 1;
			if (dx) ans += sqr + sqr + 1;
		}
	else {
		// FIXME: 不知道为什么 WA 了
		ll sqr = int(R);
		ll shit = ll(std::ceil(R * R));
		for (int dx = 0; dx < R; dx ++) {
			while (sqr and sqr * sqr >= shit - 1ll * dx * dx) -- sqr;
			ans += (sqr + sqr + 1) * 2;
		}
		ll lim = ll(R - eps);
		ans -= lim + lim + 1;
	}

	int d = int((n - p) * 2);
	ans += 1ll * (r + 1) * (r + 1) + 1ll * r * r;

	if (r & 1) {
		ans -= 1ll * (d / 2 * 2 + 1) * r;
		ans -= 1ll * (d - d / 2) * 2 * (r + 1);
		ans -= r;
	} else {
		ans -= 1ll * (d / 2 * 2 + 1) * (r + 1);
		ans -= 1ll * (d - d / 2) * 2 * r;
		ans -= r + 1;
	}

	if (a % b == 0) ans += 2;

	printf("%lld\n", ans);
}
