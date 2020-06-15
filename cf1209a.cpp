/*
 * Since g++10 is released, some characters is not valid inside #if 0 :(
 * So, why not using clang++? :D

 * Date:
  2020.06.15

 * Solution:

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

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
} read;

const int maxn = 105;
int a[maxn];

int main () {
	int n = read;
	for (int i = 1; i <= n; i ++) read(a[i]);
	std::sort(a + 1, a + n + 1);
	int ans = 0;
	for (int i = 1; i <= n; i ++)
		if (a[i]) {
			int x = a[i];
			++ ans;
			for (int j = i; j <= n; j ++)
				if (a[j] % x == 0)
					a[j] = 0;
		}
	printf("%d\n", ans);
}
