#if 0
2019.05.16

设 f[l][r] 表示 l-r 子区间中最后一个选 l 的方案，
g[l][r] 表示 l-r 子区间中最后一个选 r 的方案，
O(1) 转移。
初始状态 f[i][i] 和 g[i][i] 只能有一个是 1 否则会重。
#endif
#include <cstdio>

inline int input() {
	int x;
	scanf("%d", &x);
	return x;
}

const int maxn = 1010, mod = 19650827;
int h[maxn];
int f[maxn][maxn], g[maxn][maxn];

int main() {
	int n = input();
	for(int i = 1; i <= n; i ++)
		h[i] = input();
	for(int i = 1; i <= n; i ++)
		f[i][i] = 1;
	for(int len = 1; len < n; len ++) {
		for(int l = 1; l + len <= n; l ++) {
			int r = l + len;
			if(h[l] < h[l + 1])
				f[l][r] += f[l + 1][r];
			if(h[l] < h[r])
				f[l][r] += g[l + 1][r];
			if(h[r] > h[l])
				g[l][r] += f[l][r - 1];
			if(h[r] > h[r - 1])
				g[l][r] += g[l][r - 1];
			if(f[l][r] >= mod) f[l][r] -= mod;
			if(g[l][r] >= mod) g[l][r] -= mod;
		}
	}
	printf("%d\n", (f[1][n] + g[1][n]) % mod);
}
