/*
 * Since g++10 is released, some characters is not valid inside #if 0 :(
 * So, why not using clang++? :D

 * Date:
  2020.06.09

 * Solution:
  李超线段树板子。

 * Digression:
  可惜第三次写李超树并没有一遍对，插入线段替换的时候位置写反了。

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
typedef double ld;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 400005;
ld K[maxn], B[maxn];
bool has[maxn];
#define ls (now << 1)
#define rs (now << 1 | 1)

void insert (int now, int L, int R, int l, int r, ld k, ld b) {
	if (r < L or l > R) return;
	int M = (L + R) >> 1;
	if (l <= L and R <= r) {
		if (!has[now])
			return K[now] = k, B[now] = b, has[now] = 1, void();
		if (k * M + b > K[now] * M + B[now]) {
			if (L < R)
				K[now] < k ? insert(ls, L, M, l, r, K[now], B[now]) :
					insert(rs, M + 1, R, l, r, K[now], B[now]);
			K[now] = k;
			B[now] = b;
		} else if (L < R)
			k < K[now] ? insert(ls, L, M, l, r, k, b) :
				insert(rs, M + 1, R, l, r, k, b);
		return;
	}
	insert(ls, L, M, l, r, k, b);
	insert(rs, M + 1, R, l, r, k, b);
}

ld ans;
void query (int now, int L, int R, int p) {
	if (has[now]) ans = std::max(ans, K[now] * p + B[now]);
	if (L == R) return;
	int M = (L + R) >> 1;
	if (p <= M) query(ls, L, M, p);
	else query(rs, M + 1, R, p);
}

int L = 0, R = 100000;
void insert () {
	int x1 = read, y1 = read;
	int x2 = read, y2 = read;
	if (x1 > x2) std::swap(x1, x2), std::swap(y1, y2);
	/* debug("%d %d\n", x1, x2); */
	if (x2 < L or x1 > R) return;
	if (x1 == x2)
		return insert(1, L, R, x1, x2, 0, std::max(y1, y2));
	ld k = ld(y2 - y1) / (x2 - x1);
	ld b = y1 - x1 * k;
	/* debug("%.2lf %.2lf\n", k, b); */
	insert(1, L, R, x1, x2, k, b);
}

int main () {
	int n = read, q = read;
	while (n --) insert();
	while (q --) {
		int o = read;
		if (o == 0) insert();
		if (o == 1) {
			ans = - 1e300;
			query(1, L, R, read);
			if (ans <= - 1e300 and ans >= - 1e300)
				puts("0.0000000");
			else
				printf("%.6lf\n", ans);
		}
	}
}
