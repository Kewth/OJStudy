/*
 * Author: Kewth

 * Date:
  2020.07.20

 * Solution:
  要求能在最上方的直线，就是求个凸包，按套路直线求凸包转换为点求凸包即可。

 * Digression:

 * CopyRight:
          ▁▃▄▄▄▃▃▃▃▄▶
        ▗▇▀▔    ▔▔▔▔
       ▄▛   ▃▅━━■▄▂
      ▟▊   ▐▘     ▀▙
     ▟▜▌   ▐▖   ▋  ▐▍
    ▟▘ ▜   ▝▀▇▆●▘  ▐▌
  ▗▟▘   ▜▃       ▁▅▛
  ▔▀▼▅▄▃▃██▅▄▄▄▅■▀▔
        ▔▔▔▔▔▔
 */

#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

static struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
} read;

const int maxn = 10005;
struct point { int x, y, id; };
struct vector { int x, y; };
point p[maxn], s[maxn];
int ans[maxn], ap;

vector operator - (point a, point b) { return {a.x - b.x, a.y - b.y}; }
ll cross (vector a, vector b) { return 1ll * a.x * b.y - 1ll * b.x * a.y; }

int main () {
	int n = read;
	for (int i = 1; i <= n; i ++) p[i].id = i;
	for (int i = 1; i <= n; i ++) read(p[i].y);
	for (int i = 1; i <= n; i ++) read(p[i].x);
	std::sort(p + 1, p + n + 1, [] (point a, point b) {
				return a.x == b.x ? a.y < b.y : a.x < b.x;
			});
	int sp = 0;
	for (int i = 1; i <= n; i ++) {
		while (sp >= 2 and cross(s[sp] - s[sp - 1], p[i] - s[sp]) > 0) -- sp;
		s[++ sp] = p[i];
	}
	int x = 1;
	for (int i = 1; i <= sp; i ++) if (s[i].y > s[x].y) x = i;
	for (int i = x; i <= sp; i ++) ans[++ ap] = s[i].id;
	std::sort(ans + 1, ans + ap + 1);
	printf("%d\n", ap);
	for (int i = 1; i <= ap; i ++) printf("%d ", ans[i]);
	puts("");
}
