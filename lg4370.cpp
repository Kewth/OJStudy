#if 0
2020.06.01

  注意到组合数每一列都是单调的，那么每一列一个个选，用堆维护当前最优的列即可，唯一的
问题在于堆中需要快速比较两个组合数的大小，没有想到什么优美的方案，一个一般般的做法是
把组合数取对数比较大小，只需要预处理每个阶乘的对数即可。
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
#include <cmath>
#include <cstdio>
#include <algorithm>
#include <queue>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef long double ld;
typedef std::pair<ld, int> par;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 1000005, mod = 1000000007;
ll fac[maxn], ifac[maxn];
ld lg[maxn];

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

inline ll C (int n, int m) {
	if (n < m) return 0;
	return fac[n] * ifac[m] % mod * ifac[n - m] % mod;
}

inline ld lC (int n, int m) {
	if (n < m) return -1; // NaN
	return lg[n] - lg[m] - lg[n - m];
}

void combinator_init (int n) {
	fac[0] = 1;
	for (int i = 1; i <= n; i ++)
		fac[i] = fac[i - 1] * i % mod;
	ifac[n] = power(fac[n], -1);
	for (int i = n; i; i --)
		ifac[i - 1] = ifac[i] * i % mod;
	for (int i = 1; i <= n; i ++)
		lg[i] = lg[i - 1] + std::log(ld(i));
}

int now[maxn];

int main () {
	int n = read, k = read;
	combinator_init(n);
	std::priority_queue<par> q;
	for (int i = 0; i <= n; i ++)
		q.push(par(lC(now[i] = n, i), i));

	ll ans = 0;
	while (k --) {
		int m = q.top().second;
		q.pop();
		/* debug("%d %d -> %lld %Lf\n", now[m], m, C(now[m], m), lC(now[m], m)); */
		ans += C(now[m] --, m);
		if (now[m] >= m)
			q.push(par(lC(now[m], m), m));
	}

	printf("%lld\n", ans % mod);
}
