#if 0
2019.07.24

带修莫队模板。
#endif
#include <cstdio>
#include <algorithm>
#include <cmath>
#define debug(...) // fprintf(stderr, __VA_ARGS__)

inline int input() {
	int c = getchar(), x = 0;
	while(c < '0' or c > '9') c = getchar();
	while(c >= '0' and c <= '9') x = x * 10 + c - '0', c = getchar();
	return x;
}

struct Query {
	int	l, r, time, id;
};

const int maxn = 50005, maxv = 1000005;
int a[maxn];
Query qu[maxn];
int modi_p[maxn], modi_c[maxn], before[maxn];
int mp, qp;
int ans[maxn];
int town[maxv];
int diff;

inline void add(int p) {
	if(not town[a[p]])
		diff ++;
	town[a[p]] ++;
}

inline void remove(int p) {
	town[a[p]] --;
	if(not town[a[p]])
		diff --;
}

inline void modify(int t, int l, int r) {
	// debug("modify %d(a[%d]=%d) in %d-%d\n", p, modi_p[p], modi_c[p], l, r);
	int p = modi_p[t];
	if(l <= p and p <= r)
		remove(p);
	a[p] = modi_c[t];
	if(l <= p and p <= r)
		add(p);
}

inline void undo(int t, int l, int r) {
	int p = modi_p[t];
	if(l <= p and p <= r)
		remove(p);
	a[p] = before[t];
	if(l <= p and p <= r)
		add(p);
}

int block;
inline bool cmp(Query a, Query b) {
	if(a.l / block == b.l / block) {
		if(a.r / block == b.r / block)
			return a.time < b.time;
		return a.r < b.r;
	}
	return a.l < b.l;
}

int main() {
	freopen("color.in", "r", stdin);
	freopen("color.out", "w", stdout);
	int n = input(), q = input();
	for(int i = 1; i <= n; i ++)
		a[i] = input();
	while(q --) {
		int c = getchar();
		while(c != 'Q' and c != 'R') c = getchar();
		int x = input(), y = input();
		if(c == 'R') {
			modi_p[++ mp] = x;
			modi_c[mp] = y;
			before[mp] = a[x];
			a[x] = y;
		} else {
			qu[++ qp].l = x;
			qu[qp].r = y;
			qu[qp].time = mp;
			qu[qp].id = qp;
		}
	}
	block = pow(qp, 0.6666);
	std::sort(qu + 1, qu + qp + 1, cmp);
	int l = 1, r = 0, t = mp;
	for(int i = 1; i <= qp; i ++) {
		debug("%d, %d, %d -> %d, %d, %d(%d)\n", l, r, t, qu[i].l, qu[i].r, qu[i].time, qu[i].id);
		while(t < qu[i].time) modify(++ t, l, r);
		while(t > qu[i].time) undo(t --, l, r);
		while(l > qu[i].l) add(-- l);
		while(r < qu[i].r) add(++ r);
		while(l < qu[i].l) remove(l ++);
		while(r > qu[i].r) remove(r --);
		ans[qu[i].id] = diff;
	}
	for(int i = 1; i <= qp; i ++)
		printf("%d\n", ans[i]);
}
