#if 0
2019.10.26

首先数是 k 的倍数的限制可以用单位根反演解决，在模意义下求出原根即可得到 k 次单位根。
剩下的问题是组合数乘上一个斐波那契数，将斐波那契数 F[n] 表示为 A^n ，
则可以用二项式定理快速计算结果。
但这个 A 是什么呢？
事实上很难找出 A 对应的整数，但是通过斐波那契数的矩阵乘法表示不难的出 A 就是转移矩阵。
在矩阵运算的意义下二项式定理仍成立，因而仍可以使用快速幂计算结果。
#endif
#include <cstdio>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;

inline int input() { int x; scanf("%d", &x); return x; }
inline lolong linput() { lolong x; scanf("%lld", &x); return x; }

int mod;
lolong power(lolong x, int k) {
	if(k < 0) k += mod - 1;
	lolong res = 1;
	while(k) {
		if(k & 1) (res *= x) %= mod;
		(x *= x) %= mod;
		k >>= 1;
	}
	return res;
}

struct Matrix {
	lolong a[2][2];
	Matrix(lolong x = 0) {
		a[0][0] = a[1][1] = x;
		a[0][1] = a[1][0] = 0;
	}
};

Matrix operator * (Matrix a, Matrix b) {
	Matrix c;
	for(int i = 0; i < 2; i ++)
		for(int j = 0; j < 2; j ++) {
			c.a[i][j] = 0;
			for(int k = 0; k < 2; k ++)
				c.a[i][j] += a.a[i][k] * b.a[k][j];
			c.a[i][j] %= mod;
		}
	return c;
}

Matrix operator + (Matrix a, Matrix b) {
	Matrix c;
	for(int i = 0; i < 2; i ++)
		for(int j = 0; j < 2; j ++)
			c.a[i][j] = (a.a[i][j] + b.a[i][j]) % mod;
	return c;
}

Matrix power(Matrix x, lolong k) {
	/* debug("%lld %lld %lld %lld\n", x.a[0][0], x.a[0][1], x.a[1][0], x.a[1][1]); */
	Matrix res = 1;
	while(k) {
		if(k & 1) res = res * x;
		x = x * x;
		k >>= 1;
	}
	/* debug("%lld %lld %lld %lld\n", res.a[0][0], res.a[0][1], res.a[1][0], res.a[1][1]); */
	return res;
}

lolong getG() {
	int fac[30];
	int p = 0;
	int x = mod - 1;
	for(int i = 2; i * i <= x; i ++)
		while(!(x % i)) {
			fac[p ++] = i;
			x /= i;
		}
	if(x > 1)
		fac[p ++] = x;
	int g = 2;
	while(1) {
		for(int i = 0; i < p; i ++)
			if(power(g, (mod - 1) / fac[i]) == 1)
				goto FAIL;
		return g;
FAIL:
		g ++;
	}
}

int main() {
	int T = input();
	while(T --) {
		lolong n = linput();
		int k = input();
		mod = input();
		lolong G = getG();
		/* debug("%lld\n", G); */
		lolong Wk = power(G, (mod - 1) / k);

		Matrix A;
		A.a[0][0] = 0;
		A.a[0][1] = 1;
		A.a[1][0] = 1;
		A.a[1][1] = 1;

		Matrix F;
		F.a[0][0] = F.a[1][0] = 1;
		F.a[0][1] = F.a[1][1] = 0;

		lolong W = 1;
		lolong ans = 0;

		for(int i = 0; i < k; i ++) {
			/* debug("%lld\n", W); */
			Matrix M = power(A * W + 1, n) * F;
			ans += M.a[0][0];
			/* debug("-> %lld\n", ans); */
			(W *= Wk) %= mod;
		}

		((ans %= mod) *= power(k, -1)) %= mod;
		printf("%lld\n", ans);
	}
}
