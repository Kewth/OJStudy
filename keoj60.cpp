#if 0
2019.09.14

设 f[n] = a[n] / b[n] ，递推 a, b 用十进制矩阵快速幂即可。
#endif
#include <cstdio>
#include <cstring>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;
const int maxn = 1000005, mod = 998244353;
char s[maxn];

lolong M[2][2];
lolong R[2][2];

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

lolong get[2][2];
void mul(lolong a[2][2], lolong b[2][2]) {
	for(int i = 0; i < 2; i ++)
		for(int j = 0; j < 2; j ++)
			get[i][j] = (a[i][0] * b[0][j] + a[i][1] * b[1][j]) % mod;
}

int main() {
	scanf("%s", s + 1);
	int n = int(strlen(s + 1));

	M[0][0] = 5;
	M[0][1] = 3;
	M[1][0] = 3;
	M[1][1] = 2;

	R[0][0] = R[1][1] = 1;
	R[1][0] = R[0][1] = 0;

	for(int i = n; i; i --) {
		int x = s[i] - '0';
		while(x --) {
			mul(R, M);
			memcpy(R, get, sizeof R);
		}
		lolong B[2][2];
		memcpy(B, M, sizeof B);
		for(int j = 0; j < 9; j ++) {
			mul(M, B);
			memcpy(M, get, sizeof M);
		}
	}

	M[0][0] = 1;
	M[0][1] = 0;
	M[1][0] = 0;
	M[1][1] = 0;

	mul(R, M);
	memcpy(R, get, sizeof R);

	printf("%lld\n", R[0][0] * power(R[1][0], -1) % mod);
}
