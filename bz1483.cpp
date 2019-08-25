#if 0
date +%Y.%m.%d

题解先咕着。
#endif
#include <cstdio>
#include <cassert>
#define debug(...) fprintf(stderr, __VA_ARGS__)

inline int input() { int x; scanf("%d", &x); return x; }

struct Tree;
Tree *null;
struct Tree {
	Tree *lt, *rt;
	int tot;
	bool hasl, hasr, fuckmemory[2];

	inline void update() {
		tot = lt -> tot + rt -> tot;
		if(lt -> hasr and rt -> hasl)
			tot --;
		hasl = lt -> hasl;
		hasr = rt -> hasr;
	}

	Tree(): lt(null), rt(null), tot(0), hasl(false), hasr(false) { }
};

void merge(Tree *&a, Tree *b) {
	if(b == null)
		return;

	if(a == null) {
		a = b;
		return;
	}

	merge(a -> lt, b -> lt);
	merge(a -> rt, b -> rt);

	/* debug("%d %d\n", a -> tot, b -> tot); */

	if(a -> lt == null and a -> rt == null) {
		a -> tot = a -> tot or b -> tot;
		a -> hasl = true;
		a -> hasr = true;
	} else
		a -> update();
}

inline void lain(Tree *&now, int l, int r, int p) {
	/* debug("%d %d %d\n", l, r, p), fflush(stderr); */
	if(now == null)
		now = new Tree();
	if(l == r) {
		now -> tot ++;
		now -> hasl = now -> hasr = true;
		return;
	}
	int mid = (l + r) >> 1;
	if(p <= mid)
		lain(now -> lt, l, mid, p);
	else
		lain(now -> rt, mid + 1, r, p);
	now -> update();
}


const int maxn = 1000005;
Tree *T[maxn];

int main() {
	null = new Tree();

	int n = input(), q = input();

	for(int i = 0; i < maxn; i ++)
		T[i] = new Tree();

	for(int i = 1; i <= n; i ++)
		lain(T[input()], 1, n, i);

	int ans = 0;
	for(int i = 1; i < maxn; i ++)
		ans += T[i] -> tot;

	while(q --) {
		if(input() == 1) {
			int x = input(), y = input();

			if(x != y) {
				ans -= T[x] -> tot + T[y] -> tot;
				merge(T[y], T[x]);
				T[x] = new Tree();
				ans += T[x] -> tot + T[y] -> tot;
			}

			/* for(int i = 1; i <= n; i ++) */
			/* 	debug(" %d", T[i] -> tot); */
			/* debug("\n"); */
		}

		else
			printf("%d\n", ans);
	}
}
