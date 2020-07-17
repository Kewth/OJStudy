/*
 * Since g++10 is released, some characters is not valid inside #if 0 :(
 * So, why not using clang++? :D

 * Date:
  2020.07.17

 * Solution:
  不难发现 D 最小的数就是重心，把它作为根。
  把所有点按 D 降序，一个个考虑其父亲节点，并维护每个点的 size 即可。

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
typedef std::pair<ll, int> par;

struct _ {
    inline operator int () { int x; return scanf("%d", &x), x; }
    inline operator ll () { ll x; return scanf("%lld", &x), x; }
} read;

const int maxn = 100005;
par p[maxn];
int fa[maxn], size[maxn], dis[maxn];

int main () {
	int n = read;
	if (n < 7) return puts("-1"), 0;

	for (int i = 1; i <= n; i ++) p[i] = par(read, i);
	std::sort(p + 1, p + n + 1);

	for (int i = 1; i <= n; i ++) size[i] = 1;

	for (int i = n; i > 1; i --) {
		int u = p[i].second;
		ll x = p[i].first - n + size[u] * 2;
		int j = int(std::lower_bound(p + 1, p + n + 1, par(x, 0)) - p);
		if (j > n or p[j].first != x) return puts("-1"), 0;
		fa[u] = p[j].second;
		size[fa[u]] += size[u];
	}

	ll test = 0;
	for (int i = 2; i <= n; i ++) {
		int u = p[i].second;
		dis[u] = dis[fa[u]] + 1;
		test += dis[u];
	}

	if (test != p[1].first) return puts("-1"), 0;

	for (int u = 1; u <= n; u ++)
		if (fa[u])
			printf("%d %d\n", fa[u], u);
}
