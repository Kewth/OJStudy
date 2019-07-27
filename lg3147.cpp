#if 0
2019.07.27

普通 DP 设 g[i][j] = k ，k 表示 [i, j] 区间可以合并出的最大值。
状态 O(n^2) ，值最多 58 。
改为 f[i][k] = j 即可，状态 O(58n) ，值 O(n) 。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 262146, maxv = 58;
int f[maxn][maxv];

int main() {
	int n = input();
	for(int i = 1; i <= n; i ++)
		f[i][input()] = i;
	int ans = 0;
	for(int j = 1; j < maxv; j ++)
		for(int i = 1; i <= n; i ++) {
			if(not f[i][j] and f[i][j - 1])
				f[i][j] = f[f[i][j - 1] + 1][j - 1];
			if(f[i][j])
				// debug("%d,%d->%d\n", i, j, f[i][j]),
				ans = j;
		}
	printf("%d\n", ans);
}
