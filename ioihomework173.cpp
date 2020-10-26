/*
 * Author: Kewth

 * Date:
  2020.10.16

 * Solution:
  有两种情况，把若干数修改为一个是所有数的倍数的数，或者把若干数分别修改为已经存在的数。
  对两种情况分别算最优操作然后取更优即可，枚举权值和倍数，复杂度调和级数。

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

const int maxw = 1000005;
int tot[maxw];
int tmp[maxw], tp;
int f[maxw], g[maxw];

int main () {
	int n = read, w = 1000000;
	for (int i = 1; i <= n; i ++) ++ tot[read];
	int orign = 0;
	for (int x = 1; x <= w; x ++)
		if (tot[x]) {
			++ orign;
			bool ok = 0;
			for (int y = x + x; y <= w; y += x)
				ok |= tot[y];
			if (ok) tmp[++ tp] = tot[x];
		}

	std::sort(tmp + 1, tmp + tp + 1);
	for (int i = 1; i <= tp; i ++)
		f[tmp[i] += tmp[i - 1]] = 1;
	for (int x = 1; x <= n; x ++)
		f[x] += f[x - 1];

	tp = 0;
	for (int x = 1; x <= w; x ++)
		if (tot[x])
			tmp[++ tp] = tot[x];
	std::sort(tmp + 1, tmp + tp + 1);
	g[0] = -1;
	for (int i = 1; i <= tp; i ++)
		g[tmp[i] += tmp[i - 1]] = 1;
	for (int x = 1; x <= n; x ++)
		g[x] += g[x - 1];

	for (int i = 0; i <= n; i ++)
		printf("%d ", orign - std::max(f[i], g[i]));
	puts("");
}
