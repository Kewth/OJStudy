/*
 * Author: Kewth

 * Date:
  2022.07.06

 * Solution:
  没有必要筛素数。

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
typedef unsigned int ui;

bool mark[1000005];
int main () {
	ui l, r;
	while (~scanf("%u%u", &l, &r)) {
		for (ui i = l; i <= r; i ++) mark[i - l] = 0;
		if (l == 1) mark[0] = 1;
		for (ui i = 2; i <= r / i; i ++)
			for (ui j = (std::max(i * i, l) + i - 1) / i * i; j <= r; j += i)
				mark[j - l] = 1;
		ui lst = 0, min = 1000000000, max = 0;
		ui minx, miny, maxx, maxy;
		for (ui i = l; i <= r; i ++)
			if (!mark[i - l]) {
				if (lst and i - lst < min)
					min = i - lst, minx = lst, miny = i;
				if (lst and i - lst > max)
					max = i - lst, maxx = lst, maxy = i;
				lst = i;
			}
		if (max) printf("%u,%u are closest, %u,%u are most distant.\n", minx, miny, maxx, maxy);
		else puts("There are no adjacent primes.");
	}
}
