#pragma GCC optimize(2)
#if 0
2020.03.25

妙极。

设要求的答案是序列 A ，考虑计算其父集和 B ，然后通过反演得到 A 。
那么 B[S] 的意义就是钦定排列一些位置必须连边，其他随意。

可以发现，B[S] 相当于将排列划分为若干连续段，要求每个段内必须连成一条链。
那么对于 B[S], B[T] ，如果 S, T 代表的划分本质相同，就一定有 B[S] = B[T] 。
也就是说只需要对于所有 n 的划分计算 B[S] 即可。

预处理出 f[S] 表示用集合 S 内的点能组成多少条链。
那么对于一个划分的答案，就是所有对应长度的点集划分的 f 的乘积和。
枚举点集划分是不可取的，事实上，将对应的 f 做一个并卷积，最终序列的全集位置的值就是答案。
因为确定了长度划分，如果若干集合存在一对有交，它们的并的长度就会小于 n ，不可能是全集。

常数略微有点大。
复杂度本身其实也有点炸裂，上界 O(K 2^n n + 2^n n^2) ，其中 K 是 n 的划分数。
不过实现好的话应该能做到 O(K 2^n + 2^n n^2) 。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator bool () {
		int c = getchar(); while (c != '0' and c != '1') c = getchar();
		return c == '1';
	}
	template<class T> inline void operator () (T &x) { x = *this; }
} read;

const int maxn = 19;
bool link[maxn][maxn];
ll Ans[1 << maxn], f[maxn][1 << maxn], g[1 << maxn][maxn], tmp[1 << maxn];

void FWT_or (ll *a, int n, int x) {
	for (int m = 1; m < n; m <<= 1)
		for (int i = 0; i < n; i += m << 1)
			for (int k = i; k < i + m; k ++)
				a[k + m] += a[k] * x;
}

void iFMT (ll *a, int n) {
	for (int m = 1; m < n; m <<= 1)
		for (int i = 0; i < n; i += m << 1)
			for (int k = i; k < i + m; k ++)
				a[k] -= a[k + m];
}

int a[maxn];

ll solve (int n, int p) {
	/* debug("solve"); */
	/* for (int i = 0; i < p; i ++) debug(" %d", a[i]); */
	/* debug("\n"); */
	std::fill(tmp, tmp + (1 << n), 1);
	for (int i = 0; i < p; i ++)
		for (int S = 0; S < (1 << n); S ++)
			tmp[S] *= f[a[i]][S];
	FWT_or(tmp, 1 << n, -1);
	/* debug("get %lld\n", tmp[(1 << n) - 1]); */
	return tmp[(1 << n) - 1];
}

int main () {
	int n = read;
	for (int i = 0; i < n; i ++)
		for (int j = 0; j < n; j ++)
			read(link[i][j]);

	f[0][0] = 1;
	for (int S = 0; S < (1 << n); S ++) {
		int tot = 0;
		for (int i = 0; i < n; i ++) tot += S >> i & 1;
		for (int i = 0; i < n; i ++)
			if (S >> i & 1) {
				int T = S ^ (1 << i);
				if (T == 0)
					g[S][i] = 1;
				for (int j = 0; j < n; j ++)
					if (T >> j & 1 and link[i][j])
						g[S][i] += g[T][j];
				f[tot][S] += g[S][i];
			}
		/* debug("f[%d] = %lld\n", S, f[tot][S]); */
	}

	for (int i = 0; i < n; i ++)
		FWT_or(f[i], 1 << n, 1);

	for (int S = 0; S < (1 << n >> 1); S ++) {
		int p = 1;
		a[0] = 1;
		for (int i = 0; i < n - 1; i ++)
			S >> i & 1 ? ++ a[p - 1] : a[p ++] = 1;
		bool first = 1;
		for (int i = 0; i < p - 1; i ++)
			first &= a[i] >= a[i + 1];
		if (first) Ans[S] = solve(n, p);
		else {
			std::sort(a, a + p, [] (int x, int y) { return x > y; });
			int T = (1 << n) - 1, pre = 0;
			for (int i = 0; i < p; i ++)
				T ^= 1 << (pre += a[i]) >> 1;
			/* debug("%d -> %d\n", S, T); */
			Ans[S] = Ans[T];
		}
	}

	iFMT(Ans, 1 << n >> 1);
	for (int S = 0; S < (1 << n >> 1); S ++)
		printf("%lld ", Ans[S]);
	puts("");
}
