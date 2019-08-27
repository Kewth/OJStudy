#if 0
2019.08.25

生成函数，第 i 个权值的生成函数 f(i) = (1 + x^{2^i})^3 ，特别地对于王牌 f(0) = (1 + x)^2 。
直接算不行，利用平方差公式，把多项式乘上 (1 + x)(1 - x)^3 ，最后多项式成了：
(1 - x^{2^{k+1}})
那么原多项式模 x^{n+1} 即：
\frac{1}{(1 + x)(1 - x)^3}
即：
\frac{1}{(1 - x^2)(1 - x)^2}
展开：
(1 + x^2 + x^4 + ... + x^n) (1 + 2x + 3x^2 + ... + (n - 1)x^n)
容易算出 x^n 的系数就是 (n / 2 + 1)^2 。
#endif
#include <cstdio>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;

inline lolong input() { lolong x; scanf("%lld", &x); return x; }

const int mod = 998244353;

int main() {
	lolong k = input(), n = input();
	printf("%lld\n", ((n / 2 + 1) % mod) * ((n / 2 + 1) % mod) % mod);
}
