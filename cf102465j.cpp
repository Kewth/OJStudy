/*
 * Author: Kewth

 * Date:
  2020.08.03

 * Solution:
  To be updated after "Accept".

 * Digression:

 * CopyRight:
          ▁▃▄▄▄▃▃▃▃▄▶
        ▗▇▀▔    ▔▔▔▔
       ▄▛   ▃▅━━■▄▂
      ▟▊   ▐▘     ▀▙
     ▟▜▌   ▐▖   ▋  ▐▍
    ▟▘ ▜   ▝▀▇▆■▘  ▐▌
  ▗▟▘   ▜▃       ▁▅▛
  ▔▀▼▅▄▃▃██▅▄▄▄▅■▀▔
        ▔▔▔▔▔▔
 */

#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef unsigned long long ull;

static struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ull () { ull x; return scanf("%llu", &x), x; }
} read;

struct ele { ull x, i; };
struct Ele { ull x, i, j; };
Ele operator ^ (ele a, ele b) { return { a.x ^ b.x, a.i, b.i}; }
struct RAND {
	ull s[2], U, p;
	RAND (int n, ull se) {
		s[0] = se, s[1] = se ^ 0x7263d9bd8409f526;
		U = (1ull << n) - 1, p = 0;
	}
	ele operator () () {
		ull s0 = s[0];
		ull s1 = s[1];
		ull result = s0 + s1;
		s1 ^= s0;
		s[0] = ((s0 << 55) | (s0 >> 9)) ^ s1 ^ (s1 << 14);
		s[1] = (s1 << 36) | (s1 >> 28);
		return {result & U, ++ p};
	}
};

const int maxn = 1 << 16;
ele a[maxn], b[maxn], c[maxn], d[maxn];
Ele ab[maxn * 10], cd[maxn * 10];
int p1, p2;

bool check () {
	auto cmp = [&] (Ele x, Ele y) { return x.x < y.x; };
	std::sort(ab, ab + p1, cmp);
	std::sort(cd, cd + p2, cmp);
	for (int i = 0, j = 0; i < p1; i ++) {
		while (j < p2 and cd[j].x < ab[i].x) ++ j;
		if (j < p2 and ab[i].x == cd[j].x) {
			printf("%llu %llu %llu %llu\n", ab[i].i, ab[i].j, cd[j].i, cd[j].j);
			return 1;
		}
	}
	return 0;
}

int main () {
	const int n = read, k = n / 3, m = 1 << k;
	RAND A(n, read), B(n, read), C(n, read), D(n, read);
	const ull S = (1ull << k) - 1;
	auto cmp = [&] (ele x, ele y) { return (x.x & S) < (y.x & S); };

	while (!check()) {
		for (int i = 0; i < m; i ++) a[i] = A();
		for (int i = 0; i < m; i ++) b[i] = B();
		for (int i = 0; i < m; i ++) c[i] = C();
		for (int i = 0; i < m; i ++) d[i] = D();

		std::sort(a, a + m, cmp);
		std::sort(b, b + m, cmp);
		std::sort(c, c + m, cmp);
		std::sort(d, d + m, cmp);

		for (int i = 0, j = 0; i < m; i ++) {
			while (j < m and cmp(b[j], a[i])) ++ j;
			if (j < m and !cmp(a[i], b[j])) ab[p1 ++] = a[i] ^ b[j ++];
		}
		for (int i = 0, j = 0; i < m; i ++) {
			while (j < m and cmp(d[j], c[i])) ++ j;
			if (j < m and !cmp(c[i], d[j])) cd[p2 ++] = c[i] ^ d[j ++];
		}
	}
}
