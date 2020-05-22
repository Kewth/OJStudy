#if 0
2020.05.22

  首先不难发现第一行的数单调不减，第二行的数单调不增，这样答案一定不会更劣。
  其次由于只能向下走一次，那么两条路径不同当且仅当向下走的位置不同，假设在第 i 列向下走
得到的答案是 A(i) ，那么对于 A(i) - A(i - 1) ，根据上面的单调性可以发现 A(i) - A(i - 1)
也是单调不减的，也就是说 A 是单峰的，那么最大值只能是 A(1) 或 A(n) 。
  有了这些就能 DP ，从大到小加数，设 f[i][j][x] 表示加了 i 个数，其中 j 个数放在了第一
行，当前第一行的和是否可能为 x 。考虑统计答案，不妨把最小的数放右下角，那么枚举左上角的
数，设其为第 i 大的数，那么在 f[i - 1][n - 1] 里枚举所有 x 即可统计这部分对答案的贡献。
输出方案则倒推一遍即可，f 可以用 bitset 优化，复杂度 O(n^3 a) 。
        ▁▃▄▄▄▃▃▃▃▄▶
      ▗▇▀▔    ▔▔▔▔
     ▄▛   ▃▅━━■▄▂
    ▟▊   ▐▘     ▀▙
   ▟▜▌   ▐▖   ▋  ▐▍
  ▟▘ ▜   ▝▀▇▆●▘  ▐▌
▗▟▘   ▜▃       ▁▅▛
▔▀▼▅▄▃▃██▅▄▄▄▅■▀▔   CopyRight :)
      ▔▔▔▔▔▔
#endif
#include <cstdio>
#include <algorithm>
#include <bitset>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef size_t si;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
} read;

const int maxn = 27, maxw = 1250005;
int a[maxn << 1];
std::bitset<maxw> f[maxn << 1][maxn];
bool mark[maxn << 1];

int main () {
	int n = read, N = n << 1;
	for (int i = 1; i <= N; i ++) read(a[i]);
	std::sort(a + 1, a + N + 1);

	int sum = 0, ans = 1000000000, pos = 0, k = 0;
	for (int i = 2; i <= N; i ++) sum += a[i];

	f[N + 1][0].set(0);
	for (int i = N; i > 2; i --) {
		f[i][0].set(0);
		for (int j = 1; j < n and j <= N - i + 1; j ++)
			f[i][j] = f[i + 1][j] | (f[i + 1][j - 1] << si(a[i]));
		for (int p = 0; p < maxw; p ++)
			if (f[i][n - 1].test(si(p))) {
				int q = sum - p - a[i - 1];
				int now = std::max(p, q) + a[i - 1] + a[1];
				if (now < ans) {
					ans = now;
					pos = i - 1;
					k = p;
				}
			}
	}

	/* debug("%d\n", ans); */

	mark[pos] = 1;
	for (int i = pos + 1, j = n - 1; i <= N; i ++) {
		/* assert(f[i][j].test(si(k))); */
		if (j and k >= a[i] and f[i + 1][j - 1].test(si(k - a[i]))) {
			mark[i] = 1;
			-- j;
			k -= a[i];
		}
	}

	for (int i = 1; i <= N; i ++)
		if (mark[i])
			printf("%d ", a[i]);
	puts("");
	for (int i = N; i; i --)
		if (!mark[i])
			printf("%d ", a[i]);
	puts("");
}
