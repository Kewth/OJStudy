#if 0
2019.09.08

首先括号只有放在减号右边才有影响，这里规定只能有这样的括号。
朴素 DP 设 f[i][j] 表示前 i 个数构成式子中有 j 个左括号未匹配的答案。
转移枚举 f[i - 1][k] ，考虑在第 i 数后面放几个右括号，如果是减号还能加一个左括号。
这样做是 O(n^2) 的，但事实上 f 的第二维只有 0/1/2 可能最终贡献到答案，于是 O(n) 。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;

inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 200005, maxm = 5;
int a[maxn], b[maxn];
lolong f[maxn][maxm];

int main() {
	int n = input();

	a[1] = '+';
	b[1] = input();
	for(int i = 2; i <= n; i ++) {
		a[i] = getchar();
		while(a[i] != '-' and a[i] != '+')
			a[i] = getchar();
		b[i] = input();
		if(a[i] == '-')
			b[i] *= -1;
	}
	a[n + 1] = '-';
	b[n + 1] = 0;

	int m = 2;
	for(int j = 1; j <= m; j ++)
		f[0][j] = - 1000000000000000000;

	for(int i = 1; i <= n; i ++) {
		for(int j = 0; j <= m; j ++) {
			f[i][j] = - 1000000000000000000;
			for(int k = j; k <= m; k ++)
				f[i][j] = std::max(f[i][j],
						f[i - 1][k] + (k & 1 ? - b[i] : b[i]));
			if(a[i] == '-' and j)
				f[i][j] = std::max(f[i][j],
						f[i - 1][j - 1] + (j & 1 ? b[i] : - b[i]));
			/* if(f[i][j] >= - 100) */
				/* debug(" %lld", f[i][j]); */
			/* else */
				/* debug(" @"); */
		}
		/* debug("\n"); */
	}

	printf("%lld\n", f[n][0]);
}
