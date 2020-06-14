/*
 * Since g++10 is released, some characters is not valid inside #if 0 :(
 * So, why not using clang++? :D

 * Date:
  2020.06.13

 * Solution:
  显然操作 O(log) 次后就会变成全 n 。

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

const int maxn = 200005;
int a[maxn], b[maxn];

int main () {
	int n = read, m = read;
	for (int i = 1; i <= n; i ++) read(a[i]);
	while (m --) {
		for (int i = 1; i <= n; i ++) {
			int l = std::max(1, i - a[i]), r = std::min(i + a[i], n);
			++ b[l];
			-- b[r + 1];
		}
		bool full = 1;
		for (int i = 1; i <= n; i ++) {
			a[i] = b[i] + a[i - 1];
			b[i] = 0;
			full &= a[i] == n;
		}
		if (full) break;
	}
	for (int i = 1; i <= n; i ++)
		printf("%d ", a[i]);
	puts("");
}
