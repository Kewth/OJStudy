/*
 * Since g++10 is released, some characters is not valid inside #if 0 :(
 * So, why not using clang++? :D

 * Date:
  2020.07.14

 * Solution:
 * 边分治，二分答案

  不难想到先求出 f[u] 表示对于所有服务节点 x 中 waste(u, x) 的最大值。那么二分答案 X 的
时候只需要考虑 f[u] < X 的所有用户节点 u 是否能通过更改的节点满足要求。

  考虑如何求 f ，可以使用边分治，将两个路径拼接时，设它们的最值分别为 [L1, R1] 和
[L2, R2] ，那么拼接后路径的极差就是 max(R1, R2) - min(L1, L2) ，根据加减法对 min/max 的
分配率，可以分为四种情况，分别考虑即可。

  然后考虑对于二分的答案 X 判断是否可行，也就是判断是否存在一个关键节点 u 满足对任意满足
f[x] < X 的用户节点 x 都有 waste(u, x) >= X 。仍然可以使用边分治，如果对于一个点 u ，存
在用户节点 x 满足 f[x] < X 且 waste(u, x) < X ，就称 x 覆盖了 u 。用边分治维护这个覆盖，
将路径拼接中的 min(L1, L2) 分 L1 <= L2 和 L1 > L2 两种情况讨论即可，最后没有被覆盖的点就
是合法的关键节点。

 * Digression:
  复杂度 O(n logn logC) ，但是边分治常数很大很大很大，实际运行时间 7s+ 。在找到常数更优
秀的边分治实现前先这样吧。另外值得注意的是菊花图上运行时间只有 2s+ ，而两者在瓶颈部分的
运行次数是没有太大差异的，或许这个常数都在 cache miss 上去了？

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

#pragma GCC optimize(3)
#include <cstdio>
#include <algorithm>
#include <vector>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef size_t si;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	/* inline operator ll () { ll x; return scanf("%lld", &x), x; } */
	template<class T> inline void operator () (T &x) { x = *this; }
	/* template<class T, class ...A> inline void operator () (T &x, A &...a) */
	/* { x = *this; this -> operator () (a...); } */
} read;

const int maxn = 200005, inf = 1000000000;
int head[maxn], nxt[maxn << 1], to[maxn << 1], val[maxn << 1], hp = 1;
int las[maxn], np;
int typ[maxn];
int size[maxn];
bool ban[maxn];
int f[maxn];
int dx[maxn], dy[maxn];
int dls[maxn], drs[maxn], dsize[maxn];
std::vector<int> dl[maxn], dr[maxn];

inline void add (int u, int v, int w) {
	/* if (u < v) debug("%d %d %d\n", u, v, w); */
	nxt[++ hp] = head[u];
	head[u] = hp;
	to[hp] = v;
	val[hp] = w;
}

inline void expand (int u) {
	if (las[u]) {
		typ[++ np] = 2;
		add(las[u], np, -1);
		add(np, las[u], -1);
		las[u] = np;
	} else
		las[u] = u;
}

int cen, censize;
void findcen (int u, int fe, int n) {
	size[u] = 1;
	for (int i = head[u]; i; i = nxt[i])
		if ((i >> 1) != fe and !ban[i >> 1]) {
			/* debug("%d %d\n", u, to[i]); */
			findcen(to[i], i >> 1, n);
			size[u] += size[to[i]];
		}
	int now = std::max(n - size[u], size[u]);
	if (now < censize) cen = fe, censize = now;
}

int L[maxn], R[maxn];
void dfs1 (int u, int fe, std::vector<int> *tar) {
	/* debug("%d : %d %d\n", u, L[u], R[u]); */
	if (tar) tar -> push_back(u);
	for (int i = head[u]; i; i = nxt[i])
		if ((i >> 1) != fe and !ban[i >> 1]) {
			int v = to[i], w = val[i];
			if (~w) {
				L[v] = std::min(L[u], w);
				R[v] = std::max(R[u], w);
			} else
				L[v] = L[u], R[v] = R[u];
			dfs1(v, i >> 1, tar);
		}
}

