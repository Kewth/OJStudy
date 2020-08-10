/*
 * Author: Kewth

 * Date:
  2020.08.04

 * Solution:
  这个平方的额外费用用经典套路处理掉，直接排序贪心就完事了。

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
#include <queue>
#include <algorithm>
#include <set>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

static struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
} read;

const int maxn = 305;

int a[maxn];
std::multiset<int> set; // XXX: 又双叒叕忘了用 multiset ！！！！
int main () {
	int n = read, m = read;
	ll ans = 0;
	for (int i = 1; i <= n; i ++) {
		for (int j = 1; j <= m; j ++) read(a[j]);
		std::sort(a + 1, a + m + 1);
		for (int j = 1; j <= m; j ++)
			set.insert(a[j] + j + j - 1);
		ans += *set.begin();
		set.erase(set.begin());
	}
	printf("%lld\n", ans);
}
