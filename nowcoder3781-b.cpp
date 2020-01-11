#if 0
2020.01.10
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
	{ x = *this; this -> operator ()(a...); }
} read;

int main() {
	int T = read;
	while(T --) {
		int hp1 = read, hp2 = read, at1 = read, at2 = read, m = read;
		if(at1 >= hp2) {
			puts("Yes");
			continue;
		}
		int t = (hp1 - 1) / at2;
		ll fuck = 1ll * t * (at1 - m) + at1;
		if(fuck >= hp2)
			puts("Yes");
		else
			puts("No");
	}
}
