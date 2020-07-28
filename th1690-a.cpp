/*
 * Author: Kewth

 * Date:
  2020.07.27

 * Solution:
  In blog.

 * Digression:

 * CopyRight:
          ▁▃▄▄▄▃▃▃▃▄▶
        ▗▇▀▔    ▔▔▔▔
       ▄▛   ▃▅━━■▄▂
      ▟▊   ▐▘     ▀▙
     ▟▜▌   ▐▖   ▋  ▐▍
    ▟▘ ▜   ▝▀▇▆■▘  ▐▌
  ▗▟▘   ▜▃       ▁▅▛
  ▔▀▼▅▄▃▃██▅▄▄▄▅■▀▔
        ▔▔▔▔▔▔
 */

#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef unsigned int ui;

static struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 3030;
ui a[maxn];
char col[maxn][maxn];

int main () {
	int n = read, m = read;
	ui S = 0;
	for (int i = 1; i <= n; i ++) {
		while (__builtin_popcount(S) != m / 2) ++ S;
		a[i] = S ++;
	}

	for (int i = 2; i <= n; i ++) {
		scanf("%s", col[i] + 1);
		for (int j = 1; j < i; j ++)
			if (col[i][j] == '1')
				putchar('a' + __builtin_ctz(a[i] & (~a[j])));
			else
				putchar('a' + __builtin_ctz(a[j] & (~a[i])));
		puts("");
	}
}
