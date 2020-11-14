/*
 * Author: Kewth

 * Date:
  2020.11.13

 * Solution:
  由于 T2 是随机的树，修改的是随机的点，那么碰到修改暴力遍历子树转换为单点修改即可。
  维护直径两个端点就可以很容易支持单点修改，因为新的直径一定由原直径端点和修改点构成。

 * Digression:

 * CopyRight:
   __  __                  __   __
  |  |/  |.-----.--.--.--.|  |_|  |--.
  |     < |  -__|  |  |  ||   _|     |
  |__|\__||_____|________||____|__|__|

 */

#include <cstdio>
#include <algorithm>
#include <vector>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

static struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 1000005;
struct Edge { int v, w; };
std::vector<Edge> G1[maxn], G2[maxn];
int id[maxn], iid[maxn], fa[maxn], ip;
int st[20][maxn << 1], hb[maxn << 1], first[maxn], stp;
ll dis[maxn];
int fa2[maxn];
ll a[maxn];

void stinit () {
	for (int i = 2; i <= stp; i ++)
		hb[i] = hb[i >> 1] + 1;
	for (int i = stp; i; i --)
		for (int k = 1; i + (1 << k) - 1 <= stp; k ++)
			st[k][i] = std::min(st[k - 1][i], st[k - 1][i + (1 << k >> 1)]);
}

void dfs (int u) {
	iid[id[u] = ++ ip] = u;
	st[0][first[u] = ++ stp] = id[u];
	for (Edge e : G1[u])
		if (e.v != fa[u]) {
			dis[e.v] = dis[u] + e.w;
			fa[e.v] = u;
			dfs(e.v);
			st[0][++ stp] = id[u];
		}
}

inline int lca (int x, int y) {
	int l = first[x], r = first[y];
	if (l > r) std::swap(l, r);
	int k = hb[r - l + 1];
	return iid[std::min(st[k][l], st[k][r - (1 << k) + 1])];
}

ll dist (int x, int y) {
	if (x == y) return -1;
	int c = lca(x, y);
	return dis[x] + dis[y] - dis[c] * 2 + a[x] + a[y];
}

void dfs2 (int u) {
	for (Edge e : G2[u])
		if (e.v != fa2[u])
			a[e.v] = a[u] + e.w, fa2[e.v] = u, dfs2(e.v);
}

int x, y;
ll now;
void modify (int u, ll X) {
	a[u] += X;
	ll t1 = dist(u, x), t2 = dist(u, y);
	if (t1 > now and t1 >= t2)
		now = t1, y = u;
	if (t2 > now and t2 > t1)
		now = t2, x = u;
}

void add (int u, ll X) {
	modify(u, X);
	for (Edge e : G2[u])
		if (e.v != fa2[u])
			add(e.v, X);
}

int main () {
	int n = read, q = read;
	for (int i = 1; i < n; i ++) {
		int u = read, v = read, w = read;
		G1[u].push_back({v, w});
		G1[v].push_back({u, w});
	}
	for (int i = 1; i < n; i ++) {
		int u = read, v = read, w = read;
		G2[u].push_back({v, w});
		G2[v].push_back({u, w});
	}
	dfs(1);
	dfs2(1);
	stinit();

	x = 1, y = 2, now = dist(x, y);
	ll tmp;
	for (int i = 3; i <= n; i ++)
		if ((tmp = dist(x, i)) > now)
			y = i, now = tmp;
	for (int i = 1; i <= n; i ++)
		if ((tmp = dist(y, i)) > now)
			x = i, now = tmp;
	printf("%lld\n", now);

	while (q --) {
		int u = read, X = read;
		add(u, X);
		printf("%lld\n", now);
	}
}
