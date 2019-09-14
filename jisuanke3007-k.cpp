#if 0
2019.09.14

考虑枚举延迟的天数 d ，那么 a[1] 到 a[2k] 都可以确定，
把 p[d] 看做变量，就可以得出 p[d] 对 f 的贡献。
将这些贡献写成方程，联立得到关于 p 的方程组，高斯消元算出 p 。
然后就可以枚举延迟天数 d 算 a[1] 到 a[n] 对答案的贡献了。
#endif
#include <cstdio>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;
inline int input() { int x; scanf("%d", &x); return x; }
inline lolong linput() { lolong x; scanf("%lld", &x); return x; }

const int maxk = 77, mod = 1000000007;
lolong a[maxk << 1], f[maxk];
lolong M[maxk][maxk];
lolong p[maxk];
lolong s[maxk];

lolong power(lolong x, int k) {
	if(k < 0)
		k += mod - 1;
	lolong res = 1;
	while(k) {
		if(k & 1) (res *= x) %= mod;
		(x *= x) %= mod;
		k >>= 1;
	}
	return res;
}

int main() {
	int T = input();

	while(T --) {
		int k = input();
		lolong n = linput();

		for(int i = 1; i <= k; i ++)
			a[i] = input();
		for(int i = 1; i <= k; i ++)
			f[i] = input();

		for(int d = 1; d <= k; d ++) {
			for(int i = k + 1; i <= (k << 1); i ++)
				a[i] = a[i - d];
			for(int i = 1; i <= k; i ++)
				M[i][d] = a[k + i - d];
		}
		for(int i = 1; i <= k; i ++)
			M[i][k + 1] = f[i];

		/* for(int i = 1; i <= k; i ++) { */
		/* 	for(int j = 1; j <= k + 1; j ++) */
		/* 		debug(" %lld", M[i][j]); */
		/* 	debug("\n"); */
		/* } */

		for(int x = 1; x <= k; x ++) {
			lolong iMxx = power(M[x][x], -1);
			for(int i = 1; i <= k + 1; i ++)
				(M[x][i] *= iMxx) %= mod;
			for(int i = 1; i <= k; i ++)
				if(i != x) {
					lolong Mix = M[i][x];
					for(int j = 1; j <= k + 1; j ++)
						((M[i][j] -= M[x][j] * Mix + mod) %= mod) += mod;
				}
		}

		for(int i = 1; i <= k; i ++)
			p[i] = M[i][k + 1] * power(M[i][i], -1) % mod;

		/* for(int i = 1; i <= k; i ++) */
		/* 	debug(" %lld", p[i]); */
		/* debug("\n"); */

		lolong ans = 0;

		for(int d = 1; d <= k; d ++) {
			for(int i = 1; i <= d; i ++)
				a[k + i] = a[k + i - d];
			for(int i = 1; i <= d; i ++)
				s[i] = (s[i - 1] + a[k + i]) % mod;
			lolong sum = (n - k) / d % mod * s[d] + s[(n - k) % d];
			for(int i = 1; i <= k; i ++)
				sum += a[i];
			ans += sum % mod * p[d] % mod;
		}

		printf("%lld\n", ans % mod);
	}
}
