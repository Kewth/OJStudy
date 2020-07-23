/*
 * Author: Kewth

 * Date:
  2020.07.22

 * Solution:
  广义 SAM 模板。

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
} read;

const int maxn = 1000005, maxc = 26;
int ch[maxn << 1][maxc], len[maxn << 1], fa[maxn << 1], cp = 1;
char s[maxn];

int insert (int pre, int x) {
	int now = ++ cp;
	len[now] = len[pre] + 1;
	while (pre and !ch[pre][x]) ch[pre][x] = now, pre = fa[pre];
	if (pre) {
		int preto = ch[pre][x];
		if (len[preto] == len[pre] + 1) fa[now] = preto;
		else {
			int sp = ++ cp;
			len[sp] = len[pre] + 1;
			fa[sp] = fa[preto];
			std::copy(ch[preto], ch[preto] + maxc, ch[sp]);
			while (pre and ch[pre][x] == preto) ch[pre][x] = sp, pre = fa[pre];
			fa[now] = fa[preto] = sp;
		}
	} else fa[now] = 1;
	return now;
}

int main () {
	int n = read;
	for (int i = 1; i <= n; i ++) {
		scanf("%s", s);
		int las = 1;
		for (char *t = s; *t; ++ t)
			las = insert(las, *t - 'a');
	}
	ll ans = 0;
	for (int i = 1; i <= cp; i ++)
		ans += len[i] - len[fa[i]];
	printf("%lld\n", ans);
}
