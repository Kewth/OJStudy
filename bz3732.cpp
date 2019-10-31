#if 0
2019.10.30

最小瓶颈路，即最小生成树上路径的最长边。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
} read;

const int maxn = 30005, maxk = 20;
int ex[maxn], ey[maxn], ew[maxn], p[maxn];
int fa[maxn][maxk], max[maxn][maxk];
int head[maxn], nxt[maxn << 1], to[maxn << 1], val[maxn << 1], hp = 1;
int deep[maxn];

inline void add(int u, int v, int w) {
	nxt[++ hp] = head[u];
	head[u] = hp;
	to[hp] = v;
	val[hp] = w;
}

void dfs(int u) {
	deep[u] = deep[*fa[u]] + 1;
	for(int k = 1; k < maxk; k ++) {
		fa[u][k] = fa[fa[u][k - 1]][k - 1];
		max[u][k] = std::max(max[u][k - 1], max[fa[u][k - 1]][k - 1]);
	}
	for(int i = head[u]; i; i = nxt[i])
		if(to[i] != *fa[u]) {
			*fa[to[i]] = u;
			*max[to[i]] = val[i];
			dfs(to[i]);
		}
}

bool cmp(int x, int y) {
	return ew[x] < ew[y];
}

int _fa[maxn];
int find(int x) {
	if(x == _fa[x]) return x;
	return _fa[x] = find(_fa[x]);
}

int main() {
	int n = read, m = read, q = read;

	for(int i = 1; i <= m; i ++)
		read(ex[p[i] = i], ey[i], ew[i]);

	std::sort(p + 1, p + m + 1, cmp);

	for(int i = 1; i <= n; i ++)
		_fa[i] = i;

	for(int i = 1; i <= m; i ++) {
		int x = ex[p[i]], y = ey[p[i]], w = ew[p[i]];
		if(find(x) != find(y)) {
			add(x, y, w);
			add(y, x, w);
			_fa[find(x)] = find(y);
		}
	}

	dfs(1);

	while(q --) {
		int x = read, y = read, ans = 0;
		if(deep[x] < deep[y]) std::swap(x, y);
		for(int k = maxk - 1; k >= 0; k --)
			if(deep[fa[x][k]] >= deep[y]) {
				ans = std::max(ans, max[x][k]);
				x = fa[x][k];
			}
		for(int k = maxk - 1; k >= 0; k --)
			if(fa[x][k] != fa[y][k]) {
				ans = std::max(ans, max[x][k]);
				x = fa[x][k];
				ans = std::max(ans, max[y][k]);
				y = fa[y][k];
			}
		if(x != y)
			ans = std::max(ans, std::max(*max[x], *max[y]));
		printf("%d\n", ans);
	}
}
