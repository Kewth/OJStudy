/*
 * Author: Kewth

 * Date:
  2020.08.11

 * Solution:

 * Digression:
  刷板题，用时 13min 。

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
typedef double ld;

inline bool z (ld x) { return x <= 0 and x >= 0; }
/* struct T { ld x, y; }; */
/* typedef T vector, point; */
struct vector { ld x, y; };
struct point { ld x, y; };
vector operator - (point a, point b) { return {a.x - b.x, a.y - b.y}; }
point operator + (point a, vector b) { return {a.x + b.x, a.y + b.y}; }
int from (vector a) { return a.x > 0 or (z(a.x) and a.y > 0); }
ld cross (vector a, vector b) { return a.x * b.y - a.y * b.x; }
vector operator * (vector a, ld b) { return {a.x * b, a.y * b}; }

static struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator point () { point a; return scanf("%lf %lf", &a.x, &a.y), a; }
} read;

struct line { point p; vector v; };
ld cross (line l, point p) { return cross(l.v, p - l.p); }
point inter (line a, line b) {
	return a.p + a.v * (cross(b, a.p) / cross(a.v, b.v));
}

const int maxn = 505;
line li[maxn], q[maxn];
point p[maxn];

int main () {
	int m = read, lp = 0, l = 1, r = 0;
	while (m --) {
		int k = read;
		point a = read, b = a;
		while (-- k) {
			point c = read;
			li[++ lp] = {c, b - c};
			b = c;
		}
		li[++ lp] = {a, b - a};
	}

	std::sort(li + 1, li + lp + 1, [] (line a, line b) {
				if (from(a.v) != from(b.v)) return from(a.v) > from(b.v);
				ld tmp = cross(a.v, b.v);
				if (z(tmp)) return cross(a, b.p) >= 0; // XXX: 这里第一次写反了
				return tmp <= 0;
			});

	for (int i = 1; i <= lp; i ++) {
		if (i > 1 and z(cross(li[i].v, li[i - 1].v))) continue;
		while (r > l and cross(li[i], p[r]) >= 0) -- r;
		while (r > l and cross(li[i], p[l + 1]) >= 0) ++ l;
		q[++ r] = li[i];
		if (r > l) p[r] = inter(q[r - 1], q[r]);
	}
	while (r > l and cross(q[l], p[r]) >= 0) -- r;
	p[l] = inter(q[r], q[l]);

	ld ans = 0;
	for (int i = l + 2; i <= r; i ++)
		ans += cross(p[i] - p[l], p[i - 1] - p[l]);
	printf("%.3lf\n", ans / 2);

	/* for (int i = l; i <= r; i ++) */
	/* 	debug("%lf %lf\n", p[i].x, p[i].y); */
}
