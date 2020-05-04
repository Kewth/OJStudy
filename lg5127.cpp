#if 0
2020.05.02

  考虑单独一位的贡献，不难发现只要存在 1 就是 2^(n-1) ，否则为 0 ，那么总的贡献就是 2^(n-1) x 。
其中 x 是所有数的按位或。树剖套线段树维护，问题在于处理区间异或。可以发现某一位异或 1 后的结果
只与这一位是否有 0 有关，那么维护按位或的同时维护按位与即可。
#endif
#include <cstdio>
#include <algorithm>
#include <vector>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 200005, mod = 1000000007;
std::vector<int> G[maxn];
int top[maxn], deep[maxn], son[maxn], size[maxn], fa[maxn];
int id[maxn], iid[maxn], ip;
int ands[maxn << 2], ors[maxn << 2], tag[maxn << 2];
ll po2[maxn];

void modi (int now, int x) {
	int o = ors[now], a = ands[now];
	ors[now] = (~x & o) ^ (x & ~a);
	ands[now] = (~x & a) ^ (x & ~o);
	tag[now] ^= x;
}

void push (int now) {
	if (tag[now]) {
		modi(now << 1, tag[now]);
		modi(now << 1 | 1, tag[now]);
		tag[now] = 0;
	}
}

int query (int now, int L, int R, int l, int r) {
	if (r < L or l > R) return 0;
	if (l <= L and R <= r) return ors[now];
	push(now);
	int M = (L + R) >> 1;
	return query(now << 1, L, M, l, r) | query(now << 1 | 1, M + 1, R, l, r);
}

void modify (int now, int L, int R, int l, int r, int x) {
	if (r < L or l > R) return;
	if (l <= L and R <= r) return modi(now, x);
	int M = (L + R) >> 1;
	push(now);
	modify(now << 1, L, M, l, r, x);
	modify(now << 1 | 1, M + 1, R, l, r, x);
	ors[now] = ors[now << 1] | ors[now << 1 | 1];
	ands[now] = ands[now << 1] & ands[now << 1 | 1];
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

void dfs2(int u) {
	iid[id[u] = ++ ip] = u;
	if (!top[u]) top[u] = u;
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

	for (int i = 1; i <= n; i ++)
		modify(1, 1, n, id[i], id[i], read);
	po2[0] = 1;
	for (int i = 1; i <= n; i ++)
		po2[i] = (po2[i - 1] << 1) % mod;

	while (q --) {
		int o = read;
		if (o == 1) {
			int x = read, y = read, ans = 0, d = deep[x] + deep[y];
			while (top[x] != top[y]) {
				if (deep[top[x]] < deep[top[y]]) std::swap(x, y);
				ans |= query(1, 1, n, id[top[x]], id[x]);
				x = fa[top[x]];
			}
			if (deep[x] < deep[y]) std::swap(x, y);
			ans |= query(1, 1, n, id[y], id[x]);
			d -= deep[y] << 1;
			printf("%lld\n", po2[d] * ans % mod);
		}
		if (o == 2) {
			int x = read, y = read, z = read;
			while (top[x] != top[y]) {
				if (deep[top[x]] < deep[top[y]]) std::swap(x, y);
				modify(1, 1, n, id[top[x]], id[x], z);
				x = fa[top[x]];
			}
			if (deep[x] < deep[y]) std::swap(x, y);
			modify(1, 1, n, id[y], id[x], z);
		}
	}
}
