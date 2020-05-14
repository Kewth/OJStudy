#if 0
2020.05.13

  走的路径一定是向左向右反复横跳的，朴素 DP 设 f[i][j][t] = k 表示逆时针经过了 i 个点，
顺时针经过了 j 个点，用了时间 t ，最多能获得 k 的收益。显然 k 随 t 单调不减，交换这个
状态和值，也就是设 f[i][j][k] = t 表示获得 k 的收益最少需要用时间 t 即可。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
} read;

const int maxn = 205;
const ll inf = 1000000000000000000;
ll f[maxn][maxn][maxn], g[maxn][maxn][maxn];
int X[maxn], T[maxn];

inline bool chkmin (ll &x, ll y) {
	if(y < x) return x = y, 1;
	return 0;
}

int main () {
	int n = read, m = read;
	for (int i = 1; i <= n; i ++) read(X[i]);
	for (int i = 1; i <= n; i ++) read(T[i]);
	X[n + 1] = m;
	for (int i = 0; i <= n; i ++)
		for (int j = n + 1; j > i; j --)
			for (int k = 0; k <= i + n - j + 1; k ++)
				f[i][j][k] = g[i][j][k] = inf;
	f[0][n + 1][0] = 0;
	g[0][n + 1][0] = 0;
	int ans = 0;
	for (int i = 0; i <= n; i ++)
		for (int j = n + 1; j > i; j --)
			for (int k = 0; k <= i + n - j + 1; k ++) {
				ll t;
				if (f[i][j][k] < inf) {
					t = f[i][j][k] + X[i + 1] - X[i];
					chkmin(f[i + 1][j][k + (t <= T[i + 1])], t);
					t = f[i][j][k] + X[i] + m - X[j - 1];
					chkmin(g[i][j - 1][k + (t <= T[j - 1])], t);
					ans = std::max(ans, k);
				}
				if (g[i][j][k] < inf) {
					t = g[i][j][k] + X[j] - X[j - 1];
					chkmin(g[i][j - 1][k + (t <= T[j - 1])], t);
					t = g[i][j][k] + m - X[j] + X[i + 1];
					chkmin(f[i + 1][j][k + (t <= T[i + 1])], t);
					ans = std::max(ans, k);
				}
			}
	printf("%d\n", ans);
}
