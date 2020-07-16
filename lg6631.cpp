/*
 * Since g++10 is released, some characters is not valid inside #if 0 :(
 * So, why not using clang++? :D

 * Date:
  2020.07.16

 * Solution:
 * 贪心，转化

  从左到右逐个贪心，如果能确定每个点用了多少次连续操作和多少次间隔操作，那么到第 i 个
位置的时候就可以用 A, B, C 三个值描述当前状态，分别表示第 i 个位置可以免费使用 A 个连
续操作和 B 个间隔操作，第 i + 1 个位置可以免费使用 C 个间隔操作。维护这三个值即可。

  考虑如果具体求出第 i 个点两种操作用了多少次。如果 A + B <= a[i] ，那么先把 A, B, C
三种操作先执行（执行免费操作一定不劣），此时 a[i] 会变为 a[i] - A - B 而 a[i + 1] 会
变为 max(0, a[i + 1] - A - C) ，转换后就可以暂时忽略 A, B, C 的影响。

  一个重要的贪心结论是，A = B = C = 0 时，使用恰好 min(a[i], a[i + 1]) 次连续操作即为
第 i 个位置的一个最优方案。

  如果 A + B > a[i] ，设 K = A + B - a[i] ，那么第 i 个位置的所有操作都要是免费操作，
至少要用 A - K 次连续操作和 B - K 次间隔操作。把 A, B 都减去 K 即可转换为上述情况，并
去掉第 i 个位置的操作代价即可。

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

const int maxn = 100000;
int a[maxn + 5];

int main () {
	int T = read;
	while (T --) {
		int n = read;
		for (int i = 1; i <= n; i ++) read(a[i]);
		a[n + 1] = 0;

		int A = 0, B = 0, C = 0;
		ll ans = 0;
		for (int i = 1; i <= n; i ++) {
			A = std::min(A, a[i]);
			B = std::min(B, a[i]);
			C = std::min(C, a[i + 1]);
			int K = a[i] - A - B;
			if (K < 0) {
				K = -K;
				A -= K;
				B -= K;
				ans -= K;
			}
			int x = std::max(0, std::min(K, a[i + 1] - A - C)), y = K - x;
			A += x;
			B += y;
			ans += K;
			/* debug("%d %d\n", A, B); */
			std::swap(B, C);
		}
		printf("%lld\n", ans);
	}
}
