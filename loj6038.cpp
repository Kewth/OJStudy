/*
 * Since g++10 is released, some characters is not valid inside #if 0 :(
 * So, why not using clang++? :D

 * Date:
  2020.06.10

 * Solution:
  维护每个联通块的直径即可，一个点的最远点一定是直径的一个端点。
  但是强制在线，没有什么好的方法快速求两个点的距离，只能 lct 维护。

 * Digression:
  吐了，lct 果然难调，一个小错误能调一年。

 * CopyRight:
          ▁▃▄▄▄▃▃▃▃▄▶
        ▗▇▀▔    ▔▔▔▔
       ▄▛   ▃▅━━■▄▂
      ▟▊   ▐▘     ▀▙
     ▟▜▌   ▐▖   ▋  ▐▍
    ▟▘ ▜   ▝▀▇▆●▘  ▐▌
  ▗▟▘   ▜▃       ▁▅▛
  ▔▀▼▅▄▃▃██▅▄▄▄▅■▀▔
        ▔▔▔▔▔▔
 */

#include <cstdio>
#include <cassert>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 300005;
struct Splay {
	int lti, rti, fai;
	int size;
	int rev;
} pool[maxn];
#define self pool[now]
#define lt pool[self.lti]
#define rt pool[self.rti]
#define fa pool[self.fai]
inline int from (int now) { return fa.rti == now; }
inline bool isroot (int now) { return fa.lti != now and fa.rti != now; }

inline void update (int now) { self.size = lt.size + rt.size + 1; }

/* void print (const char *s) { */
/* 	debug("%s\n", s); */
/* 	for (int now = 1; now <= 5; now ++) */
/* 		if (now != 2) */
/* 		debug("%d : {%d %d} f=%d s=%d r=%d\n", */
/* 				now, self.lti, self.rti, self.fai, self.size, self.rev); */
/* 	debug("\n"); */
/* } */

void push (int now) {
	if (now and self.rev) {
		std::swap(self.lti, self.rti);
		lt.rev ^= 1;
		rt.rev ^= 1;
		self.rev = 0;
	}
}

void rotate (int now) {
	int p = fa.fai, f = self.fai, fr = from(now), s = fr ? self.lti : self.rti;
	// XXX: 艹，这玩意调了一年。
	/* if (p) (from(f) ? pool[p].rti : pool[p].lti) = now; */
	if (!isroot(f)) (from(f) ? pool[p].rti : pool[p].lti) = now;
	(fr ? pool[f].rti : pool[f].lti) = s;
	(fr ? self.lti : self.rti) = f;
	pool[s].fai = f;
	self.fai = p;
	pool[f].fai = now;
	update(f);
	update(now);
}

int stack[maxn], sp;
void splay (int now) {
	stack[++ sp] = now;
	for (int x = now; !isroot(x); x = stack[sp])
		stack[++ sp] = pool[x].fai;
	while (sp) push(stack[sp --]);
	while (!isroot(now)) {
		if (!isroot(self.fai))
			rotate(from(now) == from(self.fai) ? self.fai : now);
		rotate(now);
	}
}

void access (int now) {
	int bak = now;
	for (int las = 0; now; now = self.fai) {
		splay(now);
		self.rti = las;
		if (las) assert(pool[las].fai == now);
		update(now);
		las = now;
	}
	splay(bak);
}

inline void makeroot (int now) { access(now), self.rev ^= 1; }

int dis (int x, int y) {
	makeroot(x);
	access(y);
	return pool[y].size - 1;
}

int top[maxn], px[maxn], py[maxn], pd[maxn];
inline int find (int x) { return top[x] == x ? x : top[x] = find(top[x]); }

int main () {
	int t = read;
	int n = read, q = read, ans = 0;
	for (int now = 1; now <= n; now ++)
		self.size = 1;

	for (int i = 1; i <= n; i ++) top[i] = px[i] = py[i] = i;

	while (q --) {
		int o = read;
		if (o == 1) {
			int x = read, y = read;
			if (t) x ^= ans, y ^= ans;
			if (x < 1 or x > n) return 1;
			if (y < 1 or y > n) return 1;
			makeroot(x);
			pool[x].fai = y;
			x = find(x);
			y = find(y);
			top[x] = y;
			int tmp;
			if ((tmp = dis(px[x], px[y])) > pd[y])
				pd[y] = tmp, std::swap(py[y], px[x]);
			/* debug("%d -> %d (%d %d %d)\n", x, y, px[y], py[y], pd[y]); */
			if ((tmp = dis(px[x], py[y])) > pd[y])
				pd[y] = tmp, px[y] = px[x];
			/* debug("%d -> %d (%d %d %d)\n", x, y, px[y], py[y], pd[y]); */
			if ((tmp = dis(py[x], px[y])) > pd[y])
				pd[y] = tmp, std::swap(py[y], py[x]);
			/* debug("%d -> %d (%d %d %d)\n", x, y, px[y], py[y], pd[y]); */
			if ((tmp = dis(py[x], py[y])) > pd[y])
				pd[y] = tmp, px[y] = py[x];
			/* debug("%d -> %d (%d %d %d)\n", x, y, px[y], py[y], pd[y]); */
			/* debug("\n"); */
		}
		if (o == 2) {
			int x = read;
			if (t) x ^= ans;
			int tx = find(x);
			/* debug("query in %d %d\n", px[tx], py[tx]); */
			printf("%d\n", ans = std::max(dis(x, px[tx]), dis(x, py[tx])));
		}
	}
}
