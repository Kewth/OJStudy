#if 0
2019.07.24

线性消元裸题。
从左到右把 a[i] 表示为 b[i] * a[i + 1] + c[i] 的形式，
再从右到左根据上式求出所有 a[i] 。
#endif
#include <cstdio>
#define debug(...) fprintf(stderr, __VA_ARGS__)

inline int input() {
	int c = getchar(), x = 0;
	while(c < '0' or c > '9') c = getchar();
	while(c >= '0' and c <= '9') x = x * 10 + c - '0', c = getchar();
	return x;
}

const int maxn = 3030;
double b[maxn], c[maxn], d[maxn];

int main() {
	int n = input();
	scanf("%lf%lf", c, c + n + 1);
	for(int i = 1; i <= n; i ++)
		scanf("%lf", d + i);
	for(int i = 1; i <= n; i ++) {
		b[i] = 0.5;
		c[i] = c[i - 1] / 2 - d[i];
		double x = 1 - b[i - 1] / 2;
		b[i] /= x;
		c[i] /= x;
		/* debug("%lf %lf(%lf)\n", b[i], c[i], x); */
	}
	for(int i = n; i; i --)
		c[i] += b[i] * c[i + 1];
	printf("%.2lf\n", c[1]);
}

