#if 0
2020.04.19

常系数齐次线性递推模板，暴力做多项式运算即可。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 2050, mod = 1000000007;
int len;
int c[maxn], g[maxn], tmp[maxn << 1];
int coe[maxn];

void pmul (int *a, int *b) {
	std::fill(tmp, tmp + len * 2, 0);
	for (int i = 0; i < len; i ++)
		for (int j = 0; j < len; j ++)
			tmp[i + j] = (tmp[i + j] + 1ll * a[i] * b[j]) % mod;
	// pmod
	for (int i = len * 2 - 2; i >= len; i --)
		for (int j = 1; j <= len; j ++)
			tmp[i - j] = (tmp[i - j] + 1ll * tmp[i] * coe[j]) % mod;
	std::copy(tmp, tmp + len, a);
	for (int i = 0; i < len; i ++)
		if (a[i] < 0)
			exit(1);
}

void ppow (int *a, int *b, int k) {
	while (k) {
		if (k & 1) pmul(a, b);
		pmul(b, b);
		k >>= 1;
	}
}

int main () {
	int n = read, m = read;
	for (int i = 1; i <= m; i ++)
		coe[i] = (read + mod) % mod;

	c[0] = 1;
	g[1] = 1;

	len = m;
	ppow(c, g, n);

	int ans = 0;
	for (int i = 0; i < m; i ++)
		ans = (ans + 1ll * (read + mod) * c[i]) % mod;
	printf("%d\n", ans);
}
