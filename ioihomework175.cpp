/*
 * Author: Kewth

 * Date:
  2020.11.14

 * Solution:
  In blog.

 * Digression:

 * CopyRight:
   __  __                  __   __
  |  |/  |.-----.--.--.--.|  |_|  |--.
  |     < |  -__|  |  |  ||   _|     |
  |__|\__||_____|________||____|__|__|

 */

#include <cstdio>
#include <cmath>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

static struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator double () { double x; return scanf("%lf", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
} read;

const int maxw = 505;
double R[maxw][maxw];
bool has[maxw][maxw];

int main () {
	int n = read;
	for (int i = 1; i <= n; i ++) {
		int x = read, y = read;
		has[x][y] = 1;
		read(R[x][y]);
	}

	int q = read;
	while (q --) {
		int x1 = read, y1 = read, x2 = read, y2 = read, ans = 0;
		if (x1 == x2) {
			if (y1 > y2) std::swap(y1, y2);
			for (int y = y1; y <= y2; y ++)
				ans += has[x1][y];
		} else {
			if (x1 > x2) std::swap(x1, x2), std::swap(y1, y2);
			int dx = x2 - x1, dy = y2 - y1;
			double h = std::sqrt(dx * dx + dy * dy) / dx, k = 1.0 * dy / dx;
			double A = k, B = -1, C = y1 - k * x1, tmp = std::sqrt(A * A + B * B);
			int ymax = std::max(y1, y2), ymin = std::min(y1, y2);
			for (int x = x1; x <= x2; x ++) {
				double Y = y1 + k * (x - x1);
				for (int y = std::min(ymax, int(Y + h)); y >= Y - h and y >= ymin; y --)
					ans += has[x][y] and std::abs(A * x + B * y + C) < R[x][y] * tmp;
			}
		}
		printf("%d\n", ans);
	}
}
