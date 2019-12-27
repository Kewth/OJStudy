#if 0
2019.12.26

询问就是问 (x, y) 两边子树大小的乘积，
动态加边可以用 lct 维护，但是一般来讲 lct 只能维护链上信息，而这里需要询问子树大小。
每个点维护 isize 表示虚儿子的 size 和，此时 size 包括 isize 。
这样的话由于虚儿子对父亲有影响，有两个地方与普通 lct 不同：
1) access 的时候每次换儿子需要维护 isize
2) link 的时候需要维护 isize ，且 link 的两个点都必须是根的 splay 的顶端，才能保证只会影响一个点。

另外 update 了一下 lct 的写法，然而代码长度和时间效率都并没有什么优化。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	inline operator char () { char x[3]; return scanf("%s", x), *x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
} read;

struct Splay {
	int size, isize;
	int lti, rti, fai;
	int rev;
	inline int &son(bool x) { return x ? rti : lti; }
};
#define self pool[now]
#define lt pool[self.lti]
#define rt pool[self.rti]
#define fa pool[self.fai]
const int maxn = 100005;
Splay pool[maxn];

inline void print(int now) {
	debug("%d: s=%d, is=%d l=%d r=%d f=%d r=%d\n",
			now, self.size, self.isize,
			self.lti, self.rti, self.fai, self.rev);
}

inline void push_down(int now) {
	if(self.rev and now) {
		std::swap(self.lti, self.rti);
		lt.rev ^= 1;
		rt.rev ^= 1;
		self.rev = 0;
	}
}

inline void update(int now) {
	self.size = lt.size + rt.size + self.isize + 1;
}

inline bool from(int now) { return fa.rti == now; }
inline bool isroot(int now) { return fa.lti != now and fa.rti != now; }

void rotate(int now) {
	int p = fa.fai, f = self.fai, fr = from(now), s = fr ? self.lti : self.rti;

	if(!isroot(f)) pool[p].son(from(f)) = now;
	pool[f].son(fr) = s;
	self.son(!fr) = f;

	pool[s].fai = f;
	self.fai = p;
	pool[f].fai = now;

	update(f);
	update(now);
}

int stack[maxn], sp;
void splay(int now) {
	stack[++ sp] = now;
	for(int x = now; !isroot(x); x = pool[x].fai)
		stack[++ sp] = pool[x].fai;
	while(sp) push_down(stack[sp --]);
	while(!isroot(now)) {
		if(!isroot(self.fai))
			rotate(from(self.fai) == from(now) ? self.fai : now);
		rotate(now);
	}
}

void access(int now) {
	for(int last = 0; now; last = now, now = self.fai) {
		splay(now);
		self.isize += rt.size;
		self.rti = last;
		self.isize -= rt.size;
		update(now);
	}
}

void makeroot(int now) {
	access(now);
	splay(now);
	self.rev ^= 1;
}

void split(int now, int x) {
	makeroot(x);
	access(now);
	splay(now);
}

void link(int now, int x) {
	split(x, now);
	self.fai = x;
	pool[x].isize += self.size;
	update(x);
}

int main() {
	int n = read, q = read;

	for(int now = 1; now <= n; now ++)
		self.size = 1;

	while(q --) {
		if(char(read) == 'A') {
			int x = read, y = read;
			link(x, y);
		}

		else {
			int x = read, y = read;
			split(x, y);
			int size = pool[x].size;
			printf("%lld\n", 1ll * pool[y].size * (size - pool[y].size));
		}

		/* for(int now = 1; now <= n; now ++) */
		/* 	print(now); */
		/* debug("\n"); */
	}
}
