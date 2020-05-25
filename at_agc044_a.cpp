#if 0
2020.05.24

  考虑从 N 操作到 0 ，如果需要用到倍乘 k 的操作，那么操作一定形如：
    x -> x +/- 1 -> ... -> ky -> y
  事实上 y 一定取在 x / k 的下取整或者上取整，否则操作一定不优。据此可以 DP ，设 f(n) 表示
答案，转移枚举 k 以及两种科能的 y 即可。
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
#include <map>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator () (a...); }
} read;

const ll inf = 1000000000000000000;
std::map<ll, ll> f;
ll a, b, c, d;

ll dp (ll n) {
	if (f.count(n)) return f[n];
	return f[n] = std::min({
			n <= inf / d ? n * d : inf,
			dp(n / 2) + (n % 2) * d + a,
			dp(n / 2 + 1) + (2 - n % 2) * d + a,
			dp(n / 3) + (n % 3) * d + b,
			dp(n / 3 + 1) + (3 - n % 3) * d + b,
			dp(n / 5) + (n % 5) * d + c,
			dp(n / 5 + 1) + (5 - n % 5) * d + c,
			});
}

int main () {
	int q = read;
	while (q --) {
		ll n = read;
		read(a, b, c, d);
		f.clear();
		f[0] = 0;
		f[1] = d;
		f[2] = std::min(d + a, d + d);
		printf("%lld\n", dp(n));
		/* for (int i = 1; i <= 12; i ++) */
		/* 	debug("%lld\n", dp(i)); */
	}
}
