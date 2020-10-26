/*
 * Author: Kewth

 * Date:
  2020.10.22

 * Solution:
  In blog.

 * Digression:

 * CopyRight:
   __  __                  __   __
  |  |/  |.-----.--.--.--.|  |_|  |--.
  |     < |  -__|  |  |  ||   _|     |
  |__|\__||_____|________||____|__|__|

 */

#include <cstdio>
#include <algorithm>
#include <vector>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

static struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator () (a...); }
} read;

const int maxn = 200005, maxd = 1000005, D = 1000000;
struct rectangle {
	int x1, y1, x2, y2;
} rec[maxn];
struct point {
	int x, y, i;
} po[maxn << 1];
struct line {
	int h, l, r, i, v;
} lin[maxn << 1];
bool sta[maxn];
int map[maxn];
int cnt[maxn << 1];
std::vector<int> G[maxn << 1];
int poh[maxn << 1];

int seg[maxd << 2];
void push (int now)  {
	if (seg[now]) { // 然后忘了这个
		seg[now << 1] = seg[now << 1 | 1] = seg[now];
		seg[now] = 0; // 先是忘了这个
	}
}
void cover (int now, int L, int R, int l, int r, int x) {
	if (r < L or l > R) return;
	if (l <= L and R <= r) return seg[now] = x, void();
	int M = (L + R) >> 1;
	push(now);
	cover(now << 1, L, M, l, r, x);
	cover(now << 1 | 1, M + 1, R, l, r, x);
}
int get (int now, int L, int R, int p) {
	if (seg[now]) return seg[now];
	int M = (L + R) >> 1;
	if (p <= M) return get(now << 1, L, M, p);
	return get(now << 1 | 1, M + 1, R, p);
}

void dfs1 (int u, int m) {
	cnt[u] = po[u].i <= m; // real point
	for (int v : G[u]) {
		dfs1(v, m);
		cnt[u] += cnt[v];
	}
}

void get_G (int t, int n, int typ) {
	for (int i = 1; i <= n; i ++)
		po[i].i = i;
	for (int i = 1; i <= t; i ++) {
		lin[i * 2 - 1] = {rec[i].x1, rec[i].y1, rec[i].y2, i, 0};
		lin[i * 2 - 0] = {rec[i].x2 + 1, rec[i].y1, rec[i].y2, i, 0};
		if (typ == 0)
			po[n + i] = {rec[i].x1 - 1, rec[i].y1 - 1, n + i};
		if (typ == 1)
			po[n + i] = {rec[i].x2, rec[i].y1 - 1, n + i};
	}
	std::sort(po + 1, po + n + t + 1, [] (point a, point b) {
				return a.x < b.x;
			});
	std::sort(lin + 1, lin + t + t + 1, [] (line a, line b) {
				return a.h < b.h;
			});
	std::fill(sta, sta + t + 1, 0); // status of rectangle
	std::fill(G, G + n + t + 1, std::vector<int>());
	seg[1] = -1;

	for (int i = 1, j = 0; i <= n + t; i ++) {
		if (po[i].i > n)
			map[po[i].i - n] = i; // rectangle to added point
		while (j + 1 <= t + t and lin[j + 1].h <= po[i].x) {
			++ j;
			sta[lin[j].i] ^= 1;
			cover(1, 1, D, lin[j].l, lin[j].r, lin[j].i);
		}
		int k = po[i].y ? get(1, 1, D, po[i].y) : -1;
		if (k != -1 and sta[k] == 0) {
			G[map[k]].push_back(i);
			poh[i] = rec[k].x2 + 1;
		}
		else {
			G[0].push_back(i);
			poh[i] = k == -1 ? 1 : rec[k].x1;
		}
	}
}

point mp[maxn << 2];
line quer[maxn << 1];
int bit[maxd];
int val[maxn << 1], ans[maxn];

void dfs2 (int u, int n) {
	if (po[u].i <= n)
		ans[po[u].i] = val[u];
	for (int v : G[u]) {
		val[v] += val[u];
		dfs2(v, n);
	}
}

void add (int p, int x) {
	if (p) // 被这个卡了一手。。。
		for (int k = p; k <= D; k += k & -k)
			bit[k] += x;
}
int query (int l, int r) {
	int res = 0;
	for (int k = r; k; k -= k & -k)
		res += bit[k];
	for (int k = l - 1; k; k -= k & -k) // 这尼玛能把 l - 1 写成 l 我是服的
		res -= bit[k];
	return res;
}

int main () {
	int t = read;
	for (int i = 1; i <= t; i ++)
		read(rec[i].x1, rec[i].y1, rec[i].x2, rec[i].y2);

	int m = read;
	for (int i = 1; i <= m; i ++)
		read(po[i].x, po[i].y);
	get_G(t, m, 0);
	dfs1(0, m);
	int pp = 0;
	for (int i = 1; i <= m + t; i ++)
		if (cnt[i]) {
			mp[++ pp] = {poh[i], po[i].y, +cnt[i]};
			mp[++ pp] = {po[i].x + 1, po[i].y, -cnt[i]};
		}

	int n = read;
	for (int i = 1; i <= n; i ++) {
		int x = read, y = read;
		po[i].x = D - y + 1, po[i].y = D - x + 1;
	}
	for (int i = 1; i <= t; i ++)
		rec[i] = {D - rec[i].y2 + 1, D - rec[i].x2 + 1,
			D - rec[i].y1 + 1, D - rec[i].x1 + 1};
	get_G(t, n, 1);
	for (int i = 1; i <= n + t; i ++)
		quer[i] = {D - po[i].y + 1, D - po[i].x + 1, D - poh[i] + 1, i, 0};

	std::sort(mp + 1, mp + pp + 1, [] (point a, point b) {
				return a.x < b.x;
			});
	std::sort(quer + 1, quer + n + t + 1, [] (line a, line b) {
				return a.h < b.h;
			});

	for (int i = 1, j = 0; i <= n + t; i ++) {
		while (j + 1 <= pp and mp[j + 1].x <= quer[i].h) {
			++ j;
			add(mp[j].y, mp[j].i);
		}
		val[quer[i].i] = query(quer[i].l, quer[i].r);
	}

	dfs2(0, n);
	for (int i = 1; i <= n; i ++)
		printf("%d\n", ans[i]);
}
