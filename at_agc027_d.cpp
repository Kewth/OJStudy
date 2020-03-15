#if 0
2020.03.15

不妨令 m = 1 ，设 n 为奇数。
将矩阵黑白染色，确定白色的值，然后令黑色的值为周围白色的值的 lcm + 1 。
一个简单的构造时在两个对角线上放质数，然后把白格子按两个对角线建坐标轴，
每个白色的值钦定为在在两个坐标轴上对应的质数的乘积。
那么每个黑色的格子一定是四个质数的乘积加一。
然而第 1000 个质数是 7000+ ，四个如此大小的质数相乘会超出范围。
因此放质数也有讲究，要把最大的和最小的交替放，避免两个大质数相乘。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
} read;

const int maxn = 505;
int prime[maxn << 1], tmp[maxn << 1], pp;
ll a[maxn][maxn];

ll gcd(ll x, ll y) {
	if(!y) return x;
	return gcd(y, x % y);
}

ll lcm(ll x, ll y) {
	if(!x or !y) return x + y;
	return x / gcd(x, y) * y;
}

int main() {
	int n = read;
	bool mark = !(n & 1);
	if(mark) ++ n;

	for(int x = 2; pp < n * 2; x ++) {
		bool ok = 1;
		for(int d = 2; d * d <= x; d ++)
			// XXX: 震惊！这里不强制转 bool 竟然会出错？！
			ok &= bool(x % d);
		if(ok)
			tmp[++ pp] = x;
	}

	for(int i = 1; i <= n; i ++)
		prime[i * 2 - 1] = tmp[i];
	for(int i = 1; i <= n; i ++)
		prime[pp - i * 2 + 2] = tmp[n + i];

	for(int i = 1; i <= n; i ++)
		a[i][i] = prime[i];

	for(int i = 1; i <= n; i ++)
		a[i][n - i + 1] = prime[n + i];

	for(int i = 1; i <= n; i ++)
		for(int j = (i & 1) ? 1 : 2; j <= n; j += 2)
			if(!a[i][j])
				a[i][j] = a[(i + j) >> 1][(i + j) >> 1] *
					a[(n + 1 + i - j) >> 1][(n + 1 + j - i) >> 1];

	for(int i = 1; i <= n; i ++)
		for(int j = (i & 1) ? 2 : 1; j <= n; j += 2)
			a[i][j] = lcm(a[i - 1][j], lcm(a[i][j - 1],
						lcm(a[i + 1][j], a[i][j + 1]))) + 1;

	if(mark) -- n;
	for(int i = 1; i <= n; i ++) {
		for(int j = 1; j <= n; j ++)
			printf("%lld ", a[i][j]);
		puts("");
	}
}
