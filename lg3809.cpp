#if 0
2019.12.29

relearn sa.
#endif
#include <cstdio>
#include <cstring>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

const int maxn = 1000005, maxk = 200;
char s[maxn];
int rank[maxn], sa[maxn];
int sa2[maxn], tmprk[maxn];
int t[maxn];

int main() {
	scanf("%s", s + 1);
	int n = int(strlen(s + 1)), tot = 0;

	for(int i = 1; i <= n; i ++) {
		rank[i] = s[i];
		sa2[i] = i;
	}

	for(int i = 1; i <= n; i ++) ++ t[rank[i]];
	for(int i = 1; i <= maxk; i ++) t[i] += t[i - 1];
	for(int i = n; i; i --) sa[t[rank[sa2[i]]] --] = sa2[i];
	std::fill(t + 1, t + maxk + 1, 0);
	rank[sa[1]] = tot = 1;
	for(int i = 2; i <= n; i ++)
		rank[sa[i]] = s[sa[i]] == s[sa[i - 1]] ? tot : ++ tot;
	/* debug("%d\n", tot); */
	/* for(int i = 1; i <= n; i ++) debug("%d ", rank[i]); debug("rk\n"); */
	/* for(int i = 1; i <= n; i ++) debug("%d ", sa[i]); debug("sa\n"); */

	for(int m = 1; tot < n; m <<= 1) {
		int p = 0;
		for(int i = 1; i <= m; i ++) sa2[++ p] = n - m + i;
		for(int i = 1; i <= n; i ++) if(sa[i] > m) sa2[++ p] = sa[i] - m;

		for(int i = 1; i <= n; i ++) ++ t[rank[i]];
		for(int i = 1; i <= tot; i ++) t[i] += t[i - 1];
		for(int i = n; i; i --) sa[t[rank[sa2[i]]] --] = sa2[i];
		std::fill(t + 1, t + tot + 1, 0);

		std::copy(rank + 1, rank + n + 1, tmprk + 1);
		rank[sa[1]] = p = 1;
		for(int i = 2; i <= n; i ++)
			if(tmprk[sa[i]] == tmprk[sa[i - 1]] and tmprk[sa[i] + m] == tmprk[sa[i - 1] + m])
				rank[sa[i]] = p;
			else
				rank[sa[i]] = ++ p;
		tot = p;
		/* debug("%d\n", tot); */
		/* for(int i = 1; i <= n; i ++) debug("%d ", rank[i]); debug("rk\n"); */
		/* for(int i = 1; i <= n; i ++) debug("%d ", sa[i]); debug("sa\n"); */
	}

	for(int i = 1; i <= n; i ++) printf("%d ", sa[i]);
}
