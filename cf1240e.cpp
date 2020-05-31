#if 0
2020.05.29

  枚举 y ，考虑求出最大的 x 。
  将木材按长度整除 y 分段，每段的长度都在 [ky, ky + y) 之间，求出 cnt 表示一共能够切出
多少长度为 y 的木材。注意到段的总数是调和级数，这启发我们对于每个段单独统计。
  不妨放宽条件，允许 x 比 y 大，而算贡献的时候面积定义为 y * min(x, c) ，其中 c 是切出
2 个 x 后最多能切出的 y 的数量。
  如果两个 x 来自同一个木材，设该木材长为 a ，那么注意到如果 2x mod y > a mod y ，那么
增大 x 不会使 c 变小，也就一定不劣，因此可以认为有 2x mod y <= a mod y 。假设 2x 确定，
那么可以直接确定最优的 a 就是满足 a >= 2x 且 a mod y 最大的木材。枚举 2x 所在的段，找
出满足条件的最优 a 即可。
  如果两个 x 来自两个木材，情况有所不同但又类似，此时最优的仍是满足 a >= x 且 a mod y
最大的两个木材，枚举 x 所在的段，找出 a mod y 最大和次大值即可。
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
} read;

const int maxn = 500005;
int tot[maxn];
int pre[maxn], las[maxn];

int main () {
	int n = read;
	for (int i = 1; i <= n; i ++) ++ tot[read];
	n = 500000;
	while (!tot[n]) -- n;

	for (int i = 1; i <= n; i ++) pre[i] = pre[i - 1] + tot[i];
	las[0] = -1;
	for (int i = 1; i <= n; i ++) las[i] = tot[i] ? i : las[i - 1];

	ll ans = 0;
	for (int y = 2; y <= n; y ++) {
		ll cnt = 0;
		int lim = 0;
		for (int k = 0; k * y <= n; k ++) {
			int l = k * y, r = std::min(k * y + y - 1, n);
			cnt += 1ll * k * (pre[r] - (l ? pre[l - 1] : 0));
			lim = k;
		}

		/* debug("y = %d (cnt = %lld)\n", y, cnt); */

		int max = -1, semax = -1;
		for (int k = lim; k >= 0; k --) {
			int l = k * y, r = std::min(k * y + y - 1, n);
			int a = -1, b = -1;
			if (las[r] >= l) {
				a = las[r] % y;
				b = tot[las[r]] > 1 ? a :
					(las[las[r] - 1] >= l ? las[las[r] - 1] % y : -1);
				if (a > max) semax = max, max = a;
				else if (a > semax) semax = a;
				semax = std::max(semax, b);
			}
			/* if (y == 3 and k == 0) debug("%d %d\n", semax, max); */
			if (max >= 0) {
				ll x = std::min<ll>((l + max) >> 1, cnt - k);
				if (x >= 2)
					/* debug(" x = %lld (t1)\n", x), */
					ans = std::max(ans, y * x);
			}
			if (max >= 0 and pre[n] - pre[l + max - 1] >= 2) {
				ll x = std::min<ll>(l + max, cnt - k - k - 1);
				if (x >= 2)
					/* debug(" x = %lld (t2)\n", x), */
					ans = std::max(ans, y * x);
			}
			if (semax >= 0) {
				ll x = std::min<ll>(l + semax, cnt - k - k);
				if (x >= 2)
					/* debug(" x = %lld (t3)\n", x), */
					ans = std::max(ans, y * x);
			}
		}
	}

	printf("%lld\n", ans);
}
