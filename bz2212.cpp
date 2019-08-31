#if 0
2019.08.25

傻吊 luogu 卡老子空间。
傻吊 loj 卡老子时间。

每个节点合并儿子的时候只需考虑儿子之间逆序对的贡献，儿子内部的内部贡献没有影响。
因此每个节点都是使逆序对尽可能少。
开权值线段树逐步合并，中途维护是否交换儿子的不同逆序对即可。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;

inline int input() {
	int x = 0, c = getchar();
	while(c < '0' or c > '9') c = getchar();
	while(c >= '0' and c <= '9') x = x * 10 + c - '0', c = getchar();
	return x;
}

struct Tree;
Tree *null;

struct Tree {
	Tree *lt, *rt;
	int val;
	int shit;

	inline void update() {
		val = lt -> val + rt -> val;
	}

	inline Tree(): lt(null), rt(null), val(0) { }
};

void lain(Tree *&now, int l, int r, int p) {
	if(now == null)
		now = new Tree();

	if(l == r) {
		now -> val ++;
		return ;
	}

	int mid = (l + r) >> 1;

	if(p <= mid)
		lain(now -> lt, l, mid, p);
	else
		lain(now -> rt, mid + 1, r, p);

	now -> update();
}

void merge(Tree *&a, Tree *b, lolong &ans1, lolong &ans2) {
	if(b == null)
		return;
	if(a == null) {
		a = b;
		return;
	}

	ans1 += 1ll * a -> rt -> val * b -> lt -> val;
	ans2 += 1ll * b -> rt -> val * a -> lt -> val;

	merge(a -> lt, b -> lt, ans1, ans2);
	merge(a -> rt, b -> rt, ans1, ans2);
	if(a -> lt == null and a -> rt == null)
		a -> val += b -> val;
	else
		a -> update();
}

void shit(Tree *&now) {
	if(now == null)
		return;
	delete now;
	now = null;
}

Tree *solve(lolong &ans) {
	int x = input();

	/* debug("%d\n", x); */

	if(x) {
		Tree *T = new Tree();
		lain(T, 1, 1000000, x);
		return T;
	}

	Tree *l = solve(ans);
	Tree *r = solve(ans);

	lolong ans1 = 0, ans2 = 0;
	merge(l, r, ans1, ans2);

	// 这个内存回收会影响到 l ，但是实际上似乎没有关系，不会 RE
	shit(r);

	/* debug("%lld %lld\n", ans1, ans2); */

	ans += std::min(ans1, ans2);

	return l;
}

int main() {
	null = new Tree();

	input();
	lolong ans = 0;
	Tree *T = solve(ans);
	printf("%lld\n", ans);

	shit(T);
	shit(null);
}
