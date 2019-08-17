#if 0
2019.07.26

假设有一个跨环，那么两个最大区间和等于总和减去两个最小区间和。
把序列全变为相反数就可以用求最大区间和的方法求最小区间和。
考虑线性求两个最大区间和。
设 f[i], g[i] 表示以 i 为终点，起点的最大区间和，可以 DP 出来，
枚举把两个区间和隔开的分界线，再在两边求 f, g 的最大值加起来就是该分割线的答案，
处理 f, g 的前缀后缀最大值即可。
注意特判直接选可能选空区间的情况。
#endif
#include <cstdio>
#include <algorithm>
#include <climits>
#define debug(...) fprintf(stderr, __VA_ARGS__)

inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 200005;
int a[maxn];
int f[maxn], g[maxn];

int get(int n) {
	f[1] = a[1];
	for(int i = 2; i <= n; i ++)
		f[i] = std::max(f[i - 1], 0) + a[i];
	for(int i = 2; i <= n; i ++)
		f[i] = std::max(f[i], f[i - 1]);
	g[n] = a[n];
	for(int i = n - 1; i; i --)
		g[i] = std::max(g[i + 1], 0) + a[i];
	for(int i = n - 1; i; i --)
		g[i] = std::max(g[i], g[i + 1]);
	int res = INT_MIN;
	for(int i = 1; i < n; i ++)
		res = std::max(res, f[i] + g[i + 1]);
	return res;
}

int main() {
	int n = input(), sum = 0, cnt = 0;
	for(int i = 1; i <= n; i ++) {
		sum += (a[i] = input());
		cnt += a[i] > 0;
	}
	if(cnt <= 1) {
		printf("%d\n", get(n));
		return 0;
	}
	int big = get(n);
	for(int i = 1; i <= n; i ++)
		a[i] *= -1;
	int small = get(n);
	printf("%d\n", std::max(big, sum + small));
}
