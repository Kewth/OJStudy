#if 0
2020.01.14

对每个权值开一颗动态开点线段树，维护那些位置有值，询问 kth 就很好 O(logN) 处理。
修改部分用 odt ，由于除了区间覆盖以外没有任何其他操作需要暴力扫，
只用 odt 处理修改的复杂度是有保证的，lower_bound 复杂度 O(logN) ，
每个线段被操作的次数是 O(1) 的。
#endif
#include <cstdio>
#include <algorithm>
#include <set>
#include <map>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 100005;
struct Tree {
	int lti, rti;
	int val, lazy;
};
Tree pool[maxn * 80];
int pp;
#define self pool[now]
#define lt pool[self.lti]
#define rt pool[self.rti]

inline void add(int &now, int L, int R, int x) {
	if(!now) now = ++ pp;
	self.val += x * (R - L + 1);
	self.lazy += x;
}

inline void push_down(int now, int L, int R) {
	if(self.lazy) {
		int M = (L + R) >> 1;
		add(self.lti, L, M, self.lazy);
		add(self.rti, M + 1, R, self.lazy);
		self.lazy = 0;
	}
}

void modify(int &now, int L, int R, int l, int r, int x) {
	if(r < L or l > R) return;
	if(l <= L and R <= r) return add(now, L, R, x), void();
	if(!now) now = ++ pp;
	push_down(now, L, R);
	int M = (L + R) >> 1;
	modify(self.lti, L, M, l, r, x);
	modify(self.rti, M + 1, R, l, r, x);
	self.val = lt.val + rt.val;
}

int kth(int now, int L, int R, int l, int r, int k, int &sz) {
	if(r < L or l > R) return sz = 0;
	if(l <= L and R <= r) {
		sz = self.val;
		if(k > self.val or k <= 0) return 0;
		if(L == R) return L;
		push_down(now, L, R);
		int M = (L + R) >> 1, tmp;
		if(k <= lt.val) return kth(self.lti, L, M, l, r, k, tmp);
		return kth(self.rti, M + 1, R, l, r, k - lt.val, tmp);
	}
	push_down(now, L, R);
	int M = (L + R) >> 1, lsz, rsz;
	int lres = kth(self.lti, L, M, l, r, k, lsz);
	int rres = kth(self.rti, M + 1, R, l, r, k - lsz, rsz);
	sz = lsz + rsz;
	if(lres) return lres;
	if(rres) return rres;
	return 0;
}

struct Node {
	int l, r;
	mutable int v;
	Node(int l = 0, int r = 0, int v = 0): l(l), r(r), v(v) { }
};
bool operator < (Node x, Node y) { return x.l < y.l; }

typedef std::set<Node>::iterator iter;
std::set<Node> odt;

iter split(int x) {
	iter it = -- odt.upper_bound(x);
	if(it -> l == x) return it;
	if(x > it -> r) return odt.end();
	int l = it -> l, r = it -> r;
	int v = it -> v;
	odt.erase(it);
	odt.insert(Node(l, x - 1, v));
	return odt.insert(Node(x, r, v)).first;
}

int main() {
	int n = read, q = read;
	std::map<int, int> T;

	for(int i = 1; i <= n; i ++) {
		int x = read;
		int &t = T[x];
		odt.insert(Node(i, i, x));
		modify(t, 1, n, i, i, 1);
	}

	int ans = 0;
	while(q --) {
		char o[3];
		scanf("%s", o);
		int l = read ^ ans, r = read ^ ans;
		if(*o == 'Q') {
			int k = read ^ ans, x = read ^ ans, tmp = 0;
			ans = kth(T[x], 1, n, l, r, k, tmp);
			printf("%d\n", ans);
		}
		if(*o == 'M') {
			int x = read ^ ans;
			iter end = split(r + 1);
			iter it = split(l);
			while(it != end) {
				modify(T[it -> v], 1, n, it -> l, it -> r, -1);
				odt.erase(it ++);
			}
			odt.insert(Node(l, r, x));
			modify(T[x], 1, n, l, r, 1);
		}
	}
}
