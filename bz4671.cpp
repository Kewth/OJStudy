#if 0
2020.01.03

设 f[i] 表示选出来恰好有 i 个联通块的方案数。
g[i] 表示把 n 个点染 i 个不同的颜色，有多少异或图满足不同颜色之间没有边。
那么不难得到 g[i] = sum_{j=i}^n S(j, i) f[j] 。
根据斯特灵反演得到 f[i] = sum_{j=i}^n (-1)^{j-i} s(j, i) g[j] ，
要求的答案就是 f[1] ，现在转换为求 g 。

暴力枚举染色方案，对于一个确定的染色方案，只需要考虑不同颜色之间的边，
边数是很少的，状压起来，每个图对应一个二进制数，
问题转换为对于一个数集统计有多少子集异或和为 0 ，用线性基可以很好解决。
#endif
#include <cstdio>
#include <cstring>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
} read;

const int maxn = 70;
char s[maxn][maxn];
int a[maxn];
ll lin[maxn];
ll fac[maxn]; // s(n + 1, 1)

ll ans = 0;
void solve(int x, int max, int n, int m) {
	if(x == n + 1) {
		int inlin = 0;
		memset(lin, 0, sizeof lin);

		for(int i = 1; i <= m; i ++) {
			ll S = 0;
			int tot = 0;
			int j = 0;

			for(int u = 1; u <= n; u ++)
				for(int v = u + 1; v <= n; v ++) {
					++ j;
					if(a[u] != a[v]) S |= (1ll << tot ++) * (s[i][j] == '1');
				}

			for(int k = 0; k < tot; k ++)
				if(S >> k & 1) {
					if(!lin[k]) {
						lin[k] = S;
						++ inlin;
						break;
					} else
						S ^= lin[k];
				}
		}

		ans += (max & 1 ? 1 : -1) * fac[max - 1] * (1ll << m >> inlin);

		return;
	}

	for(int i = 1; i <= max + 1; i ++) {
		a[x] = i;
		solve(x + 1, std::max(max, i), n, m);
	}
}

int main() {
	int m = read, n = 0;
	for(int i = 1; i <= m; i ++) {
		scanf("%s", s[i] + 1);
		int len = int(strlen(s[i] + 1));
		while(n * (n - 1) != len * 2)
			++ n;
	}
	fac[0] = 1;
	for(int i = 1; i <= n; i ++)
		fac[i] = fac[i - 1] * i;
	solve(1, 0, n, m);
	printf("%lld\n", ans);
}
