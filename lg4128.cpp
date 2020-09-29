/*
 * Since g++10 is released, some characters is not valid inside #if 0 :(
 * So, why not using clang++? :D

 * Date:
  2020.09.18

 * Solution:
  套用 burnside 引理，考虑对于一个点集的置换如何求不动点。注意到虽然置换的数量很多，但是
由于每个点没有本质区别，许多置换是本质相同的，事实上两个置换对应的轮换大小完全相同，这两
个置换的不动点数量就一定相同，因此搜所有划分求不动点即可。
  现在对于一个置换求不动点，由于要计数的对象是边，而置换的对象是点，不能直接套用 polya ，
考虑求出对应的边置换的轮换数再套用 polya 。对于一条边两个端点在原置换的同一个轮换和不同
轮换分别讨论，枚举每个轮换的贡献和每对轮换的贡献即可，这里略去。

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

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
} read;

const int maxn = 65;
int mod;
int a[maxn];
ll po[maxn * maxn];
ll fac[maxn], ifac[maxn];

inline ll power (ll x, int k) {
	if (k < 0) k += mod - 1;
	ll res = 1;
	while (k) {
		if (k & 1) (res *= x) %= mod;
		(x *= x) %= mod;
		k >>= 1;
	}
	return res;
}

ll ans;
void force (int s, int n, int m) {
	if (s == n) {
		ll x = 0;
		for (int i = 1; i <= m; i ++)
			x += a[i] >> 1;
		for (int i = 1; i <= m; i ++)
			for (int j = i + 1; j <= m; j ++)
				x += std::__gcd(a[i], a[j]);
		x = po[x];
		for (int i = 1, las = 0; i <= m; i ++) {
			(x *= ifac[a[i]]) %= mod;
			(x *= fac[a[i] - 1]) %= mod;
			if (i == m or a[i] != a[i + 1]) {
				(x *= ifac[i - las]) %= mod;
				las = i;
			}
		}
		ans += x;
		/* for (int i = 1; i <= m; i ++) */
		/* 	debug(" %d", a[i]); */
		/* debug(" -> %d\n", x * fac[n] % mod); */
		return;
	}
	for (int x = m ? a[m] : 1; s + x <= n; x ++) {
		a[m + 1] = x;
		force(s + x, n, m + 1);
	}
}

int main () {
	int n = read, m = read;
	read(mod);

	po[0] = 1;
	for (int i = 1; i <= n * n; i ++) po[i] = po[i - 1] * m % mod;

	fac[0] = 1;
	for (int i = 1; i <= n; i ++) fac[i] = fac[i - 1] * i % mod;
	ifac[n] = power(fac[n], -1);
	for (int i = n; i; i --) ifac[i - 1] = ifac[i] * i % mod;

	force(0, n, 0);

	printf("%lld\n", ans % mod);
}
