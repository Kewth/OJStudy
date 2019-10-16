#if 0
2019.10.16

莫队二次离线。
区间逆序对直接用莫队需要在端点移动的时候用权值树状数组维护，带个 log 。
树状数组处理的是动态询问，将每次端点移动看做一次询问，
那么再次用离线的手段处理这些询问，即端点移动对答案的影响，就是莫队二次离线。

以下只讨论右端点向右移动的影响。
当右端点从 r 移动到 r + 1 时，新产生的逆序对是 [l, r] 中比 r + 1 大的数。
差分这个区间，就是 [1, r] 中比 r + 1 大的数减去 [1, l - 1] 中比 r + 1 大的数。
前者只与 r 有关，可以设为 f[r] 直接预处理。
而后者难以通过预处理达到 O(1) 查询。

考虑 r 的一次整体移动，即从 r 移动到 r + k 。
移动的过程中 l 是不变的，是这次整体移动的常量，
而需要的也只是这次整体移动产生的贡献和。
那么将这次整体移动的区间 [r + 1, r + l] 记录到 l 上，再通过二次离线处理。
二次离线使用扫描线，从小到大处理每个 l 的移动区间，
期间只需维护 [1, l - 1] 里面的数，
然后对于 l 记录的区间的每一个数都询问在 [1, l - 1] 中比该数大的数来计算逆序对。

由于记录的区间的长度和是 O(n^1.5) 的，那么维护 [1, l - 1] 中的数需要支持 O(1) 查询。
而修改只有 O(n) 次加点，那么修改最多允许 O(n^0.5) 。
值域分块，维护块间前缀和和块内前缀和即可。
#endif
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;

inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 100005, maxb = 340;
struct Query {
	int l, r, id;
} qu[maxn];
int head[maxn << 1], nxt[maxn << 1], tl[maxn << 1], tr[maxn << 1], get[maxn << 1], hp;
int inxt[maxn << 1], tail[maxn << 1];

void pushback(int p, int l, int r) {
	nxt[++ hp] = head[p];
	inxt[head[p]] = hp;
	head[p] = hp;
	tl[hp] = l;
	tr[hp] = r;
}

int S, B;
bool cmp(Query x, Query y) {
	if(x.l / B == y.l / B)
		return (x.l / B) & 1 ? x.r > y.r : x.r < y.r;
	return x.l < y.l;
}

int bit[maxn];
lolong tol[maxn], tor[maxn];

int query(int k) {
	int res = 0;
	while(k) {
		res += bit[k];
		k -= k & -k;
	}
	return res;
}

void modify(int k) {
	while(k < maxn) {
		bit[k] ++;
		k += k & -k;
	}
}

int a[maxn];
int tmp[maxn];
int spre[maxb], pre[maxb * maxb];
lolong ans[maxn];

int Query(int k) {
	return pre[k] + (k / B ? spre[k / B - 1] : 0);
}

void Modify(int k) {
	for(int i = k; i / B == k / B; i ++)
		pre[i] ++;
	for(int i = k / B; i < S; i ++)
		spre[i] ++;
}

int main() {
	int n = input(), q = input();
	B = int(sqrt(n) + 1);
	S = n / B + 1;
	for(int i = 1; i <= n; i ++)
		tmp[i] = a[i] = input();

	std::sort(tmp + 1, tmp + n + 1);
	for(int i = 1; i <= n; i ++)
		a[i] = int(std::lower_bound(tmp + 1, tmp + n + 1, a[i]) - tmp);

	for(int i = 1; i <= n; i ++) {
		tol[i] = tol[i - 1] + i - 1 - query(a[i]);
		modify(a[i]);
	}

	memset(bit, 0, sizeof bit);
	for(int i = n; i; i --) {
		tor[i] = tor[i + 1] + query(a[i] - 1);
		modify(a[i]);
	}

	for(int i = 1; i <= q; i ++) {
		qu[i].l = input();
		qu[i].r = input();
		qu[i].id = i;
	}

	std::sort(qu + 1, qu + q + 1, cmp);

	int l = 1, r = 1;
	for(int i = 1; i <= q; i ++) {
		int L = qu[i].l, R = qu[i].r;
		if(L < l) {
			pushback(n + r, L, l - 1);
			l = L;
		}
		if(r < R) {
			pushback(l, r + 1, R);
			r = R;
		}
		if(l < L) {
			pushback(n + r, l, L - 1);
			l = L;
		}
		if(R < r) {
			pushback(l, R + 1, r);
			r = R;
		}
	}

	for(int i = 1; i <= n; i ++) {
		for(int p = head[i]; p; tail[i] = p, p = nxt[p])
			for(int k = tl[p]; k <= tr[p]; k ++)
				get[p] += i - 1 - Query(a[k]);
		Modify(a[i]);
		/* for(int p = head[i]; p; p = nxt[p]) */
		/* 	debug("%d-%d - %d-%d : %d\n", 1, i - 1, tl[p], tr[p], get[p]); */
	}

	memset(pre, 0, sizeof pre);
	memset(spre, 0, sizeof spre);
	for(int i = n; i; i --) {
		for(int p = head[n + i]; p; tail[n + i] = p, p = nxt[p])
			for(int k = tl[p]; k <= tr[p]; k ++)
				get[p] += Query(a[k] - 1);
		Modify(a[i]);
		/* for(int p = head[n + i]; p; p = nxt[p]) */
		/* 	debug("%d-%d - %d-%d : %d\n", tl[p], tr[p], i + 1, n, get[p]); */
	}

	lolong Ans = 0;
	l = 1, r = 1;
	for(int i = 1; i <= q; i ++) {
		int L = qu[i].l, R = qu[i].r;
		if(L < l) {
			Ans += tor[L] - tor[l];
			Ans -= get[tail[n + r]];
			tail[n + r] = inxt[tail[n + r]];
			l = L;
		}
		if(R > r) {
			Ans += tol[R] - tol[r];
			Ans -= get[tail[l]];
			tail[l] = inxt[tail[l]];
			r = R;
		}
		if(L > l) {
			Ans -= tor[l] - tor[L];
			Ans += get[tail[n + r]];
			tail[n + r] = inxt[tail[n + r]];
			l = L;
		}
		if(R < r) {
			Ans -= tol[r] - tol[R];
			Ans += get[tail[l]];
			tail[l] = inxt[tail[l]];
			r = R;
		}
		ans[qu[i].id] = Ans;
	}

	for(int i = 1; i <= q; i ++)
		printf("%lld\n", ans[i]);
}
