#if 0
2019.07.27

设 f[i] 表示前 i 个玩具的最小代价，转移需要 O(n) 枚举 j 。
可以斜率优化，而且斜率递增，用单调双端队列维护凸包，复杂度 O(n) 。
#endif
#include <cstdio>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;
inline int input() { int x; scanf("%d", &x); return x; }

struct Dot {
	lolong x, y;
};
const int maxn = 50005;
lolong s[maxn];
lolong f[maxn];
Dot q[maxn];

inline double K(Dot a, Dot b) {
	return (a.y - b.y) / (a.x - b.x);
}

int main() {
	int n = input(), L = input();
	for(int i = 1; i <= n; i ++)
		s[i] = s[i - 1] + input();
	for(int i = 1; i <= n; i ++)
		s[i] += i;
	int l = 1, r = 1;
	q[1].x = 0;
	q[1].y = 0;
	for(int i = 1; i <= n; i ++) {
		lolong k = 2 * (s[i] - L - 1);
		while(r > l and K(q[l], q[l + 1]) < k)
			l ++;
		f[i] = q[l].y - q[l].x * q[l].x + (k / 2 - q[l].x) * (k / 2 - q[l].x);
		debug("f[%d] = %lld, %d-%d, k=%lld\n", i, f[i], l, r, k);
		Dot d;
		d.x = s[i];
		d.y = f[i] + s[i] * s[i];
		while(r > l and K(q[r - 1], q[r]) > K(d, q[r]))
			r --;
		q[++ r] = d;
	}
	printf("%lld\n", f[n]);
}
