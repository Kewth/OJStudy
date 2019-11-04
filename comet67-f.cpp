#if 0
2019.11.03

DAG 是可拓扑的，考虑用拓扑排序的过程统计 DAG 的方案数。
设 f[S] 表示点集 S 内的 DAG 方案，枚举入度为 0 的非空点集 T ，
那么 T 内的边需要全部删掉，T 与 S - T 之间的边要么删掉要么必须从 T 这边出发。
设 g[S] 表示点集 S 内的边数，T 与 S - T 边的数量通过简单容斥，
可以得到就是 g[S] - g[T] - g[S - T] ，那么 f 的转移就是
f[S] = sum(2^(g[S] - g[T] - g[S - T]) f[S - T]) ，
但是无法保证 S - T 内的点的入度都不为 0 ，考虑容斥，
枚举 T 换为钦定 T 内入度为 0 ，那么容斥系数就是 -(-1)^|T| 。
转移可以写成
f[S] / 2^g[S] = sum(f[S - T] / 2^g[S - T] -(-1)^|T| / 2^g[T]) 。
不难发现是个子集卷积，虽然是 f 自己和另一个函数卷，
但是子集卷积的优秀性质使得它并不需要分治 FFT 之类的，加上一维后 f 到 f 的转移没有后效性。

垃圾玩意卡空间。
#endif
#include <cstdio>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
} read;

const int maxn = 20, mod = 998244353;
int g[1 << maxn];
int h[maxn + 1][1 << maxn], f[maxn + 1][1 << maxn];

inline ll power(ll x, int k) {
	if(k < 0) k += mod - 1;
	ll res = 1;
	while(k) {
		if(k & 1) (res *= x) %= mod;
		(x *= x) %= mod;
		k >>= 1;
	}
	return res;
}

int count(int x) {
	int res = 0;
	while(x) {
		res ++;
		x -= x & -x;
	}
	return res;
}

inline void FMT(int *a, int n, int t) {
	for(int m = 1; m < n; m <<= 1)
		for(int i = 0; i < n; i += m << 1)
			for(int k = i; k < i + m; k ++)
				if(t == 1)
					(a[k + m] += a[k]) %= mod;
				else
					(a[k + m] += mod - a[k]) %= mod;
}

int main() {
	int n = read, m = read;

	for(int i = 1; i <= m; i ++) {
		int u = read - 1, v = read - 1;
		g[1 << u | 1 << v] = 1;
	}

	FMT(g, 1 << n, 1);

	for(int S = 1; S < (1 << n); S ++)
		h[count(S)][S] = power(mod - 1, count(S) + 1) * power(2, - g[S]) % mod;

	/* for(int S = 0; S < (1 << n); S ++) */
	/* 	debug("%d\n", count(S)); */

	/* for(int S = 1; S < (1 << n); S ++) */
	/* 	debug("%lld\n", h[count(S)][S]); */

	for(int i = 1; i <= n; i ++)
		FMT(h[i], 1 << n, 1);

	f[0][0] = 1;
	FMT(f[0], 1 << n, 1);

	for(int i = 1; i <= n; i ++)
		for(int j = 0; j < i; j ++)
			for(int S = 0; S < (1 << n); S ++)
				f[i][S] = (f[i][S] + 1ll * f[j][S] * h[i - j][S]) % mod;

	FMT(f[n], 1 << n, -1);

	ll ans = f[n][(1 << n) - 1];
	(ans *= power(2, g[(1 << n) - 1])) %= mod;
	(ans *= power(3, - m)) %= mod;

	printf("%lld\n", ans);
}
