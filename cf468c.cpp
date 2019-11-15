#if 0
2019.11.15

考虑一个足够大的数 k 满足在足够大的范围内的所有 x 都有 f(x) + 1 = f(x + 10^k) 。
通过这个可以把范围内的部分 f(x) 替换为 f(x + 10^k) - 1 。
设 0 到 10^k - 1 内的 f(x) 和模 a 为 p ，那么只需将 0 到 a - p - 1 的 f(x) 按上述方式替换，
得到 a - p 到 10^k + a - p - 1 内的 f(x) 和模 a 为 0 。
这样就找到了一个可行的区间，唯一的问题在于求出 p 。
p 是很好求的，因为在 0 到 10^k-1 的范围内每个数在每个数位的分布是均匀的。
每个数位算贡献，不难得出 p = sum(0~9) 10^(k-1) k 。

对于乘法我用了 O(1) 快速乘，然后发现普通的 O(1) 快速乘对于模数小的情况不适用。
因为当模数足够小时 x / m * y 转 long double 后超过 long long 的范围，
而一个超过 long long 范围的 long double 转成 long long 会直接转成 INT64_MAX ，而不溢出。
#endif
#include <cstdio>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef long double ld;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
} read;

inline ll mul(ll x, ll y, ll m) {
	x %= m;
	y %= m;
	ll tmp = x * y - ll(ld(x) / m * y + 0.5) * m;
	return tmp < 0 ? tmp + m : tmp;
}

int main() {
	ll a = read;
	ll k = 18;
	ll po10 = 1;
	for(int i = 0; i < k; i ++)
		po10 *= 10;
	ll p = mul(po10 / 10, 45 * k, a);
	printf("%lld %lld\n", a - p, po10 + a - p - 1);
}
