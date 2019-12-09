#if 0
2019.12.08

不妨设 A <= B 。
首先如果存在三个数两两的差小于 A 方案数一定为 0 ，因为根据抽屉原理一定要有两个数在一个集合。
排除上述情况后，满足差小于 A 的一定只能是相邻两数。
DP 设 f[i] 表示考虑前 i 个数，把第 i 个数放在 B 集合的方案数，
朴素转移枚举可行的 j ，j 有两个限制，
一个是 a[j] 和 a[i] 的差不小于 B ，另一个是 i + 1 到 j 之间的数相邻之间的差都不小于 A 。
这两个限制都将 j 限制再一个区间，那么 f[i] 的转移对应的是一段 f[j] 的区间和，前缀和优化即可。
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

const int maxn = 100005, mod = 1000000007;
ll s[maxn];
int lpos[maxn];
int f[maxn], sf[maxn];

int main() {
	int n = read;
	ll a = read, b = read;
	if(a > b) std::swap(a, b);

	for(int i = 1; i <= n; i ++)
		read(s[i]);

	for(int i = 3; i <= n; i ++)
		if(s[i] - s[i - 2] < a)
			return puts("0"), 0;

	lpos[1] = 1;
	for(int i = 2; i <= n; i ++)
		if(s[i] - s[i - 1] >= a)
			lpos[i] = lpos[i - 1];
		else
			lpos[i] = i;

	s[++ n] = 2000000000000000000;
	f[0] = sf[0] = 1;
	for(int i = 1; i <= n; i ++) {
		int l = std::max(0, lpos[i - 1] - 1);
		int r = std::min(int(std::upper_bound(s + 1, s + i + 1, s[i] - b) - s - 1), i - 1);
		f[i] = l <= r ? (sf[r] + mod - sf[l - 1]) % mod : 0;
		sf[i] = (sf[i - 1] + f[i]) % mod;
		/* debug("%d : %d %d -> %d\n", i, l, r, f[i]); */
	}

	printf("%d\n", f[n]);
}
