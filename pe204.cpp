#pragma GCC optimize(3)
#if 0
2020.05.28

  朴素的暴力直接搜，不够优雅，考虑折半。把 k 以内的质数分为两个部分，对于两个部分分别
搜出所有合法的数，然后最终合法的数一定是两边的数的乘积，但要满足不超过 n 的限制，枚举
一边的元素，在另一边二分即可。
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
#include <vector>
#include <map>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef std::pair<ll, int> par;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
} read;

const int maxm = 105;
bool nop[maxm];
int prime[maxm], pp;
std::map<par, ll> f;

std::vector<ll> a, b;
void dfs (ll x, int i, int lim, ll n) {
	if (i > lim) return a.push_back(x);
	dfs(x, i + 1, lim, n);
	if (x <= n / prime[i])
		dfs(x * prime[i], i, lim, n);
}

int main () {
#ifdef PE
	ll n = 1000000000;
	int m = 100;
#else
	ll n = read;
	int m = read; // 1000000000 100
#endif

	for (int i = 2; i <= m; i ++)
		if (!nop[i]) {
			prime[++ pp] = i;
			for (int j = i + i; j <= m; j += i)
				nop[j] = 1;
		}

	if (pp <= 8) {
		dfs(1, 1, pp, n);
		printf("%lu\n", a.size());
	}

	else {
		dfs(1, 1, 8, n);
		std::swap(a, b);
		dfs(1, 9, pp, n);
		std::sort(b.begin(), b.end());
		/* debug("%lu\n", a.size()); */
		/* debug("%lu\n", b.size()); */

		ll ans = 0;
		for (ll x : a)
			ans += std::upper_bound(b.begin(), b.end(), n / x) - b.begin();
		printf("%lld\n", ans);
	}
}
