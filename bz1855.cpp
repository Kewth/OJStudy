#if 0
2019.07.29

DP 设 f[i][j] 表示前 i 天，最后剩下 j 个股票的最大收益。
转移是求两个区间的最大值，可以用滑动窗口的技巧做到均摊 O(1) 转移。
#endif
#include <cstdio>
#include <algorithm>
#include <climits>
#define debug(...) fprintf(stderr, __VA_ARGS__)

inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 2020;
int f[maxn][maxn];
int g[maxn];
int q[maxn];

int main() {
	int n = input(), m = input(), w = input();
	for(int j = 1; j <= m; j ++)
		f[0][j] = INT_MIN >> 1;
	for(int i = 1; i <= n; i ++) {
		int a = input(), b = input(), amax = input(), bmax = input();
		for(int j = 0; j <= m; j ++)
			f[i][j] = f[i - 1][j];
		int k = std::max(i - w - 1, 0);
		for(int j = 0; j <= m; j ++)
			g[j] = f[k][j] + j * a;
		int l = 1, r = 0;
		for(int j = 1; j <= m; j ++) {
			while(l <= r and g[j - 1] > q[r])
				r --;
			q[++ r] = g[j - 1];
			if(j - amax - 1 >= 0 and g[j - amax - 1] == q[l])
				l ++;
			f[i][j] = std::max(f[i][j], q[l] - j * a);
		}
		for(int j = 0; j <= m; j ++)
			g[j] = f[k][j] + j * b;
		l = 1, r = 0;
		for(int j = m - 1; j >= 0; j --) {
			while(l <= r and g[j + 1] > q[r])
				r --;
			q[++ r] = g[j + 1];
			if(j + bmax + 1 <= m and g[j + bmax + 1] == q[l])
				l ++;
			f[i][j] = std::max(f[i][j], q[l] - j * b);
		}
		// for(int j = 0; j <= m; j ++)
			// debug(" %d", f[i][j]);
		// debug("\n");
	}
	printf("%d\n", f[n][0]);
}
