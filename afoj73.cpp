#if 0
2019.08.18

设 A[i] 表示 a 数组中值为 i 的元素数量，B[i] 同理。
那么设 ans[i] 表示众数为 i 的最大次数，那么容易得出 ans 关于 A, B 的表达式，
这个表达式很像卷积，不同的是把相乘变成了取 min ，暴力做是 O(n^2) 的。

考虑把 min 换成乘积以便使用 NTT/FFT 优化。
把原本表达式里的 min(A[i], B[j]) 换成 max(0, min(A[i] - 1, B[j] - 1)) 计算出 ans' 。
考虑 ans' 比 ans 少了什么，是 max 右边仍然不小于左边的情况。
也就是 A[i] * B[j] > 0 的情况。
那么可以用 NTT 把 A[i] * B[j] > 0 对 ans 的贡献算出来，
具体地，设 A'[i] = bool(A[i] > 0)，那么直接卷 A', B' 就行了。
接下来算 ans' ，这时候把所有 A[i] 替换成 max(0, A[i] - 1) ，B[i] 同理，那么又成了子问题。
这样一直做，直到当前所有 A, B 都为 0 ，最多做 n 次，复杂度 O(n^2 logn) ，没用。

优化上述做法，事实上每次子问题的转化会导致 A, B 取 0 的值变多（或不变），
如果 A, B 有很多值取 0 ，那么只考虑不为 0 的 A, B 之间取 min 的贡献，
如果 0 足够多，暴力算的复杂度是可以接受的。
具体地，如果当前做了 K 次转换，那么只有原来值大于 K 的 A, B 会产生贡献，
由于 A, B 的和都恰好为 n ，那么大于 K 的数是 O(n / K) 的，接下来暴力，复杂度 O(n^2 / K^2) 。

总复杂度 O(K*n*logn + n^2 / K^2) ，这实际上是一种另类的分块。
#endif
#include <cstdio>
#include <algorithm>
#include <vector>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;

inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 100005, mod = 998244353;

int a[maxn << 2], b[maxn << 2];
lolong A[maxn << 2], B[maxn << 2], C[maxn << 2];
int rev[maxn << 2];
int ans[maxn << 2];

lolong power(lolong x, int k) {
	if(k < 0) k += mod - 1;
	lolong res = 1;
	while(k) {
		if(k & 1) (res *= x) %= mod;
		(x *= x) %= mod;
		k >>= 1;
	}
	return res;
}

void NTT(lolong *f, int n, int typ) {
	for(int i = 0; i < n; i ++)
		if(i < rev[i])
			std::swap(f[i], f[rev[i]]);

	for(int m = 1; m < n; m <<= 1) {
		lolong G = power(3, (mod - 1) / (m << 1) * typ);
		for(int i = 0; i < n; i += (m << 1)) {
			lolong Gn = 1;
			for(int k = i; k < i + m; k ++) {
				lolong x = f[k], y = f[k + m] * Gn % mod;
				f[k] = (x + y) % mod;
				f[k + m] = (x - y + mod) % mod;
				(Gn *= G) %= mod;
			}
		}
	}

	if(typ == -1) {
		lolong p = power(n, -1);
		for(int i = 0; i < n; i ++)
			(f[i] *= p) %= mod;
	}
}

int main() {
	int n = input();
	for(int i = 1; i <= n; i ++)
		a[input()] ++;
	for(int i = 1; i <= n; i ++)
		b[input()] ++;

	int loglen = 0;
	while((1 << loglen) <= (n << 1))
		loglen ++;
	for(int i = 1; i < (1 << loglen); i ++)
		rev[i] = rev[i >> 1] >> 1 | ((i & 1) << (loglen - 1));

	int K = 10;

	for(int x = 1; x <= (n << 1) and x <= K; x ++) {
		for(int i = 0; i <= (1 << loglen); i ++)
			A[i] = x <= a[i];
		for(int i = 0; i <= (1 << loglen); i ++)
			B[i] = x <= b[i];

		NTT(A, 1 << loglen, 1);
		NTT(B, 1 << loglen, 1);
		for(int i = 0; i < (1 << loglen); i ++)
			C[i] = A[i] * B[i] % mod;
		NTT(C, 1 << loglen, -1);

		/* for(int i = 0; i < (1 << loglen); i ++) */
		/* 	debug(" %lld", C[i]); */
		/* debug("\n"); */

		for(int i = 0; i < (1 << loglen); i ++)
			ans[i] += C[i];
	}

	std::vector<int> va, vb;
	for(int i = 1; i <= n; i ++)
		if(a[i] > K)
			va.push_back(i);
	for(int i = 1; i <= n; i ++)
		if(b[i] > K)
			vb.push_back(i);
	for(int x : va)
		for(int y : vb)
			ans[x + y] += std::min(a[x], b[y]) - K;

	int max = 0;
	for(int i = 1; i <= (n << 1); i ++)
		max = std::max(max, ans[i]);
	printf("%d\n", max);
}
