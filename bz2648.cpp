#if 0
2019.08.20

KD 树模板题，虽然 KD 树求最近点的复杂度是不对的，理论上界仍然是 O(n) 。
我擦两个地方的比较符都写反了，还难调得很，因为树结构错误不会影响答案，只会影响剪枝效率。
常数巨大，需要 O2 。
#endif
#include <cstdio>
#include <algorithm>
#include <climits>
#define debug(...) fprintf(stderr, __VA_ARGS__)

inline int input() { int x; scanf("%d", &x); return x; }

struct Kdtree;
Kdtree *null;

const int maxn = 500005;
Kdtree *pool[maxn];
int cmp_d;
int TOT, high, deep;

struct Kdtree {
	int size;
	int p[2], min[2], max[2], fuck_memory;
	Kdtree *son[2];

	static inline bool cmp(Kdtree *a, Kdtree *b) {
		return a -> p[cmp_d] < b -> p[cmp_d];
	}

	inline void update() {
		size = son[0] -> size + son[1] -> size + 1;

		for(int i = 0; i < 2; i ++) {
			min[i] = max[i] = p[i];
			min[i] = std::min(min[i], son[0] -> min[i]);
			min[i] = std::min(min[i], son[1] -> min[i]);
			max[i] = std::max(max[i], son[0] -> max[i]);
			max[i] = std::max(max[i], son[1] -> max[i]);
		}
	}

	static Kdtree *rebuild(int l, int r, bool d) {
		if(l > r)
			return null;

		int mid = (l + r) >> 1;

		cmp_d = d;
		std::nth_element(pool + l, pool + mid, pool + r + 1, cmp);

		pool[mid] -> son[0] = rebuild(l, mid - 1, !d);
		pool[mid] -> son[1] = rebuild(mid + 1, r, !d);
		pool[mid] -> update();

		return pool[mid];
	}

	void make_pool(int &tot) {
		if(this == null)
			return;

		son[0] -> make_pool(tot);
		pool[++ tot] = this;
		son[1] -> make_pool(tot);
	}

	static inline void check(Kdtree *&now, bool d) {
		if(std::max(now -> son[0] -> size, now -> son[1] -> size) >=
				now -> size * 0.75) {
			int tot = 0;
			now -> make_pool(tot);
			now = rebuild(1, tot, d);
		}
	}

	static void insert(Kdtree *&now, Kdtree *t, bool d) {
		if(now == null) {
			now = t;
			return;
		}

		insert(now -> son[t -> p[d] > now -> p[d]], t, !d);
		now -> update();
		check(now, d);
	}

	int h(int qp[2]) {
		if(this == null)
			return INT_MAX;

		int res = 0;
		for(int i = 0; i < 2; i ++)
			res += std::max(0, qp[i] - max[i]) + std::max(0, min[i] - qp[i]);
		return res;
	}

	void query(int qp[2], int &ans) {
		/* TOT ++; */
		/* high ++; */
		/* deep = std::max(deep, high); */

		int dis[2] = {son[0] -> h(qp), son[1] -> h(qp)};
		bool id = dis[0] > dis[1];

		ans = std::min(ans, std::abs(p[0] - qp[0]) + std::abs(p[1] - qp[1]));

		if(dis[id] < ans)
			son[id] -> query(qp, ans);
		if(dis[!id] < ans)
			son[!id] -> query(qp, ans);

		/* high --; */
	}

	inline Kdtree(int x, int y): size(1) {
		min[0] = max[0] = p[0] = x;
		min[1] = max[1] = p[1] = y;
		son[0] = son[1] = null;
	}
};


int main() {
	null = new Kdtree(0, 0);
	null -> size = 0;
	null -> min[0] = null -> min[1] = INT_MAX;
	null -> max[0] = null -> max[1] = INT_MIN;

	int n = input(), q = input();
	for(int i = 1; i <= n; i ++) {
		int x = input(), y = input();
		pool[i] = new Kdtree(x, y);
	}

	Kdtree *T = Kdtree::rebuild(1, n, 0);

	while(q --) {
		int typ = input(), x = input(), y = input();

		/* TOT = deep = 0; */

		if(typ == 1)
			Kdtree::insert(T, new Kdtree(x, y), 0);

		else {
			int ans = INT_MAX, p[2] = {x, y};
			T -> query(p, ans);
			printf("%d\n", ans);
		}

		/* debug("%d %d\n", TOT, deep); */
		/* int tot = 0; */
		/* T -> make_pool(tot); */
		/* for(int i = 1; i <= tot; i ++) */
		/* 	debug("pos %d %d min %d %d max %d %d\n", */
		/* 			pool[i] -> p[0], pool[i] -> p[1], */
		/* 			pool[i] -> min[0], pool[i] -> min[1], */
		/* 			pool[i] -> max[0], pool[i] -> max[1]); */
		/* debug("\n"); */
	}
}
