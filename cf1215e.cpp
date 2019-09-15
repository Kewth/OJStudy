#if 0
2019.09.15

假设确定了权值之间的相对位置，
那么答案就是原序列的“逆序对” (a, b) 数量，满足 a 的相对位置在 b 右边。
据此可以枚举排列 p 表示相对位置，那么答案就是 sum(i > j, g[p[i]][p[j]]) 的最小值，
其中 g[i][j] 表示原序列数对 (i, j) 的数量。
预处理出 g ，考虑优化枚举排列的过程。
设 f[S] 枚举 p 前 len(S) 位在 S 集合中的答案，那么枚举最后的 p[len(S)] 即可转移。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;
inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 400005, maxa = 20;
int cnt[maxa];
lolong g[maxa][maxa];
lolong f[1 << maxa];

int main() {
	int n = input();
	for(int i = 1; i <= n; i ++) {
		int a = input() - 1;
		for(int x = 0; x < maxa; x ++)
			g[x][a] += cnt[x];
		cnt[a] ++;
	}

	f[0] = 0;
	for(int S = 1; S < (1 << maxa); S ++) {
		f[S] = 1000000000000000000;
		for(int k = 0; k < maxa; k ++)
			if(S >> k & 1) {
				lolong now = f[S ^ (1 << k)];
				for(int x = 0; x < maxa; x ++)
					if(S >> x & 1 and x != k)
						now += g[k][x];
				f[S] = std::min(f[S], now);
			}
	}

	printf("%lld\n", f[(1 << maxa) - 1]);
}
