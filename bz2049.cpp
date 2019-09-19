#if 0
2019.09.18

LCT 维护动态图，查询 x, y 连通性判断两点所在树的根是否相同。
实现一个 find_root() ， access() 后一直跳到深度最小的点即可。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

inline int input() { int x; scanf("%d", &x); return x; }

struct Splay {
	int ltid, rtid, faid;
	int rev;
};

#define self pool[now]
#define lt pool[pool[now].ltid]
#define rt pool[pool[now].rtid]
#define fa pool[pool[now].faid]

const int maxn = 10050;
Splay pool[maxn];

void push_down(int now) {
	if(self.rev and now) {
		std::swap(self.ltid, self.rtid);
		lt.rev ^= 1;
		rt.rev ^= 1;
		self.rev = 0;
	}
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
	/* makeroot(x); */
	/* access(now); */
	makeroot(now);
	access(x);
	splay(now, 0);
}

void link(int now, int x) {
	makeroot(now);
	self.faid = x;
}

void cut(int now, int x) {
	split(now, x);
	push_down(now);
	self.rtid = 0;
	pool[x].faid = 0;
}

int find_root(int now) {
	access(now);
	splay(now, 0);
	while(self.ltid)
		now = self.ltid;
	return now;
}

int main() {
	int n = input(), q = input();
	while(q --) {
		char op[10];
		scanf("%s", op);
		if(*op == 'Q') {
			if(find_root(input()) == find_root(input()))
				puts("Yes");
			else
				puts("No");
		}

		else if(*op == 'C')
			link(input(), input());

		else if(*op == 'D')
			cut(input(), input());
	}
}
