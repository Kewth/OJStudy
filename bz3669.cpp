#if 0
2019.09.22

问题要求 min(max(a) + max(b)) 。
从小到大枚举 a 一个一个加边，直接钦定最后加的边 max(a) 后求 min(max(b)) 。
事实上就是 b 的最小生成树上的路径的 max(b) 。
那么用 LCT 在加边过程中动态维护 b 的最小生成树，由于是边权，将边也看做点一起考虑。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

inline int input() { int x; scanf("%d", &x); return x; }

struct Splay {
	int ltid, rtid, faid;
	int eid;
	int maxid;
	int rev;
};

#define self pool[now]
#define lt pool[pool[now].ltid]
#define rt pool[pool[now].rtid]
#define fa pool[pool[now].faid]

struct Edge {
	int x, y, a, b;
};

const int maxn = 50005, maxm = 100005;
Splay pool[maxn + maxm];
Edge e[maxm];

void push_down(int now) {
	if(self.rev) {
		std::swap(self.ltid, self.rtid);
		lt.rev ^= 1;
		rt.rev ^= 1;
		self.rev = 0;
	}
}

void update(int now) {
	self.maxid = self.eid;
	if(e[lt.maxid].b > e[self.maxid].b)
		self.maxid = lt.maxid;
	if(e[rt.maxid].b > e[self.maxid].b)
		self.maxid = rt.maxid;
}

void rotate(int now) {
	int p = fa.faid, f = self.faid;
	push_down(p);
	push_down(f);
	push_down(now);

	bool right = fa.ltid == now;
	int s = right ? self.rtid : self.ltid;

	(right ? pool[f].ltid : pool[f].rtid) = s;
	if(s) pool[s].faid = f;

	(right ? self.rtid : self.ltid) = f;
	pool[f].faid = now;

	if(pool[p].ltid == f)
		pool[p].ltid = now;
	if(pool[p].rtid == f)
		pool[p].rtid = now;
	self.faid = p;

	update(f);
	update(now);
}

void splay(int now, int top) {
	while(self.faid != top) {
		if(fa.faid == top or (pool[fa.faid].ltid == self.faid) != (fa.ltid == now))
			rotate(now);
		else {
			rotate(self.faid);
			rotate(now);
		}
	}
}

int find_top(int now) {
	while(fa.ltid == now or fa.rtid == now)
		now = self.faid;
	return now;
}

void access(int now) {
	int last = 0;
	while(now) {
		splay(now, pool[find_top(now)].faid);
		push_down(now);
		self.rtid = last;
		update(now);
		last = now;
		now = self.faid;
	}
}

void makeroot(int now) {
	access(now);
	splay(now, 0);
	self.rev ^= 1;
}

void split(int now, int x) {
	makeroot(now);
	access(x);
	splay(now, 0);
}

void link(int now, int x) {
	/* debug("link %d %d\n", now, x); */
	makeroot(now);
	self.faid = x;
}

void cut(int now, int x) {
	/* debug("cut %d %d\n", now, x); */
	split(now, x);
	push_down(now);
	self.rtid = 0;
	update(now);
	pool[x].faid = 0;
}

int find_root(int now) {
	access(now);
	splay(now, 0);
	while(self.ltid)
		now = self.ltid;
	return now;
}

inline bool cmp(Edge a, Edge b) {
	return a.a < b.a;
}

int main() {
	int n = input(), m = input();

	for(int i = 1; i <= m; i ++) {
		e[i].x = input();
		e[i].y = input();
		e[i].a = input();
		e[i].b = input();
	}

	std::sort(e + 1, e + m + 1, cmp);

	int ans = 1000000000;
	for(int i = 1; i <= m; i ++) {
		pool[n + i].maxid = pool[n + i].eid = i;
		int x = e[i].x, y = e[i].y;

		/* debug("%d %d %d %d\n", x, y, e[i].a, e[i].b); */

		if(x == y)
			continue;

		if(find_root(x) == find_root(y)) {
			split(x, y);
			int eid = pool[x].maxid;
			if(e[i].b >= e[eid].b)
				continue;
			cut(e[eid].x, n + eid);
			cut(e[eid].y, n + eid);
		}

		link(x, n + i);
		link(y, n + i);

		/* for(int now = 1; now <= n + i; now ++) */
		/* 	debug("%d: %d %d %d| %d\n", now, self.ltid, self.rtid, self.faid, self.maxid); */

		if(find_root(1) == find_root(n)) {
			split(1, n);
			ans = std::min(ans, e[i].a + e[pool[1].maxid].b);
		}
	}

	printf("%d\n", ans == 1000000000 ? -1 : ans);
}
