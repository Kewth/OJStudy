#if 0
2020.03.24

对于修改操作，不妨考虑指定的点为根。
那么一个点的权值发生改变，当且仅当随机的点与其不在一颗子树。
那么每个点的权值期望就会增加 (n - size) / n * d ，其中 size 是该点所在子树大小。
一个暴力的想法是对于每个子树进行区间加，但是这样的复杂度与度数成正比。

注意到一颗子树的修改系数只与 size 有关，而 size 的总和是 O(n) 的。
对 size 根号分治，size >= sqrt(n) 的子树数量不超过 sqrt(n) ，暴力扫每一个进行区间加，
size < sqrt(n) 的子树种类不超过 sqrt(n) ，令相同 size 的子树 dfs 序连续，
然后对于每种 size 进行区间加即可。

注意到每次修改要进行 O(sqrt(n)) 次区间加，而询问只要进行一次单点查。
树状数组其实并不合适，用分块维护，O(1) 区间加 O(sqrt(n)) 单点查，总复杂度 O(q sqrt(n)) 。

以上两段屁话。

黑科技，树链剖分，对于修改操作，只对关键点的重儿子进行区间加，然后在关键点上打标记，
查询的时候，除了单点查询外，还要考虑作为轻儿子被忽略的贡献，在重链上跳，每次跳就加上标记。
总复杂度 O(q logn) ，优秀许多。
#endif
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cmath>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 150005, mod = 998244353;
ll bit[maxn];
std::vector<int> G[maxn];
int top[maxn], deep[maxn], fa[maxn], size[maxn], son[maxn];
ll tag[maxn];

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

void modify (int l, int r, ll x) {
	for (int k = r; k; k -= k & -k) bit[k] += x;
	for (int k = l - 1; k; k -= k & -k) bit[k] -= x;
}

ll query (int p) {
	ll res = 0;
	for (int k = p; k < maxn; k += k & -k) res += bit[k];
	return res % mod;
}

void dfs1 (int u) {
	deep[u] = deep[fa[u]] + 1;
	size[u] = 1;
	for (int v : G[u])
		if (v != fa[u]) {
			fa[v] = u;
			dfs1(v);
			size[u] += size[v];
			if (size[v] > size[son[u]])
				son[u] = v;
		}
}

int id[maxn], iid[maxn], ip;
void dfs2 (int u) {
	if (!top[u]) top[u] = u;
	id[u] = ++ ip;
	if (son[u]) {
		top[son[u]] = top[u];
		dfs2(son[u]);
		for (int v : G[u])
			if (v != fa[u] and v != son[u])
				dfs2(v);
	}
}

int main () {
	int n = read, q = read;
	for (int i = 1; i < n; i ++) {
		int u = read, v = read;
		G[u].push_back(v);
		G[v].push_back(u);
	}

	dfs1(1);
	dfs2(1);

	ll inv = power(n, -1);

	while (q --) {
		int o = read;
		if (o == 1) {
			int u = read, s = son[u];
			ll x = read * inv % mod;
			modify(1, n, x * n % mod);
			if (s) modify(id[s], id[s] + size[s] - 1, size[s] * (mod - x) % mod);
			modify(1, n, (n - size[u]) * (mod - x) % mod);
			modify(id[u], id[u] + size[u] - 1, (n - size[u]) * x % mod);
			tag[u] += x;
		}
		if (o == 2) {
			int u = read;
			ll ans = query(id[u]);
			while (u) {
				u = top[u];
				(ans += size[u] * (mod - tag[fa[u]])) %= mod;
				u = fa[u];
			}
			printf("%lld\n", ans);
		}
	}
}
