/*
 * Since g++10 is released, some characters is not valid inside #if 0 :(
 * So, why not using clang++? :D

 * Date:
  2020.06.03

 * Solution:
  二分答案 k ，问题转换为判断一个长为 k 的子串 x 是否在区间 [a, b] 中出现过。
  继续在 height 数组上二分，求出后缀序的一个最大区间满足长为 k 的前缀就是 x ，那么问题进
一步转换为求左端点在 [a, b] 的后缀中有没有排名在该区间中的后缀，用主席树维护即可。

 * CopyRight:
          ▁▃▄▄▄▃▃▃▃▄▶
        ▗▇▀▔    ▔▔▔▔
       ▄▛   ▃▅━━■▄▂
      ▟▊   ▐▘     ▀▙
     ▟▜▌   ▐▖   ▋  ▐▍
    ▟▘ ▜   ▝▀▇▆●▘  ▐▌
  ▗▟▘   ▜▃       ▁▅▛
  ▔▀▼▅▄▃▃██▅▄▄▄▅■▀▔
        ▔▔▔▔▔▔
 */

#pragma GCC optimize(3)
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 100005;
char s[maxn];
int sa[maxn], rank[maxn], hi[maxn];
int tmp[maxn], sa2[maxn], t[maxn];

void build (int n, int max) {
	for (int i = 1; i <= n; i ++) rank[i] = s[i], sa2[i] = i;

	std::fill(t, t + max + 1, 0);
	for (int i = 1; i <= n; i ++) ++ t[rank[i]];
	for (int i = 1; i <= max; i ++) t[i] += t[i - 1];
	for (int i = n; i; i --) sa[t[rank[sa2[i]]] --] = sa2[i];
	rank[sa[1]] = max = 1;
	for (int i = 2; i <= n; i ++)
		rank[sa[i]] = s[sa[i]] == s[sa[i - 1]] ? max : ++ max;

	for (int m = 1; max < n; m <<= 1) {
		int p = 0;
		for (int i = 0; i < m; i ++) sa2[++ p] = n - i;
		for (int i = 1; i <= n; i ++) if (sa[i] > m) sa2[++ p] = sa[i] - m;
		std::fill(t, t + max + 1, 0);
		for (int i = 1; i <= n; i ++) ++ t[rank[i]];
		for (int i = 1; i <= max; i ++) t[i] += t[i - 1];
		for (int i = n; i; i --) sa[t[rank[sa2[i]]] --] = sa2[i];
		std::copy(rank, rank + n + 1, tmp);
		rank[sa[1]] = max = 1;
		for (int i = 2; i <= n; i ++)
			rank[sa[i]] = (tmp[sa[i]] == tmp[sa[i - 1]] and
					tmp[sa[i] + m] == tmp[sa[i - 1] + m]) ? max : ++ max;
	}

	for (int i = 1; i <= n; i ++) {
		int &k = hi[rank[i]] = std::max(0, hi[rank[i - 1]] - 1);
		while (s[i + k] == s[sa[rank[i] - 1] + k]) ++ k;
	}
}

const int maxk = 20;
int hb[maxn], st[maxn][maxk];

int query (int l, int r) {
	int k = hb[r - l + 1];
	return std::min(st[l][k], st[r - (1 << k) + 1][k]);
}

int find_l (int p, int, int k) {
	int l = 1, r = p;
	while (l < r) {
		int mid = (l + r) >> 1;
		if (query(mid + 1, p) >= k)
			r = mid;
		else
			l = mid + 1;
	}
	return l;
}

int find_r (int p, int n, int k) {
	int l = p, r = n;
	while (l < r) {
		int mid = (l + r + 1) >> 1;
		if (query(p + 1, mid) >= k)
			l = mid;
		else
			r = mid - 1;
	}
	return r;
}

struct Tree {
	int lti, rti;
	int val;
} pool[maxn * 20];
int pp;
#define self pool[now]

void lain (int &now, int L, int R, int p) {
	pool[++ pp] = self;
	now = pp;
	++ self.val;
	if (L == R) return;
	int M = (L + R) >> 1;
	if (p <= M) lain(self.lti, L, M, p);
	else lain(self.rti, M + 1, R, p);
}

int query (int now, int L, int R, int l, int r) {
	if (r < L or l > R or !self.val) return 0;
	if (l <= L and R <= r) return self.val;
	int M = (L + R) >> 1;
	return query(self.lti, L, M, l, r) + query(self.rti, M + 1, R, l, r);
}

int seg[maxn];

int main () {
	int n = read, q = read;
	scanf("%s", s + 1);
	build(n, 256);

	for (int i = 2; i <= n; i ++)
		hb[i] = hb[i >> 1] + 1;
	for (int i = n; i; i --) {
		st[i][0] = hi[i];
		for (int k = 1; i + (1 << k) - 1 <= n; k ++)
			st[i][k] = std::min(st[i][k - 1], st[i + (1 << k >> 1)][k - 1]);
	}

	for (int i = 1; i <= n; i ++)
		lain(seg[i] = seg[i - 1], 1, n, rank[i]);

	while (q --) {
		int a = read, b = read, c = read, d = read;
		int l = 0, r = std::min(b - a + 1, d - c + 1);
		while (l < r) {
			int mid = (l + r + 1) >> 1;
			int L = find_l(rank[c], n, mid);
			int R = find_r(rank[c], n, mid);
			if (query(seg[b - mid + 1], 1, n, L, R) > query(seg[a - 1], 1, n, L, R))
				l = mid;
			else
				r = mid - 1;
		}
		printf("%d\n", l);
	}
}
