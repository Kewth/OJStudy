#if 0
2020.04.21

智障了，while 写成 if 调了一年。
#endif
#include <cstdio>
#include <algorithm>
#include <cmath>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator () (a...); }
} read;

inline bool eq (double x, double y) { return x <= y and x >= y; }

struct T { double x, y; };
using point = T;
using vector = T;
struct line { point p; vector v; };

vector operator - (point a, point b) { return {a.x - b.x, a.y - b.y}; }
vector operator + (vector a, vector b) { return {a.x + b.x, a.y + b.y}; }
T operator * (T a, double x) { return {a.x * x, a.y * x}; }

double cross (vector a, vector b) { return a.x * b.y - a.y * b.x; }
int place (T a) { return a.x > 0 or (a.x >= 0 and a.y > 0); }
double cross (line l, point p) { return cross(l.v, p - l.p); }

point inter (line a, line b) { return b.p + b.v * (cross(a, b.p) / cross(b.v, a.v)); }

const int maxn = 505;
line li[maxn], ql[maxn];
point qp[maxn];

void plane_intersection (int n, int &l, int &r) {
	std::sort(li + 1, li + n + 1, [] (line a, line b) {
				/* return atan2(a.v.y, a.v.x) > atan2(b.v.y, b.v.x); */
				if (place(a.v) != place(b.v)) return place(a.v) > place(b.v);
				if (eq(cross(a.v, b.v), 0))
					return cross(b, a.p) < 0;
				return cross(a.v, b.v) < 0;
			});
	l = 1, r = 0;
	for (int i = 1; i <= n; i ++) {
		while (r >= l and eq(cross(li[i].v, ql[r].v), 0) and
				place(li[i].v) == place(ql[r].v)) -- r;
		while (r > l and cross(li[i], qp[r]) <= 0) -- r;
		while (r > l and cross(li[i], qp[l + 1]) <= 0) ++ l;
		ql[++ r] = li[i];
		if (r > l) qp[r] = inter(ql[r], ql[r - 1]);
	}
	while (r > l and cross(ql[l], qp[r]) <= 0) -- r;
	qp[l] = inter(ql[l], ql[r]);
}

point po[maxn];
int main () {
	int n = read, p = 0;
	for (int i = 1; i <= n; i ++) {
		int m = read;
		for (int j = 1; j <= m; j ++)
			read(po[j].x, po[j].y);
		po[0] = po[m];
		for (int j = 1; j <= m; j ++)
			li[++ p] = {po[j - 1], po[j] - po[j - 1]};
	}
	int l, r;
	plane_intersection(p, l, r);
	if (l >= r - 1) return puts("0.000"), 0;
	double ans = cross(qp[l], qp[r]);
	for (int i = l + 1; i <= r; i ++)
		ans += cross(qp[i], qp[i - 1]);
	ans /= 2;
	printf("%.3lf\n", ans);
}
