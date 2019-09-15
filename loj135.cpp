#if 0
2019.09.15

通过单点修区间查实现区间修区间查。
可以通过实现一个等价的问题“修改右下矩阵查询左上矩阵”来实现。
#endif
#include <cstdio>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;
inline int input() { int x = -1; scanf("%d", &x); return x; }

const int maxn = 2050;
lolong bit[4][maxn][maxn];

void add(int x, int y, lolong c) {
	for(int i = x; i < maxn; i += i & -i)
		for(int j = y; j < maxn; j += j & -j) {
			bit[0][i][j] += c;
			bit[1][i][j] += c * (x - 1);
			bit[2][i][j] += c * (y - 1);
			bit[3][i][j] += c * (x - 1) * (y - 1);
		}
}

lolong query(int x, int y) {
	lolong res = 0;
	for(int i = x; i; i -= i & -i)
		for(int j = y; j; j -= j & -j) {
			res += bit[0][i][j] * x * y;
			res -= bit[1][i][j] * y;
			res -= bit[2][i][j] * x;
			res += bit[3][i][j];
		}
	return res;
}

int main() {
	int n = input(), m = input();
	while(true) {
		int typ = input();
		if(typ == -1)
			break;
		if(typ == 1) {
			int a = input(), b = input(), c = input(), d = input(), e = input();
			add(a, b, e);
			add(a, d + 1, - e);
			add(c + 1, b, - e);
			add(c + 1, d + 1, e);
		} else if(typ == 2) {
			int a = input(), b = input(), c = input(), d = input();
			printf("%lld\n",
					query(c, d) - query(a - 1, d) - query(c, b - 1) + query(a - 1, b - 1));
		}
	}
}
