#if 0
2020.03.21

假设最终路径确定，那么最小的翻转次数就是路径上连续的黑格子块数。
那么问题就是求连续黑格子块数最小的一条路径，图是无环的，DP 即可。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 105;
char s[maxn][maxn];
int f[maxn][maxn];

int main () {
	int n = read, m = read;
	for (int i = 1; i <= n; i ++)
		scanf("%s", s[i] + 1);

	for (int i = 0; i < maxn; i ++)
		f[i][0] = f[0][i] = 1000000000;

	f[1][1] = s[1][1] == '#';
	for (int i = 1; i <= n; i ++)
		for (int j = 1; j <= m; j ++)
			if (i > 1 or j > 1) {
				f[i][j] = std::min({
						f[i - 1][j] + (s[i][j] == '#' and s[i - 1][j] == '.'),
						f[i][j - 1] + (s[i][j] == '#' and s[i][j - 1] == '.')});
			}

	printf("%d\n", f[n][m]);
}
