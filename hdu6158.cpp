#if 0
2020.05.27

  以两圆切点为反演中心，两圆的反形是两条平行直线，两圆内的小圆的反形是与两平行线相切的若干
全等圆。
  那么小圆的反形的各点坐标是很好求的，设小圆的圆心为 C ，C 与反演中心 O 的连线与该小圆交于
A, B 两点，与其反形交于 C, D 两点，那么 A, B 与 C, D 也互为反演，根据 C, D 可以求出 A, B ，
而线段 AB 的中点就是 C ，由于相邻小圆之间相切，根据相邻小圆的坐标就能求出小圆半径了。
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

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

struct point { double x, y; };
point operator * (point p, double a) { return {p.x * a, p.y * a}; }

double dis2 (point a, point b) {
	double x = a.x - b.x, y = a.y - b.y;
	return x * x + y * y;
	/* return std::sqrt(x * x + y * y); */
}

int main () {
	int T = read;
	double pi = std::acos(-1);

	while (T --) {
		int r1 = read, r2 = read, n = read;
		if (r1 > r2) std::swap(r1, r2);
		double h1 = 2 * r1 * r1 / double(r2);
		double h2 = 2 * r1;
		double dr = (h2 - h1) / 2;

		auto inv = [r1] (point p) {
			double coe = 4 * r1 * r1 / dis2(p, {0, 0});
			p.x *= coe;
			p.y *= coe;
			return p;
		};

		point las = {0, double(r1 + r2)};
		double las_r = r2 - r1;
		double sum = las_r * las_r;
		for (int i = 2; i <= n; i += 2) {
			point up = {i * dr, h1 + dr};
			double di = std::sqrt(dis2(up, {0, 0}));
			point p1 = inv(up * ((di - dr) / di));
			point p2 = inv(up * ((di + dr) / di));
			point now = point({p1.x + p2.x, p1.y + p2.y}) * 0.5;
			double r = std::sqrt(dis2(now, las)) - las_r;
			double area = r * r;
			sum += area;
			if (i + 1 <= n)
				sum += area;
			if (area < 1e-13) break;
			/* debug("%lf\n", r); */
			las = now;
			las_r = r;
		}

		printf("%.5lf\n", pi * sum);
	}
}
