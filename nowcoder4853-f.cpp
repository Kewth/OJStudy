#if 0
2020.03.27

对于在线段一侧的每个点 d ，求出夹角 dab 和 dba ，得到 d 的一个二元组 (dab, dba) 。
那么对于这一侧的所有点，可以发现 d1, d2 穿过线段，当且仅当它们的二元组满足二维偏序。
对于另一侧，把外角（即补角）最为二元组元素即可，问题就是求有多少偏序对。
#endif
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <set>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef long double ld;
typedef std::pair<ll, ll> par;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
} read;

const int maxn = 200005;
struct aplha {
	ll y, x;
};
bool operator < (aplha a, aplha b) {
	if (a.x == 0) return b.x < 0;
	if (b.x == 0) return a.x > 0;
	if ((a.x < 0) != (b.x < 0)) return (a.x < 0) < (b.x < 0);
	return __int128(a.y) * b.x < __int128(b.y) * a.x;
}
bool operator > (aplha a, aplha b) {
	return b < a;
}

struct shit {
	aplha a1, a2;
	int i2;
} shi[maxn];
/* par pr[maxn]; */

int bit[maxn];
void add (int p) {
	for (int k = p; k < maxn; k += k & -k)
		++ bit[k];
}
int sum (int p) {
	int res = 0;
	for (int k = p; k; k -= k & -k)
		res += bit[k];
	return res;
}

ll cross (ll x1, ll y1, ll x2, ll y2) {
	return x1 * y2 - x2 * y1;
}

ll dot (ll x1, ll y1, ll x2, ll y2) {
	return x1 * x2 + y1 * y2;
}

std::set<par> set;

int main () {
	int n = read;
	ll ax = read, ay = read, bx = read, by = read;
	/* ld pi = acosl(-1); */
	ll dx = ax - bx, dy = ay - by;
	for (int i = 1; i <= n; i ++) {
		ll x = read, y = read;
		if (set.count(par(x, y))) return 1;
		set.insert(par(x, y));
		ll dax = ax - x, day = ay - y;
		ll dbx = bx - x, dby = by - y;
		shi[i].a1 = {cross(dax, day, dx, dy), dot(dax, day, dx, dy)};
		shi[i].a2 = {cross(dbx, dby, -dx, -dy), - dot(dbx, dby, -dx, -dy)};
		/* ld a1 = + atan2l(day, dax) - atan2l(ay - by, ax - bx); */
		/* ld a2 = - atan2l(dby, dbx) + atan2l(by - ay, bx - ax); */
		/* while (a1 < 0) a1 += pi; */
		/* while (a2 < 0) a2 += pi; */
		/* while (a1 > pi) a1 -= pi; */
		/* while (a2 > pi) a2 -= pi; */
		/* debug("%.4Lf %.4Lf\n", a1, a2); */
		/* shi[i] = {a1, a2, 0}; */
		if (shi[i].a1.y < 0) shi[i].a1.y *= -1, shi[i].a1.x *= -1;
		if (shi[i].a2.y < 0) shi[i].a2.y *= -1, shi[i].a2.x *= -1;
	}

	std::sort(shi + 1, shi + n + 1, [] (shit x, shit y) {
				return x.a2 < y.a2;
			});
	for (int i = 1; i <= n; i ++)
		shi[i].i2 = i;

	std::sort(shi + 1, shi + n + 1, [] (shit x, shit y) {
				return x.a1 < y.a1;
			});

	ll ans = 0;
	for (int i = 1; i <= n; i ++) {
		ans += sum(shi[i].i2);
		add(shi[i].i2);
	}

	printf("%lld\n", ans);
}
