#if 0
2019.07.11

根据容斥原理，如果 n 种饮料能恰好装进 n - 1 个瓶子里，那这些瓶子一定合法。
那么对于饮料集合 S 和瓶子容量 L ，有合法方案当且仅当下面至少一个条件成立：
1) S 只有一种饮料且该饮料体积为 L 。
2) S 能恰好装进 |S| - 1 个瓶子里。
3) S 可以分成若干集合 T 使得每个 T 满足 1) 或 2)
易得 3) 等价于以下的 4)
4) 存在 S 的子集 T 使得 T 满足 1) 或 2) 且 S / T 有合法方案。

可据此枚举答案并 dfs 验证。
#endif
#include <cstdio>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;
inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 22;
lolong sum[1 << maxn];
int size[1 << maxn];

inline int lowbit(int k) { return k & -k; }

inline bool desk(int S, lolong Lx, lolong Ly) {
	return (size[S] == 1 and sum[S] * Ly == Lx)
		or sum[S] * Ly == Lx * (size[S] - 1);
}

inline bool ifans(int S, lolong Lx, lolong Ly) {
	debug("%d, %lld/%lld\n", S, Lx, Ly);
	if(desk(S, Lx, Ly)) return true;
	for(int T = S - lowbit(S); T; T = (T - 1) & S)
		if(desk(T, Lx, Ly) and ifans(S ^ T, Lx, Ly))
			return true;
	return false;
}

int main() {
	int n = input();
	for(int i = 0; i < n; i ++) {
		sum[1 << i] = input();
		size[1 << i] = 1;
	}
	for(int S = 0; S < (1 << n); S ++)
		if(not size[S]) {
			sum[S] = sum[S - lowbit(S)] + sum[lowbit(S)];
			size[S] = size[S - lowbit(S)] + size[lowbit(S)];
		}
	lolong totsum = sum[(1 << n) - 1];
	for(int i = 1; i <= n; i ++)
		if(ifans((1 << n) - 1, totsum, i)) {
			printf("%d\n", i);
			return 0;
		}
}
