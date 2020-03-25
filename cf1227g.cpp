#if 0
2020.03.24

构造。
总是使用 n + 1 个操作，构造 (n + 1) * n 的矩阵。
将 a 升序，对于 a[i] ，从 (i, i) 开始一直向上填 1 直到填满 a[i] 个。
其中 (x, y) 向上是指到 ((x - 1) % (n + 1), y) 。
可以证明这样一定不会有两行相同。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 1010;
struct shit { int x, id; } a[maxn];
bool b[maxn][maxn];

int main () {
	int n = read;
	for (int i = 0; i < n; i++)
		a[i] = {read, i};
	std::sort(a, a + n, [] (shit x, shit y) { return x.x < y.x; });

	for (int i = 0; i < n; i ++)
		for (int j = 0; j < a[i].x; j ++)
			b[(i - j + n + 1) % (n + 1)][a[i].id] = 1;

	printf("%d\n", n + 1);
	for (int i = 0; i < n + 1; i ++) {
		for (int j = 0; j < n; j ++)
			printf("%d", b[i][j]);
		puts("");
	}
}
