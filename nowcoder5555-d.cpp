#pragma GCC optimize(2)
#if 0
2020.05.15

  如果没有 1, 2 操作，每个颜色开线段树维护位置，对于询问线段树二分即可。
  如果没有 2 操作，用 odt 维护区间覆盖来辅助线段树进行修改即可。
  对于 2 操作，可以看做把颜色 x 合并入颜色 y 再删除颜色 x 。合并就是线段树合并，但是 odt
里面的颜色也需要修改，而直接修改是不可行的，可以用并查集来维护 odt 节点的实际颜色。而删除
掉一个颜色也很简单，如果删除颜色 x ，那么开一个新颜色 c ，之后所有对于 x 的操作都改为对 c
操作即可。
#endif
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator char () { char x[10]; return scanf("%s", x), *x; }
} read;

const int maxn = 200005, LIM = maxn * 60;
struct Tree {
	int lti, rti;
	int val, lazy;
};
Tree pool[LIM];
int pp;
#define self pool[now]
#define lt pool[self.lti]
#define rt pool[self.rti]
bool mark[LIM];

int newnode () {
	++ pp;
	while (mark[pp]) ++ pp;
	pool[pp] = {0, 0, 0, 0};
	return pp;
}

inline void add (int &now, int L, int R, int x) {
	if (!now) now = newnode();
	self.val += x * (R - L + 1);
	self.lazy += x;
}

inline void push_down (int now, int L, int R) {
	if (self.lazy) {
		int M = (L + R) >> 1;
		add(self.lti, L, M, self.lazy);
		add(self.rti, M + 1, R, self.lazy);
		self.lazy = 0;
	}
}

void modify (int &now, int L, int R, int l, int r, int x) {
	if (r < L or l > R) return;
	if (l <= L and R <= r) return add(now, L, R, x), void();
	if (!now) now = newnode();
	push_down(now, L, R);
	int M = (L + R) >> 1;
	modify(self.lti, L, M, l, r, x);
	modify(self.rti, M + 1, R, l, r, x);
	self.val = lt.val + rt.val;
}

int findmax (int now, int L, int R, int r) {
	if (L > r or !now or !self.val) return -1;
	if (L == R) return R;
	push_down(now, L, R);
	int M = (L + R) >> 1;
	int rf = findmax(self.rti, M + 1, R, r);
	if (rf != -1) return rf;
	return findmax(self.lti, L, M, r);
}

int findmin (int now, int L, int R, int l) {
	if (R < l or !now or !self.val) return -1;
	if (L == R) return L;
	push_down(now, L, R);
	int M = (L + R) >> 1;
	int lf = findmin(self.lti, L, M, l);
	if (lf != -1) return lf;
	return findmin(self.rti, M + 1, R, l);
}

void merge (int &now, int an, int L, int R) {
	if (!an) return;
	if (!now) return now = an, void();
	self.val += pool[an].val;
	self.lazy += pool[an].lazy;
	if (L == R) return;
	/* push_down(now, L, R); */
	/* push_down(an, L, R); */
	int M = (L + R) >> 1;
	merge(self.lti, pool[an].lti, L, M);
	merge(self.rti, pool[an].rti, M + 1, R);
}

struct Node {
	int l, r;
	mutable int v;
	Node (int l = 0, int r = 0, int v = 0): l(l), r(r), v(v) { }
};
bool operator < (Node x, Node y) { return x.l < y.l; }

typedef std::set<Node>::iterator iter;
std::set<Node> odt;

iter split (int x) {
	iter it = -- odt.upper_bound(x);
	if (it -> l == x) return it;
	if (x > it -> r) return odt.end();
	int l = it -> l, r = it -> r;
	int v = it -> v;
	odt.erase(it);
	odt.insert(Node(l, x - 1, v));
	return odt.insert(Node(x, r, v)).first;
}

int realco[maxn];
int fa[maxn];
int seg[maxn];

int find (int x) {
	if (fa[x] == x) return x;
	return fa[x] = find(fa[x]);
}

void forcemark (int now) {
	if (!now or mark[now]) return;
	mark[now] = 1;
	forcemark(self.lti);
	forcemark(self.rti);
}

int main () {
	int n = read, q = read;
	for (int i = 1; i <= n; i ++) {
		odt.insert(Node(i, i, i));
		modify(seg[i], 1, n, i, i, 1);
		realco[i] = i;
		fa[i] = i;
	}

	int cp = n;
	while (q --) {
		char o = read;
		if (o == 'c') {
			int l = read, r = read, c = read;
			c = realco[c];
			iter end = split(r + 1);
			iter it = split(l);
			while (it != end) {
				modify(seg[find(it -> v)], 1, n, it -> l, it -> r, -1);
				odt.erase(it ++);
			}
			odt.insert(Node(l, r, c));
			modify(seg[c], 1, n, l, r, 1);
		}
		if (o == 'r') {
			int x = read, y = read;
			if (x != y) {
				int X = realco[x];
				int Y = realco[y];
				merge(seg[Y], seg[X], 1, n);
				seg[X] = 0;
				realco[x] = ++ cp;
				fa[cp] = cp;
				fa[X] = Y;
			}
		}
		if (o == 'f') {
			int p = read, d = read, c = read;
			c = realco[c];
			int max = findmax(seg[c], 1, n, p + d);
			int min = findmin(seg[c], 1, n, p - d);
			if (max < p) max = -1;
			if (min > p) min = -1;
			if (max == -1 and min == -1)
				puts("-1");
			else if (max == -1)
				printf("%d\n", p - min);
			else if (min == -1)
				printf("%d\n", max - p);
			else
				printf("%d\n", std::max(p - min, max - p));
		}
		if (pp + 100000 > LIM) {
			memset(mark, 0, sizeof mark);
			for (int i = 1; i <= cp; i ++)
				forcemark(seg[i]);
			pp = 0;
		}
	}

	/* debug("%lu\n", sizeof (pool) >> 20); */
}
