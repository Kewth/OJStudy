#if 0
2020.03.25

不难发现如果 n 有两个不同的质因子，那么所有点都必须是同一个颜色。
否则质因子为 p ，就可以把点分为 p 段，答案就是 p 。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator () (a...); }
} read;

int main () {
	ll n = read, x = n, las = 1;
	for (ll d = 2; d * d <= x; d ++)
		if (x % d == 0) {
			debug("%lld\n", d);
			if (las > 1) return puts("1"), 0;
			las = d;
			while (x % d == 0)
				x /= d;
		}
	if (x > 1) {
		if (las > 1) return puts("1"), 0;
		las = x;
	}
	printf("%lld\n", las);
}
