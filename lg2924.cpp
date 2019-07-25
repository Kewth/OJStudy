#if 0
date +%Y.%m.%d

从凸包最上边的点逆时针跑，所经过的边极角递增。
将所有的边按极角排序，然后枚举每个点作为凸包的最上边的点求一个最大凸包。
那么所经过的边一定是按顺序来的，考虑从小到大加入边，那么新加的边一定作为当前的末尾边。
设 f[i] 表示以点 i 为结尾的最大路径，可以每加一条边 O(1) 维护。
#endif
#include <cstdio>
#include <algorithm>
#include <cmath>
#define debug(...) fprintf(stderr, __VA_ARGS__)

inline int input() { int x; scanf("%d", &x); return x; }

struct Edge {
	int from, to;
	double a;
};
const int maxn = 255;
Edge e[maxn * maxn];
int x[maxn], y[maxn];
int f[maxn];

inline bool cmp(Edge a, Edge b) {
	return a.a < b.a;
}

int main() {
	int n = input();
	for(int i = 0; i < n; i ++) {
		x[i] = input();
		y[i] = input();
	}
	int ep = 0;
	for(int i = 0; i < n; i ++)
		for(int j = 0; j < n; j ++)
			if(i != j) {
				e[ep].from = i;
				e[ep].to = j;
				e[ep].a = atan2(y[j] - y[i], x[j] - x[i]);
				ep ++;
			}
	std::sort(e, e + ep, cmp);
	// for(int j = 0; j < ep; j ++)
		// debug("%d->%d\n", e[j].from, e[j].to);
	int ans = 0;
	for(int i = 0; i < n; i ++) {
		for(int j = 0; j < n; j ++)
			f[j] = - n;
		f[i] = 0;
		for(int j = 0; j < ep; j ++)
			// debug("%d->%d(%d->%d)\n", e[j].from, e[j].to, f[e[j].from], f[e[j].to]),
			f[e[j].to] = std::max(f[e[j].to], f[e[j].from] + 1);
		// debug("f[%d] = %d\n", i, f[i]);
		ans = std::max(ans, f[i]);
	}
	printf("%d\n", ans);
}
