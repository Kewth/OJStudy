#if 0
2019.10.22

将 0, 2 的最低点连成路径，不难发现问题等价与求放两条无交路径的方案数。
神奇容斥，先不考虑无交点的限制，就是 A 从 (0, m) 走到 (n, 0) B 从 (1, m + 1) 到 (n + 1, 1) ，
方案数 C(n + m, n) C(n + m, m) 。
然后考虑每个有交点的方案，把最后一个交点 A, B 的出路交换，
那么变成了 A 从 (0, m) 到 (n + 1, 1) B 从 (1, m + 1) 到 (n, 0) ，
并且每个有交点的方案都能与上述的路径一一对应，反之亦然，
故有交点的方案数就是 C(n + m, n - 1) C(n + m, m - 1) 。

UPDATE: 这玩意就是不交路径计数。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;

inline int input() { int x = -1; scanf("%d", &x); return x; }

const int maxn = 1000005, mod = 1000000007;
lolong fac[maxn << 1], ifac[maxn << 1];

inline lolong C(int n, int m) {
	return fac[n] * ifac[m] % mod * ifac[n - m] % mod;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("gird.in", "r", stdin);
	freopen("gird.out", "w", stdout);
#endif

	fac[0] = 1;
	for(int i = 1; i < (maxn << 1); i ++)
		fac[i] = fac[i - 1] * i % mod;
	ifac[0] = ifac[1] = 1;
	for(int i = 2; i < (maxn << 1); i ++)
		ifac[i] = (mod - mod / i) * ifac[mod % i] % mod;
	for(int i = 1; i < (maxn << 1); i ++)
		(ifac[i] *= ifac[i - 1]) %= mod;

	while(1) {
		int n = input(), m = input();
		if(n == -1) break;
		/* debug("%lld %lld %lld\n", */
		/* 		C(n + m - 4, n - 2), C(n + m - 4, n - 3), C(n + m - 4, m - 3)); */
		printf("%lld\n", (C(n + m, n) * C(n + m, m) +
				mod - C(n + m, n - 1) * C(n + m, m - 1) % mod) % mod);
	}
}
