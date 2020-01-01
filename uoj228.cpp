#if 0
2020.01.01

又是一种神奇线段树。
（ps: 还可以支持区间覆盖，区间查询最值）
如果只有开根操作，众所周知只对大于 1 的数开根即可，一个数 x 经过 loglogx 次开根就会变成 1 。
但是有区间加和区间覆盖这类会试数变大的操作，开根次数就没有保证了。

考虑有什么值是会随着开根快速减小，但是不受区间加或区间覆盖影响。
这个值就是极差，max - min 。
有 sqrt(max) - sqrt(min) <= sqrt(max - min) ，这说明极差经过上界 loglogx 次开根也会不超过 1 。

用线段树维护 max, min, sum ，对于开根操作：
1) max - min > 1: 暴力递归
2) max - min = 1:
  i) sqrt(max) - sqrt(min) = 1: 区间加值
  ii) sqrt(max) = sqrt(min): 区间覆盖
3) max - min = 0: 区间覆盖
#endif
#include <cstdio>
#include <algorithm>
#include <cmath>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
} read;

struct Tree {
	ll sum;
	ll max, min;
	ll add, cover;
};
const int maxn = 100005, magic = - 19260817;
Tree pool[maxn << 2];
#define self pool[now]
#define lt pool[now << 1]
#define rt pool[now << 1 | 1]

void update(int now) {
	self.sum = lt.sum + rt.sum;
	self.max = std::max(lt.max, rt.max);
	self.min = std::min(lt.min, rt.min);
}

void modi_add(int now, ll x, int len) {
	self.sum += 1ll * x * len;
	self.max += x;
	self.min += x;
	if(self.cover == magic)
		self.add += x;
	else
		self.cover += x;
}

void modi_cover(int now, ll x, int len) {
	self.sum = 1ll * x * len;
	self.max = x;
	self.min = x;
	self.cover = x;
}

void push_down(int now, int len) {
	if(self.cover != magic) {
		modi_cover(now << 1, self.cover, (len + 1) >> 1);
		modi_cover(now << 1 | 1, self.cover, len >> 1);
		self.cover = magic;
		self.add = 0;
	}
	if(self.add) {
		modi_add(now << 1, self.add, (len + 1) >> 1);
		modi_add(now << 1 | 1, self.add, len >> 1);
		self.add = 0;
	}
}

void modi_sqrt(int now, int len) {
	int sqmax = int(sqrt(self.max)), sqmin = int(sqrt(self.min));
	if(sqmax == sqmin) return modi_cover(now, sqmax, len);
	if(self.max == self.min + 1) return modi_add(now, sqmax - self.max, len);
	push_down(now, len);
	modi_sqrt(now << 1, (len + 1) >> 1);
	modi_sqrt(now << 1 | 1, len >> 1);
	update(now);
}

void modify_sqrt(int now, int L, int R, int l, int r) {
	if(l > R or r < L) return;
	if(l <= L and R <= r) return modi_sqrt(now, R - L + 1), void();
	int M = (L + R) >> 1;
	push_down(now, R - L + 1);
	modify_sqrt(now << 1, L, M, l, r);
	modify_sqrt(now << 1 | 1, M + 1, R, l, r);
	update(now);
}

void modify_add(int now, int L, int R, int l, int r, int x) {
	if(l > R or r < L) return;
	if(l <= L and R <= r) return modi_add(now, x, R - L + 1), void();
	int M = (L + R) >> 1;
	push_down(now, R - L + 1);
	modify_add(now << 1, L, M, l, r, x);
	modify_add(now << 1 | 1, M + 1, R, l, r, x);
	update(now);
}

ll query(int now, int L, int R, int l, int r) {
	if(l > R or r < L) return 0;
	if(l <= L and R <= r) return self.sum;
	push_down(now, R - L + 1);
	int M = (L + R) >> 1;
	return query(now << 1, L, M, l, r) + query(now << 1 | 1, M + 1, R, l, r);
}

int a[maxn];
void build(int now, int L, int R) {
	if(L == R) return self = Tree({a[L], a[L], a[L], 0, magic}), void();
	self.add = 0;
	self.cover = magic;
	int M = (L + R) >> 1;
	build(now << 1, L, M);
	build(now << 1 | 1, M + 1, R);
	update(now);
}

int main() {
	int n = read, q = read;
	for(int i = 1; i <= n; i ++)
		read(a[i]);
	build(1, 1, n);
	while(q --) {
		int op = read, l = read, r = read;
		if(op == 1) modify_add(1, 1, n, l, r, int(read));
		if(op == 2) modify_sqrt(1, 1, n, l, r);
		if(op == 3) printf("%lld\n", query(1, 1, n, l, r));
	}
}
