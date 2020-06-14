/*
 * Since g++10 is released, some characters is not valid inside #if 0 :(
 * So, why not using clang++? :D

 * Date:
  2020.06.12

 * Solution:
 * 贪心，单调栈，双指针

  考场上一直想的 DP ，到 O(n^2) 就死路了。抛弃 DP 上贪心，可以发现（反正我是没发现，没
救了没救了）末尾的段只要尽可能段就是最优的（因为同时满足了贡献的最优性和转移的最优性）。
那么就是要求出 g[i] 表示以 i 为结尾的段的最小的长度，设 j = i - g[i] ，那么 g[i] 是满足
s[i] - s[j] >= s[j] - s[j - g[j]] 的最小的正值。

  问题转换为求 g 数组，不妨设 f[i] = s[i] + s[i] - s[i - g[i]] ，那么上述条件可以表述为
s[i] >= f[j] ，要求出这样的最大的 j 。

  对于 j1 < j2 且 f[j1] >= f[j2] ，j2 严格比 j1 优，维护这样的 j2 ，也就是可以用单调栈
维护所有有用的 f ，这些 f 的下标和值都是递增的。这样每次求最优的 j 就可在单调栈上二分，
但要做到线性还是不够。

  注意到 s[i] 也是递增的，二分是多余的，利用双指针的思想在单调栈上用一个指针维护最优转
移即可（另一个指针是 i 本身）。

 * Digression:
  我是傻逼啊。

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
typedef __int128 lll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator () (a...); }
} read;

const int maxn = 40000005;
int g[maxn];
ll a[maxn];
int st[maxn], sp, np;
int ans[40], ap;

inline ll f (int i) { return a[i] * 2 - a[i - g[i]]; }

int main () {
	int n = read, t = read;
	if (t == 0)
		for (int i = 1; i <= n; i ++)
			read(a[i]);
	if (t == 1) {
		int x = read, y = read, z = read;
		read(a[1], a[2]);
		int m = read, M = (1 << 30) - 1;
		for (int i = 3; i <= n; i ++)
			a[i] = (x * a[i - 1] + y * a[i - 2] + z) & M;
		int i = 0;
		while (m --) {
			int p = read, l = read, r = read;
			while (i < p)
				++ i, a[i] = a[i] % (r - l + 1) + l;
		}
	}

	for (int i = 1; i <= n; i ++) a[i] += a[i - 1];
	for (int i = 1; i <= n; i ++) {
		while (np < sp and f(st[np + 1]) <= a[i]) ++ np;
		g[i] = i - st[np];
		while (sp and f(st[sp]) >= f(i)) -- sp;
		if (np > sp) np = sp;
		st[++ sp] = i;
	}

	lll x = 0;
	int i = n;
	while (i) {
		/* debug("%d %d\n", i - g[i] + 1, i); */
		x += lll(a[i] - a[i - g[i]]) * (a[i] - a[i - g[i]]);
		i -= g[i];
	}

	while (x) {
		ans[++ ap] = x % 10;
		x /= 10;
	}
	if (!ap) ans[++ ap] = 0;
	while (ap) putchar('0' + ans[ap --]);
	puts("");
}
