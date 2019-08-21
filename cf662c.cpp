#if 0
2019.08.21

枚举哪些行交换了，假设交换的集合为 S ，这时的答案为 h[S] 。
接下来考虑每一列的贡献，假设第 j 列初始的 01 串是 a[i] ，那么此时就成了 a[i] xor S 。
设 f[S] 表示 S 这个 01 串的贡献，那么有 h[S] = sum(f[a[i] xor S]) 。
这个不好优化，考虑枚举 a[i] ，设 g[S] 表示 a[i] = S 的 i 的数量，那么有
h[S] = sum(f[x xor S] * g[x])
这时候，FWT 优化卷积即可。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;
inline lolong input() { lolong x; scanf("%lld", &x); return x; }

const int maxn = 21, maxm = 100005;
lolong f[1 << maxn], g[1 << maxn], h[1 << maxn];
char s[maxn][maxm];

void FWT(lolong *a, int n, int typ) {
	for(int m = 1; m < n; m <<= 1)
		for(int i = 0; i < n; i += m << 1)
			for(int k = i; k < i + m; k ++) {
				lolong a0 = a[k], a1 = a[k + m];
				a[k] = a0 + a1;
				a[k + m] = a0 - a1;
			}

	if(typ == -1)
		for(int i = 0; i < n; i ++)
			a[i] /= n;
}

int main() {
	int n = input(), m = input();
	for(int i = 0; i < n; i ++)
		scanf("%s", s[i]);

	for(int j = 0; j < m; j ++) {
		int S = 0;
		for(int i = 0; i < n; i ++)
			if(s[i][j] == '1')
				S += 1 << i;
		g[S] ++;
	}

	for(int S = 0; S < (1 << n); S ++) {
		int tot = 0;
		for(int k = 0; k < n; k ++)
			if(S >> k & 1)
				tot ++;
		f[S] = std::min(tot, n - tot);
	}

/* 	for(int S = 0; S < (1 << n); S ++) */
/* 		debug("%lld\n", f[S]); */
/* 	for(int S = 0; S < (1 << n); S ++) */
/* 		debug("%lld\n", g[S]); */

	FWT(f, 1 << n, 1);
	FWT(g, 1 << n, 1);

	for(int S = 0; S < (1 << n); S ++)
		h[S] = f[S] * g[S];

	FWT(h, 1 << n, -1);

/* 	for(int S = 0; S < (1 << n); S ++) */
/* 		debug("%lld\n", h[S]); */

	lolong ans = 1000000000000000000;
	for(int S = 0; S < (1 << n); S ++)
		ans = std::min(ans, h[S]);

	printf("%lld\n", ans);
}
