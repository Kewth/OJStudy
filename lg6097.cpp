#if 0
2020.04.26

板子。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
} read;

const int maxn = 20, mod = 1000000009;
ll tmp[1 << maxn];

inline int count (int x) { return __builtin_popcount(unsigned(x)); }

void FWT (int *a, int n) {
	std::copy(a, a + n, tmp);
	for (int m = 1; m < n; m <<= 1)
		for (int i = 0; i < n; i += m << 1)
			for (int k = i; k < i + m; k ++)
				tmp[k + m] += tmp[k];
	for (int i = 0; i < n; i ++) a[i] = tmp[i] % mod;
}

void iFWT (int *a, int n) {
	std::copy(a, a + n, tmp);
	for (int m = 1; m < n; m <<= 1)
		for (int i = 0; i < n; i += m << 1)
			for (int k = i; k < i + m; k ++)
				tmp[k + m] -= tmp[k];
	for (int i = 0; i < n; i ++) a[i] = int((tmp[i] %= mod) < 0 ? tmp[i] + mod : tmp[i]);
}

void subset_convolution (int *a, int *b, int *c, int n) {
	static int A[maxn + 1][1 << maxn], B[maxn + 1][1 << maxn], C[maxn + 1][1 << maxn];
	int l = 1 << n;
	for (int i = 0; i < l; i ++) A[count(i)][i] = a[i];
	for (int i = 0; i < l; i ++) B[count(i)][i] = b[i];
	for (int x = 0; x <= n; x ++) FWT(A[x], l), FWT(B[x], l);
	for (int x = 0; x <= n; x ++)
		for (int y = 0; y <= x; y ++)
			for (int i = 0; i < l; i ++)
				C[x][i] = (C[x][i] + 1ll * A[y][i] * B[x - y][i]) % mod;
	for (int x = 0; x <= n; x ++) iFWT(C[x], l);
	for (int i = 0; i < l; i ++) c[i] = int(C[count(i)][i]);
}

int a[1 << maxn], b[1 << maxn], c[1 << maxn];
int main () {
	int n = read;
	for (int i = 0; i < (1 << n); i ++) read(a[i]);
	for (int i = 0; i < (1 << n); i ++) read(b[i]);
	subset_convolution(a, b, c, n);
	for (int i = 0; i < (1 << n); i ++) printf("%d ", c[i]);
	puts("");
}
