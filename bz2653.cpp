#if 0
2020.01.07

一遍过挺神奇的。
中位数按套路二分答案，然后对于当前答案 x ，将所有 >= x 的数设为 1 其他 -1 ，
一个区间的区间和 >= 0 说明该区间中位数 >= x 。
对于所有 x 建线段树，其中第 x 颗线段树在第 x - 1 颗线段树的基础上可持久化而来。
那么对于询问二分答案，只要查询 [a, b] 的最大后缀和 + (b, c) 的区间和 + [c, d] 的最大前缀和。
#endif
#include <cstdio>
#include <algorithm>
#include <vector>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
} read;

const int maxn = 20005;
struct Data {
	int sum;
	int pre, suf;
	Data(): sum(0), pre(0), suf(0) { }
};
struct Tree {
	int lti, rti;
	Data val;
};
Tree pool[maxn * 40];
#define self pool[now]
#define lt pool[self.lti]
#define rt pool[self.rti]

int tmp[maxn], a[maxn];
std::vector<int> pos[maxn];
int T[maxn], tp;
Data null;

Data operator + (Data l, Data r) {
	Data x;
	x.sum = l.sum + r.sum;
	x.pre = std::max(l.pre, l.sum + r.pre);
	x.suf = std::max(r.suf, r.sum + l.suf);
	return x;
}

void modify(int &now, int L, int R, int p, int x) {
	pool[++ tp] = self;
	now = tp;
	if(L == R) {
		self.val.sum += x;
		self.val.pre += x;
		self.val.suf += x;
		return;
	}
	int M = (L + R) >> 1;
	if(p <= M) modify(self.lti, L, M, p, x);
	else modify(self.rti, M + 1, R, p, x);
	self.val = lt.val + rt.val;
}

Data query(int now, int L, int R, int l, int r) {
	if(r < L or l > R) return null;
	if(l <= L and R <= r) return self.val;
	int M = (L + R) >> 1;
	return query(self.lti, L, M, l, r) + query(self.rti, M + 1, R, l, r);
}

int main() {
	null.pre = null.suf = - 1000000000;

	int n = read;
	for(int i = 1; i <= n; i ++) tmp[i] = a[i] = read;
	std::sort(tmp + 1, tmp + n + 1);
	for(int i = 1; i <= n; i ++) {
		a[i] = int(std::lower_bound(tmp + 1, tmp + n + 1, a[i]) - tmp);
		pos[a[i]].push_back(i);
	}

	for(int i = 1; i <= n; i ++)
		modify(T[1], 1, n, i, 1);

	for(int i = 2; i <= n; i ++) {
		T[i] = T[i - 1];
		for(int p : pos[i - 1]) modify(T[i], 1, n, p, -2);
	}

	int q = read, ans = 0;
	while(q --) {
		int s[4];
		for(int i = 0; i < 4; i ++) s[i] = 1 + (read + ans) % n;
		std::sort(s, s + 4);
		int l1 = s[0], r1 = s[1], l2 = s[2], r2 = s[3];

		/* debug("%d-%d %d-%d\n", l1, r1, l2, r2); */

		int l = 1, r = n;
		while(l < r) {
			int mid = (l + r + 1) >> 1;
			int sum = query(T[mid], 1, n, l1, r1).suf +
				query(T[mid], 1, n, r1 + 1, l2 - 1).sum +
				query(T[mid], 1, n, l2, r2).pre;
			/* debug("%d: %d\n", mid, sum); */
			if(sum >= 0) l = mid;
			else r = mid - 1;
		}

		printf("%d\n", ans = tmp[l]);
	}
}
