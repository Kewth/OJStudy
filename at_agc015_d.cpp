#if 0
2019.12.15

假设 l, r 的最高位 (k) 相同，那么 [l, r] 内的数的或的第 k 位一定为 1 。
那么第 k 位无需考虑，也就是说 l, r 可以去掉一些位直到 r 的最高位为 1 且 l 最高位为 0 。
设此时的位数为 k ，有 l < 2^k <= r 。

1) [l, 2^k) 内的数的或的集合恰好也是 [l, 2^k) ，因为两个数的或不会小于其中任意一个数。

2) [2^k, r] 内的数的或的集合是 [2^k, 2^k + 2^d) ，其中 d 是 r 去掉第 k 位后的最小的前导零。

3) 考虑 [l, 2^k) 和 [2^k, r] 之间的或，
也就是 [l, 2^k) 和 [2^k, 2^k + 2^d) 分别选一个数得到的或的集合，
前者的第 k 位一定是 0 但是后者在该位上为 1 ，
因此就是 [2^k + l, 2^(k+1)) 和 [2^k, 2^k + 2^d) 的或的集合，
根据 1) 可以知道这部分或的集合是 [2^k + l, 2^(k+1)) 。

将三者的或的集合并起来求大小即可，总复杂度可以做到 O(1) 。
#endif
#include <cstdio>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef unsigned long long ull;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
} read;

int main() {
	ll l = read, r = read;

	if(l == r) return puts("1"), 0;

	int k = 63 - __builtin_clzll(ull(l ^ r));

	/* debug("%d\n", k); */

	l &= (2ll << k) - 1;
	r &= (2ll << k) - 1;

	/* debug("%lld %lld\n", l, r); */

	int d = r == (1ll << k) ? 0 : 64 - __builtin_clzll(ull(r ^ (1ll << k)));

	/* debug("%d\n", d); */

	ll l1 = l, r1 = (1ll << k) + (1ll << d) - 1;
	ll l2 = (1ll << k) + l, r2 = (1ll << k << 1) - 1;

	/* debug("%lld %lld %lld %lld\n", l1, r1, l2, r2); */

	if(l2 <= r1) printf("%lld\n", r2 - l1 + 1);
	else printf("%lld\n", r2 - l2 + r1 - l1 + 2);
}
