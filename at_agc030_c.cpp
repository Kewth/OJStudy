#if 0
2020.01.30

每行放一个颜色即可构造 n = k 的方案。
如果 k 为 4 的倍数，每行相间放两个颜色即可构造 n = k / 2 的方案。
但是如果 k 不是 4 的倍数的时候这个构造方法就不使用了，
任何一行如果只放一个颜色，由于其相邻的行是相间的，不符合要求。

从斜行方向考虑，每斜行放一个颜色同样可以构造 n = k 的方案。
同样如果 k 为 4 的倍数，每斜行相间放两个颜色即可构造 n = k / 2 的方案。
而这个构造方式很优秀，把一斜行换成只填一种颜色仍然合法，
因为两斜行的相交部分本来就是相邻两个块。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
} read;

const int maxn = 500;
int a[maxn][maxn];

int main() {
	int k = read;
	int n = (k + 3) >> 2 << 1;

	if(k == 1) {
		puts("1");
		puts("1");
		return 0;
	}

	int c = 0;
	for(int i = 0; i < n; i ++) {
		++ c;
		for(int j = 0; j < n; j += 2)
			a[(i + j) % n][j] = c;
	}

	for(int i = 0; i < n; i ++) {
		int x = ++ c;
		if(x > k)
			x = a[i][0];
		for(int j = 1; j < n; j += 2)
			a[(i + j) % n][j] = x;
	}

	printf("%d\n", n);
	for(int i = 0; i < n; i ++) {
		for(int j = 0; j < n; j ++)
			printf("%d ", a[i][j]);
		puts("");
	}
}
