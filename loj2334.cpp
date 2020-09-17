/*
 * Author: Kewth

 * Date:
  2020.09.15

 * Solution:

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

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator () (a...); }
} read;

const int maxn = 2020;
int a[maxn][maxn];
int p[maxn];
int min = 1000000000, max = 0;

bool check_1 (int n, int m, int d) {
	int Min = 1000000000, Max = 0;
	p[0] = m;
	for (int i = 1; i <= n; i ++) {
		int j = 0;
		while (j + 1 <= p[i - 1] and a[i][j + 1] <= min + d)
			++ j;
		p[i] = j;
		for (++ j; j <= m; j ++) {
			Min = std::min(Min, a[i][j]);
			Max = std::max(Max, a[i][j]);
		}
	}
	return Max - Min <= d;
}

inline void swapn (int n, int m) {
	for (int i = 1; i < n - i + 1; i ++)
		for (int j = 1; j <= m; j ++)
			std::swap(a[i][j], a[n - i + 1][j]);
}

inline void swapm (int n, int m) {
	for (int i = 1; i <= n; i ++)
		for (int j = 1; j < m - j + 1; j ++)
			std::swap(a[i][j], a[i][m - j + 1]);
}

bool check_2 (int n, int m, int d) {
	swapn(n, m);
	int res = check_1(n, m, d);
	swapn(n, m);
	return res;
}

bool check_3 (int n, int m, int d) {
	swapm(n, m);
	int res = check_1(n, m, d);
	swapm(n, m);
	return res;
}

bool check_4 (int n, int m, int d) {
	swapn(n, m);
	swapm(n, m);
	int res = check_1(n, m, d);
	swapn(n, m);
	swapm(n, m);
	return res;
}

int main () {
	int n = read, m = read;
	for (int i = 1; i <= n; i ++)
		for (int j = 1; j <= m; j ++) {
			read(a[i][j]);
			min = std::min(min, a[i][j]);
			max = std::max(max, a[i][j]);
		}
	int l = 0, r = max - min;
	while (l < r) {
		int mid = (l + r) >> 1;
		if (check_1(n, m, mid) or check_2(n, m, mid) or
				check_3(n, m, mid) or check_4(n, m, mid))
			r = mid;
		else
			l = mid + 1;
	}
	printf("%d\n", l);
}
