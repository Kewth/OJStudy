#if 0
2020.04.16

  判断两个可重集是否相等可以使用哈希，但不能是随机权异或，可以令值 x 的权值为 p^x 。其中
p 是一个足够大的质数，类似与字符串哈希的 base 。然后两个可重集的权值和的哈希值相等就可以
认为两个可重集相同。

  但是这里允许有一个位置不同。

  由于比较两个区间是比较排序后的，那么区间内的数实际上顺序无关，可以用权值线段树维护一些
顺序无关的数。而对应到区间上，由于不要修改，用主席树即可胜任（带修换成树状数组套线段树即
可）。那么在主席树上二分出最大的 x 满足只考虑 [1, x) 的数两个区间相同，同理有最小的 y 满
足 (y, MAX] 中两个区间相同。

  不难发现只要在两个区间内 [x, y] 的数都只有恰好一个，这两个区间就是相似且不同的。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef unsigned long long ull;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 100005;
struct Tree {
	int lti, rti;
	ull val;
} pool[maxn * 20];
int pp;
#define self pool[now]
#define Seg(x) pool[seg[x]]

ull po[maxn];

void insert (int &now, int L, int R, int p) {
	pool[++ pp] = self;
	now = pp;
	self.val += po[p];
	if (L == R) return;
	int M = (L + R) >> 1;
	if (p <= M) insert(self.lti, L, M, p);
	else insert(self.rti, M + 1, R, p);
}

ull query (int now, int L, int R, int l, int r) {
	if (r < L or l > R or !now) return 0;
	if (l <= L and R <= r) return self.val;
	int M = (L + R) >> 1;
	return query(self.lti, L, M, l, r) + query(self.rti, M + 1, R, l, r);
}

int seg[maxn];

int find_min (int a, int b, int c, int d, int L, int R) {
	ull x = pool[b].val - pool[a].val;
	ull y = pool[d].val - pool[c].val;
	if (x == y) return -1;
	if (L == R) return L;
	int M = (L + R) >> 1;
	int get = find_min(pool[a].lti, pool[b].lti, pool[c].lti, pool[d].lti, L, M);
	if (get != -1) return get;
	return find_min(pool[a].rti, pool[b].rti, pool[c].rti, pool[d].rti, M + 1, R);
}

int find_max (int a, int b, int c, int d, int L, int R) {
	ull x = pool[b].val - pool[a].val;
	ull y = pool[d].val - pool[c].val;
	if (x == y) return -1;
	if (L == R) return R;
	int M = (L + R) >> 1;
	int get = find_max(pool[a].rti, pool[b].rti, pool[c].rti, pool[d].rti, M + 1, R);
	if (get != -1) return get;
	return find_max(pool[a].lti, pool[b].lti, pool[c].lti, pool[d].lti, L, M);
}

int main () {
	int T = read, V = 100000;
	po[0] = 1;
	for (int x = 1; x <= V; x ++)
		po[x] = po[x - 1] * 23456789;

	while (T --) {
		int n = read, q = read;
		seg[0] = pp = 0;
		for (int i = 1; i <= n; i ++) {
			seg[i] = seg[i - 1];
			insert(seg[i], 1, V, read);
		}

		while (q --) {
			int a = read, b = read, c = read, d = read;
			-- a, -- c;
			if (Seg(b).val - Seg(a).val == Seg(d).val - Seg(c).val) {
				puts("YES");
				continue;
			}
			int x = find_min(seg[a], seg[b], seg[c], seg[d], 1, V);
			int y = find_max(seg[a], seg[b], seg[c], seg[d], 1, V);
			/* debug("%d %d\n", x, y); */
			ull X = query(seg[b], 1, V, x, y) - query(seg[a], 1, V, x, y);
			ull Y = query(seg[d], 1, V, x, y) - query(seg[c], 1, V, x, y);
			if ((X == po[x] or X == po[y]) and (Y == po[x] or Y == po[y]))
				puts("YES");
			else
				puts("NO");
		}
	}
}
