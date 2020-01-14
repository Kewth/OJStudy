#if 0
2020.01.14

边分治板子，统计经过中心边的路径时，
枚举最小值所在的链，钦定另一端的最小值大于这个最小值，
那么最优端点就有单调性，可以双指针。

和点分治一个不同的地方是边分治递归的过程会共用点，导致 size 在递归一次后会变，
这个问题调了一年。
#endif
#include <cstdio>
#include <algorithm>

#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 200005;

int head[maxn], nxt[maxn << 1], to[maxn << 1], len[maxn << 1], hp = 1;
inline void add(int u, int v, int l) {
	nxt[++ hp] = head[u];
	head[u] = hp;
	to[hp] = v;
	len[hp] = l;
}

int val[maxn];
int last[maxn], np;
inline void expand(int u) {
	if(last[u]) {
		val[++ np] = val[u];
		add(np, last[u], 0);
		add(last[u], np, 0);
		last[u] = np;
	} else
		last[u] = u;
}

int cen, censize;
bool vis[maxn];
int size[maxn];
void find_cen(int u, int from, int n) {
	size[u] = 1;
	for(int i = head[u]; i; i = nxt[i])
		if(!vis[i >> 1]) {
			vis[i >> 1] = 1;
			find_cen(to[i], i >> 1, n);
			size[u] += size[to[i]];
			vis[i >> 1] = 0;
		}
	int now = std::max(size[u], n - size[u]);
	if(now < censize) {
		cen = from;
		censize = now;
	}
}

void dfs(int u, int deep, int minval, int *tar, int &max) {
	minval = std::min(minval, val[u]);
	max = std::max(max, deep);
	tar[deep] = std::max(tar[deep], minval);
	for(int i = head[u]; i; i = nxt[i])
		if(!vis[i >> 1]) {
			vis[i >> 1] = 1;
			dfs(to[i], deep + len[i], minval, tar, max);
			vis[i >> 1] = 0;
		}
}

ll ans;
void solve(int *a, int n, int *b, int m, int l) {
	int p = -1;
	for(int i = 0; i <= n; i ++) {
		while(p + 1 <= m and b[p + 1] >= a[i])
			++ p;
		if(p >= 0)
			ans = std::max(ans, 1ll * (p + i + l) * a[i]);
	}
}

int a[maxn], b[maxn];
void divi(int u, int n) {
	if(n == 1) return;

	cen = 0;
	censize = maxn;
	find_cen(u, 0, n);
	if(size[u] != n) exit(1);
	vis[cen] = 1;
	int x = to[cen << 1], y = to[cen << 1 | 1];

	int alim = 0, blim = 0;
	dfs(x, 0, 1000000000, a, alim);
	dfs(y, 0, 1000000000, b, blim);

	solve(a, alim, b, blim, len[cen << 1] + 1);
	solve(b, blim, a, alim, len[cen << 1] + 1);

	std::fill(a, a + alim + 1, 0);
	std::fill(b, b + blim + 1, 0);

	if(size[x] > size[y]) {
		int tmp = size[y];
		divi(x, n - size[y]);
		divi(y, tmp);
	} else {
		int tmp = n - size[x];
		divi(x, size[x]);
		divi(y, tmp);
	}
}

int main() {
	int n = read;
	for(int i = 1; i <= n; i ++)
		ans = std::max(ans, ll(val[i] = read));
	np = n;

	for(int i = 1; i < n; i ++) {
		int u = read, v = read;
		expand(u);
		expand(v);
		add(last[u], last[v], 1);
		add(last[v], last[u], 1);
	}

	divi(1, np);
	printf("%lld\n", ans);
}
