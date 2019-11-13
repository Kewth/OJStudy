#if 0
2019.11.13

要求的是一颗代价最小的有根生成树，生成树上每个点对代价的贡献与其深度和父亲边有关。
考虑逐层加点，状压当前加的点集，即 DP 设 f[S][i] 表示用点集 S 构造深度为 i 的生成树最小代价。
转移枚举第 i 层用的点集 T ，然后就是 S - T 对 T 的每个点连边，
然后就发现没法确定代价，因为 S - T 的每个点的深度信息丢失了，
但没有问题，钦定所有 T 的点深度为 i 即可，
这样的确可能会把深度算大，从而使得这个转移的贡献比应有的要大，
但如果能保证合法的深度分配被统计到就一定比不合法的深度分配要优，
从而不合法的深度分配不会造成影响。
不难发现钦定深度为 i 是能统计到合法分配的，因为总存在合法分配使得 T 的深度都为 i 。
现在考虑转移，设 g[S][i] 表示点集 S 中连向 i 点的最小边权即可进行转移。
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

const int maxn = 12;
int f[1 << maxn][maxn + 1];
int g[1 << maxn][maxn];
int link[maxn][maxn];

int main() {
	int n = read, m = read;

	if(n == 1) return puts("0"), 0;

	for(int i = 0; i < n; i ++)
		for(int j = 0; j < n; j ++)
			link[i][j] = 1000000000;

	for(int i = 1; i <= m; i ++) {
		int u = read - 1, v = read - 1, w = read;
		link[u][v] = std::min(link[u][v], w);
		link[v][u] = std::min(link[v][u], w);
	}

	for(int S = 0; S < (1 << n); S ++)
		for(int i = 0; i < n; i ++) {
			g[S][i] = 1000000000;
			for(int j = 0; j < n; j ++)
				if(S >> j & 1)
					g[S][i] = std::min(g[S][i], link[j][i]);
		}

	for(int S = 0; S < (1 << n); S ++)
		for(int i = 1; i <= n; i ++)
			f[S][i] = 1000000000;

	for(int i = 0; i < n; i ++)
		f[1 << i][1] = 0;

	int ans = 1000000000;
	for(int i = 2; i <= n; i ++) {
		for(int S = 0; S < (1 << n); S ++) {
			for(int T = (S - 1) & S; T; T = (T - 1) & S) {
				ll now = f[T][i - 1];
				for(int j = 0; j < n; j ++)
					if(S >> j & 1 and !(T >> j & 1))
						now += 1ll * g[T][j] * (i - 1);
				if(now < f[S][i])
					f[S][i] = int(now);
			}
			/* if(f[S][i] < 1000000000) */
			/* 	debug("f[%d][%d] = %d\n", S, i, f[S][i]); */
		}
		ans = std::min(ans, f[(1 << n) - 1][i]);
	}

	printf("%d\n", ans);
}
