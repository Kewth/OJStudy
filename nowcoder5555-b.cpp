#if 0
2020.05.15

* 抽屉原理，分段

  把数分为四段，两个数相似当且仅当不超过三个位置不同，那么根据抽屉原理，至少有一段是完全
相同的。对于每一段每种数开个 vector 记所有数，询问在每个段对应的数的 vector 暴力扫，因为
序列随机，可以认为每个 vector 里的数是均匀的，也就是说一个 vector 的大小的期望是 n/2^16 。
#endif
#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef unsigned long long ull;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ull () { ull x; return scanf("%llu", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
} read;

ull Rand (ull x) {
    x ^= x << 13;
    x ^= x >> 7;
    x ^= x << 17;
    return x;
}

const int maxn = 1000005, mod = 998244353;
ull a[maxn];
ll po[maxn];
std::vector<ull> set[4][1 << 16];

int count (ull x) {
	return __builtin_popcountll(x);
}

int main() {
	int n = read, q = read;
	read(a[0]);
	for (int i = 1; i < n; i ++)
		a[i] = Rand(a[i - 1]);
	for (int i = 0; i < n; i ++) {
		for (int j = 0; j < 4; j ++)
			set[j][a[i] >> (16 * j) & ((1 << 16) - 1)].push_back(a[i]);
	}

	po[0] = 1;
	for (int i = 1; i <= q; i ++)
		po[i] = (po[i - 1] << 1) % mod;

	ll ans = 0;
	while (q --) {
		ull x = read;
		bool now = 0;
		for (int j = 0; j < 4; j ++)
			for (ull y : set[j][x >> (16 * j) & ((1 << 16) - 1)])
				if (count(x ^ y) <= 3)
					now = 1;
		if (now)
			ans += po[q];
	}

	printf("%lld\n", ans % mod);
}
