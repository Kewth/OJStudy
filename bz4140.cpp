#if 0
2020.05.26

  以原点为反演中心，那么一个点在圆内可以转换为一个点在半平面内，这题比较特殊，事实上就是
在一条直线下方。进一步的，可以把给定的圆转换为点，询问的点转换为一条直线，询问是否所有给
定的点都在询问的直线下方。
  二进制分组，每组维护一个凸包，对于询问在凸包上二分到对应的位置即可。
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
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator double () { double x; return scanf("%lf", &x), x; }
} read;

struct T { double x, y; };
using point = T;
using vector = T;

vector operator - (point a, point b) { return {a.x - b.x, a.y - b.y}; }

double cross (vector a, vector b) { return a.x * b.y - a.y * b.x; }

const int maxn = 500005, maxk = 20;
const double eps = double(1e-13);

struct Group {
	point con[maxn], stack[maxn];
	int cp, sp;
	void build () {
		std::sort(con + 1, con + cp + 1, [] (point a, point b) {
					if (std::abs(a.x - b.x) <= eps) return a.y < b.y;
					return a.x < b.x;
				});
		sp = 0;
		for (int i = 1; i <= cp; i ++) {
			while (sp > 1 and cross(stack[sp] - stack[sp - 1], con[i] - stack[sp]) >= -eps)
				-- sp;
			stack[++ sp] = con[i];
		}
	}
	bool query (double k, double b) {
		int L = 1, R = sp;
		while (L < R) {
			int M = (L + R + 1) >> 1;
			if (cross(stack[M] - stack[M - 1], {1, k}) <= eps)
				L = M;
			else
				R = M - 1;
		}
		return stack[L].y <= k * stack[L].x + b + eps;
	}
};

Group g[maxk];

int main () {
	int q = read;
	bool has = 0;
	int tot = 0;
	while (q --) {
		int o = read;
		double a = read, b = read;
		a += tot, b += tot;
		if (o == 0) a *= 2, b *= 2;
		double d = a * a + b * b;
		a /= -d;
		b /= -d;
		/* debug("%lf %lf\n", a, b); */
		if (o == 0) {
			has = 1;
			int K = 0;
			while (g[K].cp) ++ K;
			g[K].con[++ g[K].cp] = {a / -b, (a * a + b * b) / -b};
			for (int k = 0; k < K; k ++) {
				for (int i = 1; i <= g[k].sp; i ++)
					g[K].con[++ g[K].cp] = g[k].stack[i];
				g[k].cp = 0;
			}
			g[K].build();
		}
		if (o == 1) {
			bool ans = has;
			for (int k = 0; k < maxk and ans; k ++)
				if (g[k].cp)
					ans &= g[k].query(a, -b);
			puts(ans ? "Yes" : "No");
			tot += ans;
		}
	}
}
