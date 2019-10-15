#if 0
2019.10.14

最近突然想刷 Ynoi ，先搞个弱化版的分块区间众数练手。

离线的话回滚莫队是很好做的，在线的话考虑序列分块。
查询的时候，如果查询区间在一个块内，暴力扫。
否则众数一定是两种情况之一：
1) 在完整的块中，预处理块间的所有区间众数。
2) 在零散的块中，暴力枚举零散的块，判断是否为众数。
其中 2) 判断众数需要直到完整的块中每个数 x 的出现次数，
预处理出每个块的前缀的每个数的出现次数即可。
#endif
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;

inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 40005, maxb = 205;
int a[maxb * maxb], tmp[maxn];
int num[maxb][maxb];
int times[maxb][maxn];
int tot[maxn];
int B;

int main() {
	int n = input(), q = input();
	B = int(sqrt(n) + 1);

	for(int i = 0; i < n; i ++)
		tmp[i] = a[i] = input();

	std::sort(tmp, tmp + n);
	for(int i = 0; i < n; i ++)
		a[i] = int(std::lower_bound(tmp, tmp + n, a[i]) - tmp + 1);

	for(int b = 0; b < B; b ++) {
		if(b)
			memcpy(times[b], times[b - 1], sizeof times[b - 1]);
		for(int i = 0; i < B; i ++)
			times[b][a[b * B + i]] ++;
	}

	for(int l = 0; l < B; l ++) {
		memset(tot, 0, sizeof tot);
		for(int r = l; r < B; r ++) {
			if(r > l)
				num[l][r] = num[l][r - 1];
			for(int i = 0; i < B; i ++) {
				int x = a[r * B + i];
				if(x)
					tot[x] ++;
				if(tot[x] > tot[num[l][r]] or
						(tot[x] == tot[num[l][r]] and x < num[l][r]))
					num[l][r] = x;
			}
		}
	}

	memset(tot, 0, sizeof tot);

	int ans = 0;
	while(q --) {
		int l = (input() + ans - 1) % n;
		int r = (input() + ans - 1) % n;
		if(l > r) std::swap(l, r);
		int L = l / B + 1, R = r / B - 1;
		/* debug("%d %d\n", l, r); */

		if(L > R) {
			ans = 0;
			for(int i = l; i <= r; i ++) {
				tot[a[i]] ++;
				/* debug("%d(%d) %d(%d)\n", a[i], tot[a[i]], ans, tot[ans]); */
				if(tot[a[i]] > tot[ans] or
						(tot[a[i]] == tot[ans] and a[i] < ans))
					ans = a[i];
			}
			for(int i = l; i <= r; i ++)
				tot[a[i]] --;
		}

		else {
			ans = num[L][R];
			for(int i = l; i / B < L; i ++) {
				tot[a[i]] ++;
				int totai = times[R][a[i]] - (L ? times[L - 1][a[i]] : 0) + tot[a[i]];
				int totans = times[R][ans] - (L ? times[L - 1][ans] : 0) + tot[ans];
				if(totai > totans or (totai == totans and a[i] < ans))
					ans = a[i];
			}
			for(int i = r; i / B > R; i --) {
				tot[a[i]] ++;
				int totai = times[R][a[i]] - (L ? times[L - 1][a[i]] : 0) + tot[a[i]];
				int totans = times[R][ans] - (L ? times[L - 1][ans] : 0) + tot[ans];
				if(totai > totans or (totai == totans and a[i] < ans))
					ans = a[i];
			}
			for(int i = l; i / B < L; i ++)
				tot[a[i]] --;
			for(int i = r; i / B > R; i --)
				tot[a[i]] --;
		}

		/* debug("%d -> %d\n", ans, tmp[ans - 1]); */
		ans = tmp[ans - 1];
		printf("%d\n", ans);
	}
}
