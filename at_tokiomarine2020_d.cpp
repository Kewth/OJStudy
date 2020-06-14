/*
 * Since g++10 is released, some characters is not valid inside #if 0 :(
 * So, why not using clang++? :D

 * Date:
    2020.06.14

 * Solution:
    虽然是个背包问题，但在这个数据规模下朴素的背包 DP 一定是没有效果的。注意到树高只
有 18 ，也就是说每次背包的物品数量很少，枚举集合 2^18 也没有效果，但是通过折半就可以
达到 2^9 的复杂度。
    具体的，把深度不超过 9 的点预处理背包，然后对于询问一条链，把链上深度大于 9 的点
单独拿出来枚举集合，在预处理的背包上对应查询即可。

 * Digression:
    思维僵化了？

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
#include <vector>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator () (a...); }
} read;

const int maxn = 270000, maxw = 100005;
int val[maxn], wei[maxn], dep[maxn];
ll f[515][maxw];
ll sv[515], sw[515];

int main () {
	int n = read;
	for (int i = 1; i <= n; i ++)
		read(val[i], wei[i]);

	for (int i = 1; i <= n; i ++)
		dep[i] = dep[i >> 1] + 1;

	int K = dep[n] >> 1, Lim = 100000;
	for (int i = 1; i <= n and dep[i] <= K; i ++) {
		std::copy(f[i >> 1], f[i >> 1] + wei[i], f[i]);
		for (int w = wei[i]; w <= Lim; w ++)
			f[i][w] = std::max(f[i >> 1][w], f[i >> 1][w - wei[i]] + val[i]);
	}

	int q = read;
	while (q --) {
		int u = read, lim = read;
		if (dep[u] <= K) {
			printf("%lld\n", f[u][lim]);
			continue;
		}
		int p = dep[u] - K, x = u >> p;
		for (int i = 0; i < p; i ++)
			sv[1 << i] = val[u >> i], sw[1 << i] = wei[u >> i];
		ll ans = f[x][lim];
		for (int S = 0; S < (1 << p); S ++) {
			sv[S] = sv[S & (S - 1)] + sv[S & -S];
			sw[S] = sw[S & (S - 1)] + sw[S & -S];
			if (sw[S] <= lim)
				ans = std::max(ans, f[x][lim - sw[S]] + sv[S]);
		}
		printf("%lld\n", ans);
	}
}
