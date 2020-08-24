/*
 * Author: Kewth

 * Date:
  2020.08.11

 * Solution:

 * Digression:
  刷板题系列，用时 7min 。

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
#include <cstring>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

const int maxn = 1000005;
char s[maxn];
int sa[maxn], rank[maxn];
int tmp[maxn], t[maxn], sa2[maxn];

void build (int n) {
	for (int i = 1; i <= n; i ++) ++ t[int(s[i])];
	for (int i = 1; i <= 256; i ++) t[i] += t[i - 1];
	for (int i = n; i; i --) sa[t[int(s[i])] --] = i;
	int max = rank[sa[1]] = 1;
	for (int i = 2; i <= n; i ++)
		rank[sa[i]] = s[sa[i]] == s[sa[i - 1]] ? max : ++ max;

	for (int m = 1; max < n; m <<= 1) {
		int p = 0;
		for (int i = 0; i < m; i ++) sa2[++ p] = n - i;
		for (int i = 1; i <= n; i ++) if (sa[i] > m) sa2[++ p] = sa[i] - m;
		std::fill(t, t + max + 1, 0);
		for (int i = 1; i <= n; i ++) ++ t[rank[i]];
		for (int i = 1; i <= max; i ++) t[i] += t[i - 1];
		for (int i = n; i; i --) sa[t[rank[sa2[i]]] --] = sa2[i];
		std::copy(rank, rank + n + 1, tmp);
		max = rank[sa[1]] = 1;
		for (int i = 2; i <= n; i ++)
			rank[sa[i]] = (tmp[sa[i]] == tmp[sa[i - 1]] and
					tmp[sa[i] + m] == tmp[sa[i - 1] + m]) ? max : ++ max;
	}
}

int main () {
	scanf("%s", s + 1);
	int n = int(strlen(s + 1));
	build(n);
	for (int i = 1; i <= n; i ++) printf("%d%c", sa[i], " \n"[i == n]);
}
