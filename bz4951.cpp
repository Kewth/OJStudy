#if 0
2019.07.25

首先对于工厂，如果有 i, j 满足 p[i] >= p[j], d[i] >= d[j], 那么 j 一定比 i 优。
删掉像 i 这样没用的点，剩余的点按 x 排序后 y 一定单调递减，商店同理。

考虑从左到右枚举工厂分别选商店，
若当前工厂 i 的最优商店为 j ，易得大于 i 的最优商店不大于 j 。
即决策具有单调性，可以据此分治决策。

具体地，令 solve(la, ra, lb, rb) 表示 [la, ra] 的工厂选 [lb, rb] 的商店的最优解。
求出 [la, ra] 中点 mid ，暴力在 [lb, rb] 求出 mid 的最优决策 trans，
那么 mid 的两边分为了两个子问题 solve(la, mid - 1, lb, trans) 和 solve(mid + 1, ra, trans, rb) 。
特别地，若 mid 没有商店可以选，那么二维平面上根据 mid 的位置同样可以将 [lb, rb] 划分为两个区间。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;
inline int input() { int x; scanf("%d", &x); return x; }

struct Dot {
	int x, y;
};

const int maxn = 500005;
Dot a[maxn], b[maxn];
Dot A[maxn], B[maxn];

bool inline cmp(Dot x, Dot y) {
	return x.x == y.x ? x.y < y.y : x.x < y.x;
}

lolong solve(int la, int ra, int lb, int rb) {
	if(la > ra or lb > rb) return 0;
	// debug("%d-%d %d-%d\n", la, ra, lb, rb);
	int mid = (la + ra) >> 1;
	int l = lb, r = rb;
	while(l <= rb and B[l].x <= A[mid].x)
		l ++;
	while(r >= lb and B[r].y <= A[mid].y)
		r --;
	if(l > r) return std::max(solve(la, mid - 1, l, rb), solve(mid + 1, ra, lb, r));
	int trans;
	lolong now = 0;
	for(int i = l; i <= r; i ++) {
		lolong x = 1ll * (B[i].x - A[mid].x) * (B[i].y - A[mid].y);
		if(x > now) {
			now = x;
			trans = i;
		}
	}
	return std::max(now, std::max(solve(la, mid - 1, trans, rb), solve(mid + 1, ra, lb, trans)));
}

int main() {
	int n = input(), m = input();
	for(int i = 1; i <= n; i ++) {
		a[i].x = input();
		a[i].y = input();
	}
	for(int i = 1; i <= m; i ++) {
		b[i].x = input();
		b[i].y = input();
	}
	std::sort(a + 1, a + n + 1, cmp);
	std::sort(b + 1, b + m + 1, cmp);
	int ap = 0, bp = 0;
	for(int i = n; i; i --) {
		while(ap > 0 and A[ap].y >= a[i].y)
			ap --;
		A[++ ap] = a[i];
	}
	for(int i = 1; i <= m; i ++) {
		while(bp > 0 and B[bp].y <= b[i].y)
			bp --;
		B[++ bp] = b[i];
	}
	// for(int i = 1; i <= ap; i ++)
		// debug("A %d, %d\n", A[i].x, A[i].y);
	// for(int i = 1; i <= bp; i ++)
		// debug("B %d, %d\n", B[i].x, B[i].y);
	printf("%lld\n", solve(1, ap, 1, bp));
}
