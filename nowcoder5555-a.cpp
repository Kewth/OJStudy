#if 0
2020.05.15

  设 m = a sqrt(b) ，其中 sqrt(b) 是无理数，那么前面的所有数都要是 c sqrt(b) 的形式。
  由于数列 {c} 要去重，不妨统计单调不减的序列，但是单调不减相当于多了个限制，不妨统
计该序列的差分。DP ，设 f[i][j] 表示前 i 个数选贡献和为 j 的方案数。
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
	{ x = *this; this -> operator () (a...); }
} read;

const int maxn = 10010, mod = 998244353;
ll f[maxn][maxn];

int main () {
	int n = read, m = read, a = 1;
	for (int x = 2; x * x <= m; x ++)
		while (m % (x * x) == 0) {
			m /= x * x;
			a *= x;
		}
	f[0][0] = 1;
	for (int i = 1; i <= n; i ++) {
		for (int x = 0; x <= a; x ++) {
			for (int j = 0; j <= x; j += i)
				f[i][x] += f[i - 1][x - j];
			f[i][x] %= mod;
		}
	}
	printf("%lld\n", f[n][a]);
}
