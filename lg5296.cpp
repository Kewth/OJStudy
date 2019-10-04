#if 0
2019.10.04

如果生成树的权值是边权乘积，那么就可以直接用矩阵树定理的扩展去做。
而此处生成树的权值是边权和，考虑放到指数上转换为乘积，
把每条边的权值从 w 用生成函数 e^(wx) 表示，那么一颗生成树的权值就是权值乘积 e^(sum(w)x) 。
而将 e^(wx) 展开后的 x^k 的系数就是 w^k / k! ，
那么将矩阵树定理扩展到多项式上，在多项式矩阵上求行列式，
此处求出来的行列式也是多项式，为 sum(e^(sum(w)x)) ，展开后 x^k 的系数乘上 k! 就是答案。

另外 update 了多项式求逆的写法，神 tm 我之前写的都是递归的。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;

inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 35, mod = 998244353;
typedef lolong Poly[maxn << 2];
typedef lolong *piter;
int ra[maxn << 2];
Poly ma[maxn][maxn];
Poly line[maxn];
Poly ans;

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

/* void print(piter a, int m) { */
/* 	debug("("); */
/* 	for(int i = 0; i < m; i ++) */
/* 		debug("%lld,", a[i]); */
/* 	debug("%lld)", a[m]); */
/* } */

void NTT(piter a, int n, int typ) {
	for(int i = 1; i < n; i ++)
		ra[i] = (ra[i >> 1] >> 1) | ((i & 1) * (n >> 1));
	for(int i = 0; i < n; i ++)
		if(i < ra[i])
			std::swap(a[i], a[ra[i]]);
	for(int m = 1; m < n; m <<= 1) {
		lolong Gn = power(3, typ * (mod - 1) / (m << 1));
		for(int i = 0; i < n; i += m << 1) {
			lolong G = 1;
			for(int k = i; k < i + m; k ++) {
				lolong a0 = a[k], a1 = a[k + m] * G;
				a[k] = (a0 + a1) % mod;
				a[k + m] = (a0 - a1 - mod) % mod + mod;
				(G *= Gn) %= mod;
			}
		}
	}
	if(typ == -1) {
		lolong pp = power(n, -1);
		for(int i = 0; i < n; i ++)
			(a[i] *= pp) %= mod;
	}
}

inline void mul(piter a, piter b, int n, int m) {
	n <<= 1;
	NTT(a, n, 1);
	NTT(b, n, 1);
	for(int i = 0; i < n; i ++)
		(a[i] *= b[i]) %= mod;
	NTT(a, n, -1);
	NTT(b, n, -1);
	std::fill(a + m + 1, a + n, 0);
}

Poly tmp, out;
void get_inv(piter a, int n) {
	std::fill(out, out + (n << 1), 0);
	out[0] = power(a[0], -1);

	for(int m = 2; m <= n; m <<= 1) {
		std::copy(a, a + m, tmp);
		std::fill(tmp + m, tmp + (m << 1), 0);

		NTT(out, m << 1, 1);
		NTT(tmp, m << 1, 1);
		for(int i = 0; i < (m << 1); i ++)
			(out[i] *= mod + 2 - out[i] * tmp[i] % mod) %= mod;
		NTT(out, m << 1, -1);

		std::fill(out + m, out + (m << 1), 0);
	}
}

int main() {
	int n = input(), m = input();

	for(int i = 1; i <= n; i ++) {
		for(int j = 1; j <= n; j ++) {
			int x = input();
			lolong now = 1;
			for(int k = 0; k <= m; k ++) {
				ma[i][j][k] += mod - now;
				ma[i][i][k] += now;
				(now *= x * power(k + 1, -1) % mod) %= mod;
			}
		}
	}

	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= n; j ++)
			for(int k = 0; k <= m; k ++)
				ma[i][j][k] %= mod;

	int len = 1;
	while(len < m + 1)
		len <<= 1;

	/* for(int i = 2; i <= n; i ++) { */
	/* 	for(int j = 2; j <= n; j ++) */
	/* 		print(ma[i][j], m); */
	/* 	debug("\n"); */
	/* } debug("\n"); */

	for(int i = 2; i < n; i ++) {
		get_inv(ma[i][i], len);
		std::fill(out + m + 1, out + len, 0);

		for(int j = i + 1; j <= n; j ++) {
			for(int k = i; k <= n; k ++) {
				std::copy(ma[i][k], ma[i][k] + m + 1, line[k]);
				mul(line[k], out, len, m);
				mul(line[k], ma[j][i], len, m);
			}

			for(int k = i; k <= n; k ++)
				for(int l = 0; l <= m; l ++)
					(ma[j][k][l] += mod - line[k][l]) %= mod;
		}
	}

/* 	for(int i = 2; i <= n; i ++) { */
/* 		for(int j = 2; j <= n; j ++) */
/* 			print(ma[i][j], m); */
/* 		debug("\n"); */
/* 	} debug("\n"); */

	ans[0] = 1;
	for(int i = 2; i <= n; i ++)
		mul(ans, ma[i][i], len, m);

	for(int i = 1; i <= m; i ++)
		(ans[m] *= i) %= mod;

	printf("%lld\n", ans[m]);
}
