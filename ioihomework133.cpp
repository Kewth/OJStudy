/*
 * Author: Kewth

 * Date:
  2020.10.20

 * Solution:
  On blog.

 * Digression:

 * CopyRight:
   __  __                  __   __
  |  |/  |.-----.--.--.--.|  |_|  |--.
  |     < |  -__|  |  |  ||   _|     |
  |__|\__||_____|________||____|__|__|

 */

#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

static struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	/* inline operator ll () { ll x; return scanf("%lld", &x), x; } */
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator () (a...); }
} read;

const int maxn = 1000005, inf = 1000000000;
int x1[maxn], y1[maxn], z1[maxn];
int x2[maxn], y2[maxn], z2[maxn];

struct rectangle {
	int lx, rx, ly, ry;
} rec[maxn];
struct range {
	int y, l, r;
} xR[maxn], yR[maxn];

bool check2 (int rp, int p, range *R) {
	int left = inf, right = - inf, up = - inf, down = inf;
	for (int i = 1; i <= rp; i ++) {
		left = std::min(left, rec[i].rx);
		right = std::max(right, rec[i].lx);
		up = std::max(up, rec[i].ly);
		down = std::min(down, rec[i].ry);
	}
	for (int i = 1; i <= p; i ++)
		if (up > R[i].y or down < R[i].y or left < R[i].l or right > R[i].r)
			return 0;
	/* const int MAGIC = 834812492; */
	std::sort(rec + 1, rec + rp + 1, [] (rectangle a, rectangle b) {
				return a.rx < b.rx;
			});
	std::sort(R + 1, R + p + 1, [] (range a, range b) {
				return a.r < b.r;
			});
	for (int i = 1, j = 0, max = - inf; i <= p; i ++) {
		while (j + 1 <= rp and rec[j + 1].rx < R[i].r)
			max = std::max(max, rec[++ j].lx);
		if (max > R[i].l)
			return 0;
	}
	return 1;
}

bool check (int n) {
	int rp = 0, xp = 0, yp = 0;
	int zmin = inf, zmax = - inf;

	for (int i = 1; i <= n; i ++)
		if (z1[i] == z2[i]) {
			auto &r = rec[++ rp];
			r.lx = x1[i];
			r.rx = x2[i];
			r.ly = y1[i];
			r.ry = y2[i];
			/* if (r.lx > r.rx) std::swap(r.lx, r.rx); */
			/* if (r.ly > r.ry) std::swap(r.ly, r.ry); */
			zmin = std::min(zmin, z1[i]);
			zmax = std::max(zmax, z1[i]);
		}
	if (rp == 0 or rp == n) return 0;

	for (int i = 1; i <= n; i ++)
		if (z1[i] != z2[i]) {
			/* int lz = z1[i], rz = z2[i]; */
			/* if (lz > rz) std::swap(lz, rz); */
			/* if (zmin < lz or zmax > rz) */
			/* 	return 0; */
			if (zmin < z1[i] or zmax > z2[i])
				return 0;
			if (x1[i] == x2[i])
				yR[++ yp] = {x1[i], y1[i], y2[i]};
			if (y1[i] == y2[i])
				xR[++ xp] = {y1[i], x1[i], x2[i]};
		}

	if (!check2(rp, xp, xR)) return 0;
	for (int i = 1; i <= rp; i ++) {
		std::swap(rec[i].lx, rec[i].ly);
		std::swap(rec[i].rx, rec[i].ry);
	}
	bool res = check2(rp, yp, yR);
	for (int i = 1; i <= rp; i ++) {
		std::swap(rec[i].lx, rec[i].ly);
		std::swap(rec[i].rx, rec[i].ry);
	}
	return res;
}

inline void change (int n) {
	for (int i = 1; i <= n; i ++) {
		std::swap(x1[i], y1[i]);
		std::swap(x2[i], y2[i]);
		std::swap(z1[i], y1[i]);
		std::swap(z2[i], y2[i]);
	}
}

void print (int n) {
	for (int i = 1; i <= n; i ++)
		debug("%d %d %d, %d %d %d\n", x1[i], y1[i], z1[i], x2[i], y2[i], z2[i]);
}

int main () {
	int T = read;
	while (T --) {
		int n = read;
		for (int i = 1; i <= n; i ++) {
			read(x1[i], y1[i], z1[i], x2[i], y2[i], z2[i]);
			if (x1[i] > x2[i]) std::swap(x1[i], x2[i]);
			if (y1[i] > y2[i]) std::swap(y1[i], y2[i]);
			if (z1[i] > z2[i]) std::swap(z1[i], z2[i]);
		}
		if (check(n) or (change(n), check(n)) or (change(n), check(n)))
			/* print(n), */
			puts("YES");
		else
			puts("NO");
	}
}
