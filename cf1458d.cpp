/*
 * Author: Kewth

 * Date:
  2020.12.21

 * Solution:
 * 问题转换，贪心

  在数轴上，把 1 看做向正方向移动一个单位，0 看做向负方向移动一个单位。每次从 x
移动到 y 就连一条边（可以重边），由此可以得到一张特殊的图，原串就对应与一条欧拉
路。

  考虑串的翻转操作在图上造成的影响，不难发现就是在欧拉路上选一个环，然后翻转该
环的方向。不难想到，任意一条欧拉路都能由有限次操作得到，那么要求字典序最小的串，
就等价于选出一条“字典序”最小的欧拉路，贪心即可。

 * Digression:

 * CopyRight:
   __  __                  __   __
  |  |/  |.-----.--.--.--.|  |_|  |--.
  |     < |  -__|  |  |  ||   _|     |
  |__|\__||_____|________||____|__|__|

 */

#include <cstdio>
#include <cstring>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

static struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 500005;
char s[maxn];
int a[maxn << 1];

int main () {
	int T = read;
	while (T --) {
		scanf("%s", s + 1);
		int n = int(strlen(s + 1)), p = maxn, l = maxn, r = maxn;
		/* for (int i = 0; i <= n; i ++) */
		/* 	a[maxn - i] = a[maxn + i] = 0; */
		for (int i = 1; i <= n; i ++) {
			if (s[i] == '0')
				++ a[-- p];
			else
				++ a[p ++];
			l = std::min(l, p);
			r = std::max(r, p);
		}
		int q = maxn;
		for (int i = 1; i <= n; i ++) {
			if (q == r) {
				putchar('0'), -- a[-- q];
				if (!a[q]) -- r;
			}
			else if (q == l) {
				putchar('1'), -- a[q ++];
				if (!a[q - 1]) ++ l;
			}
			else if (a[q - 1] > 1)
				putchar('0'), -- a[-- q];
			else
				putchar('1'), -- a[q ++];
		}
		puts("");
	}
}
