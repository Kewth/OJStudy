#if 0
2019.10.04

将移动 k 个数分成两步：先删掉 k 个数，再插入被删的 k 个数。
后面的插入可以贪心，对于每个数 x ，如果当前数列中存在 x 就放它旁边，混乱度不变，
否则放最旁边，混乱度 +1 。

考虑前面的部分，假设不用插入，
那么就可以 DP 设 f[i][j][x] 表示前 i 个数删掉 j 个后最后一个数是 x 的最小混乱度。
考虑到插入产生的影响，只与有多少数被删完了有关，而数的个数很少，可以直接状压，
设 f[i][j][x][S] 表示原来的意义下添加一个限制：当前值的集合为 S 。
这样在最后只需对每个没有出现在 S 的数算插入的贡献即可。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 105, maxv = 8;
int a[maxn];
int f[2][maxn][maxv + 1][1 << maxv];

inline int count(int x) {
	int res = 0;
	while(x) {
		res ++;
		x -= x & -x;
	}
	return res;
}

int main() {
	int T = 0;
	while(++ T) {
		int n = input(), m = input();
		if(!n and !m) return 0;

		int S = 0;
		for(int i = 1; i <= n; i ++) {
			a[i] = input() - 25;
			S |= 1 << a[i];
		}
		a[0] = maxv;

		for(int j = 0; j <= m; j ++)
			for(int x = 0; x <= maxv; x ++)
				for(int s = S; s >= 0; s --) {
					s &= S;
					f[0][j][x][s] = n + 1;
				}

		f[0][0][maxv][0] = 0;
		for(int i = 1; i <= n; i ++) {
			int o = i & 1;
			for(int j = 0; j <= m; j ++) {
				for(int x = 0; x <= maxv; x ++)
					for(int s = S; s >= 0; s --) {
						s &= S;
						f[o][j][x][s] = n + 1;
					}

				for(int x = 0; x <= maxv; x ++)
					for(int s = S; s >= 0; s --) {
						s &= S;
						f[o][j][a[i]][s | (1 << a[i])] =
							std::min(f[o][j][a[i]][s | (1 << a[i])],
									f[!o][j][x][s] + (a[i] != x));
					}

				if(j)
					for(int x = 0; x <= maxv; x ++)
						for(int s = S; s >= 0; s --) {
							s &= S;
							f[o][j][x][s] = std::min(f[o][j][x][s], f[!o][j - 1][x][s]);
						}

				/* debug("%d %d\n", i, j); */
				/* for(int x = 0; x <= maxv; x ++) */
				/* 	for(int s = S; s >= 0; s --) { */
				/* 		s &= S; */
				/* 		if(f[o][j][x][s] <= n) */
				/* 			debug("f[%d][%d][%d][%d] = %d\n", */
				/* 					i, j, x, s, f[o][j][x][s]); */
				/* 	} */
				/* debug("%d %d\n", i, j); */
			}
		}

		int ans = n + 1;
		for(int j = 0; j <= m; j ++)
			for(int x = 0; x <= maxv; x ++)
				for(int s = S; s >= 0; s --) {
					s &= S;
					ans = std::min(ans, f[n & 1][j][x][s] + count(S ^ s));
					/* debug("%d %d %d : %d\n", j, x, s, f[n & 1][j][x][s]); */
				}

		printf("Case %d: %d\n\n", T, ans);
	}
}
