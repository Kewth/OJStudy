#if 0
2019.12.30

从小到大加数 x ，每次 x 是当前最大值，可以孤立或者连接两段，
DP 设 f[i][j] 表示加了 1 ~ x 个数构成 j 段的方案数。
转移分 i < s / i = s / s < i < t / i = t / t < i < n / i = n 分类，
因为 s, t 比较特殊，s 必须在最左边而 t 必须在最右边，
另外 s 和 t 在 i < n 的时候都不能被合成一段。

这个过程反过来就是把笛卡尔树的最大值一个个删掉，每一段对应的就是一个联通块。
一个个删值是唯一的，但是反过来一个个加数是需要决策的。
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

const int maxn = 2020, mod = 1000000007;
ll f[maxn][maxn];
inline void __a(int &x) { if(x >= mod) x -= mod; }

int main() {
	int n = read, s = read, t = read;
	if(s > t) std::swap(s, t);

	f[0][0] = 1;
	for(int i = 1; i <= n; i ++) {
		for(int j = 1; j <= i and j <= n - i + 1; j ++)
			if(i < s)
				f[i][j] = (j * f[i - 1][j - 1] + j * f[i - 1][j + 1]) % mod;
			else if(i == s)
				f[i][j] = (f[i - 1][j - 1] + f[i - 1][j]) % mod;
			else if(i < t)
				f[i][j] = ((j - 1) * f[i - 1][j - 1] + j * f[i - 1][j + 1]) % mod;
			else if(i == t)
				f[i][j] = (f[i - 1][j - 1] + f[i - 1][j]) % mod;
			else if(i < n)
				f[i][j] = ((j - 2) * f[i - 1][j - 1] + j * f[i - 1][j + 1]) % mod;
			else
				f[i][j] = (j * f[i - 1][j + 1]) % mod;
		if(t <= i and i < n) f[i][1] = 0;
		/* for(int j = 1; j <= i and j <= n - i + 1; j ++) */
		/* 	debug(" %lld", f[i][j]); */
		/* debug("\n"); */
	}

	printf("%lld\n", f[n][1]);
}
