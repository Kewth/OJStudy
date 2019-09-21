#if 0
2019.09.21

直接把左上 b * a 的矩阵以及右下 (n - b) * (m - a) 的矩阵填 1 即可。
#endif
#include <cstdio>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;

inline int input() { int x; scanf("%d", &x); return x; }
inline lolong linput() { lolong x; scanf("%lld", &x); return x; }

const int maxn = 1010;
bool s[maxn][maxn];

int main() {
	int n = input(), m = input(), a = input(), b = input();

	for(int i = 1; i <= n; i ++) {
		for(int j = 1; j <= m; j ++)
			if((i <= b and j <= a) or (i > b and j > a))
				putchar('1');
			else
				putchar('0');
		puts("");
	}
}
