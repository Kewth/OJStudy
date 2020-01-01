#if 0
2020.01.01

吉司机线段树。
传统懒标记线段树的问题在于一个节点对 x 取最小值后无法更新和。
事实上只需维护 max, semax, maxtot 分别表示最大值，小于最大值的次大值和最大值的数量。
这样当一个节点对 x 取最小值时可以分为三种情况：
1) x >= max: 没有影响。
2) semax < x < max: 只有值恰为最大值的 maxtot 个位置会被修改，可以更新区间和。
3) x <= semax: 无法更新，向下递归地修改两个儿子再 update 。
重点在于第 3 种情况的复杂度，虽然最坏情况下修改的复杂度没有保证，
但是其均摊复杂度似乎似乎上界是 O(log^2n) 的，似乎可以势能分析，网上也找不到证明？
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
} read;

const int maxn = 500005, inf = 2000000000;
struct Tree {
	ll sum;
	int max, semax, maxtot;
	int tag;
};
Tree pool[maxn << 2];
#define self pool[now]
#define lt pool[now << 1]
#define rt pool[now << 1 | 1]

void update(int now) {
	self.sum = lt.sum + rt.sum;
	self.max = std::max(lt.max, rt.max);
	self.semax = std::max(lt.semax, rt.semax);
	self.maxtot = 0;
	if(lt.max == self.max) self.maxtot += lt.maxtot;
	else self.semax = std::max(self.semax, lt.max);
	if(rt.max == self.max) self.maxtot += rt.maxtot;
	else self.semax = std::max(self.semax, rt.max);
}

void modi(int, int);
void push_down(int now) {
	modi(now << 1, self.tag);
	modi(now << 1 | 1, self.tag);
	self.tag = inf;
}

void modi(int now, int x) {
	if(x >= self.max) return;
	if(x > self.semax) {
		self.sum -= 1ll * (self.max - x) * self.maxtot;
		self.max = x;
		self.tag = std::min(self.tag, x);
		return;
	}
	self.tag = std::min(self.tag, x);
	push_down(now);
	update(now);
}

void modify(int now, int L, int R, int l, int r, int x) {
	/* debug("%d: (%d-%d) sum=%lld max=%d semax=%d maxtot=%d tag=%d\n", */
	/* 		now, L, R, self.sum, self.max, self.semax, self.maxtot, self.tag); */
	if(r < L or l > R) return;
	if(l <= L and R <= r) return modi(now, x), void();
	int M = (L + R) >> 1;
	push_down(now);
	modify(now << 1, L, M, l, r, x);
	modify(now << 1 | 1, M + 1, R, l, r, x);
	update(now);
}

ll query(int now, int L, int R, int l, int r) {
	if(r < L or l > R) return 0;
	if(l <= L and R <= r) return self.sum;
	int M = (L + R) >> 1;
	push_down(now);
	return query(now << 1, L, M, l, r) + query(now << 1 | 1, M + 1, R, l, r);
}

int a[maxn];
void build(int now, int L, int R) {
	if(L == R) {
		self = Tree({a[L], a[L], - inf, 1, inf});
		return;
	}
	int M = (L + R) >> 1;
	build(now << 1, L, M);
	build(now << 1 | 1, M + 1, R);
	self.tag = inf;
	update(now);
}

int main() {
	int n = read, q = read;
	for(int i = 1; i <= n; i ++)
		read(a[i]);

	build(1, 1, n);

	while(q --)
		if(int(read)) {
			int l = read, r = read, x = read;
			modify(1, 1, n, l, r, x);
		} else {
			int l = read, r = read;
			printf("%lld\n", query(1, 1, n, l, r));
		}
}
