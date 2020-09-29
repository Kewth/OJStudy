/*
 * Since g++10 is released, some characters is not valid inside #if 0 :(
 * So, why not using clang++? :D

 * Date:
  2020.09.25

 * Solution:
  把总分看成一个新维度做三维偏序即可。

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
#include <map>
#include <unordered_map>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct _{
	inline operator int () { int x; return scanf("%d", &x), x; }
	/* inline operator ll () { ll x; return scanf("%lld", &x), x; } */
} read;

const int maxn = 100005;
struct ele { int x, y, z, i; } e[maxn << 1];
int tmp[maxn << 1], tp;
int ans[maxn];
std::unordered_map<int, int> bit[maxn << 1];

#define PREWORK(x)\
	tp = 0; \
	for (int i = 1; i <= n + q; i ++) \
		tmp[++ tp] = e[i].x; \
	std::sort(tmp + 1, tmp + tp + 1); \
	tp = int(std::unique(tmp + 1, tmp + tp + 1) - tmp - 1); \
	for (int i = 1; i <= n + q; i ++) \
		e[i].x = int(std::lower_bound(tmp + 1, tmp + tp + 1, e[i].x) - tmp);

int main () {
	int n = read, q = read, V = 1000000000;
	for (int i = 1; i <= n; i ++) {
		e[i].x = V - read;
		e[i].y = V - read;
		e[i].z = e[i].x + e[i].y;
		e[i].i = 0;
	}
	for (int i = 1; i <= q; i ++) {
		e[n + i].x = V - read;
		e[n + i].y = V - read;
		e[n + i].z = V + V - read;
		e[n + i].i = i;
	}

	PREWORK(x)
	PREWORK(y)
	PREWORK(z)

	std::sort(e + 1, e + n + q + 1, [] (ele a, ele b) {
				return a.x == b.x ? a.i < b.i : a.x < b.x;
			});

	for (int i = 1; i <= n + q; i ++) {
		if (e[i].i == 0) {
			for (int j = e[i].y; j <= n + q; j += j & -j)
				for (int k = e[i].z; k <= n + q; k += k & -k)
					++ bit[j][k];
		}
		else {
			for (int j = e[i].y; j; j -= j & -j)
				for (int k = e[i].z; k; k -= k & -k)
					ans[e[i].i] += bit[j][k];
		}
	}

	for (int i = 1; i <= q; i ++)
		printf("%d\n", ans[i]);
}
