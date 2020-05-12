#if 0
2020.05.11

  二分答案，也就是在所有本质不同的子串中二分答案子串对应的字典序排名 k 。
  check 的时候从后往前贪心，如果当前的字符加进去产生的后缀的排名不超过 k 则可行，否则必须
新开一个划分。需要实现两个操作：比较两个子串的字典序，把排名转换为子串。
  而判断两个子串的字典序大小可以先两个后缀的 lcp 然后比较 lcp 后一位，用 height 数组求 lcp
即可。而把一个排名 k 转换为对应的子串，在后缀序上记一个本质不同子串的前缀和即可。
#endif
#include <cstdio>
#include <cstring>
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
int hb[maxn], st[20][maxn];

void build (int n, int max) {
	for (int i = 1; i <= n; i ++) rank[i] = s[i], sa2[i] = i;

	std::fill(t, t + max + 1, 0);
	for (int i = 1; i <= n; i ++) ++ t[rank[i]];
	for (int i = 1; i <= max; i ++) t[i] += t[i - 1];
	for (int i = n; i; i --) sa[t[rank[sa2[i]]] --] = sa2[i];
	max = rank[sa[1]] = 1;
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
		max = rank[sa[1]] = 1;
		for (int i = 2; i <= n; i ++)
			rank[sa[i]] = (tmp[sa[i]] == tmp[sa[i - 1]] and
					tmp[sa[i] + m] == tmp[sa[i - 1] + m]) ? max : ++ max;
	}

	for (int i = 1; i <= n; i ++) {
		int &k = hi[rank[i]] = std::max(0, hi[rank[i - 1]] - 1);
		while (s[i + k] == s[sa[rank[i] - 1] + k]) ++ k;
	}

	for (int i = 2; i <= n; i ++)
		hb[i] = hb[i >> 1] + 1;
	for (int i = n; i; i --) {
		st[0][i] = hi[i];
		for (int k = 1; i + (1 << k) - 1 <= n; k ++)
			st[k][i] = std::min(st[k - 1][i], st[k - 1][i + (1 << k >> 1)]);
	}
}

ll pre[maxn];
int lcp (int x, int y) {
	if (x == y) return 1000000000;
	int l = rank[x], r = rank[y];
	if (l > r) std::swap(l, r);
	++ l;
	int k = hb[r - l + 1];
	return std::min(st[k][l], st[k][r - (1 << k) + 1]);
}

int cmp (int l, int r, int L, int R) {
	int k = std::min(lcp(l, L), std::min(r - l + 1, R - L + 1));
	return (l + k <= r ? s[l + k] : 0) < (L + k <= R ? s[L + k] : 0);
}

int check (int n, ll k) {
	int L = 0, R = 0;
	for (int i = 1; i <= n; i ++)
		if (pre[i - 1] < k and k <= pre[i]) {
			L = sa[i];
			R = L + hi[i] - 1 + int(k - pre[i - 1]);
		}
	/* debug("check %lld -> %d %d\n", k, L, R); */
	int K = 0;
	for (int l = n, r = n; l; l --)
		if (cmp(L, R, l, r)) {
			++ K;
			/* debug("%d - %d\n", l + 1, r); */
			r = l;
			if (cmp(L, R, l, r)) return 1000000000;
		}
	++ K;
	/* debug(">>> %d\n", K); */
	return K;
}

int main () {
	int K = read;
	scanf("%s", s + 1);
	int n = int(strlen(s + 1));
	build(n, 256);

	for (int i = 1; i <= n; i ++)
		pre[i] = pre[i - 1] + (n - sa[i] + 1) - hi[i];

	ll l = 1, r = pre[n];
	while (l < r) {
		ll mid = (l + r) >> 1;
		if (check(n, mid) <= K) r = mid;
		else l = mid + 1;
	}

	for (int i = 1; i <= n; i ++)
		if (pre[i - 1] < l and l <= pre[i])
			for (int j = 0; j < hi[i] + l - pre[i - 1]; j ++)
				putchar(s[sa[i] + j]);
	puts("");
}
