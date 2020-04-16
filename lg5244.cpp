#if 0
2020.04.15

求出每个点为末尾的最大偏序集大小，然后按这个分层，每层都是一条反链。
逐层 DP 设 f[i] 表示以 i 点为末尾的最优答案，可以发现每个点能转移的点是上一层的一段区间。
另外如果所有点都可以转移，那么同一层内的最优转移点是单调的。
把转移区间挂在线段树上，然后对于每个线段树节点做单调性分治 DP 即可。
#endif
#include <cstdio>
#include <algorithm>
#include <vector>
#include <functional>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator () (a...); }
} read;

const int maxn = 200005, maxm = 1000005;
struct Dot { int x, y; } d[maxn];
int f[maxn];
int bit[maxm];
std::vector<int> setx[maxn], sety[maxn];

int lim;
void modify (int p, int x) {
	for (int k = p; k <= lim; k += k & -k)
		bit[k] = std::max(bit[k], x);
}

int query (int p) {
	int res = 0;
	for (int k = p; k; k -= k & -k)
		res = std::max(res, bit[k]);
	return res;
}

Dot fd[maxn], gd[maxn];
ll F[maxn], G[maxn];
std::vector<int> qv[maxn << 2];
int tmp[maxn];

void insert_query (int now, int L, int R, int l, int r, int p) {
	if (r < L or l > R) return;
	if (l <= L and R <= r) return qv[now].push_back(p), void();
	int M = (L + R) >> 1;
	insert_query(now << 1, L, M, l, r, p);
	insert_query(now << 1 | 1, M + 1, R, l, r, p);
}

ll trans (int i, int j) {
	return G[j] + 1ll * (fd[i].x - gd[j].x) * (fd[i].y - gd[j].y);
}

void solve (int l, int r, int L, int R) {
	if (l > r) return;
	int mid = (l + r) >> 1, now = tmp[mid];
	int M = L;
	ll fnow = trans(now, M);
	for (int i = L + 1; i <= R; i ++) {
		ll t = trans(now, i);
		if (t < fnow) fnow = t, M = i;
	}
	F[now] = std::min(F[now], fnow);
	/* debug("%d -> %d\n", M, now); */
	solve(l, mid - 1, M, R);
	solve(mid + 1, r, L, M);
}

void seg_solve (int now, int L, int R) {
	int tp = 0;
	for (int p : qv[now]) tmp[++ tp] = p;
	qv[now].clear();
	solve(1, tp, L, R);
	if (L == R) return;
	int M = (L + R) >> 1;
	seg_solve(now << 1, L, M);
	seg_solve(now << 1 | 1, M + 1, R);
}

int main () {
	int n = read;
	read(lim);
	for (int i = 1; i <= n; i ++)
		read(d[i].x, d[i].y);
	std::sort(d + 1, d + n + 1, [] (Dot a, Dot b) {
				return a.x < b.x;
			});
	d[++ n] = {lim, lim};

	for (int i = 1; i <= n; i ++) {
		f[i] = query(d[i].y) + 1;
		modify(d[i].y, f[i]);
		setx[f[i]].push_back(+d[i].x);
		sety[f[i]].push_back(-d[i].y);
		/* debug("%d %d %d\n", d[i].x, d[i].y, f[i]); */
	}

	/* for (int i = 1; i <= n; i ++) { */
	/* 	std::sort(setx[i].begin(), setx[i].end()); */
	/* 	std::sort(sety[i].begin(), sety[i].end(), std::greater<int> ()); */
	/* } */

	setx[0].push_back(0);
	sety[0].push_back(0);
	fd[1] = {0, 0};

	for (int v = 1; v <= n; v ++) {
		size_t sz = setx[v].size();
		if (!sz) break;
		int la = int(setx[v - 1].size());
		for (int i = 1; i <= la; i ++)
			gd[i] = fd[i], G[i] = F[i];
		/* debug("work %d\n", v); */
		for (size_t i = 0; i < sz; i ++) {
			int p = int(i + 1), x = +setx[v][i], y = -sety[v][i];
			fd[p] = {x, y};
			F[p] = 1000000000000000000;
			int l = int(std::lower_bound(sety[v - 1].begin(), sety[v - 1].end(), -y)
					- sety[v - 1].begin()) + 1;
			int r = int(std::upper_bound(setx[v - 1].begin(), setx[v - 1].end(), +x)
					- setx[v - 1].begin());
			/* debug("%d %d | %d %d %d\n", x, y, p, l, r); */
			if (l > r) return 1;
			insert_query(1, 1, la, l, r, p);
			/* F[p] = 100000000000000000; */
			/* for (int j = l; j <= r; j ++) */
			/* 	F[p] = std::min(F[p], trans(p, j)); */
		}
		seg_solve(1, 1, la);
		/* for (int i = 1; i <= int(sz); i ++) */
		/* 	debug("%lld\n", F[i]); */
	}

	printf("%lld\n", F[1]);
}
