#if 0
2019.09.28

求生成树，考虑矩阵树定理，去掉中间最特殊的点对应的行和列求行列式。
注意到这个矩阵十分优美，只有主对角线和其相邻的位置和两个角有值，
直接在主对角线上模拟高斯消元，第 i 行只能消第 i + 1 行，
由此甚至可以直接得出主对角线在高斯消元后的值的递推式，
也就是 M[i][i] = 3 - 1 / M[i - 1][i - 1] ，
特别的是由于两个角有值， M[n][n] 的式子会不太一样，
通过这个递推式就可以得出行列式的递推式。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 105, maxm = 100000;
int f[maxn][maxm], lenf[maxn];

void add(int a, int b) {
	int more = 0;
	for(int i = 1; i <= lenf[b] or more; i ++) {
		f[a][i] += f[b][i] + more;
		more = f[a][i] / 10;
		f[a][i] -= more * 10;
		lenf[a] = std::max(lenf[a], i);
	}
}

void dec(int a, int b) {
	for(int i = 1; i <= lenf[b]; i ++) {
		f[a][i] -= f[b][i];
		int less = (9 - f[a][i]) / 10;
		f[a][i] += less * 10;
		f[a][i + 1] -= less;
	}
	while(!f[a][lenf[a]])
		lenf[a] --;
}

int main() {
	int N = input();
	f[1][lenf[1] = 1] = 1;
	f[2][lenf[2] = 1] = 5;

	for(int n = 3; n <= N; n ++) {
		f[n][lenf[n] = 1] = 2;
		add(n, n - 1);
		add(n, n - 1);
		add(n, n - 1);
		dec(n, n - 2);
	}

	for(int i = lenf[N]; i; i --)
		printf("%d", f[N][i]);
	puts("");
}
