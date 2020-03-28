#if 0
2020.03.27

DP 设 f[i][j] 表示前 i 个字符能组成多少长为 j 的本质不同的子序列。
一个转移的想法是 f[i][j] = f[i - 1][j] + f[i - 1][j - 1] ，
但是不难发现这样会算重，再减去 g[pre[i]][j] 即可。
其中 g[i][j] 表示前 i 个字符能组成多少以第 i 个字符为结尾的长为 j 的本质不同的子序列，
pre[i] 表示上一个与 i 字符相同的位置。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator () (a...); }
} read;

const int maxn = 1005, mod = 1000000007;
char s[maxn];
int pre[maxn];
int las[26];
ll f[maxn][maxn], g[maxn][maxn];

int main () {
	int n = read, k = read;
	scanf("%s", s + 1);
	for (int i = 1; i <= n; i ++) {
		pre[i] = las[s[i] - 'a'];
		las[s[i] - 'a'] = i;
	}

	f[0][0] = g[0][0] = 1;
	for (int i = 1; i <= n; i ++) {
		f[i][0] = g[i][0] = 1;
		for (int j = 1; j <= n; j ++) {
			f[i][j] = (f[i - 1][j] + f[i - 1][j - 1] + mod - g[pre[i]][j]) % mod;
			g[i][j] = f[i - 1][j - 1];
		}
		/* for (int j = 1; j <= n; j ++) */
		/* 	debug(" %lld", f[i][j]); */
		/* debug("\n"); */
	}

	printf("%lld\n", f[n][k]);
}
