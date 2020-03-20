#if 0
2020.03.13
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
} read;

int main() {
	int n = read;
	ll min = + 1000000000000000000;
	ll max = - 1000000000000000000;
	while(n --) {
		ll x = read, y = read;
		ll val = y * (x - y) * (x - y);
		min = std::min(min, val);
		max = std::max(max, val);
	}
	printf("%lld\n", max - min);
}

