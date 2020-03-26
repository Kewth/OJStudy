#if 0
2020.03.25
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
} read;

int main () {
	ll n = read, a = read, b = read;
	if (a % 2 == b % 2) printf("%lld\n", std::abs(a - b) >> 1);
	else printf("%lld\n", std::min(
				std::abs(b - a - 1) / 2 + a,
				std::abs(b - a - 1) / 2 + (n - b + 1)));
}
