#if 0
2019.07.08

震惊，这题我竟然一遍过。
要求所有边被覆盖，对于这个条件，考虑用容斥处理，
对于每个边集 E ，钦定 E 不被覆盖后其他边随意的方案数为 f(E) ，
则 E 对答案的贡献为 f(E) * -1^|E| 。

钦定一些边不被覆盖相当于把树切成森林，每颗新的树独立。
考虑 DP ，设 f[u][i] 表示 u 的子树中，
去掉 u 在内的 i 个点的新树（这些点相互配对）的方案。
u -> v 转移时即 f[u][i + j] += f[u][i] * f[v][j] 。
特别地，对于 f[u][0] ，枚举 u 所在的新树大小 i ，f[u][0] -= f[u][i] * g[i] ，
其中 g[i] 表示大小为 i 的新树中随意配对的方案数，
为什么是 -= ？，因为要考虑容斥系数。
#endif
#include <cstdio>
#include <vector>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;
inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 5005, mod = 1000000007;
lolong f[maxn][maxn], fu[maxn], g[maxn];
int size[maxn];
std::vector<int> G[maxn];

void dp(int u, int fa) {
	size[u] = 1;
	f[u][1] = 1;
	for(int v : G[u])
		if(v != fa) {
			dp(v, u);
			for(int i = 0; i <= size[u]; i ++) {
				fu[i] = f[u][i];
				f[u][i] = 0;
			}
			for(int i = 0; i <= size[u]; i ++)
				for(int j = 0; j <= size[v]; j ++)
					(f[u][i + j] += fu[i] * f[v][j]) %= mod;
			size[u] += size[v];
		}
	if(f[u][0]) puts("FUCK");
	for(int i = 1; i <= size[u]; i ++)
		(f[u][0] -= f[u][i] * g[i]) %= mod;
}

int main() {
	int n = input();
	for(int i = 1; i < n; i ++) {
		int u = input(), v = input();
		G[u].push_back(v);
		G[v].push_back(u);
	}
	g[0] = 1;
	for(int i = 2; i <= n; i ++)
		g[i] = g[i - 2] * (i - 1) % mod;
	dp(1, 0);
	printf("%lld\n", (mod - f[1][0]) % mod);
}
