/*
 * Author: Kewth

 * Date:
  2021.01.08

 * Solution:
  任意勾股数 (a, b, c) 可以表示为 (m^2 - n^2, 2mn, m^2 + n^2) ，枚举 (m, n) 算贡献即可。
  (a, b, c) 互质当且仅当 (m, n) 互质且 m + n 为奇数。

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

const int N = 5000000;
int f[N + 5], g[N + 5], ans[N + 5];

int main () {
	for (int x = 1; x * x <= N; x += 2)
		for (int y = 2; x * x + y * y <= N; y += 2)
			if (std::__gcd(x, y) == 1) {
				int L = 2 * std::max(x, y) * (x + y);
				if (L <= N)
					++ f[L];
			}
	for (int i = 1; i <= N; i ++)
		for (int j = i; j <= N; j += i)
			g[j] += f[i];
	for (int i = 1; i <= N; i ++)
		ans[i] = ans[i - 1] + (g[i] == 1);

#ifdef PE
	printf("%d\n", ans[1500000]);
#else
	int q = read;
	while (q --)
		printf("%d\n", ans[int(read)]);
#endif
}
