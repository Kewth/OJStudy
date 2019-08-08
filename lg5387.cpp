#if 0
2019.08.08

原题数据似乎有问题，只有 1 个人 AC ，我自信不会写错，那就当它 A 了。
这个 sg 函数打个表很容易找出规律，是 1, 1 ~ 2, 1 ~ 4, 1 ~ 8, ... 这样，
那倍增 1 ~ 2^x 这个区间长，差分做一个区间加 1 ，得到数组 f1 。
f1[x] 即 sg = x 的值的数量。
那么设 f[i][j] 表示选 i 个子游戏异或出 j 的方案数，
转移自然是异或卷积，FWT 可以优化，最终就是 m 个 f1 的卷积，
多项式快速幂搞过去即可
#endif
#include <cstdio>
#include <algorithm>
#include <cassert>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;
inline lolong input() { lolong x; scanf("%lld", &x); return x; }

const int maxm = 2000005, mod = 998244353;
int sg[maxm];
lolong f[maxm], g[maxm];

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

void FWT(lolong *a, int n, int typ) {
	for(int m = 1; m < n; m <<= 1)
		for(int i = 0; i < n; i += m << 1)
			for(int k = i; k < i + m; k ++) {
				lolong a0 = a[k], a1 = a[k + m];
				a[k] = (a0 + a1) % mod;
				a[k + m] = (a0 - a1 + mod) % mod;
			}
	if(typ == -1) {
		lolong pp = power(n, -1);
		for(int i = 0; i < n; i ++)
			(a[i] *= pp) %= mod;
	}
}

int main() {
	lolong n = input();
	int m = input(), len = 1;
	for(int i = m; i > 0; i -= len, len <<= 1)
		g[std::min(i, len)] ++;
	for(int i = len - 2; i; i --)
		g[i] += g[i + 1];
	assert(g[0] == 0);
	f[0] = 1;
	FWT(f, len, 1);
	FWT(g, len, 1);
	while(n) {
		if(n & 1)
			for(int i = 0; i < len; i ++)
				(f[i] *= g[i]) %= mod;
		for(int i = 0; i < len; i ++)
			(g[i] *= g[i]) %= mod;
		n >>= 1;
	}
	FWT(f, len, -1);
	FWT(g, len, -1);
	lolong ans = 0;
	// for(int i = 0; i < len ; i++)
		// debug("%d: %lld\n", i, f[i]);
	for(int i = 1; i < len ; i++)
		ans += f[i];
	printf("%lld\n", ans % mod);
}
