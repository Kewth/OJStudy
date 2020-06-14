#if 0
2020.06.01

* 单独讨论小部分，问题转换

  对于 m = 1 ，考虑一次操作的影响，有四种情况：
    or 0  : 值不变
	or 1  : 值变为 1
	and 1 : 值不变
	and 0 : 值变为 0
  不妨将操作序列也看做 01 序列，其中 or 是 0 而 and 是 1 ，那么可以发现最后的结果为 1 当
且仅当操作序列反过来代表的二进制数比数字序列反过来代表的二进制数小。
  那么推广到 m > 1 就很容易了，相当于有 m 个二进制数，每次询问只需要搞出一个区间 [l, r)
那么答案就是 r - l ，求出 r, l 只需要将 m 个二进制数排序求出每个数的 rank 即可。
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
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator char * () { static char x[5005]; return scanf("%s", x + 1), x; }
} read;

const int maxn = 1005, maxm = 5005, mod = 1000000007;
int sa[maxm];
int rank[maxm];
int num[maxm][maxn];
ll val[maxm];

int main () {
	int n = read, m = read, q = read;
	for (int j = n; j; j --) {
		char *tmp = read;
		for (int i = 1; i <= m; i ++)
			num[i][j] = tmp[i] - '0';
	}

	for (int i = 1; i <= m; i ++) sa[i] = i;
	std::sort(sa + 1, sa + m + 1, [n] (int a, int b) -> bool {
				for (int i = 1; i <= n; i ++)
					if (num[a][i] != num[b][i])
						return num[a][i] < num[b][i];
				return 0;
			});

	for (int i = 1; i <= m; i ++)
		rank[sa[i]] = i;
	sa[m + 1] = m + 1;

	for (int i = 1; i <= m; i ++)
		for (int j = 1; j <= n; j ++)
			val[i] = (val[i] << 1 | num[i][j]) % mod;
	val[m + 1] = 1;
	for (int j = 1; j <= n; j ++)
		(val[m + 1] <<= 1) %= mod;

	while (q --) {
		int l = 0, r = m + 1;
		char *tmp = read;
		for (int i = 1; i <= m; i ++)
			if (tmp[i] == '1')
				r = std::min(r, rank[i]);
			else
				l = std::max(l, rank[i]);
		if (r > l)
			printf("%lld\n", (val[sa[r]] - val[sa[l]] + mod) % mod);
		else
			puts("0");
	}
}
