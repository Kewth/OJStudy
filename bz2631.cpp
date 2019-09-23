#if 0
2019.09.18

LCT 维护动态树，区间懒标记即可。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

inline int input() { int x; scanf("%d", &x); return x; }

struct Splay {
	int size;
	unsigned val, sum;
	int ltid, rtid, faid;
	int rev;
	unsigned add, mul;
};

#define self pool[now]
#define lt pool[pool[now].ltid]
#define rt pool[pool[now].rtid]
#define fa pool[pool[now].faid]

const int maxn = 100005, mod = 51061;
Splay pool[maxn];

void MUL(int now, unsigned x) {
	(self.val *= x) %= mod;
	(self.sum *= x) %= mod;
	(self.mul *= x) %= mod;
	(self.add *= x) %= mod;
}

void ADD(int now, unsigned x) {
	(self.val += x) %= mod;
	(self.sum += x * (self.size % mod) % mod) %= mod;
	(self.add += x) %= mod;
}

void push_down(int now) {
	if(!now) return;
	if(self.rev) {
		std::swap(self.ltid, self.rtid);
		lt.rev ^= 1;
		rt.rev ^= 1;
	}
	MUL(self.ltid, self.mul);
	MUL(self.rtid, self.mul);
	ADD(self.ltid, self.add);
	ADD(self.rtid, self.add);
	self.add = self.rev = 0;
	self.mul = 1;
}

void update(int now) {
	if(!now) return;
	self.size = lt.size + rt.size + 1;
	self.sum = (lt.sum + rt.sum + self.val) % mod;
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
	update(now);
	pool[x].faid = 0;
}

int main() {
	int n = input(), q = input();

	for(int now = 1; now <= n; now ++)
		self.val = self.sum = self.mul = self.size = 1;

	for(int i = 1; i < n; i ++)
		link(input(), input());

	while(q --) {
		int op = getchar();
		if(op == '+') {
			int x = input(), y = input(), z = input();
			split(x, y);
			ADD(x, unsigned(z));
		}

		else if(op == '-') {
			cut(input(), input());
			link(input(), input());
		}

		else if(op == '*') {
			int x = input(), y = input(), z = input();
			split(x, y);
			MUL(x, unsigned(z));
		}

		else if(op == '/') {
			int now = input(), x = input();
			split(now, x);
			printf("%u\n", self.sum);
		}

		else
			q ++;
	}
}
