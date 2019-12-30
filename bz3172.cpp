#if 0
2019.12.30

这不显然广义 SAM 嘛，但是出现在 SA 题单里头就拿来练练 SA 了。
（似乎还能 AC 自动机）
把所有串用特殊字符拼起来求出 height 数组后，
一个串的出现次数就是就是一个后缀 i 的长为 m 的前缀的出现次数，
也就是有多少后缀 j 满足 lcp(i, j) >= m ，
也就是有多少 j 满足 min(height[j ~ rank[i]]) >= m ，
用 ST 表维护 height 区间最小值后二分或者倍增即可。
#endif
#include <cstdio>
#include <cstring>
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

const int maxn = 1000205, maxk = 20;
char s[maxn];
int rank[maxn], sa[maxn], hi[maxn];
int tmprk[maxn], sa2[maxn], t[maxn];
int pos[maxn];
int hb[maxn];
int st[maxn][maxk];

int min(int l, int r) {
	int k = hb[r - l + 1];
	return std::min(st[l][k], st[r - (1 << k) + 1][k]);
}

int main() {
	int n = read;
	pos[1] = 1;
	for(int i = 1; i <= n; i ++) {
		scanf("%s", s + pos[i]);
		pos[i + 1] = pos[i] + int(strlen(s + pos[i]));
		s[pos[i + 1] ++] = '#';
	}

	int len = pos[n + 1] - 1, tot;
	for(int i = 1; i <= len; i ++) {
		rank[i] = s[i];
		sa2[i] = i;
	}

	for(int i = 1; i <= len; i ++) ++ t[rank[i]];
	for(int i = 1; i <= 256; i ++) t[i] += t[i - 1];
	for(int i = len; i; i --) sa[t[rank[sa2[i]]] --] = sa2[i];
	std::fill(t + 1, t + 257, 0);
	rank[sa[1]] = tot = 1;
	for(int i = 2; i <= len; i ++)
		rank[sa[i]] = s[sa[i]] == s[sa[i - 1]] ? tot : ++ tot;

	for(int m = 1; tot < len; m <<= 1) {
		int p = 0;
		for(int i = 1; i <= m; i ++) sa2[++ p] = len - m + i;
		for(int i = 1; i <= len; i ++) if(sa[i] > m) sa2[++ p] = sa[i] - m;

		for(int i = 1; i <= len; i ++) ++ t[rank[i]];
		for(int i = 1; i <= tot; i ++) t[i] += t[i - 1];
		for(int i = len; i; i --) sa[t[rank[sa2[i]]] --] = sa2[i];
		std::fill(t + 1, t + tot + 1, 0);

		std::copy(rank + 1, rank + len + 1, tmprk + 1);
		rank[sa[1]] = tot = 1;
		for(int i = 2; i <= len; i ++)
			if(tmprk[sa[i]] == tmprk[sa[i - 1]] and tmprk[sa[i] + m] == tmprk[sa[i - 1] + m])
				rank[sa[i]] = tot;
			else
				rank[sa[i]] = ++ tot;
	}

	/* for(int i = 1; i <= len; i ++) */
	/* 	debug("%d\n", sa[i]); */

	for(int i = 1; i <= len; i ++) {
		int &k = hi[rank[i]] = std::max(0, hi[rank[i - 1]] - 1);
		while(s[i + k] == s[sa[rank[i] - 1] + k])
			++ k;
	}

	/* for(int i = 1; i <= len; i ++) */
	/* 	debug(" %d", hi[i]); */
	/* debug("\n"); */

	for(int i = 2; i <= len; i ++)
		hb[i] = hb[i >> 1] + 1;
	for(int i = len; i; i --) {
		st[i][0] = hi[i];
		for(int k = 1; i + (1 << k) - 1 <= len; k ++)
			st[i][k] = std::min(st[i][k - 1], st[i + (1 << k >> 1)][k - 1]);
	}

	for(int i = 1; i <= n; i ++) {
		int p = rank[pos[i]], m = pos[i + 1] - pos[i] - 1;
		int l = p, r = p + 1;
		/* while(hi[l] >= m) -- l; */
		/* while(hi[r + 1] >= m) ++ r; */
		for(int k = hb[p]; k >= 0; k --)
			if(st[l - (1 << k) + 1][k] >= m)
				l -= 1 << k;
		for(int k = hb[len - p + 1]; k >= 0; k --)
			if(st[r][k] >= m)
				r += 1 << k;
		/* debug("%d-%d\n", l, r); */
		printf("%d\n", r - l);
	}
}
