#if 0
2019.10.18

类似于按位或，将第 i 个原料的第一次出现时间看做随机变量 X_i ，
那么答案就是所有 X_i 的第 k 小的期望，也就是 E(k-minS) ， S 是全集，包含所有 X_i 。
先把 k 小转为 n - k + 1 大，然后扩展 min-max 容斥转为有关 sum{T|S} F(T) E(minT) 的式子。
E(minT) 是很好求的，一个集合的第一个有原料出现的时间就是 1 / P(T) ，
其中 P(T) 是 T 集合代表的所有原料的概率和。

但是 n 很大，直接计算是 O(2^n) 的，无法接受，但是 m 和转换后的 k 足够小。

考虑枚举 P(T) 的值 j ，然后计算选取子集概率和为 j 的贡献和，记为 f(j) 。
但 f(j) 仍然难以计算，由于是枚举子集，一个一个元素考虑是否在选取的集合中，
若当前考虑了前 i 个元素，设这样得到的值为 f(i, j) 。
那么考虑递推，对于第 i 个元素如果不选，直接从 f(i - 1, j) 继承，如果选入子集，
那么原来要求概率和为 j 的限制到了前 i - 1 个就变为了概率和为 j - p[i] ，
也就是说 f(i, j) 应从 f(i - 1, j) 和 f(i - 1, j - p[i]) 转移而来。
然而还是不够，不能选空集的限制到了前 i - 1 个中，由于选了 X_i ，空集又成为可行的了。
干脆去掉空集的限制，但这样 f(i, j) 的式子中就出现了 C(-1, k - 1) 这样的奇怪组合数。
递推的过程需要用到组合数的递推式，
而如果能够对 C(-1, k - 1) 给出良好的定义使得它仍满足递推式，这个问题就解决了。
那么，由 C(0, 0) = C(-1, -1) + C(-1, 0) = 1 以及 C(0, 1) = C(-1, 0) + C(-1, 1) = 0 等，
不难得出 C(-1, k) 在 k = -1 时为 1 ，k=-2 时为 -1 ，否则为 0 。
据此就可以很轻松地通过组合数的递推式得到 f(i, j) 的递推式，不难发现 k 在其中的影响发生改变，
因此再加一维 f(i, j, k) 把 k 纳入状态，然后通过上述的组合数也能得出 f(0, j, k) 的边界。
#endif
#include <cstdio>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;

inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 1010, maxk = 12, maxm = 10005, mod = 998244353;
int p[maxn];
lolong f[2][maxm][maxk];

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

int main() {
	int n = input(), K = n - input() + 1, m = input();
	for(int i = 1; i <= n; i ++)
		p[i] = input();

	f[0][0][0] = 1;
	for(int i = 1; i <= n; i ++) {
		bool o = i & 1;
		for(int j = 0; j <= m; j ++) {
			f[o][j][0] = j == 0;
			for(int k = 1; k <= K; k ++) {
				f[o][j][k] = f[!o][j][k];
				if(j >= p[i])
					(f[o][j][k] += f[!o][j - p[i]][k - 1] +
					 mod - f[!o][j - p[i]][k]) %= mod;
				/* debug("f[%d][%d][%d] = %lld\n", i, j, k, f[o][j][k]); */
			}
		}
	}

	lolong ans = 0;
	for(int j = 1; j <= m; j ++)
		(ans += f[n & 1][j][K] * power(j, -1)) %= mod;
	(ans *= m) %= mod;

	printf("%lld\n", ans);
}
