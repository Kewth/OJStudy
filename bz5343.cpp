#if 0
2019.09.09

哪来这么多事，这题数据结构用两个树状数组就行了。

首先对于每个询问答案是可以二分的，但是每个询问二分的 check 都是线性的。
考虑 check 的本质，实际就是在美味度不小于 mid 的果汁中按价格从低到高选到体积满足要求。
假设把美味度满足要求的果汁按价格排序，那么选的一定是段连续区间，
那么维护前缀和后可以二分来 check ，瓶颈在于排序和前缀和预处理。

整体二分可以做到一边二分答案一边维护 check 所需要的信息。
假设当前在二分答案 [L, R] ，此时已经将美味度超过 R 的提出来存进了数据结构，
姑且认为在这个数据结构里果汁按价格排好了序且维护好了前缀和信息。
设 M = (L + R + 1) / 2 ，那么将美味度在 [M, R] 的果汁扔进该数据结构就可以了。

这个数据结构实际上树状数组就可以了，以价格为下标。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;
inline int input() { int x; scanf("%d", &x); return x; }
inline lolong linput() { lolong x; scanf("%lld", &x); return x; }

const int maxn = 100005;

struct Juice {
	int d, p, l;
};
Juice ju[maxn];

lolong qg[maxn], ql[maxn];
int ans[maxn];
int shit[maxn], shit_l[maxn], shit_r[maxn];
lolong bit_p[maxn], bit_l[maxn];

inline void add(int p, int l, int typ) {
	for(int k = p; k < maxn; k += k & -k) {
		bit_p[k] += 1ll * p * l * typ;
		bit_l[k] += l * typ;
	}
}

inline lolong query_p(int p) {
	lolong res = 0;
	for(int k = p; k; k -= k & -k)
		res += bit_p[k];
	return res;
}

inline lolong query_l(int p) {
	lolong res = 0;
	for(int k = p; k; k -= k & -k)
		res += bit_l[k];
	return res;
}

bool cmp(Juice a, Juice b) {
	return a.d < b.d;
}

void solve(int l, int r, int L, int R) {
	if(L == R) {
		for(int i = l; i <= r; i ++)
			ans[shit[i]] = ju[L].d;
		add(ju[L].p, ju[L].l, 1);
		return;
	}

	/* for(int i = l; i <= r; i ++) */
	/* 	debug(" %d", shit[i]); */
	/* debug(" <- %d-%d,%d-%d\n", l, r, L, R); */

	int M = (L + R + 1) >> 1;

	for(int i = M; i <= R; i ++)
		add(ju[i].p, ju[i].l, 1);

	int lp = 0, rp = 0;

	for(int i = l; i <= r; i ++) {
		int id = shit[i];

		int ll = 0, rr = maxn - 1;
		while(ll < rr) {
			int mid = (ll + rr) >> 1;
			if(query_l(mid) >= ql[id])
				rr = mid;
			else
				ll = mid + 1;
		}

		lolong now_l = query_l(ll), now_p = query_p(ll);
		if(now_l >= ql[id] and now_p - (now_l - ql[id]) * ll <= qg[id])
			shit_r[++ rp] = id;
		else
			shit_l[++ lp] = id;

		/* debug("id=%d, l=%lld, p=%lld\n", id, now_l, now_p); */
	}

	for(int i = 1; i <= lp; i ++)
		shit[l + i - 1] = shit_l[i];
	for(int i = 1; i <= rp; i ++)
		shit[l + lp + i - 1] = shit_r[i];

	for(int i = M; i <= R; i ++)
		add(ju[i].p, ju[i].l, -1);

	solve(l + lp, r, M, R);
	solve(l, l + lp - 1, L, M - 1);
}

int main() {
	int n = input(), q = input();

	for(int i = 1; i <= n; i ++) {
		ju[i].d = input();
		ju[i].p = input();
		ju[i].l = input();
	}

	ju[0].d = -1;
	ju[0].p = 1;
	ju[0].l = 1;

	std::sort(ju, ju + n + 1, cmp);

	for(int i = 1; i <= q; i ++) {
		qg[i] = linput();
		ql[i] = linput();
		shit[i] = i;
	}

	solve(1, q, 0, n);

	for(int i = 1; i <= q; i ++)
		printf("%d\n", ans[i]);
}
