#if 0
2020.04.17

  将串倍长，然后一段的字典序可以用该串开头的后缀 rank 代替。那么求出答案对应的 rank ，然后
在 sa 上求出位置即可。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 1000005;
char s[maxn];
int sa[maxn], rank[maxn];
int tmp[maxn], sa2[maxn], t[maxn];

void build(int n, int max) {
	for(int i = 1; i <= n; i ++) {
		rank[i] = s[i];
		sa2[i] = i;
	}

	for(int i = 1; i <= n; i ++) ++ t[rank[i]];
	for(int i = 1; i <= max; i ++) t[i] += t[i - 1];
	for(int i = n; i; i --) sa[t[rank[sa2[i]]] --] = sa2[i];
	std::fill(t + 1, t + max + 1, 0);
	int tot = rank[sa[1]] = 1;
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
		std::copy(rank, rank + n + 1, tmp);
		rank[sa[1]] = tot = 1;
		for(int i = 2; i <= n; i ++)
			rank[sa[i]] = (tmp[sa[i]] == tmp[sa[i - 1]] and
					tmp[sa[i] + m] == tmp[sa[i - 1] + m]) ? tot : ++ tot;
	}
}

int ans[maxn];

int main () {
	int n = read, m = read;
	scanf("%s", s + 1);

	for (int i = 1; i <= n; i ++)
		s[n + i] = s[i];

	build(n << 1, 256);

	for (int i = 1; i <= n; i ++)
		ans[i % m] = std::max(rank[i], ans[i % m]);
	int Ans = 1000000000;
	for (int i = 0; i < m; i ++)
		Ans = std::min(Ans, ans[i]);

	int p = sa[Ans];
	for (int i = 0; i < m; i ++)
		putchar(s[p + i]);
	puts("");
}
