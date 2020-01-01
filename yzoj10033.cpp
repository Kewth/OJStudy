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

有个 trick ，区间取 min 不需要记 tag ，直接把 max 当 tag 用即可。
我写出来常数巨大。。
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

const int maxn = 500005;
const ll inf = 1000000000000000000;
struct Tree {
	ll sum;
	ll max, semax, maxtot;
	ll add;
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

void minmodi(int, int, int, ll);
void addmodi(int now, int L, int R, ll x) {
	self.max += x;
	self.semax += x;
	self.sum += (R - L + 1) * x;
	self.add += x;
}

void push_down(int now, int L, int R) {
	int M = (L + R) >> 1;
	if(self.add) {
		addmodi(now << 1, L, M, self.add);
		addmodi(now << 1 | 1, M + 1, R, self.add);
		self.add = 0;
	}
	minmodi(now << 1, L, M, self.max);
	minmodi(now << 1 | 1, M + 1, R, self.max);
}

void minmodi(int now, int L, int R, ll x) {
	if(x >= self.max) return;
	if(x > self.semax) {
		self.sum -= (self.max - x) * self.maxtot;
		self.max = x;
		return;
	}
	/* if(L == R) debug("%d %d\n", x, self.semax); */
	self.max = x;
	push_down(now, L, R);
	update(now);
}

void minmodify(int now, int L, int R, int l, int r, int x) {
	if(r < L or l > R) return;
	if(l <= L and R <= r) return minmodi(now, L, R, x), void();
	int M = (L + R) >> 1;
	push_down(now, L, R);
	minmodify(now << 1, L, M, l, r, x);
	minmodify(now << 1 | 1, M + 1, R, l, r, x);
	update(now);
}

void addmodify(int now, int L, int R, int l, int r, int x) {
	if(r < L or l > R) return;
	if(l <= L and R <= r) return addmodi(now, L, R, x), void();
	int M = (L + R) >> 1;
	push_down(now, L, R);
	addmodify(now << 1, L, M, l, r, x);
	addmodify(now << 1 | 1, M + 1, R, l, r, x);
	update(now);
}

ll query(int now, int L, int R, int l, int r) {
	if(r < L or l > R) return 0;
	if(l <= L and R <= r) return self.sum;
	int M = (L + R) >> 1;
	push_down(now, L, R);
	return query(now << 1, L, M, l, r) + query(now << 1 | 1, M + 1, R, l, r);
}

int a[maxn];
void build(int now, int L, int R) {
	if(L == R) {
		self = Tree({a[L], a[L], - inf, 1, 0});
		return;
	}
	int M = (L + R) >> 1;
	build(now << 1, L, M);
	build(now << 1 | 1, M + 1, R);
	self.add = 0;
	update(now);
}

int main() {
	int n = read, q = read;
	for(int i = 1; i <= n; i ++)
		read(a[i]);

	build(1, 1, n);

	while(q --) {
		int op = read, l = read, r = read;
		if(op == 1) minmodify(1, 1, n, l, r, int(read));
		if(op == 2) addmodify(1, 1, n, l, r, int(read));
		if(op == 3) printf("%lld\n", query(1, 1, n, l, r));
	}
}
