/*
 * Author: Kewth

 * Date:
  2020.10.13

 * Solution:
 * 问题转换，贪心

  不妨假设 n, m 都是偶数（如果是奇数那么中间的一行或列可以独立）。

  可以发现可以把格子染色，每种颜色恰好四个格子，满足任意翻转操作后颜色矩阵不变。

  不妨假设每个数字在正确的颜色位置上。考虑每个颜色内的四个点，可以发现如果这些点构成
偶排列那么就总可以在不影响其他颜色的前提下把这四个点排好序，如果是奇排列则总是不能。
称每个颜色的左上角的点为代表点，把颜色的排列奇偶性作为标记放到代表点上，对于代表点标
记构成的 01 矩阵 A ，如果 A 是全 0 矩阵自然是有解的。

  而每次翻转对 A 的影响就是讲某一行或某一列的 01 给全部反转，因此只要能通过这个操作
把 A 弄成 01 矩阵就能得到解，这就是个很 simple 的贪心了。

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

const int maxn = 105, maxa = 100000;
int a[maxn][maxn], n, m;
bool b[maxn][maxn];
int ans[maxa], ap;

inline bool check (int i, int j) {
	return a[i][j] == (i - 1) * m + j;
}

inline void ndo (int i) {
	ans[++ ap] = i;
	for (int j1 = 1, j2 = m; j1 < j2; ++ j1, -- j2)
		b[i][j1] ^= 1, std::swap(a[i][j1], a[i][j2]);
}

inline void mdo (int j) {
	ans[++ ap] = -j;
	for (int i1 = 1, i2 = n; i1 < i2; ++ i1, -- i2)
		b[i1][j] ^= 1, std::swap(a[i1][j], a[i2][j]);
}

int main () {
	int T = read;
	while (T --) {
		ap = 0;
		read(m, n);
		for (int i = 1; i <= n; i ++)
			for (int j = 1; j <= m; j ++)
				read(a[i][j]);

		if (m & 1)
			for (int i1 = 1, i2 = n; i1 < i2; ++ i1, -- i2)
				if (!check(i1, (m + 1) >> 1))
					mdo((m + 1) >> 1);

		if (n & 1)
			for (int j1 = 1, j2 = m; j1 < j2; ++ j1, -- j2)
				if (!check((n + 1) >> 1, j1))
					ndo((n + 1) >> 1);

		for (int i1 = 1, i2 = n; i1 < i2; ++ i1, -- i2)
			for (int j1 = 1, j2 = m; j1 < j2; ++ j1, -- j2) {
				int x = a[i1][j1], y = a[i1][j2], z = a[i2][j1], k = a[i2][j2];
				int parity = (x > y) + (x > z) + (x > k) + (y > z) + (y > k) + (z > k);
				b[i1][j1] = parity & 1;
			}

		/* for (int i = 1; i <= n / 2; i ++) { */
		/* 	for (int j = 1; j <= m / 2; j ++) */
		/* 		debug("%d", b[i][j]); */
		/* 	debug("\n"); */
		/* } */
		/* debug("\n"); */

		for (int i = 1; i <= n / 2; i ++) {
			if (b[i][1]) ndo(i);
			for (int j = 2; j <= m / 2; j ++)
				if (b[i][j])
					mdo(j);
		}

		for (int i1 = 1, i2 = n; i1 < i2; ++ i1, -- i2) {
			for (int j1 = 1, j2 = m; j1 < j2; ++ j1, -- j2) {
				if (!check(i1, j1))
					mdo(j1), ndo(i1), mdo(j1), ndo(i1);
				if (!check(i1, j1))
					mdo(j1), ndo(i2), mdo(j1), ndo(i2);
				if (!check(i1, j1))
					mdo(j1), ndo(i2), mdo(j1), ndo(i2);
				if (!check(i2, j1))
					mdo(j2), ndo(i2), mdo(j2), ndo(i2);
				if (!check(i2, j1))
					mdo(j2), ndo(i2), mdo(j2), ndo(i2);
			}
		}

		bool ok = 1;
		for (int i = 1; i <= n; i ++)
			for (int j = 1; j <= m; j ++)
				ok &= check(i, j);

		if (ok) {
#ifdef GEN
			puts("POSSIBLE");
#else
			printf("POSSIBLE %d", ap);
			for (int i = 1; i <= ap; i ++)
				if (ans[i] > 0)
					printf(" R%d", ans[i]);
				else
					printf(" C%d", -ans[i]);
			puts("");
#endif
		} else
			puts("IMPOSSIBLE");
	}
}
