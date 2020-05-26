#if 0
2020.05.26

  如果 P, Q 在圆外，不难发现，如果 PQ 与圆有交则最优的 D 就是任意一个交点，否则
最优的 D 就是 PQ 垂直平分线与圆的交点中较近的一个。
  如果 P, Q 在圆内，那么 P, Q 关于圆 C 的反演 A, B 一定在圆外，并且对于任意圆上
的点 D 有 |AD| / |PD| = |BD| / |QD| = K ，其中 K 为与 D 无关的定值。
        ▁▃▄▄▄▃▃▃▃▄▶
      ▗▇▀▔    ▔▔▔▔
     ▄▛   ▃▅━━■▄▂
    ▟▊   ▐▘     ▀▙
   ▟▜▌   ▐▖   ▋  ▐▍
  ▟▘ ▜   ▝▀▇▆●▘  ▐▌
▗▟▘   ▜▃       ▁▅▛
▔▀▼▅▄▃▃██▅▄▄▄▅■▀▔   CopyRight :)
      ▔▔▔▔▔▔
#endif
#include <cstdio>
#include <cmath>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef long double ld;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ld () { double x; return scanf("%lf", &x), ld(x); }
} read;

inline ld dis (ld x, ld y) { return std::sqrt(x * x + y * y); }

ld solve (ld r, ld x1, ld y1, ld x2, ld y2) {
	ld X = (x1 + x2) / 2, Y = (y1 + y2) / 2;
	ld D = dis(X, Y);
	if (dis(X, Y) <= r) return dis(x1 - x2, y1 - y2);
	X *= r / D;
	Y *= r / D;
	return dis(X - x1, Y - y1) * 2;
}

int main () {
	int q = read;
	while (q --) {
		ld r = read;
		ld x1 = read, y1 = read;
		ld x2 = read, y2 = read;
		ld d = dis(x1, y1);
		if (d <= 0)
			printf("%.10Lf\n", r * 2);
		else {
			if (d > r + 1e-6L) return 1;
			ld c = r * r / d / d;
			printf("%.10Lf\n", solve(r, x1 * c, y1 * c, x2 * c, y2 * c) / r * d);
		}
	}
}
