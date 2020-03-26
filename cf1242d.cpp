#if 0
2020.03.26

每 k^2 + 1 个数分为一块，称在每次操作中求和得到的数为 MAGIC 。
一个关键的性质是每个块内恰好有一个 MAGIC 。
证明可以用数学归纳法，这里不讨论。

另外把除掉 MAGIC 后的数列每 k 个分为一段。
那么第 i 段的数的和就是第 i 块所含有的 MAGIC 。

如果 n 是个 MAGIC ，那么答案就是 p (k + 1) ，其中 p 是 n 所在块编号。
否则，答案就是 n + m ，其中 m 是被提到 n 前面的 MAGIC 数量。
满足这个条件的 MAAGIC 所属的块是个连续区间，求出这个区间即可。

唯一需要的是求出 n 所在块的 MAIGC ，递归求解，每次规模除以 k ，复杂度 logn / logk 。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
} read;

ll key (ll p, ll k) {
	if (p == 1) return k * (k + 1) >> 1;
	ll np = (p - 1) / k + 1;
	ll l = (np - 1) * (k * k + 1) + ((p - 1) % k) * k + 1, r = l + k - 1;
	/* debug("  %lld %lld\n", l, r); */
	ll ke = key(np, k);
	ll res = (l + r) * k >> 1;
	if (l <= ke and ke <= r)
		return res - ke + r + 1;
	if (ke <= l)
		return res + k;
	return res;
}

int main () {
	int T = read;
	while (T --) {
		ll n = read, k = read;
		ll p = (n - 1) / (k * k + 1) + 1;
		ll ke = key(p, k);
		/* debug("%lld\n", ke); */
		if (n == ke)
			printf("%lld\n", (k + 1) * p);
		else {
			ll l, r;
			if (ke < n)
				l = p + 1, r = (p - 1) * k + (n - 2) % (k * k + 1) / k;
			else
				l = p, r = (p - 1) * k + (n - 1) % (k * k + 1) / k;
			/* debug("%lld %lld\n", l, r); */
			printf("%lld\n", n + (r - l + 1));
		}
	}
}
