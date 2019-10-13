#if 0
2019.10.12

数位 DP ，要求统计数对 (x, y) ，满足：
1) x ^ y = n
2) x <= a
3) y <= b
4) |x - y| <= m
对于 1) 直接在转移的时候就可以处理，对于 2) 3) 都很容易在数位 DP 中用状态表示，
麻烦的是限制 4) ，注意到 x, y 数位相同的部分对 |x - y| 没有影响，
而 x, y 第 k 位相同当且仅当 n 第 k 位为 0 ，那么只需考虑在 n 为 1 的位。
令 X = x & n, Y = y & n ，可知 X + Y = n 。
不妨令 X > Y ，那么对于 4) 就是要 X - Y <= m ，也就是 X - (n - X) <= m ，
也就是 X <= (m + n) / 2 ，换言之，(x, y) 的 max(x & n, y & n) 不能超过 (m + n) / 2 。
也就是 x & n 和 y & n 都不能超过 (m + n) / 2 ，这就很容易在数位 DP 的状态表示了。
#endif
#include <cstdio>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;

inline int input() { int x; scanf("%d", &x); return x; }
inline lolong linput() { lolong x; scanf("%lld", &x); return x; }

const int maxk = 62;
lolong f[maxk + 2][2][2][2][2];

int main() {
	int T = input();
	while(T --) {
		lolong a = linput(), b = linput(), n = linput(), m = (linput() + n) >> 1;
		for(int ia = 0; ia < 2; ia ++)
			for(int ib = 0; ib < 2; ib ++)
				for(int im = 0; im < 2; im ++)
					for(int jm = 0; jm < 2; jm ++)
						f[0][ia][ib][im][jm] = 1;

		/* for(int k = maxk - 1; k >= 0; k --) { */
		for(int k = 0; k < maxk; k ++) {
			for(int ia = 0; ia < 2; ia ++)
				for(int ib = 0; ib < 2; ib ++) {
					for(int im = 0; im < 2; im ++)
						for(int jm = 0; jm < 2; jm ++) {
							if(n >> k & 1) {
								f[k + 1][ia][ib][im][jm] =
									((!ib or b >> k & 1) and (!jm or m >> k & 1) ?
									 f[k][ia & !(a >> k & 1)][ib]
									 [im & !(m >> k & 1)][jm] : 0) +
									((!ia or a >> k & 1) and (!im or m >> k & 1) ?
									 f[k][ia][ib & !(b >> k & 1)]
									 [im][jm & !(m >> k & 1)] : 0);
							}

							else {
								f[k + 1][ia][ib][im][jm] =
									f[k][ia & !(a >> k & 1)][ib & !(b >> k & 1)]
									[im & !(m >> k & 1)][jm & !(m >> k & 1)] +
									((!ia or a >> k & 1) and (!ib or b >> k & 1) ?
									f[k][ia][ib]
									[im & !(m >> k & 1)][jm & !(m >> k & 1)] : 0);
							}
						}
				}
		}

		/* for(int k = 1; k <= maxk; k ++) */
		/* 	for(int ia = 0; ia < 2; ia ++) */
		/* 		for(int ib = 0; ib < 2; ib ++) */
		/* 			for(int im = 0; im < 2; im ++) */
		/* 				for(int jm = 0; jm < 2; jm ++) */
		/* 					if(f[0][ia][ib][im][jm]) */
		/* 						debug("f[%d][%d%d%d] = %lld\n", */
		/* 								k - 1, ia, ib, im, f[k][ia][ib][im][jm]); */

		printf("%lld\n", f[maxk][1][1][1][1]);
	}
}
