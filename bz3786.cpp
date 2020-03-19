#if 0
2020.01.19

垃圾 ETT 毁我青春。
splay 维护括号序，一个常见 trick 是把区间平移用区间翻转来维护。
细节挺多，代码挺长。
#endif
#include <cstdio>
#include <algorithm>
#include <vector>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator char () { char x[3]; return scanf("%s", x), *x; }
} read;

const int maxn = 100005;
struct Splay {
	int fai;
	int lti, rti;
	int rev;
	ll val, sum, tag;
	int sval, ssum;
};
Splay pool[maxn << 1];
#define self pool[now]
#define lt pool[self.lti]
#define rt pool[self.rti]
#define fa pool[self.fai]

inline void add(int now, ll x) {
	if(now) {
		self.val += x * self.sval;
		self.sum += x * self.ssum;
		self.tag += x;
	}
}

inline void flip(int now) {
	if(now) {
		std::swap(self.lti, self.rti);
		self.rev ^= 1;
	}
}

inline void push_down(int now) {
	if(self.tag) {
		add(self.lti, self.tag);
		add(self.rti, self.tag);
		self.tag = 0;
	}
	if(self.rev) {
		flip(self.lti);
		flip(self.rti);
		self.rev = 0;
	}
}

inline void update(int now) {
	self.ssum = lt.ssum + self.sval + rt.ssum;
	self.sum = lt.sum + self.val + rt.sum;
	/* self.size = lt.size + rt.size + 1; */
}

inline bool from(int now) { return fa.rti == now; }

void rotate(int now) {
	int p = fa.fai, f = self.fai, fr = from(now), s = fr ? self.lti : self.rti;

	if(p) (from(f) ? pool[p].rti : pool[p].lti) = now;
	(fr ? pool[f].rti : pool[f].lti) = s;
	(fr ? self.lti : self.rti) = f;

	pool[s].fai = f;
	pool[f].fai = now;
	self.fai = p;

	update(f);
	update(now);
}

int stack[maxn << 1], sp;
void splay(int now, int top) {
	stack[++ sp] = now;
	for(int x = now; x != top; x = stack[sp])
		stack[++ sp] = pool[x].fai;
	while(sp) push_down(stack[sp --]);
	while(self.fai != top) {
		if(fa.fai != top) rotate(from(now) == from(self.fai) ? self.fai : now);
		rotate(now);
	}
}

/* inline int id(int x) { return x > maxn ? maxn - x : x; } */
/* void print(int now, int d) { */
/* 	if(!now) return; */
/* 	print(self.lti, d + 1); */
/* 	for(int i = 0; i < d; i ++) */
/* 		debug(" "); */
/* 	debug("% d: f=%d re=%d su=%lld ssum=%d tg=%lld\n", */
/* 			id(now), id(self.fai), self.rev, self.sum, self.ssum, self.tag); */
/* 	print(self.rti, d + 1); */
/* } */
/* int ROOT() { */
/* 	int now = 1; */
/* 	while(self.fai) */
/* 		now = self.fai; */
/* 	return now; */
/* } */
/* #define test print(ROOT(), 0), debug("\n") */

inline void flipnxttoend(int now) {
	splay(now, 0);
	flip(self.rti);
}

inline void flipnowtoend(int now) {
	splay(now, 0);
	if(self.lti) {
		push_down(now = self.lti);
		while(self.rti)
			// 没 push_down 去世了
			push_down(now = self.rti);
		flipnxttoend(now);
	}
}

void reset_fa(int y, int x) {
	flipnxttoend(maxn + y);
	flipnowtoend(y);
	flipnxttoend(x);
	flipnxttoend(maxn + y);
}

std::vector<int> G[maxn];
void dfs(int u, int &now) {
	if(now) {
		self.rti = u;
		rt.fai = now;
		update(now);
		rotate(u);
	}
	now = u;
	for(int v : G[u])
		dfs(v, now);
	self.rti = maxn + u;
	rt.fai = now;
	update(now);
	rotate(maxn + u);
	now = maxn + u;
}

int main() {
	int n = read;
	for(int i = 2; i <= n; i ++)
		G[int(read)].push_back(i);
	for(int i = 1; i <= n; i ++) {
		int x = read;
		int now = i;
		self.val = self.sum = x;
		self.sval = self.ssum = 1;
		now = maxn + i;
		self.val = self.sum = - x;
		self.sval = self.ssum = -1;
	}

	int root = 0;
	dfs(1, root);

	int q = read;
	while(q --) {
		char o = read;

		if(o == 'Q') {
			int now = read;
			splay(now, 0);
			printf("%lld\n", self.sum - rt.sum);
		}

		if(o == 'C') {
			int y = read, x = read;
			reset_fa(y, x);
		}

		if(o == 'F') {
			int now = read, x = read;
			splay(maxn + now, 0);
			splay(now, maxn + now);

			add(maxn + now, x);

			push_down(maxn + now);
			add(pool[maxn + now].rti, -x);

			/* if(pool[maxn + now].lti != now) */
			/* 	return 2; */

			push_down(now);
			add(pool[now].lti, -x);

			update(now);
			update(maxn + now);
		}

		/* if(pool[ROOT()].sum) */
		/* 	return 1; */
	}
}
