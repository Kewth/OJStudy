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
} read;

const int maxn = 100005;
int fa[maxn];

int find (int x) {
	if (x == fa[x]) return x;
	return fa[x] = find(fa[x]);
}

int main () {
	int n = read, m = read;
	for (int i = 1; i <= n; i ++) fa[i] = i;
	int ans = 0;
	for (int i = 1; i <= m; i ++) {
		int x = find(read), y = find(read);
		if (x == y) ++ ans;
		else fa[x] = y;
	}
	printf("%d\n", ans);
}
