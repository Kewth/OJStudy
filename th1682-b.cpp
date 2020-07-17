/*
 * Since g++10 is released, some characters is not valid inside #if 0 :(
 * So, why not using clang++? :D

 * Date:
  2020.07.17

 * Solution:
 * 设计 DP ，卡特兰数，生成函数，组合意义，折线法

  首先众所周知的是 n 边形的剖分方案数是 C[n - 2] ，其中 C 是卡特兰数。

  那么可以据此设计 DP 解决问题，固定一个 m 边形，在每条边上依次加入若干点，不难发现除
了最后一条边比较特殊外（需要确定 m 边形的相对位置），其他的转移就是背包，系数就是卡特
兰数，那么事实上问题可以转换为求卡特兰数的生成函数 C(x) 的 m - 1 次幂的各项系数。

  由 C(x) 一个重要的等式 1 + x C(x)^2 = C(x) 可以不断把 C(x)^m 降次，最后转换为一个卷
积形式，得到 O(nlog) 的做法，不在讨论范围内。

  直接考虑 C(x)^m 第 n 项的组合意义，幂次的意义就是把 n 划分为 m 个非负整数的卡特兰数
乘积的和。而卡特兰数的组合意义就是从 (0, 0) 走到 (2n, 0) 始终在 x 轴上方的路径数。结合
起来，就是把 m 段折线拼接起来，每个拼接的位置都恰好在 x 轴上。

  一步神仙的转换来了，在每个拼接点后把整个路径平移 (1, -1) ，那么终点被平移恰好 m - 1
次，到了 (2n + m - 1, 1 - m) 的位置，限制的直线也从 y = 0 平移到了 y = 1 - m ，于是方
案数就是此时从 (0, 0) 到终点的不越过该直线的路径数，用折线法可以 O(1) 求出。

 * Digression:
  折线法再一次战胜生成函数。正如《生成函数的败北》一文所说，就算能列出生成函数的式子，
未必就能用生成函数简单推导出优秀的结果，尤其在这类路径问题上更显得无力。

 * CopyRight:
          ▁▃▄▄▄▃▃▃▃▄▶
        ▗▇▀▔    ▔▔▔▔
       ▄▛   ▃▅━━■▄▂
      ▟▊   ▐▘     ▀▙
     ▟▜▌   ▐▖   ▋  ▐▍
    ▟▘ ▜   ▝▀▇▆●▘  ▐▌
  ▗▟▘   ▜▃       ▁▅▛
  ▔▀▼▅▄▃▃██▅▄▄▄▅■▀▔
        ▔▔▔▔▔▔
 */

#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 15000005, mod = 1000000007;
ll fac[maxn], ifac[maxn];

inline ll power (ll x, int k) {
	if (k < 0) k += mod - 1;
	ll res = 1;
	while (k) {
		if (k & 1) (res *= x) %= mod;
		(x *= x) %= mod;
		k >>= 1;
	}
	return res;
}

ll C (int n, int m) {
	if (m > n) return 0;
	return fac[n] * ifac[m] % mod * ifac[n - m] % mod;
}

ll Ca (int n, int m) {
	if (n == 0) return 1;
	ll res = C(n + n + m - 1, n) - C(n + n + m - 1, n - 1);
	return res < 0 ? res + mod : res;
}

int main () {
	int n = read, m = read;

	int lim = n + n + m;
	fac[0] = 1;
	for (int i = 1; i <= lim; i ++) fac[i] = fac[i - 1] * i % mod;
	ifac[lim] = power(fac[lim], -1);
	for (int i = lim; i; i --) ifac[i - 1] = ifac[i] * i % mod;

	ll sum = 0, ans = 0;
	for (int i = 0; i <= n - m; i ++) {
		(sum += Ca(i, 1) * (i + 1)) %= mod;
		(ans += Ca(n - m - i, m - 1) * sum) %= mod;
	}

	printf("%lld\n", ans * Ca(m - 2, 1) % mod);
}
