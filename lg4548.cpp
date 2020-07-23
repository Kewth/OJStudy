/*
 * Author: Kewth

 * Date:
  2020.07.22

 * Solution:
 * PGF 的应用，KMP

  设 X 表示歌唱时间，其 PGF 为 F(x) ，f[i] = P(X = i) ，要求的 E(X) 就是 F'(1) 。

  设 g[i] 表示时间为 i 时仍未结束的概率，其 OGF 为 G(x) 。

  不难得到：1 - g[i] = sum(f[j] [j <= i]) 。由此可以推导出 G(x) - x G(x) = 1 - F(x) 。
两边求导，代入 x = 1 ，有 F'(1) = G(1) 。

  另外考虑如果时间为 i 时仍未结束，在歌唱一个完整的序列后一定会结束，但结束时间不一定
恰好为 i + m ，可能在 i + 1 到 i + m 之间，可以发现能在 i + j 恰好结束当且仅当 j 是序
列的一个 border 。

  于是可以得到 G(x) (x/n)^m = sum(F(x) [i 是 border] (x/n)^{m-i}) ，代入 x = 1 可以得
到 G(1) = sum(F(1) [i 是 border] n^i) ，注意到 F(1) = 1 ，用 KMP 求出 border 即可。

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
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

static struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
} read;

const int maxn = 100005, mod = 10000;
int a[maxn], fail[maxn];
int po[maxn];

int main () {
	int n = read, T = read;
	po[0] = 1;
	for (int i = 1; i <= 100000; i ++)
		po[i] = po[i - 1] * n % mod;
	while (T --) {
		int m = read;
		for (int i = 1; i <= m; i ++) read(a[i]);
		fail[0] = -1;
		for (int i = 1; i < m; i ++) {
			int j = fail[i];
			while (~j and a[j + 1] != a[i + 1]) j = fail[j];
			fail[i + 1] = j + 1;
		}
		int ans = 0;
		for (int i = m; i; i = fail[i])
			ans += po[i];
		printf("%04d\n", ans % mod);
	}
}
