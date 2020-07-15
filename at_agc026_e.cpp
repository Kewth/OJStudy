/*
 * Since g++10 is released, some characters is not valid inside #if 0 :(
 * So, why not using clang++? :D

 * Date:
  2020.07.15

 * Solution:
  注意到对于选中的第 i 对 a, b ，如果 a 在 b 左边，那么它们之间的 a 都不能选，如果 a 在 b
右边，那么它们之间的 b 都必须选。
  据此 DP ，设 f[i] 表示只考虑第 i 到 n 对 a, b ，钦定第 i 对 a, b 必须选的最大串。转移按
第 i 对 a, b 的相对位置讨论，用 g[i] 表示 max(f[i] ~ f[n]) 即可。

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
#include <string>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef std::string str;

struct _{
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
} read;

const int maxn = 3000;
char s[maxn * 2 + 5];
int apos[maxn + 5], bpos[maxn + 5];
str f[maxn + 5], g[maxn + 5];

int main () {
	int n = read;
	scanf("%s", s + 1);

	for (int i = 1, ap = 0, bp = 0; i <= n * 2; i ++) {
		if (s[i] == 'a') apos[++ ap] = i;
		if (s[i] == 'b') bpos[++ bp] = i;
	}

	for (int i = n; i; i --) {
		if (apos[i] < bpos[i]) {
			int j = i;
			while (j <= n and apos[j] < bpos[i]) ++ j;
			f[i] = "ab" + g[j];
		}
		if (apos[i] > bpos[i]) {
			int j = i;
			while (j <= n and bpos[j] < apos[i]) ++ j;
			for (int k = 0; k < j - i; k ++) f[i] += 'b';
			f[i] += 'a' + (i + 1 == j ? g[i + 1] : f[i + 1]).substr(
					size_t(j - i - 1), str::npos);
		}
		g[i] = std::max(f[i], g[i + 1]);
	}

	puts(g[1].c_str());
}
