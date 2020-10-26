/*
 * Author: Kewth

 * Date:
  2020.10.22

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
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

static struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator () (a...); }
} read;

const int maxn = 500005;
struct point {
	int x, y;
} lp[maxn], rp[maxn];

int sort (point *p, int n, int typ) {
	std::sort(p + 1, p + n + 1, [] (point a, point b) {
				return a.x == b.x ? a.y < b.y : a.x < b.x;
			});
	int sp = 0;
	for (int i = 1; i <= n; i ++) {
		point P = p[i];
		if (typ == 0) {
			if (!sp or P.y < p[sp].y)
				p[++ sp] = P;
		}
		if (typ == 1) {
			while (sp and P.y > p[sp].y)
				-- sp;
			p[++ sp] = P;
		}
	}
	return sp;
}

ll ans;
void solve (int l, int r, int L, int R) {
	if (l > r or L > R) return;
	/* debug("%d %d | %d %d\n", l, r, L, R); */
	ll max = 0;
	int m = (l + r) >> 1, M = 0;
	point P = rp[m];
	for (int i = L; i <= R; i ++)
		if (lp[i].x <= P.x and lp[i].y <= P.y) {
			ll now = 1ll * (P.x - lp[i].x) * (P.y - lp[i].y);
			if (now >= max)
				max = now, M = i;
		}
	ans = std::max(ans, max);
	if (M) {
		solve(l, m - 1, L, M);
		solve(m + 1, r, M, R);
		return;
	}
	int i = L;
	while (i <= R and lp[i].x <= P.x) ++ i;
	solve(l, m - 1, L, i - 1);
	solve(m + 1, r, i, R);
}

int main () {
	int m = read, n = read;
	for (int i = 1; i <= m; i ++)
		read(lp[i].x, lp[i].y);
	for (int i = 1; i <= n; i ++)
		read(rp[i].x, rp[i].y);
	m = sort(lp, m, 0);
	n = sort(rp, n, 1);
	/* for (int i = 1; i <= m; i ++) */
	/* 	debug("%d %d\n", lp[i].x, lp[i].y); */
	/* debug("---\n"); */
	/* for (int i = 1; i <= n; i ++) */
	/* 	debug("%d %d\n", rp[i].x, rp[i].y); */
	solve(1, n, 1, m);
	printf("%lld\n", ans);
}
