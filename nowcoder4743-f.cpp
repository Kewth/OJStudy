#if 0
2020.03.13

首先每个果子可以看作二维平面上的一个点，
纵坐标是捡到它的时刻，横坐标是它的位置。
那么初始松鼠在 x 轴任意一个位置，每次松鼠可以从 (x, y) 到三个点之一：
(x, y - 1), (x, y), (x, y + 1)
要求最大化其经过的点的点权和。

假设松鼠到了一个关键点 (x0, y0) ，那么其下一个能到的关键点 (x1, y1) 需要满足：
y1 - y0 >= |x0 - x1|
这样的 (x1, y1) 构成的半平面是以 (x0, y0) 引出的两条射线组成的。
不难发现，只要将坐标轴旋转 45 度，这个半平面就可以看作了一个固定端点的矩形。
换言之，从点 A 能到达点 B 可以当且仅当 A, B 的左边满足二维偏序的关系。

那么问题就是找到一个权值和最大的偏序集。
用排序干掉一维后，就是找到一个权值和最大的 LIS 。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
} read;

const int maxn = 100005;
int tpos[maxn], thei[maxn];
struct Two {
	int x, y, z;
} a[maxn];
int tmp[maxn];
ll bit[maxn];

ll query(int p) {
	ll res = 0;
	for(int k = p; k; k -= k & -k)
		res = std::max(res, bit[k]);
	return res;
}

void modify(int p, ll x) {
	for(int k = p; k < maxn; k += k & -k)
		bit[k] = std::max(bit[k], x);
}

int main() {
	int n = read, m = read;
	for(int i = 1; i <= m; i ++)
		tpos[i] = read;
	for(int i = 1; i <= m; i ++)
		thei[i] = read;

	for(int i = 1; i <= n; i ++) {
		int t = read, p = read, c = read;
		int x = tpos[p];
		int y = thei[p] + t;
		a[i] = {x - y, - x - y, c};
	}

	std::sort(a + 1, a + n + 1, [](Two A, Two B) {
				return A.x == B.x ? A.y < B.y : A.x < B.x;
			});

	for(int i = 1; i <= n; i ++)
		tmp[i] = a[i].y;
	std::sort(tmp + 1, tmp + n + 1);

	for(int i = 1; i <= n; i ++) {
		int x = int(std::lower_bound(tmp + 1, tmp + n + 1, a[i].y) - tmp);
		modify(x, query(x) + a[i].z);
	}

	printf("%lld\n", query(n));
}
