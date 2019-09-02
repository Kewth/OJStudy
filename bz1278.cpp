#if 0
2019.09.02

首先有两个需要感性理解的结论：
1) 选择的向量的极角是连续的，不存在一个未选的向量夹在选了的向量中间。
2) 选择的向量一定在一条直线的一侧。

那么把向量按极角排序，然后复制一遍成环，于是选择的向量一定是长度不超过 n 的连续区间。
枚举左端点，最远右端点是可以尺取的，而且只需要考虑尺取中更新的向量和。
因为每次左端点 l 右移，相当与添了一条与 V[l] 相反的向量，
由结论 1) 可知最优解的右端点不会再往左移。
#endif
#include <cstdio>
#include <algorithm>
#include <cmath>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;

inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 100005;

struct Dot {
	int x, y;
	double a;
};

Dot d[maxn << 1];

inline bool cmp(Dot a, Dot b) {
	return a.a < b.a;
}

int main() {
	int n = input();

	for(int i = 1; i <= n; i ++) {
		d[i].x = input();
		d[i].y = input();
		d[i].a = atan2(d[i].y, d[i].x) + M_PI;
	}

	std::sort(d + 1, d + n + 1, cmp);

	for(int i = 1; i <= n; i ++) {
		d[i + n] = d[i];
		d[i + n].a += M_PI * 2;
	}

	lolong ans = 0;
	int x = 0, y = 0;

	for(int l = 1, r = 0; l <= n; l ++) {
		while(r + 1 < l + n and d[r + 1].a < d[l].a + M_PI) {
			r ++;
			x += d[r].x;
			y += d[r].y;
			ans = std::max(ans, 1ll * x * x + 1ll * y * y);
		}
		x -= d[l].x;
		y -= d[l].y;
		ans = std::max(ans, 1ll * x * x + 1ll * y * y);
	}

    printf("%lld.000\n", ans);
}
