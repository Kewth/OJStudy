/*
 * Since g++10 is released, some characters is not valid inside #if 0 :(
 * So, why not using clang++? :D

 * Date:
  2020.06.04

 * Solution:
  注意到如果存在连续 K 个相同的数并且不是全部相同就一定不会是必败态，因为可以进行一次
“不变操作”。而任意一次操作后就一定会存在 K 个相同的数，这意味着一个状态是必胜态当且仅
当它能一步操作转移到全部相同的状态，这个是很好判定的。
  但必败态未必是全部相同的状态，考虑还有什么额外的必败态，这样的状态要满足无论怎么操作
都转移到必胜态，那么不难发现如果染 [l, r] 这个区间，只要满足 l > 1 且 r < n ，必须有
[1, l) 颜色相同且 (r, n] 颜色相同且两边的颜色不同。而如果染 [1, K], 首先根据上一条可以
知道 [K + 2, n] 颜色相同，那么 K + 1 处的颜色必须与之相反，同理 n - K 处的颜色必须与另
外一段的颜色不同。
  至于其他的自然都是平局态。

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
char s[maxn];

int main () {
	int n = read, m = read;
	scanf("%s", s + 1);

	int l0 = 0, l1 = 0, r0 = 0, r1 = 0;
	for (int i = 1; i <= n; i ++)
		if (s[i] == '0') {
			r0 = i;
			if (!l0) l0 = i;
		} else {
			r1 = i;
			if (!l1) l1 = i;
		}
	if (l0 + m > r0 or l1 + m > r1)
		return puts("tokitsukaze"), 0;

	if (m * 2 < n)
		return puts("once again"), 0;

	bool lose = 1;
	for (int i = 1; i <= n - m - 1; i ++)
		lose &= s[i] == s[1];
	lose &= s[n - m] != s[1];
	lose &= s[m + 1] != s[n];
	for (int i = m + 2; i <= n; i ++)
		lose &= s[i] == s[n];

	if (lose)
		return puts("quailty"), 0;

	puts("once again");
}
