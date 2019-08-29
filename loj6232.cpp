#if 0
2019.08.29

一个类似哈希的神奇做法。
取一个数 M ，设 a[i] 表示 x % M = i 的数的异或和。
偶数次异或和没有影响，那么最后剩下的每个 a[i] > 0 ，
可以认为 a[i] 是一个答案。
如果 M 取的足够大，那么 k 个数中有两个 % M 相同的概率就可能足够小。

实在不行就双模数，增大一倍空间但是大大降低了冲突率。
一个判断是否冲突的方法是记 A[i] 表示 % M = i 的数 x 的 x * P + Q 的异或和。
P, Q 选得合适就可以通过 a[i] * P + Q 与 A[i] 比较判断是否冲突。

另外注意判断 0 。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;

inline int input() { int x; scanf("%d", &x); return x; }
inline lolong linput() { lolong x; scanf("%lld", &x); return x; }

const int M = 12333, N = 6666, P = 10000007, Q = 233, K = 505;
lolong a[M], b[N];
lolong A[M], B[N];
lolong ans[K];

int main() {
	int n = input(), k = input();

	while(n --) {
		lolong x = linput();
		a[x % M] ^= x;
		A[x % M] ^= x * P + Q;
		b[x % N] ^= x;
		B[x % N] ^= x * P + Q;
	}

	int p = 0;
	for(int i = 0; i < M; i ++)
		if(a[i] and a[i] * P + Q == A[i]) {
			ans[++ p] = a[i];
			b[a[i] % N] ^= a[i];
			B[a[i] % N] ^= a[i] * P + Q;
		}

	for(int i = 0; i < N; i ++)
		if(b[i] and b[i] * P + Q == B[i])
			ans[++ p] = b[i];

	if(p != k)
		ans[++ p] = 0;

	std::sort(ans + 1, ans + p + 1);

	for(int i = 1; i <= p; i ++)
		printf("%lld\n", ans[i]);
}
