/*
 * Since g++10 is released, some characters is not valid inside #if 0 :(
 * So, why not using clang++? :D

 * Date:
  2020.06.14

 * Solution:
  这个一般性的问题是 NPC 的，那么必须要用到每个数形如 p^k 这个性质。
  可以证明，由于权值的特殊性，从大到小每个数加入到总和较小的一个集合即可。因为对于两个
集合 A, B 满足 sum(A) > sum(B) ，在 B 加入一个不超过 min(A | B) 的数 x 后，一定仍然有
sum(A) >= sum(B) 成立。
  那么维护两个集合的差值 dt 即可，由于 dt 会很大，可以维护 dt / min ，min 是当前加入的
数的最小值，那么当 dt >= n 的时候，把所有数加入到 B 都不会超过 A ，这时就不需要关注 dt
具体的值了。

 * Digression:
  维护 dt 要特判 p = 1 和 dt = 0 的情况，这两者都会使得 dt 不变。

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
	template<class T> inline void operator () (T &x) { x = *this; }
} read;

const int maxn = 1000005, mod = 1000000007;
int a[maxn];

inline ll power (ll x, int k) {
	if (k < 0) k += mod - 1;
	ll res = 1;
	while (k) {
		if (k & 1) (res *= x) %= mod;
		(x *= x) %= mod;
		k >>= 1;
	}
	return res;
}

int main () {
	int T = read;
	while (T --) {
		int n = read, p = read;
		for (int i = 1; i <= n; i ++) read(a[i]);
		std::sort(a + 1, a + n + 1);
		ll ans = 0, d = 0;
		for (int i = n; i; i --) {
			if (i < n and p > 1 and d)
				for (int k = a[i]; k < a[i + 1] and d <= n; k ++)
					d *= p;
			if (d == 0) {
				++ d;
				ans += power(p, a[i]);
			} else {
				-- d;
				ans += mod - power(p, a[i]);
			}
		}
		ans %= mod;
		printf("%lld\n", ans);
	}
}
