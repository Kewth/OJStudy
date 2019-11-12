#if 0
2019.11.12

一维的离队操作相当于区间移动，删掉一个点并插到最后一个位置，用平衡树不难维护，
但二维的一搬区间移动两个维度之间互相干扰，难以直接维护。
但这个问题有特殊性，每次只有该行和最后一列会改变，最后一列如此特殊，可以单独用个平衡树维护。
其余的每行用平衡树维护去掉最后一列的列队情况。
那么离队就可以很好直接在两颗平衡树（一颗对应行，一颗最后一列）上进行操作了。
唯一的问题是平面过大，点数也会很多，
可以动态维护，行上的 Treap 每个节点维护一段从未拆开过的区间，
每次 split 的时候动态分裂区间即可。
这样每次询问分裂的区间数量是 O(1) 的，节点总数是线性的。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) // fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
} read;

struct Treap {
	int len, size;
	ll val, weight;
	int lti, rti;
};
#define self pool[now]
#define lt pool[self.lti]
#define rt pool[self.rti]

const int maxn = 1000000;
Treap pool[maxn << 2];
int pp;

inline void update(int now) {
	self.size = lt.size + self.len + rt.size;
}

void split(int now, int k, int &a, int &b) {
	if(!now) return a = b = 0, void();

	if(k <= lt.size) {
		split(self.lti, k, a, self.lti);
		update(b = now);
		return;
	}
	k -= lt.size;

	if(k < self.len) {
		a = ++ pp;
		pool[a] = Treap({k, lt.size + k, self.val, rand(), self.lti, 0});
		self.len -= k;
		self.val += k;
		self.lti = 0;
		update(b = now);
		return;
	}
	k -= self.len;

	split(self.rti, k, self.rti, b);
	update(a = now);
}

int merge(int a, int b) {
	if(!a) return b;
	if(!b) return a;
	if(pool[a].weight > pool[b].weight) {
		pool[a].rti = merge(pool[a].rti, b);
		update(a);
		return a;
	}
	pool[b].lti = merge(a, pool[b].lti);
	update(b);
	return b;
}

int T[maxn];

int main() {
	int n = read, m = read, q = read;

	for(int i = 1; i <= n; i ++)
		pool[T[i] = ++ pp] = Treap({m - 1, m - 1, ll(i - 1) * m, rand(), 0, 0});

	for(int i = 1; i <= n; i ++) {
		pool[++ pp] = Treap({1, 1, ll(i - 1) * m + m - 1, rand(), 0, 0});
		T[n + 1] = merge(T[n + 1], pp);
	}

	debug("fuck\n");
	for(int now = 1; now <= pp; now ++)
		debug("%d: l=%d, s=%d ->%d, %d v=%lld\n",
				now, self.len, self.size, self.lti, self.rti, self.val);

	while(q --) {
		int x = read, y = read;

		int a, b, c;
		split(T[n + 1], x, a, c);
		split(a, x - 1, a, b);
		debug("%d %d %d\n", a, b, c);

		if(y < m) {
			int A, B, C;
			split(T[x], y, A, C);
			split(A, y - 1, A, B);
			debug("%d %d %d\n", A, B, C);
			printf("%lld\n", pool[B].val + 1);
			T[x] = merge(A, merge(C, b));
			T[n + 1] = merge(a, merge(c, B));
		}

		else {
			printf("%lld\n", pool[b].val + 1);
			T[n + 1] = merge(a, merge(c, b));
		}

		debug("fuck\n");
		for(int now = 1; now <= pp; now ++)
			debug("%d: l=%d, s=%d ->%d, %d v=%lld\n",
					now, self.len, self.size, self.lti, self.rti, self.val);
	}
}
