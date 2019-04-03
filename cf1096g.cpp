#pragma GCC optimize(3)
#if 0
date

先设 DP 式 f[i][x] 表示用 i 个数和为 x 的方案数。
将 f[i] 看做多项式，那么转移就是与 f[1] 的卷积，
所以 f[n] 就是 f[1] ^ n ，多项式快速幂。
需要动态处理多项式长度。

cao, 我真 naive, 多项式快速幂取模的 FFT 真的不可靠，学一发 NTT 。

emm 被卡常了，最重要的优化就是直接把多项式转成点值再快速幂，在最后逆变换。
#endif
#include <bits/stdc++.h>

const int maxn = 4000005, mod = 998244353;
typedef long long lolong;
lolong f[maxn], ans[maxn], tmp[maxn];
int rader[maxn];

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

void NTT(lolong *a, int n, int type) {
	for(int i = 0; i < n; i ++)
		if(i < rader[i])
			std::swap(a[i], a[rader[i]]);
	for(int m = 2; m <= n; m <<= 1) {
		lolong Gn = power(3, type * (mod - 1) / m);
		for(int i = 0; i < n; i += m) {
			lolong G = 1;
			for(int k = i; k < i + (m >> 1); k ++) {
				lolong &x0 = a[k], &x1 = a[k + (m >> 1)], // 卡常
					a0 = x0, a1 = x1 * G % mod;
				x0 = (a0 + a1) % mod;
				x1 = (mod + a0 - a1) % mod;
				(G *= Gn) %= mod;
			}
		}
	}
	if(type == -1) {
		lolong pp = power(n, -1); // 卡常
		for(int i = 0; i < n; i ++)
			(a[i] *= pp) %= mod;
	}
}

int main() {
	std::ios::sync_with_stdio(false);
	int n, k;
	std::cin >> n >> k;
	n >>= 1;
	int flen = 0;
	for(int i = 0; i < k; i ++) {
		int x;
		std::cin >> x;
		f[x] = 1;
		flen = std::max(flen, x + 1);
	}
	ans[0] = 1;
	int maxlen = 1, loglen = 0;
	while(maxlen < (flen - 1) * n + 1) {
		maxlen <<= 1;
		loglen ++;
	}
	for(int i = 1; i < maxlen; i ++)
		rader[i] = rader[i >> 1] >> 1 | (i & 1) << (loglen - 1);
	NTT(ans, maxlen, 1);
	NTT(f, maxlen, 1);
	while(n) {
		if(n & 1)
			for(int i = 0; i < maxlen; i ++)
				(ans[i] *= f[i]) %= mod;
		for(int i = 0; i < maxlen; i ++)
			(f[i] *= f[i]) %= mod;
		n >>= 1;
	}
	NTT(ans, maxlen, -1);
	NTT(f, maxlen, -1);
	lolong sum = 0;
	for(int i = 0; i < maxlen; i ++)
		(sum += ans[i] * ans[i]) %= mod;
	std::cout << sum << std::endl;
}
