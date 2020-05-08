#if 0
2020.05.08

  离散化，对于每个 x 用 set 存对应的 y ，然后用线段树维护一个 x 区间的最大 y 。这样查询
的时候线段树上二分出最小的合法 x 然后再在 set 上二分出最小的合法的 y 即可。
#endif
#include <cstdio>
#include <algorithm>
#include <set>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef std::pair<int, int> par;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator char () { char x[10]; return scanf("%s", x), *x; }
} read;

const int maxn = 200005;
std::set<int> set[maxn];
int seg[maxn << 2];
int tmpx[maxn], tmpy[maxn];

void modify (int now, int L, int R, int p, int x) {
	if (L == R) return seg[now] = x, void();
	int M = (L + R) >> 1;
	if (p <= M) modify(now << 1, L, M, p, x);
	else modify(now << 1 | 1, M + 1, R, p, x);
	seg[now] = std::max(seg[now << 1], seg[now << 1 | 1]);
}

int find (int now, int L, int R, int p, int x) {
	if (seg[now] <= x or R < p) return -1;
	if (L == R) return L;
	int M = (L + R) >> 1;
	int lf = find(now << 1, L, M, p, x);
	if (lf != -1) return lf;
	return find(now << 1 | 1, M + 1, R, p, x);
}

char qo[maxn];
int qx[maxn], qy[maxn];

int main () {
	int q = read;
	for (int i = 1; i <= q; i ++) {
		qo[i] = read;
		tmpx[i] = qx[i] = read;
		tmpy[i] = qy[i] = read;
	}

	std::sort(tmpx + 1, tmpx + q + 1);
	std::sort(tmpy + 1, tmpy + q + 1);

	for (int i = 1; i <= q; i ++)
		set[i].insert(0);

	for (int i = 1; i <= q; i ++) {
		int x = int(std::lower_bound(tmpx + 1, tmpx + q + 1, qx[i]) - tmpx);
		int y = int(std::lower_bound(tmpy + 1, tmpy + q + 1, qy[i]) - tmpy);
		/* debug("%c %d %d\n", qo[i], x, y); */
		if (qo[i] == 'a') {
			set[x].insert(y);
			modify(1, 1, q, x, *set[x].rbegin());
		}
		if (qo[i] == 'r') {
			set[x].erase(y);
			modify(1, 1, q, x, *set[x].rbegin());
		}
		if (qo[i] == 'f') {
			int rx = find(1, 1, q, x + 1, y);
			if (rx == -1) puts("-1");
			else printf("%d %d\n", tmpx[rx], tmpy[*set[rx].upper_bound(y)]);
		}
	}
}
