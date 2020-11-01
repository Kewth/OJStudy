/*
 * Author: Kewth

 * Date:
  2020.11.01

 * Solution:
  可以发现 i, j 足够大时 a[i][j] = a[i - 1][j - 1] 总是成立的。

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
typedef std::pair<int, int> par;

static struct {
	inline operator short () { short x; return scanf("%hd", &x), x; }
	inline operator int () { int x; return scanf("%d", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
} read;

const int maxn = 500005;
short a1[maxn], a2[maxn], a3[maxn], a4[maxn], b1[maxn];
short c[maxn << 1];

short mex (short x, short y) {
	if (x and y) return 0;
	return x + y == 1 ? 2 : 1;
}

int main () {
	int n = read;
	for (int i = 1; i <= n; i ++) read(a1[i]);
	for (int i = 2; i <= n; i ++) read(b1[i]);
	b1[1] = a1[1];

	a2[1] = b1[2];
	a3[1] = b1[3];
	a4[1] = b1[4];
	for (int i = 2; i <= n; i ++) {
		a2[i] = mex(a2[i - 1], a1[i]);
		a3[i] = mex(a3[i - 1], a2[i]);
		a4[i] = mex(a4[i - 1], a3[i]);
	}

	ll ans[3] = {0, 0, 0};
	int now[3] = {0, 0, 0};

	if (n > 4) {
		short *C = c + n;
		for (int i = 2; i <= n; i ++)
			++ now[C[i] = a4[i]];
		/* debug("%d ", b1[3]); */
		/* for (int j = 2; j <= n; j ++) */
		/* 	debug("%d", C[j]); */
		/* debug("\n"); */
		for (int i = 5; i <= n; i ++) {
			-- C;
			-- now[C[n + 1]];
			C[2] = mex(b1[i], C[3]);
			++ now[C[2]];
			-- now[C[3]];
			C[3] = mex(C[2], C[4]);
			++ now[C[3]];
			-- now[C[4]];
			C[4] = mex(C[3], C[5]);
			++ now[C[4]];
			/* debug("%d ", b1[i]); */
			/* for (int j = 2; j <= n; j ++) */
			/* 	debug("%d", C[j]); */
			/* debug("\n"); */
			/* for (int j = 3; j <= n; j ++) */
			/* 	if (C[j] != mex(C[j - 1], C[j + 1])) */
			/* 		return 1; */
			ans[0] += now[0];
			ans[1] += now[1];
			ans[2] += now[2];
		}
	}

	for (int i = 1; i <= n; i ++)
		++ ans[b1[i]];
	for (int i = 2; i <= n; i ++) {
		ans[a1[i]] += (n >= 1);
		ans[a2[i]] += (n >= 2);
		ans[a3[i]] += (n >= 3);
		ans[a4[i]] += (n >= 4);
	}
	printf("%lld %lld %lld\n", ans[0], ans[1], ans[2]);
}
