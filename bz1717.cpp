#if 0
2019.12.30

之前用二分 + hash 过了，这次练练后缀数组。
其实很简单，如果 height 数组中连续 k 个位置都大于等于 l ，就说明 l 是一个可行的长度。
求最大长度就是把 height 中每个长为 k 的连续段的最小值取最大值。
用滑动窗口的技巧可以线性计算这个值。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
} read;

const int maxn = 20005;
int s[maxn];
int rank[maxn], sa[maxn], hi[maxn];
int tmp[maxn], sa2[maxn], t[1000005];
int queue[maxn], ql, qr;

int main() {
	int n = read, k = read, tot;
	if(k == 1) return printf("%d\n", n), 0;

	for(int i = 1; i <= n; i ++) {
		s[i] = rank[i] = read;
		sa2[i] = i;
	}

	for(int i = 1; i <= n; i ++) ++ t[s[i]];
	for(int i = 1; i <= 1000000; i ++) t[i] += t[i - 1];
	for(int i = n; i; i --) sa[t[rank[sa2[i]]] --] = sa2[i];
	std::fill(t + 1, t + 1000001, 0);
	rank[sa[1]] = tot = 1;
	for(int i = 2; i <= n; i ++)
		rank[sa[i]] = s[sa[i]] == s[sa[i - 1]] ? tot : ++ tot;

	for(int m = 1; tot < n; m <<= 1) {
		int p = 0;
		for(int i = 1; i <= m; i ++) sa2[++ p] = n - m + i;
		for(int i = 1; i <= n; i ++) if(sa[i] > m) sa2[++ p] = sa[i] - m;
		for(int i = 1; i <= n; i ++) ++ t[rank[i]];
		for(int i = 1; i <= tot; i ++) t[i] += t[i - 1];
		for(int i = n; i; i --) sa[t[rank[sa2[i]]] --] = sa2[i];
		std::fill(t + 1, t + tot + 1, 0);
		std::copy(rank + 1, rank + n + 1, tmp + 1);
		rank[sa[1]] = tot = 1;
		for(int i = 2; i <= n; i ++)
			rank[sa[i]] = (tmp[sa[i]] == tmp[sa[i - 1]] and
					tmp[sa[i] + m] == tmp[sa[i - 1] + m]) ? tot : ++ tot;
	}

	for(int i = 1; i <= n; i ++) {
		int &l = hi[rank[i]] = std::max(0, hi[rank[i - 1]] - 1);
		while(s[i + l] == s[sa[rank[i] - 1] + l]) ++ l;
	}

	/* for(int i = 1; i <= n; i ++) */
	/* 	debug("%d\n", hi[i]); */

	ql = 1, qr = 0;
	for(int i = 1; i < k; i ++) {
		while(qr >= ql and hi[queue[qr]] > hi[i]) -- qr;
		queue[++ qr] = i;
	}

	-- k;
	int ans = 0;
	for(int i = k; i <= n; i ++) {
		while(qr >= ql and hi[queue[qr]] > hi[i]) -- qr;
		queue[++ qr] = i;
		while(i - queue[ql] >= k) ++ ql;
		ans = std::max(ans, hi[queue[ql]]);
	}

	printf("%d\n", ans);
}
