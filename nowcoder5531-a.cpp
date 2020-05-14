#if 0
2020.05.08
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
} read;

const int maxn = 105;
int a[maxn];

int main () {
	int n = read;
	for (int i = 1; i <= n; i ++) read(a[i]);
	std::sort(a + 1, a + n + 1);
	for (int i = 1; i <= n; i ++)
		for (int j = i + 1; j <= n; j ++)
			for (int k = j + 1; k <= n; k ++)
				if (a[i] + a[j] > a[k]) {
					printf("%d %d %d\n", a[i], a[j], a[k]);
					return 0;
				}
	puts("No solution");
}
