#if 0
2019.10.26

考虑每个点 A ，如果一条直线 l 与 A 的距离不超过 d ，
那么 l 一定与以 A 为圆心 d 为半径的圆有交。
也就是做出每个点的圆，问题转换为找出一条直线与最多的圆产生交点。
这个问题仍然难以处理，考虑对于最优的直线 l 进行移动，使得每个交点不变，
直到 l 与一个圆相切，这样的是一定可以做到的，也就是说存在最优的直线 l 与一个圆相切。
枚举这个被切的圆 A ，然后考虑其不同的切线，再枚举其它所有圆 B ，
切线经过圆 B 时对应一个范围，倾斜角的范围，
具体来说可以找到两个区间 [l1, r1], [l2, r2] ，
满足当且仅当 l 的倾斜角在两个区间之一时与圆 B 有交。
那么算出每个 B 对应的这个区间，极角排序后就可以很好处理圆 A 的答案了。
#endif
#include <cstdio>
#include <algorithm>
#include <cmath>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;

inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 2020;
const double eps = 1e-8;
int x[maxn], y[maxn];

inline double dis(int dx, int dy) {
	return sqrt(dx * dx + dy * dy);
}

double mark[maxn << 3];
int typ[maxn << 3];
int po[maxn << 3];
int tp;
void add(double l, double r) {
	if(l <= -eps) {
		l += M_PI * 2;
		r += M_PI * 2;
	}
	if(r >= M_PI * 2 + eps) {
		add(l, M_PI * 2);
		add(0, r - M_PI * 2);
		return;
	}
	mark[++ tp] = l;
	typ[tp] = 1;
	po[tp] = tp;
	mark[++ tp] = r + eps;
	typ[tp] = -1;
	po[tp] = tp;
}

bool cmp(int a, int b) {
	return mark[a] < mark[b];
}

int n, d;
int calc(int p) {
	tp = 0;
	for(int i = 1; i <= n; i ++)
		if(i != p) {
			/* debug("%d -> %d\n", i, p); */
			int dx = x[i] - x[p], dy = y[i] - y[p];
			double a = atan2(dy, dx);

			if(dis(dx, dy) >= d + eps) {
				double da = asin(d / dis(dx, dy));
				/* debug("%lf %lf\n", a, a + da + eps); */
				add(a, a + da + eps);
				/* debug("%lf %lf\n", a + M_PI - da, a + M_PI + eps); */
				add(a + M_PI - da, a + M_PI + eps);
			}

			else
				/* debug("%lf %lf\n", a, a + M_PI), */
				add(a, a + M_PI);
		}

	std::sort(po + 1, po + tp + 1, cmp);

	int now = 1, res = 0;
	for(int i = 1; i <= tp; i ++) {
		now += typ[po[i]];
		res = std::max(res, now);
		/* debug("%lf(%lf): %d\n", mark[po[i]], mark[po[i]] - M_PI * 2, now); */
	}

	/* debug("  get ans %d\n\n", res); */

	return res;
}

int main() {
	n = input(), d = input() << 1;

	if(n == 1) {
		puts("1");
	}

	else {
		for(int i = 1; i <= n; i ++) {
			x[i] = input();
			y[i] = input();
		}

		int ans = 0;
		for(int i = 1; i <= n; i ++)
			ans = std::max(ans, calc(i));

		printf("%d\n", ans);
	}
}
