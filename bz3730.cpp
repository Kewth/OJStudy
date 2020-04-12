#if 0
2020.04.12

动态点分治，对于每个联通块用树状数组维护 f[k] 表示与重心距离为 k 的点权和。
查询的时候在点分树上跳父亲查询贡献，但是会算重复，再类似地用树状数组维护重复的贡献即可。
#endif
#include <cstdio>
#include <algorithm>
#include <vector>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef std::pair<int, int> par;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	/* inline operator ll () { ll x; return scanf("%lld", &x), x; } */
	template<class T> inline void operator () (T &x) { x = *this; }
	/* template<class T, class ...A> inline void operator () (T &x, A &...a) */
	/* { x = *this; this -> operator () (a...); } */
} read;

const int maxn = 100005;
int val[maxn];
int st[20][maxn << 1], hb[maxn << 1], first[maxn], stp;
int deep[maxn];
std::vector<int> G[maxn];
bool ban[maxn];
int size[maxn], son[maxn];
int dfa[maxn];

void stinit () {
	for (int i = 2; i <= stp; i ++)
		hb[i] = hb[i >> 1] + 1;
	for (int i = stp; i; i --)
		for (int k = 1; i + (1 << k) - 1 <= stp; k ++)
			st[k][i] = std::min(st[k - 1][i], st[k - 1][i + (1 << k >> 1)]);
}

void dfs (int u, int f) {
	st[0][first[u] = ++ stp] = deep[u] = deep[f] + 1;
	for (int v : G[u])
		if (v != f) {
			dfs(v, u);
			st[0][++ stp] = deep[u];
		}
}

inline int dis (int x, int y) {
	int l = first[x], r = first[y];
	if (l > r) std::swap(l, r);
	int k = hb[r - l + 1];
	return deep[x] + deep[y] - std::min(st[k][l], st[k][r - (1 << k) + 1]) * 2;
}

int pool[maxn * 40], *bit[2][maxn], *las_bit = pool;
int dsize[maxn];

inline void modify (int *b, int p, int x, int n) {
	if (!p) b[0] += x;
	else for (int k = p; k <= n; k += k & -k)
		b[k] += x;
}

inline int query (int *b, int p, int n) {
	int res = b[0];
	for (int k = std::min(p, n); k; k -= k & -k)
		res += b[k];
	return res;
}

void getsize (int u, int f) {
	size[u] = 1, son[u] = 0;
	for (int v : G[u])
		if (!ban[v] and v != f) {
			getsize(v, u);
			size[u] += size[v];
			if (size[v] > size[son[u]])
				son[u] = v;
		}
}

int divide (int s) {
	getsize(s, 0);
	int n = size[s], rt = s;
	while (size[son[rt]] * 2 > n)
		rt = son[rt];

	dsize[rt] = n;
	bit[0][rt] = las_bit;
	las_bit += n + 1;
	bit[1][rt] = las_bit;
	las_bit += n + 1;

	ban[rt] = 1;
	for (int u : G[rt])
		if (!ban[u]) {
			int v = divide(u);
			dfa[v] = rt;
		}

	return rt;
}

void vmodfify (int u, int x) {
	for (int f = u, s = 0; f; s = f, f = dfa[f]) {
		int d = dis(f, u);
		/* debug("%d %d %d\n", u, f, d); */
		modify(bit[0][f], d, x, dsize[f]);
		if (s) modify(bit[1][s], d, x, dsize[s]);
	}
}

int vquery (int u, int x) {
	int res = 0;
	for (int f = u, s = 0; f; s = f, f = dfa[f]) {
		int d = dis(f, u);
		if (x - d < 0) continue;
		res += query(bit[0][f], x - d, dsize[f]);
		if (s) res -= query(bit[1][s], x - d, dsize[s]);
	}
	return res;
}

int main () {
	int n = read, q = read;
	for (int i = 1; i <= n; i ++) read(val[i]);
	for (int i = 1; i < n; i ++) {
		int u = read, v = read;
		G[u].push_back(v);
		G[v].push_back(u);
	}

	dfs(1, 0);
	stinit();
	divide(1);

	for (int i = 1; i <= n; i ++)
		vmodfify(i, val[i]);

	int ans = 0;
	while (q --) {
		int o = read, u = read ^ ans, x = read ^ ans;
		if (u > n or u < 0) break;
		if (o == 0)
			printf("%d\n", ans = vquery(u, x));
		if (o == 1) {
			vmodfify(u, - val[u]);
			vmodfify(u, val[u] = x);
		}
	}
}
