#if 0
2019.09.21

直接树链剖分套线段树是两个 log 的。
注意到询问只有最后一次，考虑离线，将修改操作从小到大排序。
那么每次修改就可以直接确定答案，因为后面的修改都不会影响当前的修改。
每次修改确定一些点的答案后，用并查集将这些点合并，根设为集合深度最小的点，
之后的修改碰到确定答案的点直接用并查集跳到该集合的根，也就跳到了第一个没有确定答案的点。
这样每条边最多被修改一次，算上并查集的复杂度，大概是均摊 A(n) 以内的。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef std::pair<int, int> Par;

inline int input() {
	int x = 0, c = getchar();
	while(c < '0' or c > '9') c = getchar();
	while(c >= '0' and c <= '9') x = x * 10 + c - '0', c = getchar();
	return x;
}

const int maxn = 1000005, maxq = 1000005;
struct Que {
	int x, y, w;
};
int head[maxn], nxt[maxn << 1];
int fa[maxn];
int deep[maxn];
int _fa[maxn];
int ans[maxn];
Que qu[maxq];

inline bool cmp(Que a, Que b) {
	return a.w < b.w;
}

int find(int x) {
	if(_fa[x] == x)
		return x;
	return _fa[x] = find(_fa[x]);
}

void path(int x, int y, int w) {
	/* debug("%d %d %d\n", x, y, w); */
	x = find(x);
	y = find(y);

	while(x != y) {
		if(deep[x] < deep[y])
			std::swap(x, y);
		/* debug("%d %d\n", x, y); */
		ans[x] = w;
		_fa[x] = find(fa[x]);
		x = find(x);
	}
}

void dfs(int u) {
	deep[u] = deep[fa[u]] + 1;
	for(int i = head[u]; i; i = nxt[i])
		dfs(i);
}

int main() {
	int n = input(), q = input();

	for(int i = 2; i <= n; i ++) {
		fa[i] = input();
		nxt[i] = head[fa[i]];
		head[fa[i]] = i;
	}

	dfs(1);

	for(int i = 1; i <= n; i ++) {
		_fa[i] = i;
		ans[i] = 1000000000;
	}

	for(int i = 1; i <= q; i ++) {
		qu[i].x = input();
		qu[i].y = input();
		qu[i].w = input();
	}

	std::sort(qu + 1, qu + q + 1, cmp);

	for(int i = 1; i <= q; i ++)
		path(qu[i].x, qu[i].y, qu[i].w);

	for(int i = 2; i <= n; i ++)
		printf("%d\n", ans[i]);
}
