#pragma GCC optimize(2)
#if 0
2020.05.22

  我他妈当场被刷新三观。
  朴素的暴力枚举 2^n 个字符串然后 O(q) 判断，不那么朴素的暴力就是把 q 压位，把 n 分为
两段，预处理两边所有字符串能匹配的模式串集合，然后在两边把集合取并就是一个完整的字符串
能匹配的模式串集合，复杂度 O(2^n) 。
  大力循环展开即可，跑满的 O(2^n) 也能过 n = 30 。
        ▁▃▄▄▄▃▃▃▃▄▶
      ▗▇▀▔    ▔▔▔▔
     ▄▛   ▃▅━━■▄▂
    ▟▊   ▐▘     ▀▙
   ▟▜▌   ▐▖   ▋  ▐▍
  ▟▘ ▜   ▝▀▇▆●▘  ▐▌
▗▟▘   ▜▃       ▁▅▛
▔▀▼▅▄▃▃██▅▄▄▄▅■▀▔   CopyRight :)
      ▔▔▔▔▔▔
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef unsigned __int128 ui;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 30, maxq = 100;
char s[maxq][maxn + 1];
ui f[1 << (maxn >> 1)], g[1 << (maxn >> 1)];

int main () {
	int n = read, q = read;
	for (int i = 0; i < q; i ++)
		scanf("%s", s[i]);
	int m1 = n >> 1, m2 = n - m1;

	for (int S = 0; S < (1 << m1); S ++)
		for (int i = 0; i < q; i ++) {
			bool ok = 1;
			for (int k = 0; k < m1; k ++)
				ok &= (s[i][k] == '?' or s[i][k] - '0' == (S >> k & 1));
			if (ok) f[S] |= ui(1) << i;
		}

	for (int S = 0; S < (1 << m2); S ++)
		for (int i = 0; i < q; i ++) {
			bool ok = 1;
			for (int k = 0; k < m2; k ++)
				ok &= (s[i][m1 + k] == '?' or s[i][m1 + k] - '0' == (S >> k & 1));
			if (ok) g[S] |= ui(1) << i;
		}

	int ans = 0;

	if (n <= 5)
		for (int S = 0; S < (1 << m1); S ++)
			for (int T = 0; T < (1 << m2); T ++)
				ans += bool(f[S] & g[T]);

	else {
		for (int S = 0; S < (1 << m1); S ++) {
			int t0 = 0, t1 = 1, t2 = 2, t3 = 3, t4 = 4, t5 = 5, t6 = 6, t7 = 7,
				t8 = 8, t9 = 9, t10 = 10, t11 = 11, t12 = 12, t13 = 13, t14 = 14, t15 = 15;
			while (t15 < (1 << m2)) {
				if (f[S] & g[t0]) ++ ans; t0 += 16;
				if (f[S] & g[t1]) ++ ans; t1 += 16;
				if (f[S] & g[t2]) ++ ans; t2 += 16;
				if (f[S] & g[t3]) ++ ans; t3 += 16;
				if (f[S] & g[t4]) ++ ans; t4 += 16;
				if (f[S] & g[t5]) ++ ans; t5 += 16;
				if (f[S] & g[t6]) ++ ans; t6 += 16;
				if (f[S] & g[t7]) ++ ans; t7 += 16;
				if (f[S] & g[t8]) ++ ans; t8 += 16;
				if (f[S] & g[t9]) ++ ans; t9 += 16;
				if (f[S] & g[t10]) ++ ans; t10 += 16;
				if (f[S] & g[t11]) ++ ans; t11 += 16;
				if (f[S] & g[t12]) ++ ans; t12 += 16;
				if (f[S] & g[t13]) ++ ans; t13 += 16;
				if (f[S] & g[t14]) ++ ans; t14 += 16;
				if (f[S] & g[t15]) ++ ans; t15 += 16;
			}
		}
	}

	printf("%d\n", ans);
}
