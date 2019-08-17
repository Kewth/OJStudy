#if 0
2019.08.14

问题等价于求一个不包含给定点（在边界上不算）的矩形，最大化其周长。
由于点全是整点，首先答案至少是 max(W + 1, H + 1) * 2 。
然后可以发现要达到这个下界，矩形一定至少经过 W*H 范围矩形的两个直的对称轴之一。
那么现在只考虑经过 y = W / 2 的矩形，对于 x = H / 2 做法类似，先不管。

沿着 y = W / 2 这条中线从左向右扫，算出每个点向上向下最远能延伸到多远。
然后继续沿着这个方向维护一条扫描线，以这条扫描线作为矩形的右边算最优答案。
假设还知道左边，那么这个左右边界确定后可以贪心求出最优的上下边界，
对于之前的延伸距离上下分别取 min 即可。

但是枚举左边时间是不允许的，考虑贪心算的是什么，实际就是一段后缀最小值（以当前扫描线为最右边）。
那么要求出最优的左边界，就是把左右边界长度算上后对扫描线左边的所有点取 max 。
而随着扫描线的移动，每个点为左边界时的左右边界长都加上同一个值。
这些都很好用数据结构维护。

具体地，用单调栈维护后缀最小值，单调栈从左到右递增，
里面两个相邻点 x, y 满足 x ~ y 的最小值都是 y 。
那么扫描线移动时操作单调栈，会有一些点的后缀最小值改变，
而这些点对应若干段区间，用线段树区间加减即可实现修改。

注：线段树上每个叶子节点 x 的值维护的就是以 x 为左边界，扫描线为右边界的最大周长。
#endif
#include <cstdio>
#include <algorithm>
#include <stack>
#define debug(...) // fprintf(stderr, __VA_ARGS__)

inline int input() { int x; scanf("%d", &x); return x; }

struct Tree {
	int L, R;
	Tree *lt, *rt;
	int max, lazy;

	inline void update() {
		max = std::max(lt -> max, rt -> max);
	}

	inline void push_down() {
		lt -> max += lazy;
		lt -> lazy += lazy;
		rt -> max += lazy;
		rt -> lazy += lazy;
		lazy = 0;
	}

	void add(int l, int r, int x) {
		if(r < L or l > R)
			return;
		if(l <= L and R <= r) {
			max += x;
			lazy += x;
		} else {
			push_down();
			lt -> add(l, r, x);
			rt -> add(l, r, x);
			update();
		}
	}

	int query(int l, int r) {
		if(r < L or l > R)
			return 0;
		if(l <= L and R <= r)
			return max;
		push_down();
		return std::max(lt -> query(l, r), rt -> query(l, r));
	}

	Tree(int l, int r): L(l), R(r), max(0), lazy(0) {
		if(l == r)
			return;
		int mid = (l + r) >> 1;
		lt = new Tree(l, mid);
		rt = new Tree(mid + 1, r);
	}
};

struct Dot {
	int x, y;
};

const int maxn = 300005;
Dot dot[maxn];
int x[maxn], up[maxn], down[maxn];

inline bool cmp(Dot x, Dot y) {
	return x.x < y.x;
}

int solve(int n, int w, int h) {
	if(not n) return 0;
	for(int i = 1; i <= n; i ++)
		debug("%d, %d\n", dot[i].x, dot[i].y);

	int mid = h >> 1;
	int i = 1, p = 0;
	int res = 0;
	std::stack<int> stup, stdown;
	Tree T(1, n);

	stup.push(0);
	stdown.push(0);

	while(i <= n) {
		++ p;
		x[p] = dot[i].x;
		up[p] = h - mid;
		down[p] = mid;

		while(i <= n and dot[i].x == x[p]) {
			if(dot[i].y >= mid)
				up[p] = std::min(up[p], dot[i].y - mid);
			if(dot[i].y <= mid)
				down[p] = std::min(down[p], mid - dot[i].y);
			i ++;
		}

		while(up[stup.top()] > up[p]) {
			int tmp = stup.top();
			stup.pop();
			T.add(stup.top() + 1, tmp, up[p] - up[tmp]);
			debug("%d-%d add %d\n", stup.top() + 1, tmp, up[p] - up[tmp]);
		}

		while(down[stdown.top()] > down[p]) {
			int tmp = stdown.top();
			stdown.pop();
			T.add(stdown.top() + 1, tmp, down[p] - down[tmp]);
			debug("%d-%d add %d\n", stdown.top() + 1, tmp, down[p] - down[tmp]);
		}

		stup.push(p);
		stdown.push(p);
		T.add(p, p, w - x[p - 1] + up[p] + down[p]);
		debug("%d-%d add %d\n", p, p, w - x[p - 1] + up[p] + down[p]);
		res = std::max(res, T.query(1, p) - (w - dot[i].x));

		debug("%d: %d, %d ans=%d\n", x[p], up[p], down[p], T.query(1, p) - (w - dot[i].x));
	}

	return res;
}

int main() {
	int w = input(), h = input(), n = input(), ans = 0;

	for(int i = 1; i <= n; i ++) {
		dot[i].x = input();
		dot[i].y = input();
		if(dot[i].x == 0 or dot[i].x == w or dot[i].y == 0 or dot[i].y == h) {
			n --;
			i --;
		}
	}

	std::sort(dot + 1, dot + n + 1, cmp);
	dot[0].x = 0;
	dot[n + 1].x = w;
	for(int i = 1; i <= n + 1; i ++)
		ans = std::max(ans, h + dot[i].x - dot[i - 1].x);
	ans = std::max(ans, solve(n, w, h));

	for(int i = 1; i <= n; i ++)
		std::swap(dot[i].x, dot[i].y);

	std::sort(dot + 1, dot + n + 1, cmp);
	dot[0].x = 0;
	dot[n + 1].x = h;
	for(int i = 1; i <= n + 1; i ++)
		ans = std::max(ans, w + dot[i].x - dot[i - 1].x);
	ans = std::max(ans, solve(n, h, w));

	printf("%d\n", ans << 1);
}
