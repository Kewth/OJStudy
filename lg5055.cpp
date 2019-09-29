#if 0
2019.09.29

可持久化平衡树模板。
由于有标记下传，push_down 也要复制节点。

push_down 里头踩了两个坑，
一个是直接复制右儿子给左儿子，复制左儿子给右儿子，然后就挂了，还是得老老实实 swap 。
还有一个是没有特判儿子为空的情况，此时是不能新建节点的。
#endif
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;
inline int input() { int x; scanf("%d", &x); return x; }
inline lolong linput() { lolong x; scanf("%lld", &x); return x; }

struct Treap {
    int size, weight;
	int ltid, rtid;
	int lazy, fuck;
	lolong val, sum;
};
#define self pool[now]
#define lt pool[self.ltid]
#define rt pool[self.rtid]

const int maxn = 200005;
Treap pool[maxn * 80];
int pp;

void print(int now, int d = 0) {
	/* if(self.ltid) print(self.ltid, d + 1); */
	/* for(int i = 0; i < d; i ++) debug(" "); */
	/* debug("%d: %d %d| %d| %lld %lld(%d)\n", */
	/* 		now, self.ltid, self.rtid, self.size, self.val, self.sum, self.lazy); */
	/* if(self.rtid) print(self.rtid, d + 1); */
	/* if(!d) debug("\n"); */
}

inline void update(int now) {
	self.size = lt.size + rt.size + 1;
	self.sum = lt.sum + rt.sum + self.val;
}

inline void push_down(int now) {
	if(self.lazy) {
		if(self.ltid) {
			pool[++ pp] = lt;
			self.ltid = pp;
		}
		if(self.rtid) {
			pool[++ pp] = rt;
			self.rtid = pp;
		}
		std::swap(self.ltid, self.rtid);
		lt.lazy ^= 1;
		rt.lazy ^= 1;
		self.lazy = 0;
	}
}

void split(int now, int k, int &a, int &b) {
	/* debug("split %d %d\n", now, k); */
	if(!now)
		a = b = 0;
	else {
		pool[++ pp] = self;
		now = pp;
		push_down(now);
		if(k <= lt.size) {
			split(self.ltid, k, a, self.ltid);
			b = now;
		} else {
			split(self.rtid, k - lt.size - 1, self.rtid, b);
			a = now;
		}
		update(now);
	}
}

int merge(int a, int b) {
	if(!a) return b;
	if(!b) return a;

	if(pool[a].weight > pool[b].weight) {
		push_down(a);
		pool[a].rtid = merge(pool[a].rtid, b);
		update(a);
		return a;
	} else {
		push_down(b);
		pool[b].ltid = merge(a, pool[b].ltid);
		update(b);
		return b;
    }
}

int history[maxn];

int main() {
	srand(19491001);

	int now = ++ pp;
	self.size = 1;
	self.weight = rand();

	history[0] = 0;
	lolong ans = 0;

    int q = input();
	for(int i = 1; i <= q; i ++) {
		now = history[input()];
        int t = input();

		if(t == 1) {
			int k = int(linput() ^ ans), x = int(linput() ^ ans);
			int a, b;
			split(now, k, a, b);
			now = ++ pp;
			self = pool[1];
			self.weight = rand();
			self.val = self.sum = x;
			now = merge(a, merge(now, b));
		}

		else if(t == 2) {
			int k = int(linput() ^ ans);
			int a, b, c;
			split(now, k - 1, a, b);
			split(b, 1, b, c);
			now = merge(a, c);
		}

		else if(t == 3) {
			int l = int(linput() ^ ans), r = int(linput() ^ ans);
			/* debug("rev %d - %d\n", l, r); */
			int a, b, c;
			split(now, l - 1, a, b);
			split(b, r - l + 1, b, c);
			pool[b].lazy ^= 1;
			now = merge(a, merge(b, c));
		}

		else if(t == 4) {
			int l = int(linput() ^ ans), r = int(linput() ^ ans);
			/* debug("ask %d - %d\n", l, r); */
			int a, b, c;
			split(now, l - 1, a, b);
			split(b, r - l + 1, b, c);
			ans = pool[b].sum;
			now = merge(a, merge(b, c));
			printf("%lld\n", ans);
		}

		print(now);
		history[i] = now;
    }
}
