/*
 * Since g++10 is released, some characters is not valid inside #if 0 :(
 * So, why not using clang++? :D

 * Date:
  2020.06.15

 * Solution:
  首先设第 j 列的最大值为 c[j] ，事实上只需要保留 c 最大的 n 列，可以发现最优答案一定可
以只出现在这 n 列，接下来的讨论假设 m = n 成立，即考虑一个 n x n 的方阵。
  设计 DP 设 f[i][S] 表示考虑前 i 列，选择的行的集合是 S 的前提下，最大的贡献，转移枚举
当前行的选择集合和偏移量，枚举 S 的子集即可，可预处理转移，复杂度 O(n^2 2^n + n 3^n) 。

 * Digression:
  又双叒叕被降智了。

 * CopyRight:
          ▁▃▄▄▄▃▃▃▃▄▶
        ▗▇▀▔    ▔▔▔▔
       ▄▛   ▃▅━━■▄▂
      ▟▊   ▐▘     ▀▙
     ▟▜▌   ▐▖   ▋  ▐▍
    ▟▘ ▜   ▝▀▇▆●▘  ▐▌
  ▗▟▘   ▜▃       ▁▅▛
  ▔▀▼▅▄▃▃██▅▄▄▄▅■▀▔
        ▔▔▔▔▔▔
 */

#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef std::pair<int, int> par;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 13, maxm = 2020;
int a[maxn][maxm], b[maxn << 1][maxn];
int max[maxm], p[maxm];
int f[1 << maxn], g[1 << maxn];

int main () {
	int Test = read;
	while (Test --) {
		int n = read, m = read;
		for (int j = 1; j <= m; j ++) max[j] = 0, p[j] = j;
		for (int i = 1; i <= n; i ++)
			for (int j = 1; j <= m; j ++)
				max[j] = std::max(max[j], a[i][j] = read);
		std::sort(p + 1, p + m + 1, [] (int x, int y) {
					return max[x] > max[y];
				});
		m = std::min(n, m);

		for (int i = 1; i <= n; i ++)
			for (int j = 1; j <= m; j ++)
				b[n + i][j] = b[i][j] = a[i][p[j]];

		std::fill(f, f + (1 << n), 0);
		for (int c = 1; c <= m; c ++) {
			std::fill(g, g + (1 << n), 0);
			for (int s = 1; s <= n; s ++)
				for (int S = 0; S < (1 << n); S ++) {
					int x = 0;
					for (int i = 0; i < n; i ++)
						if (S >> i & 1)
							x += b[s + i][c];
					g[S] = std::max(g[S], x);
				}
			for (int S = (1 << n) - 1; S >= 0; S --)
				for (int T = S; T >= 0; T --) {
					T &= S;
					f[S] = std::max(f[S], f[T] + g[S ^ T]);
				}
		}

		printf("%d\n", f[(1 << n) - 1]);
	}
}
