/*
 * Since g++10 is released, some characters is not valid inside #if 0 :(
 * So, why not using clang++? :D

 * Date:
  2020.06.06

 * Solution:
  不妨假设 T 在 S 的右下方，那么最终的路径只有两种情况，要么是只走下左右，要么只走右上下，
不妨假设走的是下左右，也就是忽略向上走的可能。
  如果所有矩形都在 sy 和 ty 之间，这个问题就很经典，用扫描线 + odt 或者线段树维护每个矩形
的左上角和右上角的最短路即可。但是麻烦的是矩形可能可以和 y = sy 和 y = ty 两条直线相交，
这样一来就复杂了许多。一个很妙的结论是如果在这三种方向上存在合法解，就可以把 y > sy 和 y
< ty 的部分直接切掉而避免这个问题，而判断是否存在合法路径只需要从另一个维护用扫描线 + odt
或者线段树做几乎同样的事情即可。

 * Digression:
  实现上可以翻转坐标轴。

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
#include <algorithm>
#include <set>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct _{
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
} read;

const int maxn = 250005, inf = 1000000000;
struct Squ {
	int x1, y1, x2, y2;
} s[maxn];
int lans[maxn], rans[maxn];

bool cmpy2 (Squ a, Squ b) { return a.y2 < b.y2; }
bool cmpx1 (Squ a, Squ b) { return a.x1 < b.x1; }
bool cmpx2 (Squ a, Squ b) { return a.x2 < b.x2; }

struct Node {
	int l, r;
	int v;
	Node (int l, int r, int v): l(l), r(r), v(v) { }
};
typedef std::set<Node>::iterator iter;
std::set<Node> odt;
bool operator < (Node a, Node b) { return a.l < b.l; }

iter split (int x) {
	iter it = -- odt.upper_bound(Node(x, 0, 0));
	if (it -> l == x) return it;
	int l = it -> l, r = it -> r, v = it -> v;
	odt.erase(it);
	odt.insert(Node(l, x - 1, v));
	return odt.insert(Node(x, r, v)).first;
}

int solve (int n, int sx, int sy, int tx, int ty) {
	if (sx > tx) std::swap(sx, tx), std::swap(sy, ty);

	std::sort(s + 1, s + n + 1, cmpx1);
	odt.clear();
	odt.insert(Node(0, inf, 0));
	for (int i = n; i and s[i].x1 > sx; i --) {
		if (s[i].x1 < tx) {
			iter en = split(s[i].y2 + 1), be = split(s[i].y1);
			int fir = be -> v;
			odt.erase(be, en);
			odt.insert(Node(s[i].y1, s[i].y2, i));
			if (fir == 0)
				lans[i] = s[i].y1 > ty;
			else
				lans[i] = lans[fir];
		}
	}

	int shit = split(sy) -> v;
	if (shit and !lans[shit]) return inf;

	if (sy < ty) std::swap(sx, tx), std::swap(sy, ty);

	++ n;
	s[n].x1 = s[n].x2 = sx;
	s[n].y1 = s[n].y2 = sy;

	std::sort(s + 1, s + n + 1, cmpy2);
	odt.clear();
	odt.insert(Node(0, inf, 0));

	int p = n;
	while (s[p].y1 != s[p].y2) -- p;
	for (int i = 1; i <= p; i ++)
		if (s[i].y2 > ty) {
			iter en = split(s[i].x2 + 1), be = split(s[i].x1);
			int fir = be -> v, las = (--en) -> v;
			odt.erase(be, ++ en);
			odt.insert(Node(s[i].x1, s[i].x2, i));
			if (fir == 0)
				lans[i] = s[i].y2 - ty + std::abs(tx - s[i].x1);
			else
				lans[i] = s[i].y2 - s[fir].y2 + std::min(
						s[i].x1 - s[fir].x1 + lans[fir], s[fir].x2 - s[i].x1 + rans[fir]);
			if (las == 0)
				rans[i] = s[i].y2 - ty + std::abs(tx - s[i].x2);
			else
				rans[i] = s[i].y2 - s[las].y2 + std::min(
						s[i].x2 - s[las].x1 + lans[las], s[las].x2 - s[i].x2 + rans[las]);
			/* debug("%d %d %d %d -> %d %d\n", */
			/* 		s[i].x1, s[i].y1, s[i].x2, s[i].y2, lans[i], rans[i]); */
		} else
			lans[i] = rans[i] = inf;

	std::swap(s[p], s[n]);
	return std::min(lans[p], rans[p]);
}

int main () {
#ifndef ONLINE_JUDGE
	freopen("travel.in", "r", stdin);
	freopen("travel.out", "w", stdout);
#endif

	int n = read, sx = read, sy = read, tx = read, ty = read;

	for (int i = 1; i <= n; i ++) {
		s[i].x1 = read;
		s[i].y1 = read;
		s[i].x2 = read;
		s[i].y2 = read;
	}

	if ((sx > tx) == (sy > ty)) {
		int M = 100000000;
		sx = M - sx;
		tx = M - tx;
		for (int i = 1; i <= n; i ++) {
			int x1 = s[i].x1, x2 = s[i].x2;
			s[i].x1 = M - x2;
			s[i].x2 = M - x1;
		}
	}

	int a = solve(n, sx, sy, tx, ty);

	for (int i = 1; i <= n; i ++) {
		std::swap(s[i].x1, s[i].y1);
		std::swap(s[i].x2, s[i].y2);
	}

	int b = solve(n, sy, sx, ty, tx);

	printf("%d\n", std::min(a, b));
	debug("%d %d\n", a, b);
}
