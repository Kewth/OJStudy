/*
 * Author: Kewth

 * Date:
  2020.12.18

 * Solution:

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

const int maxn = 202;
char s[maxn], t[maxn];

int main () {
	int T = read;
	while (T --) {
		int n = read, p = 0;
		scanf("%s", s + 1);
		for (int i = 1; i <= n; i ++)
			if (s[i] != 't')
				t[++ p] = s[i];
		for (int i = p + 1; i <= n; i ++)
			t[i] = 't';
		t[n + 1] = 0;
		puts(t + 1);
	}
}
