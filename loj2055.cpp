#if 0
2019.09.02

这种只有大小比较的，二分答案 x ，把小于 x 设为 0 ，其他为 1 ，
问题转换为求对 01 序列操作后指定位置的值。
模拟区间排序的过程，由于只有 01 ，发现就相当与区间赋值和区间求和，
拿线段树直接维护序列即可。

码完后没有任何改动直接交，居然过了。。。
#endif
#include <cstdio>
#define debug(...) fprintf(stderr, __VA_ARGS__)

inline int input() { int x; scanf("%d", &x); return x; }

struct Tree {
	Tree *lt, *rt;
	int val, lazy;

	inline void push_down(int L, int R) {
		if(lazy == -1)
			return;
		int mid = (L + R) >> 1;
		lt -> val = lazy * (mid - L + 1);
		rt -> val = lazy * (R - mid);
		lt -> lazy = rt -> lazy = lazy;
		lazy = -1;
	}

	inline void update() {
		val = lt -> val + rt -> val;
	}

	void modify(int L, int R, int l, int r, int x) {
		if(r < L or l > R)
			return;

		if(l <= L and R <= r) {
			val = x * (R - L + 1);
			lazy = x;
			return;
		}

		push_down(L, R);

		int mid = (L + R) >> 1;
		lt -> modify(L, mid, l, r, x);
		rt -> modify(mid + 1, R, l, r, x);

		update();
	}

	int query(int L, int R, int l, int r) {
		if(r < L or l > R)
			return 0;

		if(l <= L and R <= r)
			return val;

		push_down(L, R);

		int mid = (L + R) >> 1;
		return lt -> query(L, mid, l, r) + rt -> query(mid + 1, R, l, r);
	}

	Tree(int L, int R): val(0), lazy(-1) {
		if(L == R)
			return;

		int mid = (L + R) >> 1;
		lt = new Tree(L, mid);
		rt = new Tree(mid + 1, R);
	}
};

const int maxn = 100005;
int a[maxn];
int typ[maxn], ql[maxn], qr[maxn];

int main() {
	int n = input(), q = input();

	for(int i = 1; i <= n; i ++)
		a[i] = input();

	for(int i = 1; i <= q; i ++) {
		typ[i] = input();
		ql[i] = input();
		qr[i] = input();
	}

	Tree T(1, n);

	int p = input();

	int l = 1, r = 1000000000;
	while(l < r) {
		int mid = (l + r + 1) >> 1;

		T.modify(1, n, 1, n, 0);

		for(int i = 1; i <= n; i ++)
			if(a[i] >= mid)
				T.modify(1, n, i, i, 1);

		for(int i = 1; i <= q; i ++) {
			int s = T.query(1, n, ql[i], qr[i]);

			if(typ[i]) {
				T.modify(1, n, ql[i], ql[i] + s - 1, 1);
				T.modify(1, n, ql[i] + s, qr[i], 0);
			} else {
				T.modify(1, n, qr[i] - s + 1, qr[i], 1);
				T.modify(1, n, ql[i], qr[i] - s, 0);
			}
		}

		if(T.query(1, n, p, p))
			l = mid;
		else
			r = mid - 1;
	}

	printf("%d\n", l);
}
