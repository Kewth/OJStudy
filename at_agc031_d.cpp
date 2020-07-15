/*
 * Since g++10 is released, some characters is not valid inside #if 0 :(
 * So, why not using clang++? :D

 * Date:
  2020.07.15

 * Solution:
  不拿发现把排列看成置换，有 a[i] = inv(a[i - 2]) a[i - 1] 。
  根据这个递推式，不难得出 a[1] a[4] = a[2] a[5] = a[3] a[6] = ... = r 。
  另外也可以得出 a[i] = inv(r) a[i - 6] r ，那么把这个递推式不断迭代，计算 r 的快速幂
以及 6 以内的 a 即可算出任意 a[n] 。

 * Digression:

 * CopyRight:
          ▁▃▄▄▄▃▃▃▃▄▶
        ▗▇▀▔    ▔▔▔▔
       ▄▛   ▃▅━━■▄▂
      ▟▊   ▐▘     ▀▙
     ▟▜▌   ▐▖   ▋  ▐▍
    ▟▘ ▜   ▝▀▇▆●▘  ▐▌
  ▗▟▘   ▜▃       ▁▅▛
  ▔▀▼▅▄▃▃██▅▄▄▄▅■▀▔
        ▔▔▔▔▔▔
 */

#include <cstdio>
#include <string>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct _{
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
} read;

const int maxn = 100000;
struct P {
	int x[maxn + 5];
};

int N;
P operator * (const P &a, const P &b) {
	P c;
	for (int i = 1; i <= N; i ++)
		c.x[i] = b.x[a.x[i]];
	return c;
}

P inv (const P &a) {
	P b;
	for (int i = 1; i <= N; i ++)
		b.x[a.x[i]] = i;
	return b;
}

P a[10], r, tmp;

int main () {
	N = read;
	int M = read;
	for (int i = 1; i <= N; i ++)
		a[1].x[i] = read;
	for (int i = 1; i <= N; i ++)
		a[2].x[i] = read;
	for (int i = 1; i <= N; i ++)
		r.x[i] = i;

	for (int i = 3; i <= 7; i ++)
		a[i] = inv(a[i - 2]) * a[i - 1];

	int Mx = (M - 2) / 6, My = M - Mx * 6;
	tmp = a[1] * a[4];

	for (int k = Mx; k; k >>= 1) {
		if (k & 1) r = r * tmp;
		tmp = tmp * tmp;
	}

	tmp = inv(r) * a[My] * r;

	for (int i = 1; i <= N; i ++)
		printf("%d ", tmp.x[i]);
	puts("");
}
