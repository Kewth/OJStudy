#if 0
2020.01.04

直接考虑一个排列的贡献是不现实的，应分离算贡献，考虑每个连续的段出现的次数。
枚举段长 l 和段中最大值 x ，那么这段就是由 x - l + 1 到 x 构成的一个连续区间。
这个区间在所有排列的出现次数是很好统计的，首先在 n 个位置选出长为 l 的区间的方案为 n - l + 1 ，
然后段内随意排列，方案为 l! ，段外随意排列，方案为 (n - l)! 。
然而枚举 l, x 是 O(n^2) 的，但是从上面的分析不难看出一个长为 l 的区间的出现次数与 x 无关。
那么只需要枚举 l ，其对应的 x 有 (n - l + 1) 个。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
} read;

const int maxn = 250005;
int p[maxn];
ll fac[maxn];

int main() {
	int n = read, mod = read;

	fac[0] = 1;
	for(int i = 1; i <= n; i ++)
		fac[i] = fac[i - 1] * i % mod;

	ll ans = 0;
	for(int l = 1; l <= n; l ++)
		(ans += fac[l] * fac[n - l] % mod * (n - l + 1) % mod * (n - l + 1)) %= mod;
	printf("%lld\n", ans);
}
