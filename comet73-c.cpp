#if 0
2019.11.09

联通块个数 = 点数 - 边数
点数就是 nk ，其中 k 是当前序列数，讨论统计边数。
单独考虑每条边，假设当前所有序列该边有 x 个是两边联通的，
如果该边两端被赋值，那么所有新序列该边一定连上了： x -> x + k
如果该边只有一端被赋值，那么所有新序列该边一定断了： x -> x
否则该边不受影响，新序列相当于复制一遍： x -> 2x
暴力扫描维护即可，事实上可以用线段树做到更优的复杂度。
#endif
#include <cstdio>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
} read;

const int maxn = 2020, mod = 20050321;
ll a[maxn];

int main() {
	int n = read, m = read;

	for(int i = 1; i < n; i ++)
		a[i] = 1;

	ll tot = 1;
	for(int i = 1; i <= m; i ++) {
		int l = read, r = read;
		ll ans = tot * n * 2 % mod;
		for(int j = 1; j < n; j ++) {
			if(l <= j and j < r)
				(a[j] += tot) %= mod;
			else if(j < l - 1 or j > r)
				(a[j] += a[j]) %= mod;
			ans -= a[j];
		}
		(tot <<= 1) %= mod;
		printf("%lld\n", ((ans % mod) + mod) % mod);
	}
}
