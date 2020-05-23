#if 0
2020.05.23

  把每个数表示为 2^a*b 的形式，其中 b 是奇数，那么可以发现如果集合内存在两个数 a 不相同，
这两个数就一定能构成奇环，而如果集合内所有数的 a 都相同，就一定不存在奇环，因此对于保留
数量最多的一个 a 即可。
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
#include <vector>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
} read;

const int maxn = 200005, maxk = 60;

ll a[maxn];
int ak[maxn];
int tot[maxk];

int main () {
	int n = read;
	for (int i = 1; i <= n; i ++) {
		ll x = a[i] = read;
		int k = 0;
		while (!(x & 1)) x >>= 1, ++ k;
		++ tot[k];
		ak[i] = k;
	}

	int K = 0;
	for (int k = 0; k < maxk; k ++)
		if (tot[k] > tot[K])
			K = k;

	printf("%d\n", n - tot[K]);
	for (int i = 1; i <= n; i ++)
		if (ak[i] != K)
			printf("%lld ", a[i]);
	puts("");
}
