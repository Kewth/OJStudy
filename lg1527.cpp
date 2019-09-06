#if 0
2019.09.06

整体二分例题。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 505, maxq = 60005;
struct Dot {
	int x, y, w;
};

int shit[maxq], shit_l[maxq], shit_r[maxq];
int qx1[maxq], qy1[maxq], qx2[maxq], qy2[maxq], qk[maxq];
int ans[maxq];
int bit[maxn][maxn];
Dot tmp[maxn * maxn];

void add(int x, int y, int v) {
	/* debug("%d %d %d\n", x, y, v); */
	for(int k1 = x; k1 < maxn; k1 += k1 & -k1)
		for(int k2 = y; k2 < maxn; k2 += k2 & -k2)
			bit[k1][k2] += v;
}

int query(int x, int y) {
	int res = 0;
	for(int k1 = x; k1; k1 -= k1 & -k1)
		for(int k2 = y; k2; k2 -= k2 & -k2)
			res += bit[k1][k2];
	return res;
}

inline int calc(int x1, int y1, int x2, int y2) {
	return query(x2, y2) - query(x1 - 1, y2) -
		query(x2, y1 - 1) + query(x1 - 1, y1 - 1);
}

void solve(int l, int r, int L, int R) {
	if(l > r)
		return;

	if(L == R) {
		for(int i = l; i <= r; i ++)
			ans[shit[i]] = tmp[L].w;
		return;
	}

	/* debug("%d - %d | %d - %d\n", l, r, L, R); */

	int M = (L + R) >> 1;

	for(int i = L; i <= M; i ++)
		add(tmp[i].x, tmp[i].y, 1);

	int lp = 0, rp = 0;
	for(int i = l; i <= r; i ++) {
		int p = shit[i];
		int x = calc(qx1[p], qy1[p], qx2[p], qy2[p]);
		if(qk[p] <= x)
			shit_l[++ lp] = p;
		else {
			qk[p] -= x;
			shit_r[++ rp] = p;
		}
	}

	for(int i = L; i <= M; i ++)
		add(tmp[i].x, tmp[i].y, -1);

	for(int i = 1; i <= lp; i ++)
		shit[l + i - 1] = shit_l[i];
	for(int i = 1; i <= rp; i ++)
		shit[l + lp - 1 + i] = shit_r[i];

	solve(l, l + lp - 1, L, M);
	solve(l + lp, r, M + 1, R);
}

inline bool cmp(Dot x, Dot y) {
	return x.w < y.w;
}

int main() {
	int n = input(), q = input();

	int tp = 0;
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= n; j ++) {
			tp ++;
			tmp[tp].x = i;
			tmp[tp].y = j;
			tmp[tp].w = input();
		}

	std::sort(tmp + 1, tmp + tp + 1, cmp);

	for(int i = 1; i <= q; i ++) {
		shit[i] = i;
		qx1[i] = input();
		qy1[i] = input();
		qx2[i] = input();
		qy2[i] = input();
		qk[i] = input();
	}

	tmp[++ tp].w = 1000000001;

	solve(1, q, 1, n * n);

	for(int i = 1; i <= q; i ++)
		printf("%d\n", ans[i]);
}