void update (std::vector<int> &X, std::vector<int> &Y) {
	int min = inf, max = 0, has = 0, d = 0;
	for (int u : Y)
		if (typ[u] == 1) {
			min = std::min(min, L[u]);
			max = std::max(max, R[u]);
			d = std::max(d, R[u] - L[u]);
			has = 1;
		}
	if (has)
		for (int u : X)
			f[u] = std::max({f[u], R[u] - L[u], R[u] - min, max - L[u], d});
}

bool cmp (int x, int y) { return L[x] < L[y]; }

int divide (int s, int n) {
	if (n == 1) return 0;

	/* debug("div %d\n", n); */
	cen = 0, censize = maxn;
	findcen(s, 0, n);
	int x = to[cen << 1], y = to[cen << 1 | 1];
	if (size[x] < size[y]) std::swap(x, y);
	dx[cen] = x, dy[cen] = y;
	/* debug("div %d %d\n", x, y); */

	if (~val[cen << 1])
		L[x] = L[y] = R[x] = R[y] = val[cen << 1];
	else
		L[x] = L[y] = inf, R[x] = R[y] = 0;

	dfs1(x, cen, dl + cen);
	dfs1(y, cen, dr + cen);

	std::sort(dl[cen].begin(), dl[cen].end(), cmp);
	std::sort(dr[cen].begin(), dr[cen].end(), cmp);

	update(dl[cen], dr[cen]);
	update(dr[cen], dl[cen]);

	dsize[cen] = n;
	ban[cen] = 1;
	int tmp = size[y], e = cen;
	dls[e] = divide(x, n - tmp);
	drs[e] = divide(y, tmp);

	return e;
}

int THR;
bool shit[maxn];
int pre[maxn], suf[maxn];
void solve (std::vector<int> &X, std::vector<int> &Y) {
	for (si i = 0; i < Y.size(); i ++) {
		int u = Y[i], laspre = i ? pre[i - 1] : - inf;
		pre[i] = (typ[u] == 0 and f[u] < THR and R[u] - L[u] < THR) ?
			std::max(laspre, L[u]) : laspre;
	}
	suf[Y.size()] = inf << 1;
	for (si i = Y.size(); i; i --) {
		int u = Y[i - 1];
		suf[i - 1] = (typ[u] == 0 and f[u] < THR) ?
			std::min(suf[i], R[u]) : suf[i];
	}
	si i = 0;
	for (int u : X)
		if (typ[u] == 0) {
			while (i < Y.size() and L[Y[i]] <= L[u]) ++ i;
			if (i and R[u] - pre[i - 1] < THR) shit[u] = 1;
			if (i < Y.size() and std::max(R[u], suf[i]) - L[u] < THR) shit[u] = 1;
		}
}

void divi (int e) {
	if (!e) return;

	int x = dx[e], y = dy[e];
	/* debug("div %d %d\n", x, y); */
	if (~val[e << 1])
		L[x] = L[y] = R[x] = R[y] = val[e << 1];
	else
		L[x] = L[y] = inf, R[x] = R[y] = 0;
	dfs1(x, e, nullptr);
	dfs1(y, e, nullptr);

	solve(dl[e], dr[e]);
	solve(dr[e], dl[e]);

	ban[e] = 1;
	divi(dls[e]);
	divi(drs[e]);
}

int ANS;
bool check () {
	std::fill(ban, ban + hp / 2 + 1, 0);
	std::fill(shit, shit + np + 1, 0);
	divi(cen);
	ANS = 0;
	for (int u = np; u; u --)
		if (typ[u] == 0 and !shit[u])
			ANS = u;
	return ANS;
}

int main () {
	int n = np = read;
	for (int i = 1; i <= n; i ++) read(typ[i]);
	for (int i = 1; i < n; i ++) {
		int u = read, v = read, w = read;
		expand(u);
		expand(v);
		add(las[u], las[v], w);
		add(las[v], las[u], w);
	}

	cen = divide(1, np);
	/* for (int i = 1; i <= np; i ++) */
		/* debug("%d\n", f[i]); */

	int l = 0, r = inf;
	while (l < r) {
		THR = (l + r + 1) >> 1;
		/* debug("THR = %d\n", THR); */
		if (check()) l = THR;
		else r = THR - 1;
	}

	THR = l;
	/* debug("FINDAL %d\n", THR); */
	check();
	printf("%d %d\n", ANS, THR == inf ? 0 : THR);
}
