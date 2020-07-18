/*
 * Since g++10 is released, some characters is not valid inside #if 0 :(
 * So, why not using clang++? :D

 * Date:
  2020.07.18

 * Solution:
  如果是收益的基数是一个常数 X 而不是度数，不难得到一个 O(nlog) 的等比数列求和做法。
  而由于度数和是 O(n) 的，那么不同的度数就是 O(sqrt(n)) 的，对每个都跑一遍即可。
  需要注意的是等比数列求和需要用到快速幂，可以使用 O(1) 快速幂的技巧避免带 log 。

 * Digression:

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
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
    inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 100005, maxs = 31600, mod = 998244353;
std::vector<int> G[maxn];
int a[maxn], fa[maxn];
ll f[maxn];
int ans[maxn];
bool need[maxn];

struct Power {
	ll po1[maxs], po2[maxs];
	void init (int x) {
		po1[0] = po2[0] = 1;
		for (int i = 1; i < maxs; i ++)
			po1[i] = po1[i - 1] * x % mod;
		po2[1] = po1[maxs - 1] * x % mod;
		for (int i = 2; i < maxs; i ++)
			po2[i] = po2[i - 1] * po2[1] % mod;
	}
	inline ll power (int k) {
		return po2[k / maxs] * po1[k % maxs] % mod;
	}
} Po;

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

ll INV;
void dfs (int u, int s) {
	f[u] = 1;
	for (int v : G[u]) {
		dfs(v, s);
		(f[u] *= f[v]) %= mod;
	}
	if (s == 1) (f[u] *= a[u] + 1) %= mod;
	else (f[u] *= (mod + 1 - Po.power(a[u] + 1)) * INV % mod) %= mod;
	if (int(G[u].size()) == s)
		ans[u] = int(f[u]);
}

int main () {
	int n = read;
	for (int i = 2; i <= n; i ++)
		G[fa[i] = read].push_back(i);
	for (int i = 1; i <= n; i ++)
		a[i] = read;

	for (int i = 1; i <= n; i ++)
		need[int(G[i].size())] = 1;

	for (int i = 0; i <= n; i ++)
		if (need[i]) {
			Po.init(i);
			INV = power(mod + 1 - i, -1);
			dfs(1, i);
		}

	for (int i = 1; i <= n; i ++)
		printf("%d\n", ans[i]);
}
