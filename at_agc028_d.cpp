/*
 * Since g++10 is released, some characters is not valid inside #if 0 :(
 * So, why not using clang++? :D

 * Date:
  2020.06.04

 * Solution:
  记一个联通块的编号最小和最大的点为关键点对 l, r ，如果该联通块的大小恰为 r - l + 1 ，就
称这个联通块是极小的。
  设 f[l][r] 表示 l, r 在同一个联通块，并且 [l, r] 区间内的点的连边都在 [l, r] 范围内的方
案数。如果求出了 f ，统计答案只需要单独考虑联通块的贡献，设该联通块的关键点对为 l, r ，虽
然该联通块单独出现的次数不好求，但是把关键点对相同的联通块放在一起，可以发现这些联通块的
出现次数之和就是 f[l][r] * g ，其中 g 是 [l, r] 区间外的点任意匹配的方案数。
  求 f 只需要容斥，任意匹配的方案数是很好算的，但是会算重，去重只需要枚举 l 所在联通块的
实际右端点即可。

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

const int maxn = 603, mod = 1000000007;
ll f[maxn];
ll g[maxn];
int h[maxn];
int match[maxn];

int main () {
	ll M = 1ll * mod * mod;
	int n = read, m = read;
	int N = n << 1;

	g[0] = 1;
	for (int i = 0; i < n; i ++)
		g[(i + 1) << 1] = g[i << 1] * (i << 1 | 1) % mod;

	while (m --) {
		int x = read, y = read;
		match[x] = y;
		match[y] = x;
	}

	for (int i = 1; i <= N; i ++)
		h[i] = h[i - 1] + (match[i] == 0);

	ll ans = 0;
	for (int l = 1; l <= N; l ++) {
		std::fill(f, f + N + 1, 0);
		int max = 0;
		for (int r = l; r <= N; r ++) {
			if (match[r] and match[r] < l) break;
			max = std::max(match[r], max);
			if (r >= max) {
				f[r] = g[h[r] - h[l - 1]];
				for (int x = l; x < r; x ++)
					if ((f[r] += (mod - f[x]) * g[h[r] - h[x]]) >= M)
						f[r] -= M;
				f[r] %= mod;
				(ans += f[r] * g[h[N] - h[r] + h[l - 1]]) %= mod;
			}
		}
	}

	printf("%lld\n", ans);
}
