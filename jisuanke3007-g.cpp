#if 0
2019.09.14

根据物理知识得出 f[n] 关于 f[n - 1] 的递推式，其中 f[n] 表示 n = n, a =1 的答案。
直接做是不行的，复杂度 O(n) ，
容易想到使用矩阵快速幂，但是 f[n] 的递推式中 f[n - 1] 出现在分母。
设 f[n] = a[n] / b[n] ，递推 a, b 用十进制矩阵快速幂即可。

另外有种更简单的方法：
从式子中可以看出随着 n 增大 f[n] 会趋近于一个值，
那么 n 很大时直接输出一个 f[x] ，只要 x 足够大但可以跑暴力即可。
#endif
#include <cstdio>
#include <cstring>
#define debug(...) fprintf(stderr, __VA_ARGS__)

const int maxn = 1000005;
char s[maxn];

double M[2][2];
double R[2][2];

double get[2][2];
void mul(double a[2][2], double b[2][2]) {
	for(int i = 0; i < 2; i ++)
		for(int j = 0; j < 2; j ++)
			get[i][j] = a[i][0] * b[0][j] + a[i][1] * b[1][j];
}

int main() {
	int T;
	scanf("%d", &T);

	while(T --) {
		scanf("%s", s + 1);
		int n = int(strlen(s + 1));
		double a;
		scanf("%lf", &a);

		int shi = n;
		while(s[shi] == '0') {
			s[shi] = '9';
			shi --;
		}
		s[shi] --;

		M[0][0] = 21;
		M[0][1] = -9;
		M[1][0] = 1;
		M[1][1] = 0;

		R[0][0] = R[1][1] = 1;
		R[1][0] = R[0][1] = 0;

		for(int i = n; i; i --) {
			int x = s[i] - '0';
			while(x --) {
				mul(R, M);
				memcpy(R, get, sizeof R);
			}
			mul(M, M);
			memcpy(M, get, sizeof M);
		}

		debug("%lf %lf %lf %lf\n", R[0][0], R[0][1], R[1][0], R[1][1]);

		M[0][0] = 1;
		M[0][1] = 0;
		M[1][0] = 0;
		M[1][1] = 0;

		mul(R, M);
		memcpy(R, get, sizeof R);

		double x = R[1][0] / R[0][0];
		printf("%.7lf\n", a * (5.0 / 3.0 - x));
	}
}
