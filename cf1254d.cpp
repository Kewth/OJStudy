#if 0
2020.03.23

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
（然而我写的还是树状数组）
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

const int maxn = 150005, maxb = 400, mod = 998244353;
std::vector<int> G[maxn], D[maxn], X[maxn];

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

int B;
ll bit[maxn];
void modify (int l, int r, ll x) {
	for (int k = r; k; k -= k & -k) bit[k] += x;
	for (int k = l - 1; k; k -= k & -k) bit[k] -= x;
}

ll query (int p) {
	ll res = 0;
	for (int k = p; k < maxn; k += k & -k) res += bit[k];
	return res % mod;
}

int size[maxn];
void dfs1 (int u, int fa) {
	size[u] = 1;
	for (int v : G[u])
		if (v != fa) {
			dfs1(v, u);
			size[u] += size[v];
		}
}

int id[maxn], iid[maxn], ip;
int lpos[maxn][maxb], rpos[maxn][maxb];
void dfs2 (int u, int fa) {
	id[u] = ++ ip;
	std::sort(G[u].begin(), G[u].end(), [](int x, int y) {
				return size[x] < size[y];
			});
	for (int v : G[u])
		if (v != fa) {
			dfs2(v, u);
			if (size[v] <= B) {
				if (!lpos[u][size[v]])
					X[u].push_back(size[v]), lpos[u][size[v]] = id[v];
				rpos[u][size[v]] = id[v] + size[v] - 1;
			} else
				D[u].push_back(v);
		}
}

int main () {
	int n = read, q = read;
	for (int i = 1; i < n; i ++) {
		int u = read, v = read;
		G[u].push_back(v);
		G[v].push_back(u);
	}

	B = int(sqrt(n));
	dfs1(1, 0);
	dfs2(1, 0);

	ll inv = power(n, -1);

	while (q --) {
		int o = read;
		if (o == 1) {
			int u = read;
			ll x = read * inv % mod;
			modify(1, n, x * n % mod);
			for (int s : X[u])
				modify(lpos[u][s], rpos[u][s], s * (mod - x) % mod);
			for (int v : D[u])
				modify(id[v], id[v] + size[v] - 1, size[v] * (mod - x) % mod);
			modify(1, n, (n - size[u]) * (mod - x) % mod);
			modify(id[u], id[u] + size[u] - 1, (n - size[u]) * x % mod);
		}
		if (o == 2) {
			int u = read;
			printf("%lld\n", query(id[u]));
		}
	}
}
