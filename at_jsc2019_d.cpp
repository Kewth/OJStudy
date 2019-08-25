#if 0
2019.08.24

要把原图划分成 k 个二分图，可以考虑用 k 个二分图去覆盖原图的边。
那么允许边重复，不会对结果有影响，此时用到的二分图一定是 n 点完全二分图。
那么枚举 a + b = n ，用分成 a, b 的二分图覆盖原图，那么两个集合间两两右边覆盖，
集合内部没有边覆盖，于是转换成 n = a 和 n = b 的子问题，
dp 处理这个问题并记录转移方向即可输出方案。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 505;
int f[maxn], g[maxn];
int a[maxn][maxn];

void get(int l, int r) {
	/* debug("get %d %d\n", l, r); */
	int n = r - l + 1;
	if(n <= 2) {
		a[l][r] = f[n];
		return;
	}
	int mid = l + g[n] - 1;
	get(l, mid);
	get(mid + 1, r);
	for(int i = l; i <= mid; i ++)
		for(int j = mid + 1; j <= r; j ++)
			a[i][j] = f[n];
}

int main() {
	int n = input();
	f[1] = f[2] = 1;
	for(int i = 3; i <= n; i ++) {
		f[i] = 1000000000;
		for(int j = 1; j < i; j ++) {
			int v = std::max(f[j], f[i - j]) + 1;
			if(v < f[i]) {
				f[i] = v;
				g[i] = j;
			}
		}
	}

	/* for(int i = 1; i <= n; i ++) */
	/* 	debug("%d %d\n", f[i], g[i]); */

	get(1, n);
	for(int i = 1; i < n; i ++) {
		for(int j = i + 1; j <= n; j ++)
			printf("%d ", a[i][j]);
		puts("");
	}
}
