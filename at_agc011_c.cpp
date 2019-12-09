#if 0
2019.12.08

考虑新图上 (a, b) 的移动，一个 naive 的想法是 (a, b) 总与 (c, d) 联通，
其中 a 与 c, b 与 d 分别联通。
如果真是这样那么答案就是 x^2 ，其中 x 是原图联通块数量。

如果 a 是一个孤立的点，(a, b) 根本无法移动，任意的 (a, b) 仍然是孤立点，
那么修正一下，假设有 z 个孤立点，除此之外有 x 个联通块，
那么答案就是 x^2 + 2zn - z^2 。

如果 a, b 所在联通块是个点数大于 1 的二分图，
不难发现 (a, b) 移动过程中永远无法改变两边的奇偶性，
也就是说 (a, b) 无法到达 (a, c) ，其中 b 与 c 联通但分别在二分图两端。
那么两个二分图对答案的贡献是 2 ，假设有 y 个点数大于 1 的二分图，
最后的答案就是 x^2 + y^2 + 2zn - z^2 。
#endif
#include <cstdio>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
} read;

const int maxn = 200005;
int head[maxn], nxt[maxn << 1], to[maxn << 1], hp = 1;

inline void add(int u, int v) {
	nxt[++ hp] = head[u];
	head[u] = hp;
	to[hp] = v;
}

int vis[maxn];
int identy(int u, int c) {
	vis[u] = c;
	if(!head[u]) return 3;

	bool odd = 0;
	for(int i = head[u]; i; i = nxt[i])
		if(vis[to[i]] and vis[to[i]] == c)
			odd = 1;
		else if(!vis[to[i]] and identy(to[i], 3 - c) == 1)
			odd = 1;

	return odd ? 1 : 2;
}

int main() {
	int n = read, m = read;

	for(int i = 1; i <= m; i ++) {
		int u = read, v = read;
		add(u, v);
		add(v, u);
	}

	ll x = 0, y = 0, z = 0;
	for(int i = 1; i <= n; i ++)
		if(!vis[i]) {
			int t = identy(i, 1);
			if(t == 3) ++ z;
			else {
				++ x;
				if(t == 2) ++ y;
			}
		}

	/* debug("%lld %lld %lld\n", x, y, z); */

	printf("%lld\n", x * x + y * y + z * n * 2 - z * z);
}
