#if 0
2019.09.21

模拟 kruskal 的过程，将方案按费用排序，
每次在 (a, b) 并 (c, d) 中尽可能连边直到全部联通。
用并查集维护集合，另外开一个并查集的东西维护每个点向上走走到最后一个与之连通的点。
每条边最多被合并一次，复杂度均摊下来是有保证的。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;

inline int input() {
	int x = 0, c = getchar();
	while(c < '0' || c > '9') c = getchar();
	while(c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
	return x;
}

const int maxn = 100005;
struct Modi {
	int a, b, c, d, e;
};
int head[maxn], nxt[maxn << 1], to[maxn << 1], hp = 1;
int deep[maxn];
int fa[maxn];
int _fa[maxn];
int top[maxn];
int tot[maxn];
Modi mo[maxn];

bool cmp(Modi x, Modi y) {
	return x.e < y.e;
}

inline void add(int u, int v) {
	nxt[++ hp] = head[u];
	head[u] = hp;
	to[hp] = v;
}

void dfs(int u) {
	deep[u] = deep[fa[u]] + 1;
	for(int i = head[u]; i; i = nxt[i])
		if(to[i] != fa[u]) {
			fa[to[i]] = u;
			dfs(to[i]);
		}
}

int find(int x) {
	if(_fa[x] == x)
		return x;
	return _fa[x] = find(_fa[x]);
}

int find_top(int x) {
	if(top[x] == x)
		return x;
	return top[x] = find_top(top[x]);
}

int path(int x, int y) {
	/* debug("path %d %d\n", x, y); */
	int res = 0;
	x = find_top(x);
	y = find_top(y);

	while(x != y) {
		if(deep[x] < deep[y])
			std::swap(x, y);
		/* debug("%d %d\n", x, y); */
		if(find(fa[x]) != find(x)) {
			_fa[find(x)] = find(fa[x]);
			res ++;
		}
		top[x] = find_top(fa[x]);
		x = find_top(x);
	}

	return res;
}

int main() {
	int T = input();
	while(T --) {
		int n = input(), m = input();

		for(int i = 1; i <= n; i ++)
			head[i] = 0;

		hp = 1;
		for(int i = 1; i < n; i ++) {
			int u = input(), v = input();
			add(u, v);
			add(v, u);
		}

		fa[1] = 0;
		dfs(1);

		for(int i = 1; i <= m; i ++) {
			mo[i].a = input();
			mo[i].b = input();
			mo[i].c = input();
			mo[i].d = input();
			mo[i].e = input();
		}

		std::sort(mo + 1, mo + m + 1, cmp);

		for(int i = 1; i <= n; i ++)
			top[i] = _fa[i] = i;

		int cnt = 0;
		lolong ans = 0;

		for(int i = 1; i <= m; i ++) {
			ans += 1ll * (path(mo[i].a, mo[i].b) + path(mo[i].c, mo[i].d)) * mo[i].e;
			if(find(mo[i].a) != find(mo[i].c)) {
				_fa[find(mo[i].a)] = find(mo[i].c);
				ans += mo[i].e;
			}
			/* for(int j = 1; j <= n; j ++) */
			/* 	debug("%d -> %d\n", j, find(j)); */
		}

		/* for(int i = 1; i <= n; i ++) */
		/* 	debug("%d -> %d\n", i, find(i)); */

		for(int i = 1; i <= n; i ++)
			tot[i] = 0;

		for(int i = 1; i <= n; i ++)
			tot[find(i)] ++;

		for(int i = 1; i <= n; i ++)
			if(tot[i] > 1)
				cnt += tot[i];

		printf("%d %lld\n", cnt, ans);
	}
}
