#if 0
2019.12.18

首先跳跃次数最多是 logV ，每次跳跃后，可以通过普通的移动走尽可能多的点。
那么按照 V 分 logV 层，每层 [1, n] 被拆分为若干线段，
每个线段 [l, r] 表示在该层内从这个区间任一点开始可以遍历整个区间。
那么问题转换为钦定第一层线段，求是否能从其他层中每层拿一个线段使得所有线段的并为 [1, n] 。

由于层数很少，可以状压 DP 出 exl[S] 表示选 S 集合内的线段覆盖 [1, k] 的最大 k ，
类似的有 exr[S] 表示覆盖 [k, n] 的最小 k 。
转移通过 l[k][i]/r[k][i] 表示 k 层第 i 个点的左/右端点即可。

统计答案时，枚举第一层的所有线段 [l, r]，
并判断是否存在集合 S 使得 [1, exl[S]], [l, r], [exr[S], n] 的并为 [1, n] 即可。
而如果第一层线段的数量如果超过总层数说明所有点都不会合法。
#endif
#include <cstdio>
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

const int maxn = 800005, maxk = 20;
int x[maxn];
int exl[maxn], exr[maxn];
int l[maxk][maxn], r[maxk][maxn];
int len[maxk];

int main() {
	int n = read, v = read;
	for(int i = 1; i <= n; i ++)
		read(x[i]);

	int d = 0;
	while(v) {
		len[d ++] = v;
		v >>= 1;
	}
	++ d;

	for(int k = 0; k < d; k ++) {
		l[k][1] = 1;
		for(int i = 2; i <= n; i ++)
			if(x[i - 1] + len[k] >= x[i])
				l[k][i] = l[k][i - 1];
			else
				l[k][i] = i;

		r[k][n] = n;
		for(int i = n - 1; i; i --)
			if(x[i] + len[k] >= x[i + 1])
				r[k][i] = r[k][i + 1];
			else
				r[k][i] = i;
	}

	for(int S = 0; S < (1 << d); S ++) {
		exl[S] = 0;
		exr[S] = n + 1;
		for(int k = 0; k < d; k ++)
			if(S >> k & 1) {
				int T = S ^ (1 << k);
				exl[S] = std::max(exl[S], r[k][exl[T] + 1]);
				exr[S] = std::min(exr[S], l[k][exr[T] - 1]);
			}
		/* debug("%d: %d %d\n", S, exl[S], exr[S]); */
	}

	int tot = 0;
	for(int i = 1; i <= n; i = r[0][i] + 1)
		++ tot;

	if(tot > d) {
		for(int i = 1; i <= n; i ++)
			puts("Impossible");
		return 0;
	}

	for(int i = 1; i <= n; i = r[0][i] + 1) {
		bool ok = 0;
		for(int S = 0; S < (1 << d); S += 2) {
			int T = ((1 << d) - 2) ^ S ;
			/* if(exl[S] + 1 >= exr[T] or (exl[S] + 1 >= i and r[0][i] + 1 >= exr[T])) { */
			if(exl[S] + 1 >= i and r[0][i] + 1 >= exr[T]) {
				ok = 1;
				break;
			}
		}
		for(int j = i; j <= r[0][i]; j ++)
			if(ok)
				puts("Possible");
			else
				puts("Impossible");
	}
}
