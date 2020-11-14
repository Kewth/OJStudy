/*
 * Author: Kewth

 * Date:
  2020.11.14

 * Solution:
  枚举区间长度 l ，最优的修改一定是一段后缀，然后最小化后面一段的代价，该代价每个二进制是
独立的，容易发现事实上就是 (k & ~z) << 1 ，找到最优的 z 是容易的。

 * Digression:

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
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
} read;

const int maxn = 100005, maxj = 60;
ll a[maxn];
ll pre[maxn];

int main () {
	int n = read;
	read(a[1]);
	ll d = read;
	ll k = read, y = read;
	for (int i = 2; i <= n; i ++)
		a[i] = a[i - 1] + d;
	for (int i = 1; i <= n; i ++)
		pre[i] = pre[i - 1] + a[i];

	ll ans = 4000000000000000000;
	for (int i = 1; i <= n; i ++) {
		if (pre[i - 1] > y) continue;
		ll Z = (y - pre[i - 1]) / (n - i + 1), z = 0;
		for (int j = maxj - 1; j >= 0; j --)
			if (k >> j & 1 and z + (1ll << j) <= Z)
				z += 1ll << j;
		ans = std::min(ans, (n - i + 1) * ((z ^ k) + k - z));
	}
	printf("%lld\n", ans);
}
