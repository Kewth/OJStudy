#if 0
2020.05.30

  从上到下算出每层的“自由叶子数”，即该层能在下面接儿子的节点数，设为 b[i] ，然后从下到上
统计答案，就可以计算出每层的最大实际节点数。
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
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
} read;

const int maxn = 100005;
const ll inf = 1000000000000000000;
ll a[maxn];
ll b[maxn];

int main () {
	int n = read;
	for (int i = 0; i <= n; i ++) read(a[i]);
	b[0] = 1;
	for (int i = 0; i <= n; i ++) {
		b[i] -= a[i];
		if (b[i] < 0) return puts("-1"), 0;
		b[i + 1] = std::min(inf, b[i] << 1);
	}
	ll ans = 0;
	for (int i = n; i; i --) {
		ans += a[i];
		ll x = std::min(b[i - 1], a[i]);
		a[i - 1] += x;
		/* debug("%d : %lld\n", i, a[i]); */
	}
	ans += a[0];
	printf("%lld\n", ans);
}
