/*
 * Since g++10 is released, some characters is not valid inside #if 0 :(
 * So, why not using clang++? :D

 * Date:
  2020.07.16

 * Solution:
  不难发现问题等价于求权值和最大的线性无关组。
  构造拟阵 M = (S, I) ，S 是所有给定向量的集合，对于 S 的子集 T ，T 属于 I 当且仅当 T 包
含的向量线性无关，只需要证明遗传性和交换性即可。
  遗传性等价于线性无关组的子集仍是线性无关组，显然。
  交换性的话，对于两个大小不等的线性无关组 A, B 满足 |A| < |B| ，如果不满足交换性，说明
B 中的任意一个元素都能被 A 的一个子集线性表出，那么 B 也就能被 A 线性表出，这与 B 是个比
A 大的线性无关组产生矛盾。

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

const int maxn = 100, maxk = 30;
int a[maxn + 5];
int bas[maxk];

int main () {
	int n = read;
	for (int i = 1; i <= n; i ++) read(a[i]);
	std::sort(a + 1, a + n + 1);
	ll ans = 0;
	for (int i = n; i; i --) {
		int x = a[i], insert = 0;
		for (int k = 0; k < maxk; k ++)
			if (x >> k & 1) {
				if (!bas[k]) bas[k] = x, insert = 1;
				x ^= bas[k];
			}
		if (!insert) ans += a[i];
	}
	printf("%lld\n", ans);
}
