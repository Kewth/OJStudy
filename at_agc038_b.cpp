#if 0
2019.09.21

考虑从 [l, r] 到 [l + 1, r + 1], 如果序列不变，答案就不会增加，
此时满足 a[l] = min(l to r) 且 a[r + 1] = max(l + 1 to r + 1) 。
特别地，如果一个区间本身就单调递增，那么它可能对答案是没贡献的，需要特判。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;

inline int input() { int x; scanf("%d", &x); return x; }
inline lolong linput() { lolong x; scanf("%lld", &x); return x; }

const int maxn = 200005, maxk = 20;
int min[maxn][maxk], max[maxn][maxk];
int f[maxn];
int a[maxn];

int main() {
	int n = input(), m = input();

	for(int i = 1; i <= n; i ++)
		a[i] = input();

	for(int i = 1; i <= n; i ++)
		if(a[i] > a[i - 1])
			f[i] = f[i - 1] + 1;
		else
			f[i] = 1;

	for(int i = n; i; i --) {
		min[i][0] = max[i][0] = a[i];
		for(int k = 1; k < maxk; k ++) {
			int j = i + (1 << (k - 1));
			min[i][k] = std::min(min[i][k - 1],
					j <= n ? min[j][k - 1] : maxn);
			max[i][k] = std::max(max[i][k - 1],
					j <= n ? max[j][k - 1] : 0);
			/* debug("%d %d %d\n", i, k, st[i][k]); */
		}
	}

	int log = 0;
	while((1 << (log + 1)) <= m)
		log ++;

	/* debug("%d\n", log); */

	int ans = 1;
	bool up = f[m] == m;

	for(int l = 2; l + m - 1 <= n; l ++) {
		int r = l + m - 1;
		/* debug("%d %d\n", std::min(st[l - 1][log], st[r - (1 << log)][log]), */
		/* 		std::min(st[l][log], st[r + 1 - (1 << log)][log])); */
		if(a[l - 1] != std::min(min[l - 1][log], min[r - (1 << log)][log]) or
				a[r] != std::max(max[l][log], max[r + 1 - (1 << log)][log])) {
			/* debug("%d %d\n", l, r); */
			if(!up or f[r] < m)
				ans ++;
		}
		if(f[r] >= m)
			up = 1;
	}

	printf("%d\n", ans);
}
