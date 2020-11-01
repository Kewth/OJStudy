/*
 * Author: Kewth

 * Date:
  2020.11.01

 * Solution:

 * Digression:

 * CopyRight:
   __  __                  __   __
  |  |/  |.-----.--.--.--.|  |_|  |--.
  |     < |  -__|  |  |  ||   _|     |
  |__|\__||_____|________||____|__|__|

 */

#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

static struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int mod = 998244353;
ll s (ll n) {
	return n * (n + 1) / 2 % mod;
}

int main () {
	int a = read, b = read, c = read;
	printf("%lld\n", s(a) * s(b) % mod * s(c) % mod);
}
