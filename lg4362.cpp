#if 0
2019.09.06

首先 m 增大答案一定不增。
其次 m = 3 时可以只有大头吃树枝，
证明的话，假设大头已经摆好了，剩下的果子分层给两个头吃，两个头就不会有相连的果子了。
综上， m >= 3 时只有大头吃树枝。

DP 设 f[u][i], g[u][i] 分别表示大头选或不选 u 时 u 子树恰好大头吃 i 个的最小代价。
m >= 3 的情况就是做一个树背包，
m = 2 的话相当于另一个头需要恰好吃 size[u] - i 个，等价于一个大头，也是一个树背包。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 305;
int f[maxn][maxn], g[maxn][maxn];
int head[maxn], nxt[maxn << 1], to[maxn << 1], val[maxn << 1], hp;

inline void add(int u, int v, int w) {
	nxt[++ hp] = head[u];
	head[u] = hp;
	to[hp] = v;
	val[hp] = w;
}

int n, m, k;
void dp(int u, int fa) {
	for(int i = 0; i <= k; i ++)
		f[u][i] = g[u][i] = 1000000000;
	f[u][1] = 0;
	g[u][0] = 0;

	for(int i = head[u]; i; i = nxt[i])
		if(to[i] != fa) {
			dp(to[i], u);

			for(int a = k; a >= 0; a --) {
				int minf = 1000000000, ming = 1000000000;
				for(int b = 0; b <= a; b ++) {
					minf = std::min(minf, f[u][b] + f[to[i]][a - b] + val[i]);
					minf = std::min(minf, f[u][b] + g[to[i]][a - b]);
					ming = std::min(ming, g[u][b] + f[to[i]][a - b]);
					if(m == 2)
						ming = std::min(ming, g[u][b] + g[to[i]][a - b] + val[i]);
					else
						ming = std::min(ming, g[u][b] + g[to[i]][a - b]);
				}
				f[u][a] = minf;
				g[u][a] = ming;
			}
		}

	/* for(int i = 0; i <= k; i ++) */
	/* 	debug(" %d", f[u][i]); */
	/* debug(" <- f%d\n", u); */
	/* for(int i = 0; i <= k; i ++) */
	/* 	debug(" %d", g[u][i]); */
	/* debug(" <- g%d\n", u); */
}

int main() {
	n = input(), m = input(), k = input();

	if(k + m > n) {
		puts("-1");
		return 0;
	}

	for(int i = 1; i < n; i ++) {
		int u = input(), v = input(), w = input();
		add(u, v, w);
		add(v, u, w);
	}

	dp(1, 0);

	printf("%d\n", f[1][k]);
}
