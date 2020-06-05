/*
 * Since g++10 is released, some characters is not valid inside #if 0 :(
 * So, why not using clang++? :D

 * Date:
  2020.06.05

 * Solution:
    问题就是所有排列对应的置换的阶的乘积，其中一个置换的阶就是其对应的轮换的大小的
lcm 。lcm 按套路枚举每个 p^k ，然后算有多少个置换的阶是 p^k 的倍数，设 P = p^k 。
    枚举轮换的大小 x * P ，然后计算有多少个置换的分解包含这样的轮换，显然就是在 n
个数中选 xP 个，然后 xP 是一个圆排列，其他的是任意排列。但是如果一个置换包含多个大
小为 P 的倍数的轮换，该置换就会被计算多次，处理这个问题显然可以子集容斥。
    朴素的容斥枚举一个可重集合，用 DP 描述这个容斥，设 f[i][j] 表示钦定 i 个大小为
P 的倍数的轮换，它们的大小的和为 j ，满足这样的条件的置换的数（可重）。转移枚举这
些关键轮换中编号最小的位置所对应的轮换的大小 xP ，然后在 j - 1 个数中选 xP - 1 个
数，表示该轮换具体对应的点，注意到编号最小的点已经是被钦定的，然后乘上 xP 的圆排列
即可。
    总所周知这样 f 的第一维只需要关心奇偶性，于是这个 DP 可以优化到 O(n^2) ，总复
杂度是枚举每个 P ，然后做 O((n/P)^2) 的 DP ，总复杂度仍然是 O(n^2) 。另外组合数的
预处理也需要 O(n^2) ，注意到这里算的实际上是指数，是模 mod - 1 意义下的运算。

 * Digression:
    学到许多，这个钦定一号点的组合方法确实没有想到，走了很多弯路。

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

const int maxn = 7505;
bool nop[maxn];
ll f[maxn], g[maxn];
ll C[maxn][maxn];
ll fac[maxn];

inline ll power (ll x, ll k, int mod) {
	if (k < 0) k += mod - 1;
	ll res = 1;
	while (k) {
		if (k & 1) (res *= x) %= mod;
		(x *= x) %= mod;
		k >>= 1;
	}
	return res;
}

int main () {
	int n = read, Mod = read, mod = Mod - 1;

	for (int i = 0; i <= n; i ++) {
		C[i][0] = 1;
		for (int j = 1; j <= i; j ++)
			if ((C[i][j] = C[i - 1][j] + C[i - 1][j - 1]) >= mod)
				C[i][j] -= mod;
	}

	fac[0] = 1;
	for (int i = 1; i <= n; i ++)
		fac[i] = fac[i - 1] * i % mod;

	for (int i = 2; i <= n; i ++)
		if (!nop[i])
			for (int j = i + i; j <= n; j += i)
				nop[j] = 1;

	ll ans = 1;
	for (int i = 2; i <= n; i ++)
		if (!nop[i]) {
			for (int p = i; p <= n; p *= i) {
				for (int s = 0; s <= n; s += p) f[s] = 0;
				f[0] = mod - 1;
				for (int s = p; s <= n; s += p) {
					f[s] = 0;
					for (int x = p; x <= s; x += p)
						(f[s] += (mod - f[s - x]) * fac[x - 1] % mod *
						 C[s - 1][x - 1]) %= mod;
				}
				ll sum = 0;
				for (int s = p; s <= n; s += p)
					(sum += f[s] * fac[n - s] % mod * C[n][s]) %= mod;
				sum %= mod;
				(ans *= power(i, sum, Mod)) %= Mod;
			}
		}

	printf("%lld\n", ans);
}
