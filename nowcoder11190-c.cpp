/*
 * Author: Kewth

 * Date:
  2021.05.14

 * Solution:
  建 PAM ，对于每个回文子串 DP 出它作为 k-palindrome 的 k 的最大值。只需要维护
一个 half 表示跳 fail 跳到第一个长度不超过自己一半的串即可。

 * Digression:
  难度：3 / 12

 * CopyRight:
   __  __                  __   __
  |  |/  |.-----.--.--.--.|  |_|  |--.
  |     < |  -__|  |  |  ||   _|     |
  |__|\__||_____|________||____|__|__|

 */

#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

static struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
}
 read;

const int maxn = 200005, mod = 998244353, maxc = 26;
char s[maxn];
int pos[maxn], fail[maxn], hfa[maxn], len[maxn], ch[maxn][maxc], f[maxn], cp;
ll po[maxn];

int main () {
	po[0] = 1;
	for (int i = 1; i < maxn; i ++)
		po[i] = po[i - 1] * 2 % mod;

	int T = read;
	while (T --) {
		int n = read, m = read;
		scanf("%s", s + 1);
		ll ans = 0;

		hfa[1] = fail[1] = 0, len[1] = -1;
		hfa[2] = fail[2] = 1, len[2] = 0;
		cp = pos[0] = 2;
		for (int i = 1; i <= n; i ++) {
			int pre = pos[i - 1];
			while (fail[pre] and s[i - len[pre] - 1] != s[i])
				pre = fail[pre];
			int &now = ch[pre][s[i] - 'a'];
			if (!now) {
				now = ++ cp;
				len[now] = len[pre] + 2;
				int p = fail[pre];
				while (fail[p] and s[i - len[p] - 1] != s[i])
					p = fail[p];
				fail[now] = p ? ch[p][s[i] - 'a'] : 2;
				p = hfa[pre];
				while (fail[p] and len[p] * 2 + 4 > len[now])
					p = fail[p];
				while (fail[p] and s[i - len[p] - 1] != s[i])
					p = fail[p];
				hfa[now] = p ? ch[p][s[i] - 'a'] : 2;
				f[now] = len[hfa[now]] * 2 + 2 <= len[now] ? 1 : f[hfa[now]] + 1;
				if (f[now] <= m)
					ans += po[f[now] + 1] - 2;
				else
					ans += po[m + 1] - 2;
			}
			pos[i] = now;
		}

		printf("%lld\n", ans);
		for (int i = 1; i <= cp; i ++)
			for (int c = 0; c < maxc; c ++)
				ch[i][c] = 0;
	}
}
