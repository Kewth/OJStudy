#if 0
2019.09.18

LCT 维护动态图。
将 x 弹到 y 的关系连边建图，特别地建一个节点 X 连接弹飞的点。
每次询问 x 就将 x 到 X 之间的链提出来求大小。
修改就是动态树常规操作删边加边。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

inline int input() { int x; scanf("%d", &x); return x; }

struct Splay {
	int size;
	int ltid, rtid, faid;
	int rev;
	Splay(): size(1), ltid(0), rtid(0), faid(0), rev(0) { }
};
#define self pool[now]
#define lt pool[pool[now].ltid]
#define rt pool[pool[now].rtid]
#define fa pool[pool[now].faid]

const int maxn = 200005;
Splay pool[maxn];

void print(int now) {
	debug("%d: l=%d, r=%d, f=%d, s=%d, rev=%d\n",
			now, self.ltid, self.rtid, self.faid, self.size, self.rev);
}

void push_down(int now) {
	if(self.rev and now) {
		std::swap(self.ltid, self.rtid);
		lt.rev ^= 1;
		rt.rev ^= 1;
		self.rev = 0;
	}
}

void update(int now) {
	if(now)
		self.size = lt.size + rt.size + 1;
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

	(right ? pool[now].rtid : pool[now].ltid) = f;
	pool[f].faid = now;

	if(pool[p].ltid == f)
		pool[p].ltid = now;
	if(pool[p].rtid == f)
		pool[p].rtid = now;
	pool[now].faid = p;

	update(f);
	update(now);
}

void splay(int now, int top) {
	while(self.faid != top) {
		if(fa.faid == top)
			rotate(now);
		else if((pool[fa.faid].ltid == self.faid) == (fa.ltid == now)) {
			rotate(self.faid);
			rotate(now);
		} else
			rotate(now);
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
	makeroot(x);
	access(now);
	splay(now, 0);
}


void link(int now, int x) {
	makeroot(now);
	self.faid = x;
}
void cut(int now, int x) {
	split(now, x);
	push_down(now);
	self.ltid = 0;
	update(now);
	pool[x].faid = 0;
}

int a[maxn];

int main() {
	int n = input();
	for(int i = 1; i <= n; i ++)
		a[i] = std::min(n + 1 - i, input());

	pool[0].size = 0;

	for(int i = 1; i <= n; i ++)
		link(i, i + a[i]);

	int q = input();
	while(q --) {
		if(input() == 1) {
			int x = input() + 1;
			split(x, n + 1);
			printf("%d\n", pool[x].size - 1);
		}

		else {
			int x = input() + 1;
			cut(x, x + a[x]);
			a[x] = std::min(n + 1 - x, input());
			link(x, x + a[x]);
		}
	}
}
