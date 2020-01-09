#pragma GCC optimize(3)
#if 0
2020.01.09

就是求 lcm ，筛出质数，求出每个质数的最大次数乘起来即可。
傻逼出题人垃圾模数。
需要手写 bitset ，stl 常数真的大。
#endif
#include <cstdio>
#include <algorithm>
#include <bitset>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
} read;

const int maxn = 100000065, mod = 100000007;
ll set[maxn / 64];

inline bool bitget(int x) {
	return set[x >> 6] >> (x & 63) & 1;
}

inline void bitset(int x) {
	set[x >> 6] |= 1ll << (x & 63);
}

int main() {
	int n = read;
	ll ans = 1 << (31 - __builtin_clz(unsigned(n)));
	for(int i = 3; i <= n; i += 2)
		if(!bitget(i)) {
			if(i <= n / i)
				for(int j = i * i; j <= n; j += i)
					bitset(j);
			int now = i;
			while(now <= n / i)
				now = now * i;
			(ans *= now) %= mod;
		}
	printf("%lld\n", ans);
}
