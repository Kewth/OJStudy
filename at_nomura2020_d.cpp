#if 0
2020.05.30

  不妨把 P 看做 i -> P[i] 的有向边，那么最后的图一定是一个基环树森林，而最小的用边数量就是
n - C ，其中 C 是基环树的数量，那么问题可以转换为求 C 的期望。
  对于每个未确定出边的点，其当前一定是一棵树的根，设这棵树的大小为 s ，那么有 (n-s) / (n-1)
的概率连到其他树从而使联通块数量减 1 ，那么可以初步判定 C 的期望就是最初的联通块数量减去
这个概率和。
  但是这样会算重，因为对于某 k 个未确定出边的点，它们可能连成一个环，这样联通块数量只会减去
k - 1 而不是 k ，用 DP 算这部分，设 f[i][j] 表示考虑前 i 个未确定出边的点构成大小为 j 的环
的贡献和即可。
        ▁▃▄▄▄▃▃▃▃▄▶
      ▗▇▀▔    ▔▔▔▔
     ▄▛   ▃▅━━■▄▂
    ▟▊   ▐▘     ▀▙
   ▟▜▌   ▐▖   ▋  ▐▍
  ▟▘ ▜   ▝▀▇▆●▘  ▐▌
▗▟▘   ▜▃       ▁▅▛
▔▀▼▅▄▃▃██▅▄▄▄▅■▀▔   CopyRight :)
      ▔▔▔▔▔▔
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
} read;

const int maxn = 5050, mod = 1000000007;
int fa[maxn];
int deg[maxn];
int size[maxn];
int topsort[maxn], tp;
int bl[maxn];
int a[maxn], ap;
ll f[maxn];

inline int find (int x) {
	if (bl[x] == x) return x;
	return bl[x] = find(bl[x]);
}

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

int main () {
	int n = read, tot = 0;
	for (int i = 1; i <= n; i ++) {
		read(fa[i]);
		if (fa[i] != -1) ++ deg[fa[i]];
		else ++ tot;
	}

	for (int i = 1; i <= n; i ++)
		if (!deg[i])
			topsort[++ tp] = i;

	for (int i = 1; i <= tp; i ++) {
		int u = topsort[i];
		++ size[u];
		if (fa[u] != -1) {
			if (-- deg[fa[u]] == 0)
				topsort[++ tp] = fa[u];
			size[fa[u]] += size[u];
		}
	}

	ll sum = 0, inv = power(n - 1, -1);
	for (int i = 1; i <= n; i ++)
		if (fa[i] == -1) {
			(sum += (n - size[i]) * inv) %= mod;
			a[++ ap] = size[i];
		}

	f[0] = 1;
	for (int i = 1; i <= ap; i ++)
		for (int j = i; j; j --)
			(f[j] += f[j - 1] * a[i] % mod * inv) %= mod;

	ll fac = 1;
	for (int i = 2; i <= ap; i ++) {
		(fac *= i - 1) %= mod;
		(sum += (mod - fac) * f[i]) %= mod;
	}

	for (int i = 1; i <= n; i ++) bl[i] = i;
	for (int i = 1; i <= n; i ++)
		if (fa[i] != -1) {
			int x = find(i), y = find(fa[i]);
			bl[x] = y;
		}

	int C = 0;
	for (int i = 1; i <= n; i ++)
		if (bl[i] == i)
			++ C;

	printf("%lld\n", (n - C + sum) * power(n - 1, tot) % mod);
}
