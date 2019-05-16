#if 0
2019.05.16

构造矩阵 M ，满足所有数是上方的两倍，左边的三倍（如果有），数字不超过 n 。
那么 M 中选取一些不相交的数即可满足条件，状压 DP 即可。
只有一个 M 无法考虑到 1 ~ n 的所有数，所以要枚举 M 的左上角构造若干矩阵，
保证每个 M 之间没有相同的数就互不干扰，所有 M 的结果乘起来就是答案。
#endif
#include <bits/stdc++.h>

const int mod = 1000000001;

int input() {
	int c = getchar();
	while (c < '0' || c > '9')
		c = getchar();
	int res = c - '0';
	while ((c = getchar()) >= '0' && c <= '9')
		res = res * 10 + c - '0';
	return res;
}

int work(int x, int n) {
	static int f[20][100005], limit[20];
	int imax = 0;
	for (int i = 1, l = x; l <= n; l <<= 1, i++, imax++) {
		limit[i] = 1;
		for (int j = l; j <= n; j *= 3)
			limit[i] <<= 1;
		for (int j = 0; j < limit[i]; j++)
			f[i][j] = 0;
	}
	f[imax + 1][0] = 0;
	limit[0] = limit[imax + 1] = f[0][0] = 1;
	for (int i = 0; i <= imax; i++)
		for (int j = 0; j < limit[i]; j++) {
			//			printf("%d %d:%d\n",i,j,f[i][j]);
			if (f[i][j]) {
				//				if(i == 3)
				// printf("%d:\n",limit[i+1]);
				for (int k = 0; k < limit[i + 1]; k++)
					if ((!(k & (k << 1))) && !(j & k)) {
						(f[i + 1][k] += f[i][j]) %= mod;
						//						if(i ==
						// imax) printf("%d\n",k);
					}
			}
		}
	//	printf("%d\n",f[imax+1][0]);
	return f[imax + 1][0];
}

int main() {
	int n = input();
	long long ans = 1;
	for (int i = 1; i <= n; i++)
		if (i % 2 && i % 3)
			(ans *= work(i, n)) %= mod;
	printf("%lld\n", ans);
	return 0;
}
