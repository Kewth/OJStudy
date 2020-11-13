/*
 * Author: Kewth

 * Date:
  2020.11.12

 * Solution:
  In blog.

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
typedef unsigned long long ull;

static struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 10000, maxl = 3, B = 60;
struct num {
	ull x[maxl];
	inline bool get (int k) { return x[k / B] >> (k % B) & 1; }
	num (ull y = 0) { std::fill(x, x + maxl, 0); x[0] = y; }
};
num operator + (const num &a, const num &b) {
	num c;
	ull tmp = 0;
	for (int i = 0; i < maxl; i ++) {
		c.x[i] = a.x[i] + b.x[i] + tmp;
		tmp = c.x[i] >> B & 1;
		c.x[i] ^= tmp << B;
	}
	return c;
}
num mul10 (const num &a) {
	num b = a + a, c = b + b;
	return c + c + b;
}

num f[2][maxn];

int main () {
	int n = read, l = 0, p = 1, q = 0;
	for (num bas = 1; l < maxl * B; bas = mul10(bas)) {
		++ l, q = p, p = 0;
		int o = l & 1;
		for (int i = 1; i <= q; i ++)
			if (f[!o][i].get(l - 1) == 0)
				f[o][++ p] = f[!o][i];
		int t = p;
		for (int i = 1; i <= q; i ++) {
			f[o][++ p] = f[!o][i] + bas;
			if (f[o][p].get(l - 1) == 0)
				-- p;
		}
		/* for (int k = l - 1; k >= 0; k --) */
		/* 	debug("%d", bas.get(k)); */
		/* debug(" <<\n"); */
		/* for (int i = 1; i <= p; i ++) { */
		/* 	for (int k = l - 1; k >= 0; k --) */
		/* 		debug("%d", f[o][i].get(k)); */
		/* 	debug("\n"); */
		/* } */
		if (n <= p - t) {
			for (int k = l - 1; k >= 0; k --)
				printf("%d", f[o][t + n].get(k));
			break;
		}
		n -= p - t;
		/* debug("%d : %d\n", l, p); */
	}
}
