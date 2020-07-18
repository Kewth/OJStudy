/*
 * Since g++10 is released, some characters is not valid inside #if 0 :(
 * So, why not using clang++? :D

 * Date:
  2020.07.18

 * Solution:
  一个朴素的想法是 2^n 枚举 S 的失配位置集合，如果这个集合确定，就能确定 T 的一段前缀，
和该前缀后面一个位置的字符集，而该位置后面的位置都是可以任意选的。
  如果把枚举换成搜索，减掉不合法的失配位置集合，你就会发现你过了。因为失配位置有相当强
的限制，初步测试了一下，S 越“乱”合法的失配集合就越多，但始终非常小，n = 2000 的时候失配
集合数量大概是个 1e4 的级别，可以稳健地通过。

 * Digression:
  并不会证明失配集合数量的上界。

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
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
    inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 2020, mod = 998244353;
char s[maxn], t[maxn];
int fail[maxn];
ll po[maxn];
ll ans;

ll power (ll x, int k) {
	if (k < 0) k += mod - 1;
	ll res = 1;
	while (k) {
		if (k & 1) (res *= x) %= mod;
		(x *= x) %= mod;
		k >>= 1;
	}
	return res;
}

void force (int i, int j, int tp, int ban, int n, int m) {
	if (i == n + 1) {
		int tot = 0;
		for (int c = 0; c < 5; c ++) tot += !(ban >> c & 1);
		t[tp + 1] = 0;
		// debug("%s %d%d\n", t + 1, ban >> 0 & 1, ban >> 1 & 1);
		ans += m == tp ? 1 : po[m - tp - 1] * tot;
		return;
	}

	int k = fail[j - 1];
	while (~k and t[k + 1] != s[i]) k = fail[k];
	++ k;
	int x = s[i] - 'a';

	if ((j == tp + 1 or s[i] != t[j]) and !k)
		force(i + 1, k + 1, tp, j == tp + 1 ? ban | (1 << x) : ban, n, m);

	if (j == tp + 1 or s[i] == t[j]) {
		if (j == tp + 1) {
			if (tp == m or ban >> x & 1) return;
			t[tp + 1] = s[i];
			fail[tp + 1] = k;
		}
		force(i + 1, j + 1, j == tp + 1 ? tp + 1 : tp, j == tp + 1 ? 0 : ban, n, m);
	}
}

int main () {
	int n = read, m = read;
	scanf("%s", s + 1);

	po[0] = 1;
	for (int i = 1; i <= m; i ++) po[i] = po[i - 1] * 5 % mod;

	fail[0] = -1;
	force(1, 1, 0, 0, n, m);
	ans %= mod;
	(ans *= power(po[m], -1)) %= mod;

	printf("%lld\n", ans);
}
