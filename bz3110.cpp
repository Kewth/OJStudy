#if 0
2019.09.17

带修改的整体二分，算是个板子。
#endif
#include <cstdio>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;
inline int input() { int x; scanf("%d", &x); return x; }
inline lolong linput() { lolong x; scanf("%lld", &x); return x; }

const int maxn = 50005, maxq = 50005;
int op[maxq], a[maxq], b[maxq], ans[maxq];
lolong c[maxq];
int shit[maxq], shit_l[maxq], shit_r[maxq];
lolong bit1[maxn], bit2[maxn];

inline lolong query(int p) {
	lolong sum1 = 0, sum2 = 0;
	for(int k = p; k; k -= k & -k) {
		sum1 += bit1[k];
		sum2 += bit2[k];
	}
	return sum2 - sum1 * (maxn - p - 1);
}

inline void add(int p, int x) {
	for(int k = p; k < maxn; k += k & -k) {
		bit1[k] += x;
		bit2[k] += 1ll * x * (maxn - p);
	}
}

void solve(int l, int r, int L, int R) {
	if(L == R) {
		for(int i = l; i <= r; i ++)
			ans[shit[i]] = L;
		return;
	}

	int M = (L + R) >> 1;
	int lp = 0, rp = 0;

	for(int i = l; i <= r; i ++) {
		int id = shit[i];
		/* debug("%d in %d-%d\n", id, L, R); */
		if(op[id] == 1) {
			if(c[id] > M) {
				add(a[id], 1);
				add(b[id] + 1, -1);
				shit_r[++ rp] = id;
			} else
				shit_l[++ lp] = id;
		} else if(op[id] == 2) {
			lolong k = query(b[id]) - query(a[id] - 1);
			/* debug("k = %lld\n", k); */
			if(c[id] <= k)
				shit_r[++ rp] = id;
			else {
				shit_l[++ lp] = id;
				c[id] -= k;
			}
		}
	}

	for(int i = l; i <= r; i ++) {
		int id = shit[i];
		if(op[id] == 1 and c[id] > M) {
			add(a[id], -1);
			add(b[id] + 1, 1);
		}
	}

	for(int i = 1; i <= lp; i ++)
		shit[l + i - 1] = shit_l[i];
	for(int i = 1; i <= rp; i ++)
		shit[l + lp + i - 1] = shit_r[i];

	solve(l, l + lp - 1, L, M);
	solve(l + lp, r, M + 1, R);
}

int main() {
	int n = input(), q = input();

	for(int i = 1; i <= q; i ++) {
		op[i] = input();
		a[i] = input();
		b[i] = input();
		c[i] = linput();
		shit[i] = i;
	}

	solve(1, q, 1, n);

	for(int i = 1; i <= q; i ++)
		if(op[i] == 2)
			printf("%d\n", ans[i]);
}
