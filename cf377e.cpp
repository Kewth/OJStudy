/*
 * Since g++10 is released, some characters is not valid inside #if 0 :(
 * So, why not using clang++? :D

 * Date:
  2020.06.17

 * Solution:
 * 设计 DP ，斜率优化

  不妨假设 V, C 分别严格单调递增。

  容易设计出一个 DP ，设 f[i] 表示获得 C[i] 的金币需要的最少时间，以及 g[i] 表示用
f[i] 的时间至多能得到多少金币。朴素的转移只需要枚举最后使用的工厂 j ，有转移：

    f[i] = f[j] + k, g[i] = g[j] - C[j] + k V[j]

  其中 k = ceil((C[i] - g[j] + C[j]) / V[j]) 。

  看着就很能优化，对于工厂 j 在二维平面上用一个点 (g[j] - C[j] - f[j] * V[j], V[j])
表示，设这个点为 (x, y) ，那么这个转移对应的就是找到最小的 k 满足：

    y + kx >= C[i]

  也就是要找一条直线截距为 C[i] ，斜率负整数，存在 k(x, y) 在该直线上方，最大化该斜
率。显然需要关注的点构成一个上凸壳，那么在凸壳上二分就可以得到最优转移点，但注意到
C 是单调的，因此二分没有必要，最优转移点不会左移，直接维护即可。

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
#include <cctype>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef __int128 lll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
} read;

const int maxn = 200005;
struct shit {
	ll V, C;
} s[maxn];
ll cx[maxn], cy[maxn];
int cp;

bool cmp (shit a, shit b) {
	if (a.C == b.C) return a.V > b.V;
	return a.C < b.C;
}

lll cross (ll x1, ll y1, ll x2, ll y2) {
	return lll(x1) * y2 - lll(x2) * y1;
}

int main () {
	int n = int(read);
	s[maxn - 1].C = read;
	for (int i = 1; i <= n; i ++) {
		s[i].V = read;
		s[i].C = read;
	}

	std::sort(s + 1, s + n + 1, cmp);
	while (s[n].C > s[maxn - 1].C) -- n;
	int sp = 1;
	for (int i = 2; i <= n; i ++)
		if (s[i].C > s[sp].C and s[i].V > s[sp].V)
			s[++ sp] = s[i];
	s[++ sp] = s[maxn - 1];
	n = sp;

	int p = 1;
	for (int i = 1; i <= n; i ++) {
		ll f = 0, g = 0;
		if (i > 1) {
			if (p == 0) p = 1;
			f = (s[i].C - cy[p] + cx[p] - 1) / cx[p];
			g = cy[p] + cx[p] * f;
			while (p < cp and cross(cx[p], cy[p] - g, // XXX: 这里要用 g 而不是 s[i].C ！
						cx[p + 1] - cx[p], cy[p + 1] - cy[p]) >= 0) {
				++ p;
				f = (s[i].C - cy[p] + cx[p] - 1) / cx[p];
				g = cy[p] + cx[p] * f;
			}
			/* debug("From %lld %lld\n", cx[p], cy[p]); */
		}

		/* debug("%lld %lld : %lld %lld\n", s[i].C, s[i].V, f, g); */

		if (i == n) {
			printf("%lld\n", f);
			break;
		}

		ll x = s[i].V, y = g - s[i].C - f * s[i].V;
		while (cp >= 2 and cross(cx[cp] - cx[cp - 1], cy[cp] - cy[cp - 1],
					x - cx[cp], y - cy[cp]) >= 0)
			-- cp;
		if (p > cp) p = cp;

		++ cp;
		cx[cp] = x;
		cy[cp] = y;
		/* debug("Add %lld %lld\n", x, y); */
		/* debug("\n"); */
	}
}

