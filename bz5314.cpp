#if 0
2019.12.30

直接树形背包 f[u][k][0/1][0/1] 表示 u 子树放 k 个，
u 是否放，u 是否被覆盖的方案数。
每个点对背包的大小的增加最多为 1 ，可以上下界优化。
卡空间，用 int 。
#endif
#include <cstdio>
#include <vector>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
} read;

const int maxn = 100005, maxk = 104, mod = 1000000007;
int f[maxn][maxk][2][2];
int g[maxk][2][2];
int lim[maxn];
std::vector<int> G[maxn];

inline void __a(int &x) { if(x >= mod) x -= mod; }

int TOT;
int N, K;
void dp(int u, int fa) {
	f[u][0][0][0] = 1;
	f[u][1][1][0] = 1;
	lim[u] = 1;

	for(int v : G[u])
		if(v != fa) {
			dp(v, u);

			int nlim = std::min(lim[u] + lim[v], K);
			for(int a = 0; a <= lim[u]; a ++)
				for(int b = 0; b <= lim[v] and a + b <= nlim; b ++) {
					++ TOT;
					for(int p1 = 0; p1 < 2; p1 ++)
						for(int q1 = 0; q1 < 2; q1 ++)
							for(int p2 = 0; p2 < 2; p2 ++)
								for(int q2 = 0; q2 < 2; q2 ++)
									if(q2 | p1)
										__a(g[a + b][p1][q1 | p2] +=
										 1ll * f[u][a][p1][q1] * f[v][b][p2][q2] % mod);
				}

			for(int k = 0; k <= nlim; k ++)
				for(int p = 0; p < 2; p ++)
					for(int q = 0; q < 2; q ++)
						f[u][k][p][q] = g[k][p][q];
			for(int k = 0; k <= nlim; k ++)
				g[k][0][0] = g[k][0][1] = g[k][1][0] = g[k][1][1] = 0;
			lim[u] = nlim;
		}

	/* debug("f[%d]:\n", u); */
	/* for(int k = 0; k <= lim[u]; k ++) */
	/* 	debug("k=%d: %lld %lld %lld %lld\n", k, */
	/* 			f[u][k][0][0], f[u][k][0][1], f[u][k][1][0], f[u][k][1][1]); */
}

int main() {
	read(N, K);
	for(int i = 1; i < N; i ++) {
		int u = read, v = read;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	dp(1, 0);
	printf("%d\n", (f[1][K][0][1] + f[1][K][1][1]) % mod);
	/* debug("%d %d\n", TOT, N * K); */
}
