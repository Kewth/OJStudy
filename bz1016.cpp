#if 0
2020.05.13

  一个图的所有生成树的边权可重集都相同。
  那么做 Kruskal ，对于一个边权 x ，如果在 mst 里用了 t 条边，总共有 k 条边，C(t, k)
暴力枚举选边方案判断是否满足条件（每次都合并了两个并查集）即可。如果边数很大，也可以
通过并查集的状态转换为在每个联通块内求生成树个数而使用矩阵树定理，但不在本题范畴内。
#endif
#include <cstdio>
#include <algorithm>
#include <map>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator () (a...); }
} read;

const int maxn = 105, maxm = 1005;
int p[maxn], q[maxn], r[maxn];
std::map<int, int> map;

struct Edge {
	int u, v, w;
} e[maxm];

int find (int x, int *fa) {
	if (x == fa[x]) return x;
	return fa[x] = find(fa[x], fa);
}

int main () {
	int n = read, m = read;
	for (int i = 1; i <= m; i ++)
		read(e[i].u, e[i].v, e[i].w);
	std::sort(e + 1, e + m + 1, [] (Edge a, Edge b) {
				return a.w < b.w;
			});

	for (int i = 1; i <= n; i ++) p[i] = i;
	int ans = 1, mod = 31011;
	for (int l = 1, k; l <= m; l += k) {
		k = 0;
		Edge *E = e + l;
		while (E[k].w == E[0].w) ++ k;
		std::copy(p, p + n + 1, q);
		int tot = 0;
		for (int i = 0; i < k; i ++) {
			int x = find(E[i].u, p), y = find(E[i].v, p);
			if (x > y) std::swap(x, y);
			if (x != y) {
				p[x] = y;
				++ tot;
			}
		}
		int now = 0;
		for (int S = 0; S < (1 << k); S ++)
			if (__builtin_popcount(unsigned(S)) == tot) {
				std::copy(q, q + n + 1, r);
				bool ok = 1;
				for (int i = 0; i < k; i ++)
					if (S >> i & 1) {
						int x = find(E[i].u, r), y = find(E[i].v, r);
						if (x > y) std::swap(x, y);
						r[x] = y;
						ok &= x != y;
					}
				now += ok;
			}
		(ans *= now) %= mod;
		/* debug("%d %d\n", tot, now); */
	}

	for (int i = 1; i <= n; i ++)
		if (find(i, p) != n)
			return puts("0"), 0;

	printf("%d\n", ans);
}
