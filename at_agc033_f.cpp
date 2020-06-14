/*
 * Since g++10 is released, some characters is not valid inside #if 0 :(
 * So, why not using clang++? :D

 * Date:
  2020.06.13

 * Solution:
  一个朴素的想法是逐个加边，把要加的边放进栈里，每次加边 (x, y) 就枚举所有 z 考虑是否能够松
弛出新的边，复杂度 O(n^3) ，边数是 O(n^2) 的，复杂度变大的原因在于重复松弛，枚举了不必要的
z 。
  考虑一个合法的 z 要满足什么条件，只有两点：z 和 x, y 在图上恰有一条边，x, y, z 在树上有路
径。对于前者，用 G[u] 表示与 u 相连的点的集合，就可以很好用集合表示；对于后者，在树上设两个
集合 Sub[u], Up[u] 分别表示 u 的子树集合和 u 到根的集合，那么满足条件的 z 同样是可以用集合
运算表示的。那么用 bitset 维护集合，便可以快速求出能松弛的点集 z ，在 bitset 上枚举 z 即可。
  复杂度 O(n^3/w) ，官方给的做法似乎是 O(n^2 + nm) 的。

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
typedef unsigned long long ull;

struct _{
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
} read;

const int maxn = 2005, lim = 32, maxk = 20;
struct bitset {
	ull bit[lim];
	inline void set (int k) { bit[k >> 6] |= 1llu << (k & 63); }
	inline bool test (int k) { return bit[k >> 6] >> (k & 63) & 1; }
	inline void operator &= (const bitset &an) {
		for (int i = 0; i < lim; i ++)
			bit[i] &= an.bit[i];
	}
	inline void operator |= (const bitset &an) {
		for (int i = 0; i < lim; i ++)
			bit[i] |= an.bit[i];
	}
	inline void operator ^= (const bitset &an) {
		for (int i = 0; i < lim; i ++)
			bit[i] ^= an.bit[i];
	}
	inline void minus (const bitset &an) {
		for (int i = 0; i < lim; i ++)
			bit[i] &= ~an.bit[i];
	}
};
std::vector<int> T[maxn];
bitset G[maxn];
int stx[maxn * maxn], sty[maxn * maxn], sp;
int deep[maxn], fa[maxk][maxn];
/* int iid[maxn], id[maxn], size[maxn], ip; */
bitset sub[maxn], up[maxn];

void dfs (int u) {
	for (int k = 1; k < maxk; k ++)
		fa[k][u] = fa[k - 1][fa[k - 1][u]];
	deep[u] = deep[fa[0][u]] + 1;
	/* iid[id[u] = ++ ip] = u; */
	/* size[u] = 1; */
	up[u] = up[fa[0][u]];
	up[u].set(u);
	sub[u].set(u);
	for (int v : T[u])
		if (v != fa[0][u]) {
			fa[0][v] = u;
			dfs(v);
			/* size[u] += size[v]; */
			sub[u] |= sub[v];
		}
}

int lca (int x, int y) {
	if (deep[x] < deep[y]) std::swap(x, y);
	for (int k = maxk - 1; k >= 0; k --)
		if (deep[fa[k][x]] >= deep[y])
			x = fa[k][x];
	if (x == y) return x;
	for (int k = maxk - 1; k >= 0; k --)
		if (fa[k][x] != fa[k][y])
			x = fa[k][x], y = fa[k][y];
	return fa[0][x];
}

void update (int x, const bitset &b, int y) {
	for (int i = 0; i < lim; i ++)
		if (b.bit[i]) {
			ull S = b.bit[i];
			while (S) {
				int k = __builtin_ctzll(S);
				S ^= 1llu << k;
				int z = i << 6 | k;
				if (z == x or z == y) continue;
				if (G[y].test(z)) {
					debug("ERROR\n");
					continue;
				}
				G[y].set(z);
				G[z].set(y);
				++ sp;
				stx[sp] = y, sty[sp] = z;
			}
		}
}

bitset full;
int main () {
	int n = read, m = read;
	for (int i = 1; i < n; i ++) {
		int u = read, v = read;
		T[u].push_back(v);
		T[v].push_back(u);
	}

	dfs(1);
	for (int i = 1; i <= n; i ++) full.set(i);

	while (m --) {
		int x = read, y = read;
		++ sp;
		stx[sp] = x;
		sty[sp] = y;
		G[x].set(y);
		G[y].set(x);
	}

	while (sp) {
		int x = stx[sp], y = sty[sp];
		if (deep[x] < deep[y]) std::swap(x, y);
		-- sp;
		bitset a;
		if (sub[y].test(x)) {
			int z = x;
			for (int k = maxk - 1; k >= 0; k --)
				if (deep[fa[k][z]] > deep[y])
					z = fa[k][z];
			a = full;
			a ^= sub[z];
			a |= up[x];
			a |= sub[x];
		}
		else {
			int c = lca(x, y);
			a = sub[x];
			a |= sub[y];
			bitset tmp = up[x]; tmp ^= up[y];
			a |= tmp;
			a.set(c);
		}
		bitset ax = a, ay = a;
		ax &= G[x], ay &= G[y];
		ax.minus(G[y]), ay.minus(G[x]);
		update(x, ax, y);
		update(y, ay, x);
	}

	int ans = 0;
	for (int i = 1; i <= n; i ++)
		for (int j = i + 1; j <= n; j ++)
			ans += G[i].test(j);
	printf("%d\n", ans);
}
