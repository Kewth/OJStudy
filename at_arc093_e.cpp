/*
 * Since g++10 is released, some characters is not valid inside #if 0 :(
 * So, why not using clang++? :D

 * Date:
  2020.07.14

 * Solution:
  不妨考虑求最小的满足条件的生成树的权值和 >= X 的方案数。那么这个限制就是要求所有权值和
小于 X 的生成树的边的颜色都必须相同。
  不难发现可以把边分为两类：一类是自由边，一类是非自由边，一条边是非自由边当且仅当存在一
颗权值和小于 X 的生成树包含了该边。那么所有非自由边必须染一种颜色，每条自由边可以随意染
色，总方案数就是 2^min(k + 1, m) ，其中 k 是自由边数量。
  求自由边数量只需要暴力判断每条边是否是自由边，也就是对于每条边 e 求出包含 e 的最小生成
树即可。

 * Digression:
  复杂度 O(m^2 a) ，其中 a 是并查集均摊复杂度。但是显然求包含 e 的最小生成树是有更优秀的
做法的，复杂度可以做到 O(mlog) ，这里略去。

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

struct _{
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
} read;

const int maxn = 2020, mod = 1000000007;
struct Edge {
	int u, v, w;
} e[maxn];
int fa[maxn];

ll power (ll x, int k) {
	ll res = 1;
	while (k) {
		if (k & 1) (res *= x) %= mod;
		(x *= x) %= mod;
		k >>= 1;
	}
	return res;
}

bool cmp (Edge a, Edge b) { return a.w < b.w; }

int find (int x) {
	if (fa[x] == x) return x;
	return fa[x] = find(fa[x]);
}

ll calc (int n, int m, int id) {
	for (int i = 1; i <= n; i ++) fa[i] = i;
	fa[e[id].u] = e[id].v;
	ll sum = e[id].w;
	for (int i = 1; i <= m; i ++) {
		int x = find(e[i].u), y = find(e[i].v);
		if (x != y) {
			fa[x] = y;
			sum += e[i].w;
		}
	}
	return sum;
}

int main () {
	int n = read, m = read;
	ll X = read;
	for (int i = 1; i <= m; i ++) {
		e[i].u = read;
		e[i].v = read;
		e[i].w = read;
	}
	std::sort(e + 1, e + m + 1, cmp);
	int a = 0, b = 0;
	for (int i = 1; i <= m; i ++) {
		ll s = calc(n, m, i);
		/* debug("%lld\n", s); */
		if (s >= X) ++ a;
		if (s > X) ++ b;
	}
	a = std::min(a + 1, m);
	b = std::min(b + 1, m);
	printf("%lld\n", (power(2, a) - power(2, b) + mod) % mod);
}

