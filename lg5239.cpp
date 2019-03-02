#if 0
2019.03.02

洛谷月赛 T2
二维前缀和处理一下区间就好了
#endif
#include <bits/stdc++.h>

int input() { int res; scanf("%d", &res); return res; }

typedef long long lolong;
const int maxn = 1010, mod = 19260817;
lolong C[maxn][maxn];

int main() {
	int q = input();
	for(int i=0; i<maxn; i++)
		C[i][0] = 1;
	for(int i=1; i<maxn; i++)
		for(int j=1; j<maxn; j++)
			C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % mod;
	/* for(int i=1; i<=5; i++, puts("")) */
	/* 	for(int j=1; j<=5; j++) */
	/* 		printf("%lld ", C[i][j]); */
	for(int i=0; i<maxn; i++)
		C[i][0] = 0;
	for(int i=1; i<maxn; i++)
		for(int j=1; j<maxn; j++)
			(C[i][j] += C[i][j - 1]) %= mod;
	/* for(int i=1; i<=5; i++, puts("")) */
	/* 	for(int j=1; j<=5; j++) */
	/* 		printf("%lld ", C[i][j]); */
	for(int i=1; i<maxn; i++)
		for(int j=1; j<maxn; j++)
			(C[i][j] += C[i - 1][j]) %= mod;
	/* for(int i=1; i<=5; i++, puts("")) */
	/* 	for(int j=1; j<=5; j++) */
	/* 		printf("%lld ", C[i][j]); */
	while(q --) {
		int m = input(), n = input();
		printf("%lld\n", C[n][m]);
	}
}
