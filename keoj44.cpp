#if 0
date +%Y.%m.%d

回滚莫队，离散化后添加一个数可以很容易处理。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;

inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 100505, maxb = 333;
struct Que {
	int l, r, id;
};
int a[maxn];
int tmp[maxn];
int tot[maxn];
lolong ans[maxn], nowans;
Que qu[maxn];

int b;
bool cmp(Que x, Que y) {
	if(x.l / b == y.l / b)
		return x.r < y.r;
	return x.l < y.l;
}

inline void undo(int p) {
	int x = a[p];
	tot[x] --;
}

inline void add(int p) {
	int x = a[p];
	tot[x] ++;
	nowans = std::max(nowans, 1ll * tot[x] * tmp[x]);
}

int main() {
	int n = input(), q = input();
	b = 1;
	while(b * b < n)
		b ++;
	debug("%d\n", b);

	for(int i = 0; i < n; i ++)
		tmp[i] = a[i] = input();

	std::sort(tmp, tmp + n);
	for(int i = 0; i < n; i ++)
		a[i] = int(std::lower_bound(tmp, tmp + n, a[i]) - tmp);

	for(int i = 0; i < q; i ++) {
		qu[i].l = input() - 1;
		qu[i].r = input() - 1;
		qu[i].id = i;
	}

	std::sort(qu, qu + q, cmp);

	int nowb = 0;
	int last = b - 1;
	for(int i = 0; i < q; i ++) {
		int l = qu[i].l, r = qu[i].r;
		if(l / b != nowb) {
			while(last / b > nowb)
				undo(last --);
			nowans = 0;
			nowb = qu[i].l / b;
			last = nowb * b + b - 1;
		}

		if(r / b == nowb) {
			for(int p = l; p <= r; p ++)
				add(p);
			for(int p = l; p <= r; p ++)
				undo(p);
			ans[qu[i].id] = nowans;
			nowans = 0;
		}

		else {
			while(last < r)
				add(++ last);
			lolong bak = nowans;
			for(int p = l; p / b == nowb; p ++)
				add(p);
			for(int p = l; p / b == nowb; p ++)
				undo(p);
			ans[qu[i].id] = nowans;
			nowans = bak;
		}
	}

	for(int i = 0; i < q; i ++)
		printf("%lld\n", ans[i]);
}
