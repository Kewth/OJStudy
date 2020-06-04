/*
 * Since g++10 is released, some characters is not valid inside #if 0 :(
 * So, why not using clang++? :D

 * Date:
  2020.06.03

 * Solution:
  不妨假设 a 两两不同，有相同的特判一下。
  把 a 排序，每一步操作后都必须满足 a 严格单调递增，那么最终的状态一定是 0, 1, ... n-1 ，
只要不到这个状态双方都一定可以操作，那么求出 a 到最终状态需要的操作次数即可。

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

const int maxn = 100005;
int a[maxn];

int main () {
	int n = read;
	for (int i = 1; i <= n; i ++) read(a[i]);

	std::sort(a + 1, a + n + 1);
	int shit = 0;
	for (int i = 1; i < n; i ++)
		if (a[i] == a[i + 1]) {
			if (a[i] == 0)
				return puts("cslnb"), 0;
			++ shit;
			-- a[i];
			break;
		}

	for (int i = 1; i < n; i ++)
		if (a[i] == a[i + 1])
			return puts("cslnb"), 0;

	for (int i = 1; i <= n; i ++)
		shit += a[i] - i + 1;

	if (shit & 1) puts("sjfnb");
	else puts("cslnb");
}
