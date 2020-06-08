/*
 * Since g++10 is released, some characters is not valid inside #if 0 :(
 * So, why not using clang++? :D

 * Date:
  2020.06.08

 * Solution:
  把 0 看做 -1 ，设 a[i] 为前缀和，不难发现一个字符串的不平衡度就是序列 a 的极差。设 f(X)
表示 max(a) <= X 时 min(a) 最大能是多少，那么答案自然就是 min(X - f(X)) 。注意到 f 有一个
性质，对于一个 ? 把 -1 修改为 1 会增加 2 ，比较 f(X) 和 f(X + 2) ，不难发现 X 增加 2 后最
小值最多只会增加 2 ，也就是有 f(X + 2) <= f(X) + 2 ，即 X + 2 - f(X + 2) >= X - f(X) 。
  那么答案就是 min(Z - f(Z), Z + 1 - f(Z + 1)) ，其中 Z 是 X 取值的最小值。

 * Digression:
  佛了，思路和出题人完全不在一条线上，心态炸了。

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
#include <cstring>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

const int maxn = 1000005;
char s[maxn];
int pre[maxn];
int smax[maxn];

int f (int n, int lim) {
	int add = 0, p = 0, res = 0;
	for (int i = 1; i <= n; i ++) {
		p += (s[i] == '1' ? 1 : -1);
		if (s[i] == '?' and add + smax[i] + 2 <= lim)
			add += 2, p += 2;
		res = std::min(res, p);
	}
	return res;
}

int main () {
	scanf("%s", s + 1);
	int n = int(strlen(s + 1));

	int max = 0;
	for (int i = 1; i <= n; i ++) {
		pre[i] = pre[i - 1] + (s[i] == '1' ? 1 : -1);
		max = std::max(max, pre[i]);
	}

	smax[n] = pre[n];
	for (int i = n; i; i --)
		smax[i - 1] = std::max(smax[i], pre[i - 1]);

	printf("%d\n", std::min(max - f(n, max), max + 1 - f(n, max + 1)));
}
