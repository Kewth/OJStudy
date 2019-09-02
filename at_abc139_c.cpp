#if 0
2019.09.01
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 100005;
int a[maxn];
int f[maxn];

int main() {
	int n = input();

	for(int i = 1; i <= n; i ++)
		a[i] = input();

	int ans = 0;
	for(int i = n - 1; i; i --)
		if(a[i] >= a[i + 1])
			f[i] = f[i + 1] + 1;

	for(int i = 1; i <= n; i ++)
		ans = std::max(ans, f[i]);

	printf("%d\n", ans);
}
