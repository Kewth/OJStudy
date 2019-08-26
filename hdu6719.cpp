#if 0
2019.08.25
#endif
#include <cstdio>
#include <iostream>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;
typedef __int128 Big;
inline lolong input() { lolong x; std::cin >> x; return x; }

const int maxk = 35, mod = 1000000007;
Big f[maxk];

int main() {
	int T = int(input());

	while(T --) {
		lolong n = input(), a = input(), b = input();

		f[0] = b;
		int l;
		for(l = 1; (1ll << l) <= n; l ++) {
			Big x = 1ll << l;
			f[l] = std::min(f[l - 1] * 7 + 18 * (x / 2) * (x / 2) * a,
					x * x * x * b + (x - 1) * x * x * a);
		}

		printf("%d\n", int(f[l - 1] % mod));
	}
}
