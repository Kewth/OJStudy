#if 0
2020.04.05

本质上是维护有多少不同的前缀最大值，同 uoj515 。
#endif
#include <cstdio>
#include <algorithm>
/* #include <vector> */
#include <cstdlib>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct Inputer {
	static char buffer[32 * 1024 * 1024], *p;
	inline operator int () { return int(strtol(p, &p, 10)); }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
	Inputer() { fread(buffer, 1, sizeof buffer, stdin); }
} read;
char *Inputer::p = Inputer::buffer;
char Inputer::buffer[] = {};

struct ld {
	int y, x;
};
bool operator < (ld a, ld b) {
	return 1ll * a.y * b.x < 1ll * b.y * a.x;
	/* return a.x * b.x > 0 ? */
	/* 	1ll * a.y * b.x < 1ll * b.y * a.x : */
	/* 	1ll * a.y * b.x > 1ll * b.y * a.x; */
}

const int maxn = 100005;
int ohead[maxn], onxt[maxn];
ld ox[maxn];
// vector 吃屎系列。
/* struct op { */
/* 	int t, x; */
/* }; */
/* std::vector<op> ov[maxn]; */
/* std::vector<int> qv[maxn]; */
ld max[maxn << 2], semax[maxn << 2];
int tag[maxn << 2];
#define ls (now << 1)
#define rs (now << 1 | 1)

inline void update (int now) {
	max[now] = std::max(max[ls], max[rs]);
	semax[now] = std::max(
			max[ls] < max[now] ? max[ls] : semax[ls],
			max[rs] < max[now] ? max[rs] : semax[rs]);
}

inline bool modi (int now, ld x, int y) {
	return semax[now] < x and x < max[now] ? max[now] = x, tag[now] += y, 1 : 0;
}

inline void push_down (int now) {
	if (tag[now]) {
		modi(ls, max[now], tag[now]);
		modi(rs, max[now], tag[now]);
		tag[now] = 0;
	}
}

void modify (int now, int L, int R, int l, int r, ld x) {
	/* debug("%d %d %d | %d/%d | %d/%d\n", now, L, R, */
	/* 		max[now].y, max[now].x, x.y, x.x); */
	/* if (x >= max[now]) return; */
	if (!(x < max[now])) return;
	if (l <= L and R <= r and modi(now, x, 1)) return;
	int M = (L + R) >> 1;
	push_down(now);
	if (l <= M) modify(ls, L, M, l, r, x);
	if (r > M) modify(rs, M + 1, R, l, r, x);
	update(now);
}

void query (int now, int L, int R) {
	if (L == R) return printf("%d\n", tag[now]), void();
	int M = (L + R) >> 1;
	push_down(now);
	query(ls, L, M);
	query(rs, M + 1, R);
}

int main () {
	int n = read, q = read;
	for (int i = 1; i <= q; i ++) {
		int p = read;
		onxt[i] = ohead[p];
		ohead[p] = i;
		ox[i] = {-read, p};
	}

	std::fill(max, max + q * 4, ld({0, 1}));
	std::fill(semax, semax + q * 4, ld({-1000000000, 1}));

	for (int i = 1; i <= n; i ++) {
		int las = q + 1;
		for (int t = ohead[i]; t; t = onxt[t])
			modify(1, 1, q, t, las - 1, ox[t]), las = t;
		/* if (las > 1) */
		/* 	modify(1, 1, q, 1, las - 1, {0, 1}); */
	}

	query(1, 1, q);
}
