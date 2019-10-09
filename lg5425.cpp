#if 0
2019.10.08

黑科技，O(V) 预处理 + O(1) GCD 。
对于 GCD(x, y)　将 x 表示为 a * b * c ，
满足 a, b, c 要么不大于 sqrt(x), 要么是质数。
事实上一定存在这样的分解，只需得到 x 的最小质因子 p ，
求出 x / p 的三个分解，再把 p 乘到最小的分解上即可，可以归纳证明这样是满足要求的。

用线性筛或者埃氏筛预处理出 V 以内每个数的分解，
然后考虑依次求 a, b, c 与 y 的 gcd, 每次求出 gcd d 就把 y 除以 d 即可。
这里只讨论 a, 不难发现 b, c 是类似的，
如果 a 是质数，简单讨论一下即可得到 gcd(y, a) ，
否则 a 不超过 sqrt(V) ，gcd(a, y) = gcd(a, y % a) ，
此时 a 和 y % a 都不超过 sqrt(V) ，递推预处理 sqrt(V) 内两两的 gcd 即可。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;

inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 5050, maxv = 1000005, maxb = 1005, mod = 998244353;
int a[maxn], b[maxn];
int gcd[maxb][maxb];
int magic[maxv][3];
int minp[maxv];

int GCD(int x, int y) {
	int res = 1;
	/* debug("%d -> %d * %d * %d\n", x, magic[x][0], magic[x][1], magic[x][2]); */
	for(int i = 0; i < 3; i ++) {
		int X = magic[x][i];
		int d;
		if(X < maxb)
			d = gcd[X][y % X];
		else if(y % X)
			d = 1;
		else
			d = X;
		res *= d;
		y /= d;
	}
	return res;
}

int main() {
	for(int i = 0; i < 3; i ++)
		magic[1][i] = 1;

	for(int i = 2; i < maxv; i ++)
		if(!minp[i]) {
			magic[i][2] = i;
			magic[i][0] = magic[i][1] = 1;
			if(i <= (maxv - 1) / i)
				for(int j = i * i; j < maxv; j += i)
					if(!minp[j] or i < minp[j])
						minp[j] = i;
		}

		else {
			magic[i][0] = magic[i / minp[i]][0] * minp[i];
			magic[i][1] = magic[i / minp[i]][1];
			magic[i][2] = magic[i / minp[i]][2];
			std::sort(magic[i], magic[i] + 3);
		}

	for(int i = 0; i < maxb; i ++) {
		gcd[i][0] = i;
		for(int j = 1; j <= i; j ++)
			gcd[i][j] = gcd[j][i % j];
	}

	for(int i = 0; i < maxb; i ++)
		for(int j = i + 1; j < maxb; j ++)
			gcd[i][j] = gcd[j][i];

	int n = input();
	for(int i = 1; i <= n; i ++)
		a[i] = input();
	for(int i = 1; i <= n; i ++)
		b[i] = input();

	for(int i = 1; i <= n; i ++) {
		lolong ans = 0, power = 1;
		for(int j = 1; j <= n; j ++) {
			(power *= i) %= mod;
			ans += GCD(a[i], b[j]) * power % mod;
			/* debug("%d %d : %d\n", a[i], b[j], GCD(a[i], b[j])); */
			/* if(GCD(a[i], b[j]) != std::__gcd(a[i], b[j])) */
			/* 	return 1; */
		}
		ans %= mod;
		printf("%lld\n", ans);
	}
}
