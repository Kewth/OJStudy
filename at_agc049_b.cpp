/*
 * Author: Kewth

 * Date:
  2020.11.14

 * Solution:
  操作有两种：把一个 1 往左移动一格，或删除两个相邻的 1 。从小到大枚举 t 的每个 1 ，可以
贪心地找到 s 中要移到到该位置的 1 ，进而计算答案。

 * Digression:

 * CopyRight:
   __  __                  __   __
  |  |/  |.-----.--.--.--.|  |_|  |--.
  |     < |  -__|  |  |  ||   _|     |
  |__|\__||_____|________||____|__|__|

 */

#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

static struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 500005;
char s[maxn], t[maxn];
int a[maxn], b[maxn], ap, bp;

int main () {
	int n = read;
	ll ans = 0;
	scanf("%s", s + 1);
	scanf("%s", t + 1);
	for (int i = 1; i <= n; i ++) {
		if (s[i] == '1') a[++ ap] = i;
		if (t[i] == '1') b[++ bp] = i;
	}
	int j = 1;
	for (int i = 1; i <= bp; i ++) {
		if (j > ap)
			return puts("-1"), 0;
		while (a[j] < b[i]) {
			if (ap - j + 1 < 3)
				return puts("-1"), 0;
			ans += a[j + 1] - a[j], j += 2;
		}
		ans += a[j] - b[i];
		++ j;
	}
	while (j <= ap)
		if (j == ap)
			return puts("-1"), 0;
		else
			ans += a[j + 1] - a[j], j += 2;
	printf("%lld\n", ans);
}
