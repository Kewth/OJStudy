#if 0
2020.05.08

  DP 设 f[i][j] 表示填前 i 个字符，用了 j 个 1 的最大收益。
  每次填一个字符不仅可以确定一个前缀 [1, i] 的收益，还能确定一个后缀 [i + 1, n] 的收益，
因此这样 DP 是可行的。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 1010;
char s[maxn], t[maxn];
int pre[maxn], suf[maxn];
int f[maxn][maxn], g[maxn][maxn];

int main () {
	int n = read, c0 = read, c1 = read, vp = read, vs = read;
	scanf("%s", s + 1);
	scanf("%s", t + 1);

	for (int i = 1; i <= n; i ++)
		pre[i] = pre[i - 1] + (s[i] == '1');
	for (int i = n; i; i --)
		suf[i] = suf[i + 1] + (s[i] == '1');

	f[0][0] = c1 == suf[1] ? vs : 0;
	g[0][0] = c1 == suf[1] ? vs : 0;
	for (int i = 0; i <= n; i ++)
		for (int j = i + 1; j <= n; j ++) {
			f[i][j] = + 1000000000;
			g[i][j] = - 1000000000;
		}

	for (int i = 1; i <= n; i ++) {
		for (int j = 0; j <= i and j <= c1; j ++) {
			int now = (j == pre[i] ? vp : 0) + (i < n and c1 - j == suf[i + 1] ? vs : 0);
			if (t[i] == '?') {
				f[i][j] = std::min(f[i - 1][j], f[i - 1][j - 1]) + now;
				g[i][j] = std::max(g[i - 1][j], g[i - 1][j - 1]) + now;
				if (j == 0) {
					f[i][j] = f[i - 1][j] + now;
					g[i][j] = g[i - 1][j] + now;
				}
			}
			if (t[i] == '1') {
				f[i][j] = f[i - 1][j - 1] + now;
				g[i][j] = g[i - 1][j - 1] + now;
				if (j == 0) {
					f[i][j] = 1000000000;
					g[i][j] = -1000000000;
				}
			}
			if (t[i] == '0') {
				f[i][j] = f[i - 1][j] + now;
				g[i][j] = g[i - 1][j] + now;
			}
		}
	}

	printf("%d %d\n", f[n][c1], g[n][c1]);
}
