#if 0
2020.05.26

  以原点为反演中心，那么一个点在圆内可以转换为一个点在半平面内，这题比较特殊，事实上就是
在一条直线下方。进一步的，可以把给定的圆转换为点，询问的点转换为一条直线，询问是否所有给
定的点都在询问的直线下方。
  cdq 分治，把左边的点建凸包，对于右边的询问在凸包上二分到对应的位置即可。
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

const int maxn = 500005;
const double eps = double(1e-13);
int qo[maxn];
double qx[maxn], qy[maxn];
int ans[maxn];
point con[maxn], stack[maxn];

void cdq (int l, int r) {
	if (l == r) return;
	int mid = (l + r) >> 1;
	cdq(l, mid);
	cdq(mid + 1, r);

	bool find = 0;
	for (int i = mid + 1; i <= r; i ++)
		find |= qo[i] == 1 and ans[i] == 1;
	if (!find) return;

	int cp = 0;
	for (int i = l; i <= mid; i ++)
		if (qo[i] == 0)
			con[++ cp] = {qx[i], qy[i]};

	std::sort(con + 1, con + cp + 1, [] (point a, point b) {
				if (std::abs(a.x - b.x) <= eps) return a.y < b.y;
				return a.x < b.x;
			});

	int sp = 0;
	for (int i = 1; i <= cp; i ++) {
		while (sp > 1 and cross(stack[sp] - stack[sp - 1], con[i] - stack[sp]) >= -eps)
			-- sp;
		stack[++ sp] = con[i];
	}

	for (int i = mid + 1; i <= r; i ++)
		if (qo[i] == 1 and ans[i] == 1) {
			double k = qx[i], b = qy[i];
			int L = 1, R = sp;
			while (L < R) {
				int M = (L + R + 1) >> 1;
				if (cross(stack[M] - stack[M - 1], {1, k}) <= eps)
					L = M;
				else
					R = M - 1;
			}
			ans[i] &= stack[L].y <= k * stack[L].x + b + eps;
		}
}

int main () {
	int n = read;
	bool has = 0;
	for (int i = 1; i <= n; i ++) {
		int o = qo[i] = read;
		double a = read, b = read;
		if (o == 0) a *= 2, b *= 2;
		double d = a * a + b * b;
		a /= -d;
		b /= -d;
		/* debug("%lf %lf\n", a, b); */
		if (o == 0) {
			has = 1;
			qx[i] = a / -b;
			qy[i] = (a * a + b * b) / -b;
		}
		if (o == 1) {
			qx[i] = +a;
			qy[i] = -b;
			ans[i] = has;
		}
		/* debug("%lf %lf\n", qx[i], qy[i]); */
	}
	cdq(1, n);
	for (int i = 1; i <= n; i ++)
		if (qo[i] == 1)
			puts(ans[i] ? "Yes" : "No");
}
