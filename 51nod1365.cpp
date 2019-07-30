#if 0
2019.07.30

主要用到的定理： f(x + y) = f(x) f(y + 1) + f(x - 1) f(y) 。

由此推出三个引理：
1) f(n) = f(n % k) f(k - 1)^(n / k)
2) f(k - 1)^2 = (-1)^k
3) f(k - x) f(k - 1) = f(x) (-1)^(k - x + 1)
上式都是模 f(k) 意义下的，证明略，其实不难。

根据这个就可以直接求出 f(n) % f(k) 的一个小于 f(k) 的表达式了，矩阵快速幂即可。
#endif
#include <cstdio>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;
inline lolong input() {
	int c = getchar();
	lolong x = 0;
	while(c < '0' or c > '9') c = getchar();
	while(c >= '0' and c <= '9') x = x * 10 + c - '0', c = getchar();
	return x;
}

struct Mar {
	lolong val[2][2];
	inline lolong & operator() (bool x, bool y) {
		return val[x][y];
	}
};
const int mod = 1000000007;

Mar operator * (Mar a, Mar b) {
	Mar m;
	for(int i = 0; i < 2; i ++)
		for(int j = 0; j < 2; j ++) {
			m(i, j) = 0;
			for(int k = 0; k < 2; k ++)
				m(i, j) += a(i, k) * b(k, j);
			m(i, j) %= mod;
		}
	return m;
}

inline lolong fib(lolong n) {
	Mar m, x;
	m(0, 0) = 1;
	m(0, 1) = 0;
	m(1, 0) = 0;
	m(1, 1) = 1;
	x(0, 0) = 1;
	x(0, 1) = 1;
	x(1, 0) = 1;
	x(1, 1) = 2;
	lolong k = n / 2;
	while(k) {
		if(k & 1) m = m * x;
		x = x * x;
		k >>= 1;
	}
	// debug("fib %lld\n", n);
	// debug("%lld %lld\n", m(0, 0), m(0, 1));
	// debug("%lld %lld\n", m(1, 0), m(1, 1));
	if(n & 1)
		return m(1, 1);
	else
		return m(0, 1);
}

int main() {
	int T = input();
	while(T --) {
		lolong n = input(), k = input();
		if(not (n % k) or k == 2)
			puts("0");
		else if((n / k) & 1)
			printf("%lld\n", ((n / k / 2 * k + n % k + 1) & 1 ?
						fib(k) - fib(k - n % k) + mod : fib(k - n % k)) % mod);
		else
			printf("%lld\n", ((n / k / 2 * k) & 1 ?
						fib(k) - fib(n % k) + mod : fib(n % k)) % mod);
	}
}
