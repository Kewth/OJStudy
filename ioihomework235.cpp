/*
 * Author: Kewth

 * Date:
  2020.10.15

 * Solution:
 * 问题简化，排序双指针

  首先可以发现割两条对角线总是一个合法解，也就是说我们只需要判断是否能仅用一条线割掉所有
线段。

  把门展开成一个数轴，电线看做一个区间，那么目标是选两个点满足它们的所在的区间的集合的不
交并恰好是全集。把区间排个序，枚举一个点在最左边的区间的每个位置并求出分别能到达哪些区间，
然后枚举另一个点在最右边的区间的每个位置并检查下补集是否在上个点被处理过了。

  需要注意的是要保证两个点不在同一边，可以特判掉会出现在同一边的情况。

 * Digression:

 * CopyRight:
   __  __                  __   __
  |  |/  |.-----.--.--.--.|  |_|  |--.
  |     < |  -__|  |  |  ||   _|     |
  |__|\__||_____|________||____|__|__|

 */

#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

static struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	/* inline operator ll () { ll x; return scanf("%lld", &x), x; } */
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator () (a...); }
} read;

const int maxn = 1000005;
int W, H;
struct interval {
	int l, r;
} in[maxn], st[maxn];
int tmp[maxn << 1], tp, sp;
int ban[maxn << 1];
int get[maxn << 1];
int side_1, side_2, side_3, side_4;

int getpos () {
	int x = read, y = read;
	if (x == 0) return ++ side_1, y;
	if (y == H) return ++ side_2, H + x;
	if (x == W) return ++ side_3, H + W + (H - y);
	if (y == 0) return ++ side_4, H + W + H + (W - x);
	debug("ERROR\n");
	return -1;
}

void getxy (double p, double &x, double &y) {
	if (p < H) return x = 0, y = p, void(); p -= H;
	if (p < W) return x = p, y = H, void(); p -= W;
	if (p < H) return x = W, y = H - p, void(); p -= H;
	if (p < W) return x = W - p, y = 0, void(); p -= W;
	debug("ERROR\n");
	return x = y = p, void();
}

void answer (int a, int b) {
	double x1, y1, x2, y2;
	getxy(tmp[a] + 0.5, x1, y1);
	getxy(tmp[b] + 0.5, x2, y2);
	printf("1\n%lf %lf %lf %lf\n", x1, y1, x2, y2);
}

int main () {
	int n = read;
	read(W, H);
	for (int i = 1; i <= n; i ++) {
		tmp[++ tp] = in[i].l = getpos();
		tmp[++ tp] = in[i].r = getpos();
		if (in[i].l > in[i].r) std::swap(in[i].l, in[i].r);
	}

	if (side_1 == n)
		return printf("1\n0.5 0 0.5 %d\n", H), 0;
	if (side_2 == n)
		return printf("1\n0 %d.5 %d %d.5\n", H - 1, W, H - 1), 0;
	if (side_3 == n)
		return printf("1\n%d.5 0 %d.5 %d\n", W - 1, W - 1, H), 0;
	if (side_4 == n)
		return printf("1\n0 0.5 %d 0.5\n", W), 0;

	std::sort(tmp + 1, tmp + tp + 1);
	tp = int(std::unique(tmp + 1, tmp + tp + 1) - tmp - 1);

	for (int i = 1; i <= n; i ++) {
		in[i].l = int(std::lower_bound(tmp + 1, tmp + tp + 1, in[i].l) - tmp);
		in[i].r = int(std::lower_bound(tmp + 1, tmp + tp + 1, in[i].r) - tmp);
	}
	std::sort(in + 1, in + n + 1, [] (interval a, interval b) {
				return a.l < b.l;
			});

	for (int i = 1; i <= n; i ++) {
		while (sp and in[i].r < st[sp].r) {
			++ ban[st[sp].l];
			-- ban[in[i].l];
			++ ban[in[i].r];
			-- ban[st[sp].r];
			-- sp;
		}
		st[++ sp] = in[i];
	}

	for (int i = 1; i <= tp; i ++)
		ban[i] += ban[i - 1];

	for (int i = st[1].l, j = 1; i <= st[1].r - 1; i ++) {
		while (j + 1 <= tp and st[j + 1].l <= i) ++ j;
		if (!ban[i]) get[j] = i;
	}
	if (get[tp]) return answer(0, get[tp]), 0;

	for (int i = st[sp].r - 1, j = sp; i >= st[sp].l; i --) {
		while (j - 1 >= 1 and i <= st[j - 1].r - 1) -- j;
		if (!ban[i] and get[j - 1])
			return answer(get[j - 1], i), 0;
	}

	puts("2");
	printf("0 0.5 %d %d.5\n", W, H - 1);
	printf("0.5 %d %d.5 0\n", H, W - 1);
}
