/*
 * Author: Kewth

 * Date:
  2020.07.23

 * Solution:
  求个前缀和 s，那么任意时刻要满足 s[x] >= s[y] 。
  设 [1, k] 的最大值在 X ，[k, n] 的最小值在 Y ，考虑从 (x, y) 走到 (X, Y) 。
  不难发现如果 x 走若干步走到一个 s 变小的位置再走 y ，那么交换顺序让 x 不动先走 y 一
定是不劣的，因此每次 x 要移动就要一直移动到不比当前小的位置，同理 y 要走到不比当前大
的位置，那么求出每个点左右第一个不增/不减的值以及之间的最大/最小值，然后不断往两边移
动即可判断是否能走到 (X, Y) 。
  注意到移动是可逆的，从 (X, Y) 走到 (1, n) 等价于从 (1, n) 走到 (X, Y) ，同样的问题
再做一遍即可。

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

static struct {
    inline operator int () { int x; return scanf("%d", &x), x; }
    inline operator ll () { ll x; return scanf("%lld", &x), x; }
} read;

const int maxn = 100005;
ll a[maxn];
int tol[maxn], tor[maxn];
ll lmin[maxn], rmax[maxn];
ll rmin[maxn], lmax[maxn];

#define Assert(x) if (!(x)) {puts("No"); continue;} read

int main () {
	int T = read;
	while (T --) {
		int n = read, s = read;

		a[0] = 0;
		for (int i = 1; i <= n; i ++) a[i] = a[i - 1] + ll(read);

		Assert(a[1] >= a[n]);

		for (int i = s, j; i >= 1; i = j) {
			j = i - 1;
			lmin[i] = a[i];
			while (j >= 1 and a[j] < a[i]) lmin[i] = std::min(lmin[i], a[j --]);
			tol[i] = j;
		}

		for (int i = s, j; i <= n; i = j) {
			j = i + 1;
			rmax[i] = a[i];
			while (j <= n and a[j] > a[i]) rmax[i] = std::max(rmax[i], a[j ++]);
			tor[i] = j;
		}

		int x = s, y = s, test = 1;
		while (test) {
			test = 0;
			if (tol[x] >= 1 and lmin[x] >= a[y]) x = tol[x], test = 1;
			if (tor[y] <= n and rmax[y] <= a[x]) y = tor[y], test = 1;
		}

		Assert(tol[x] < 1 and tor[y] > n);

		for (int i = 1, j; i <= x; i = j) {
			j = i + 1;
			rmin[i] = a[i];
			while (j <= x and a[j] < a[i]) rmin[i] = std::min(rmin[i], a[j ++]);
			tor[i] = j;
		}

		for (int i = n, j; i >= y; i = j) {
			j = i - 1;
			lmax[i] = a[i];
			while (j >= y and a[j] > a[i]) lmax[i] = std::max(lmax[i], a[j --]);
			tol[i] = j;
		}

		int X = 1, Y = n;
		test = 1;
		while (test) {
			test = 0;
			if (tor[X] <= x and rmin[X] >= a[Y]) X = tor[X], test = 1;
			if (tol[Y] >= y and lmax[Y] <= a[X]) Y = tol[Y], test = 1;
		}

		Assert(tor[X] > x and tol[Y] < y);
		puts("Yes");
	}
}
