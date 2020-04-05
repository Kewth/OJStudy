#pragma GCC optimize(2)
#if 0
2020.04.05

清奇，按数组下标从右到左扫描线，然后对于时间轴用线段树维护每个时间点的值。
由于数组每个点的值都是后缀最小值，那么随着扫描线左移，更新后缀最小值是比较方便的。
对于所有修改，将其影响的时间段放在线段树上修改即可。

那么需要的就是这样一颗线段树：
1) 区间取 min
2) 单点查询被取 min 的次数。

吉司机线段树可以很好胜任，但查询取 min 次数有点特殊，需要通过标记以及下传的方式实现。
具体地，线段树每个节点维护从上次 push_down 以来 max 减小了多少次，将这个作为 tag 即可。
由于修改只有区间取 min 的操作，复杂度是 O(nlogn) 的。

另外为了卡两个 log ，这题丧病地出到了 1e6 ，由于需要多次标记下传常数本来就大。
做法两个：优化 IO ，把 vector 换成链表。
#endif
#include <cstdio>
#include <algorithm>
/* #include <vector> */
#include <cstdlib>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct Inputer {
	static char buffer[32 * 1024 * 1024], *p;
	inline operator int () { return int(strtol(p, &p, 10)); }
	inline operator ll () { return strtoll(p, &p, 10); }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
	Inputer() { fread(buffer, 1, sizeof buffer, stdin); }
} read;
char *Inputer::p = Inputer::buffer;
char Inputer::buffer[] = {};

const int maxn = 1000005;
int a[maxn];
int ohead[maxn], onxt[maxn], ox[maxn];
int qhead[maxn], qnxt[maxn];
// vector 吃屎系列。
/* struct op { */
/* 	int t, x; */
/* }; */
/* std::vector<op> ov[maxn]; */
/* std::vector<int> qv[maxn]; */
int ans[maxn];
int max[maxn << 2], semax[maxn << 2], tag[maxn << 2];
#define ls (now << 1)
#define rs (now << 1 | 1)

inline void update (int now) {
	max[now] = std::max(max[ls], max[rs]);
	semax[now] = std::max(
			max[ls] < max[now] ? max[ls] : semax[ls],
			max[rs] < max[now] ? max[rs] : semax[rs]);
}

inline bool modi (int now, int x, int y) {
	return semax[now] < x and x < max[now] ? max[now] = x, tag[now] += y, 1 : 0;
}

inline void push_down (int now) {
	if (tag[now]) {
		modi(ls, max[now], tag[now]);
		modi(rs, max[now], tag[now]);
		tag[now] = 0;
	}
}

void modify (int now, int L, int R, int l, int r, int x) {
	if (x >= max[now]) return;
	if (l <= L and R <= r and modi(now, x, 1)) return;
	int M = (L + R) >> 1;
	push_down(now);
	if (l <= M) modify(ls, L, M, l, r, x);
	if (r > M) modify(rs, M + 1, R, l, r, x);
	update(now);
}

int query (int now, int L, int R, int p) {
	if (L == R) return tag[now];
	int M = (L + R) >> 1;
	push_down(now);
	if (p <= M) return query(ls, L, M, p);
	return query(rs, M + 1, R, p);
}

int main () {
	int n = read, q = read;
	for (int i = 1; i <= n; i ++)
		read(a[i]);
	for (int i = 1; i <= q; i ++) {
		int o = read;
		if (o == 1) {
			int p = read;
			onxt[i] = ohead[p];
			ohead[p] = i;
			ox[i] = read;
		}
		if (o == 2) {
			int p = read;
			qnxt[i] = qhead[p];
			qhead[p] = i;
		}
	}

	std::fill(max, max + q * 4, 1000000001);

	for (int i = n; i; i --) {
		int las = q + 1;
		for (int t = ohead[i]; t; t = onxt[t])
			modify(1, 0, q, t, las - 1, ox[t]), las = t;
		modify(1, 0, q, 0, las - 1, a[i]);
		for (int t = qhead[i]; t; t = qnxt[t])
			ans[t] = query(1, 0, q, t);
	}

	for (int i = 1; i <= q; i ++)
		if (ans[i])
			printf("%d\n", ans[i]);
}
