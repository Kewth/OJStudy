#if 0
2020.05.15

  根号重构即可，把询问换成一个点到根的，修改对询问的影响是很好求的，并且对于确定的修
改，可以一遍 dfs 求出每个点的答案。
#endif
#include <cstdio>
#include <algorithm>
#include <vector>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
} read;

const int maxn = 20005, LIM = 1000000;
struct Modi {
	int u, x;
};
std::vector<int> G[maxn];
int val[maxn];
int fa[maxn], id[maxn], size[maxn], ip;
int Fa[maxn][15], deep[maxn];
struct Tree {
	int lti, rti;
	int val;
} pool[maxn * 40];
int pp;
#define self pool[now]
#define lt pool[self.lti]
#define rt pool[self.rti]

int gcd (int a, int b) {
	if (!b) return a;
	return gcd(b, a % b);
}

void dfs (int u) {
	id[u] = ++ ip;
	deep[u] = deep[fa[u]] + 1;
	Fa[u][0] = fa[u];
	for (int k = 1; k < 15; k ++) Fa[u][k] = Fa[Fa[u][k - 1]][k - 1];
	size[u] = 1;
	for (int v : G[u])
		if (v != fa[u]) {
			fa[v] = u;
			dfs(v);
			size[u] += size[v];
		}
}

int lca (int x, int y) {
	if (deep[x] < deep[y]) std::swap(x, y);
	for (int k = 14; k >= 0; k --)
		if (deep[Fa[x][k]] >= deep[y])
			x = Fa[x][k];
	for (int k = 14; k >= 0; k --)
		if (Fa[x][k] != Fa[y][k])
			x = Fa[x][k], y = Fa[y][k];
	return x == y ? x : fa[x];
}

void lain (int &now, int L, int R, int p) {
	pool[++ pp] = self;
	now = pp;
	++ self.val;
	if (L == R) return;
	int M = (L + R) >> 1;
	if (p <= M) lain(self.lti, L, M, p);
	else lain(self.rti, M + 1, R, p);
}

int query (int now, int L, int R, int p) {
	if (L > p or !now) return 0;
	if (R <= p) return self.val;
	int M = (L + R) >> 1;
	return query(self.lti, L, M, p) + query(self.rti, M + 1, R, p);
}

int seg[maxn];
void force (int u) {
	for (int v : G[u])
		if (v != fa[u]) {
			seg[v] = seg[u];
			lain(seg[v], 1, LIM, gcd(val[u], val[v]));
			force(v);
		}
}

int tmp[maxn];
int Query (int x, int K, std::vector<Modi> &v) {
	/* debug("Q %d\n", x); */
	int res = query(seg[x], 1, LIM, K);
	for (Modi m : v)
		tmp[m.u] = val[m.u];
	for (Modi m : v)
		if (m.u == x) {
			if (fa[x]) res -= gcd(val[x], val[fa[x]]) <= K;
			val[x] = m.x;
			if (fa[x]) res += gcd(val[x], val[fa[x]]) <= K;
		} else if (id[m.u] < id[x] and id[x] < id[m.u] + size[m.u]) {
			/* debug("%d %d\n", m.u, x); */
			int y = x;
			for (int k = 14; k >= 0; k --)
				if (deep[Fa[y][k]] > deep[m.u])
					y = Fa[y][k];
			if (fa[m.u]) res -= gcd(val[m.u], val[fa[m.u]]) <= K;
			res -= gcd(val[m.u], val[y]) <= K;
			val[m.u] = m.x;
			if (fa[m.u]) res += gcd(val[m.u], val[fa[m.u]]) <= K;
			res += gcd(val[m.u], val[y]) <= K;
		}
	for (Modi m : v)
		val[m.u] = tmp[m.u];
	/* debug(" >> %d\n", res); */
	return res;
}

int main () {
	int n = read, q = read;
	for (int i = 1; i <= n; i ++)
		read(val[i]);
	for (int i = 1; i < n; i ++) {
		int u = read, v = read;
		G[u].push_back(v);
		G[v].push_back(u);
	}

	dfs(1);
	force(1);

	std::vector<Modi> v;
	while (q --) {
		int o = read, x = read, y = read;
		if (o == 1)
			v.push_back({x, y});
		if (o == 2) {
			if (v.size() > 350) {
				for (Modi m : v)
					val[m.u] = m.x;
				pp = 0;
				force(1);
				v.clear();
			}
			int k = read;
			/* debug("%d %d -> %d\n", x, y, lca(x, y)); */
			printf("%d\n", Query(x, k, v) + Query(y, k, v) - Query(lca(x, y), k, v) * 2);
		}
	}
}
