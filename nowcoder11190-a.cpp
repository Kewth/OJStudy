/*
 * Author: Kewth

 * Date:
  2021.05.14

 * Solution:
  不难发现只要找到一个 s[i] = s[i - 1] 就把 s[i] 改成与两边不同的值就可以了，
因为这样不会有相邻的修改位置，修改数自然是满足条件的。

 * Digression:
  难度：2 / 12

 * CopyRight:
   __  __                  __   __
  |  |/  |.-----.--.--.--.|  |_|  |--.
  |     < |  -__|  |  |  ||   _|     |
  |__|\__||_____|________||____|__|__|

 */

#include <cstdio>
#include <algorithm>
#include <queue>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

static struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 100005;
char s[maxn];

int main () {
	int n = read;
	char S[4] = "RGB";
	scanf("%s", s + 1);
	for (int i = 2; i <= n; i ++)
		if (s[i] == s[i - 1]) {
			for (int j = 0; j < 3; j ++)
				if (S[j] != s[i - 1] and S[j] != s[i + 1])
					s[i] = S[j];
		}
	puts(s + 1);
}
