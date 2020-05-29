#if 0
2020.05.27

  简单背包，设 f[i][j] 表示大小为 i ，和为 j 的子集数量。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef unsigned long long ull;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
} read;

const int maxn = 105, maxv = 338355;
ull f[maxn][maxv];
ull c[maxn];
int a[maxn];

int main () {
#ifdef PE
	int n = 100, m = 50;
	for (int i = 1; i <= n; i ++) a[i] = i * i;
#else
	int n = read, m = read;
	for (int i = 1; i <= n; i ++) read(a[i]);
#endif

	int sum = 0;
	f[0][0] = 1;
	c[0] = 1;
	for (int i = 1; i <= n; i ++) {
		sum += a[i];
		for (int j = i; j; j --)
			for (int x = a[i]; x <= sum; x ++)
				f[j][x] += f[j - 1][x - a[i]];
	}

	/* ull test = 0; */
	/* for (int x = 0; x <= sum; x ++) */
	/* 	test += f[m][x]; */
	/* debug("%llu\n", test); */

	ll ans = 0;
	for (int x = 0; x <= sum; x ++)
		if (f[m][x] == 1)
			ans += x;
	printf("%lld\n", ans);
}
