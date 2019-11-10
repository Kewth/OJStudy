#if 0
2019.11.09
#endif
#include <cstdio>
#include <cstring>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
} read;

const int maxn = 1000000;
char s[maxn];
int main() {
	ll n = read, a = read, b = read, r = read;

	ll ans = 0;
	for(int i = 1; i <= n; i ++) {
		ll x = read, y = read;
		if((a - x) * (a - x) + (b - y) * (b - y) <= r * r)
			ans ++;
	}

	printf("%lld\n", ans);
}
