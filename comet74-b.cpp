#if 0
2019.11.09

由于第 i 条边的长度是 2^i ，那么两点的最短路一定也是最小瓶颈路，
最小瓶颈路一定在最小生成树上，建出最小生成树查询两点距离即可。
#endif
#include <cstdio>
#include <algorithm>
#include <set>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef std::pair<int, int> Par;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
} read;

const int maxn = 300005, maxk = 20, mod = 998244353;
int a[maxn], b[maxn];
std::set<Par> set[maxn];
int _fa[maxn];
int head[maxn], nxt[maxn << 1], to[maxn << 1], val[maxn << 1], hp = 1;
int fa[maxn][maxk], faval[maxn][maxk];
int deep[maxn];

inline void __a(int &x) { if(x >= mod) x -= mod; }

inline void add(int u, int v, int w) {
	nxt[++ hp] = head[u];
	head[u] = hp;
	to[hp] = v;
	val[hp] = w;
}

int find(int x) {
	if(_fa[x] == x) return x;
	return _fa[x] = find(_fa[x]);
}

void dfs(int u) {
	deep[u] = deep[*fa[u]] + 1;
	for(int k = 1; k < maxk; k ++) {
		fa[u][k] = fa[fa[u][k - 1]][k - 1];
		__a(faval[u][k] = faval[u][k - 1] + faval[fa[u][k - 1]][k - 1]);
	}

	for(int i = head[u]; i; i = nxt[i])
		if(to[i] != *fa[u]) {
			*fa[to[i]] = u;
			*faval[to[i]] = val[i];
			dfs(to[i]);
		}
}

int path(int x, int y) {
	if(deep[x] < deep[y]) std::swap(x, y);

	int res = 0;
	for(int k = maxk - 1; k >= 0; k --)
		if(deep[fa[x][k]] >= deep[y]) {
			__a(res += faval[x][k]);
			x = fa[x][k];
		}

	for(int k = maxk - 1; k >= 0; k --)
		if(fa[x][k] != fa[y][k]) {
			__a(res += faval[x][k]);
			__a(res += faval[y][k]);
			x = fa[x][k];
			y = fa[y][k];
		}

	if(x != y) {
		__a(res += *faval[x]);
		__a(res += *faval[y]);
	}
	return res;
}

int main() {
	int n = read, m = read;

	for(int i = 1; i <= n; i ++)
		_fa[i] = i;

	for(int i = 1, w = 2; i <= m; i ++, __a(w <<= 1)) {
		int x = read, y = read;
		if(find(x) != find(y)) {
			add(x, y, w);
			add(y, x, w);
			_fa[find(x)] = find(y);
		}
	}

	dfs(1);

	int q = read;
	for(int i = 1; i <= q; i ++) {
		int x = read, y = read;
		printf("%d\n", path(x, y));
	}
}
