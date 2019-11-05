#if 0
2019.11.05

刷新我对 excrt 的认知。
#endif
#include <cstdio>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
} read;

__int128 __tmp1, __tmp2;
__int128 exgcd(__int128 a, __int128 b, __int128 &x = __tmp1, __int128 &y = __tmp2) {
	if(!b) {
		x = 1;
		y = 0;
		return a;
	}
	__int128 x0, y0;
	__int128 res = exgcd(b, a % b, x0, y0);
	x = y0;
	y = x0 - a / b * y0;
	return res;
}

int main() {
	__int128 a = 0, m = 1;

	int n = read;
	while(n --) {
		ll M = read, A = read;
		__int128 x, y;
		__int128 g = exgcd(m, M, x, y);
		a += x * ((A - a) / g) * m;
		(m /= g) *= M;
		a %= m;
		if(a < 0) a += m;
	}

	printf("%lld\n", ll(a));
}
