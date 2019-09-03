#if 0
2019.09.03

做法神仙，看策爷论文吧，到时候再补简易题解。

你妹卡常， bzoj 上 12000ms 的总时限我跑 11764ms 。
#endif
#include <cstdio>
#include <algorithm>
#include <set>
#include <cstring>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef std::pair<int, int> Par;

inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 1505, maxm = 1000005;
int ml[maxm], mr[maxm];
int c[maxn], ic[maxn];
int a[maxn], ia[maxn];
Par pr[maxn];

int min[maxn * 3], lazy[maxn * 3];

inline void push_down(int now) {
	int &l = lazy[now];
	min[now << 1] += l;
	lazy[now << 1] += l;
	min[now << 1 | 1] += l;
	lazy[now << 1 | 1] += l;
	l = 0;
}

void add(int now, int L, int R, int l, int r, int x) {
	if(l <= L and R <= r) {
		min[now] += x;
		lazy[now] += x;
	} else {
		int mid = (L + R) >> 1;
		push_down(now);
		if(l <= mid)
			add(now << 1, L, mid, l, r, x);
		if(r > mid)
			add(now << 1 | 1, mid + 1, R, l, r, x);
		min[now] = std::min(min[now << 1], min[now << 1 | 1]);
	}
}

int main() {
	int n = input(), m = input(), q = input();

	for(int i = 1; i <= m; i ++) {
		ml[i] = input();
		mr[i] = input();
	}

	for(int i = 1; i <= n; i ++)
		c[i] = i;

	std::set<int> st;
	for(int i = 1; i < n; i ++)
		st.insert(i);
	st.insert(n + 1);

	for(int i = m; i; i --) {
		int x;
		/* debug("%d - %d\n", ml[i], mr[i]); */
		while((x = *st.lower_bound(ml[i])) < mr[i]) {
			/* for(int y : st) */
			/* 	debug(" %d", y); */
			/* debug("\n"); */
			/* debug("get %d\n", x); */

			st.erase(x);

			std::swap(c[x], c[x + 1]);

			if(x + 2 <= n and c[x + 1] < c[x + 2])
				st.insert(x + 1);
			else
				st.erase(x + 1);

			if(x - 1 >= 1 and c[x - 1] < c[x])
				st.insert(x - 1);
			else
				st.erase(x - 1);
		}
	}

	for(int i = 1; i <= n; i ++)
		ic[c[i]] = i;

	/* for(int i = 1; i <= n; i ++) */
	/* 	debug(" %d", c[i]); */
	/* debug("\n"); */

	while(q --) {
		memset(min, 0, sizeof min);
		memset(lazy, 0, sizeof lazy);

		for(int i = 1; i <= n; i ++)
			pr[i] = Par(input(), i);

		std::sort(pr + 1, pr + n + 1);

		for(int i = 1; i <= n; i ++)
			a[pr[i].second] = i;

		for(int i = 1; i <= n; i ++)
			ia[a[i]] = i;

		bool ans = true;
		for(int i = 1; i < n; i ++) {
			add(1, 1, n, ia[i], n, 1);
			add(1, 1, n, ic[i], n, -1);
			if(min[1] < 0) {
				ans = false;
				break;
			}
		}

		if(ans)
			puts("AC");
		else
			puts("WA");
	}
}
