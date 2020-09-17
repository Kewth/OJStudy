#if 0
2020.05.28

  考虑 f(x) = p(x^2 - x) ，不难发现 f 可以分为若干段 [2^k, 2^k) ，每段都是单调递减的，
那么暴力找到答案对应的段，然后在段内二分具体的位置即可。
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
#include <string>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef __int128 lll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
} read;

int s1[40], s2[40], s3[100];

void solve (ll a, ll b) {
	int k = 1;
	lll l = 2, r = 3;
	while (lll(b) * k >= a * (r - 1)) {
		l = r + 1;
		r = r << 1 | 1;
		++ k;
	}
	while (l < r) {
		lll mid = (l + r) >> 1;
		if (lll(b) * k >= a * (mid - 1))
			l = mid + 1;
		else
			r = mid;
	}

	int p1 = 0, p2 = 0;
	for (lll x = l; x; x /= 10)
		s1[p1 ++] = x % 10;
	for (lll x = l - 1; x; x /= 10)
		s2[p2 ++] = x % 10;

	std::fill(s3, s3 + 100, 0);
	for (int i = 0; i < p1; i ++)
		for (int j = 0; j < p2; j ++)
			s3[i + j] += s1[i] * s2[j];

	int p3 = p1 + p2 - 1;
	for (int i = 0; i < p3; i ++) {
		s3[i + 1] += s3[i] / 10;
		s3[i] %= 10;
		if (s3[p3]) ++ p3;
	}

	for (int i = p3 - 1; i >= 0; i --)
		putchar('0' + s3[i]);
	puts("");
}

int main () {
	int T = read;
	while (T --) {
		ll a = read, b = read;
		solve(a, b);
	}
}
