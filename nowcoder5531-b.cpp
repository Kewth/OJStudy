#if 0
2020.05.08

  数学题，分类讨论算面积。
#endif
#include <cstdio>
#include <cmath>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef long double ld;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

int main () {
	int h = read, l = read, H = read, L = read;
	ld d = ld(l) * H / L;
	if (d < h)
		printf("%.10Lf\n", h * l - d * l / 2);
	else {
		ld a = ld(h) * L / H;
		printf("%.10Lf\n", a * h / 2);
	}
}
