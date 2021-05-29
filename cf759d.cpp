/*
 * Author: Kewth

 * Date:
  2021.03.30

 * Solution:
  不难想到，一个串是合法的，当且仅当把连续的相同的字符缩起来后是原串的子序列。
  那么问题本质上是统计每种长度的子序列有多少个。放在子序列自动机上就是每种长
度的路径有多少条，虽然枚举后继转移的是字符集复杂度，但是注意到子序列自动机每
个点的前驱都一定是段区间，所以前驱转移，前缀和优化即可。

 * Digression:
  难度：4~5 / 12

 * CopyRight:
   __  __                  __   __
  |  |/  |.-----.--.--.--.|  |_|  |--.
  |     < |  -__|  |  |  ||   _|     |
  |__|\__||_____|________||____|__|__|

 */

#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

static struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 8005, maxc = 26, mod = 1000000007;
char s[maxn];
int tmp[maxc];
int las[maxn];
ll f[maxn];

int main () {
	int n = read;
	scanf("%s", s + 1);

	for (int i = 1; i <= n; i ++) {
		las[i] = tmp[s[i] - 'a'];
		tmp[s[i] - 'a'] = i;
		if (!las[i])
			f[i] = 1;
	}

	for (int i = 2; i <= n; i ++) {
		for (int j = 1; j <= n; j ++)
			f[j] += f[j - 1];
		for (int j = n; j; j --)
			f[j] = (f[j] - f[las[j]]) % mod;
		f[0] = 0;
	}

	ll ans = 0;
	for (int j = 0; j <= n; j ++)
		ans += f[j];
	printf("%lld\n", ans % mod);
}
