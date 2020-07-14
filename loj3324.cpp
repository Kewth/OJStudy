/*
 * Since g++10 is released, some characters is not valid inside #if 0 :(
 * So, why not using clang++? :D

 * Date:
  2020.07.02

 * Solution:
  不妨设取走最后一个石子的一方获胜。
  需要注意到的是，对于必胜态 (k, n) ，(k + 1, n) 也一定是必胜态，那么设 F(n) 表示能构成
必胜态的最小的 k ，(k, n) 必胜当且仅当 F(n) <= k 。
  观察 F(n) 的性质，不难发现并归纳出： F(n) = n == x ? n : F(n - x) ，其中 x 是不超过 n
的最大的斐波那契数。
  那么根据上面的性质可以知道 F 的值一定是斐波那契数，预处理每个斐波那契数的所有答案即可。

 * Digression:

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

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
} read;

const int maxn = 100;
ll f[maxn];
ll ftot[maxn][maxn];
int lim = 1;

int main () {
	f[0] = f[1] = 1;
	while (f[lim] <= 1000000000000000000)
		f[lim + 1] = f[lim] + f[lim - 1], ++ lim;

	ftot[1][1] = 1;
	for (int i = 2; i <= lim; i ++) {
		for (int j = 1; j <= i; j ++)
			ftot[i][j] = ftot[i - 1][j] + ftot[i - 2][j];
		-- ftot[i][i - 2];
		++ ftot[i][i];
	}

	for (int i = 1; i <= lim; i ++)
		for (int j = 2; j <= lim; j ++)
			ftot[i][j] += ftot[i][j - 1];

	int T = read;
	while (T --) {
		ll k = read, n = read, ans = 0;
		int kf = lim;
		while (f[kf] > k) -- kf;
		-- n;

		for (int i = lim; i; i --)
			if (f[i] <= n) {
				ans += ftot[i][kf];
				n -= f[i];
			}

		printf("%lld\n", ans);
	}
}
