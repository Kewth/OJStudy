/*
 * Author: Kewth

 * Date:
  2020.10.17

 * Solution:
  把面积的式子写出来，不难发现面积为 x 的方案数 f(x) 就是满足 ab + cd = x 的正整数四元组
(a, b, c, d) 的数量。进一步可以知道 f 就是约数个数函数 d 的平方卷积。直接 FFT 即可。

 * Digression:

 * CopyRight:
   __  __                  __   __
  |  |/  |.-----.--.--.--.|  |_|  |--.
  |     < |  -__|  |  |  ||   _|     |
  |__|\__||_____|________||____|__|__|

 */

#include <cstdio>
#include <algorithm>
#include <complex>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef std::pair<ll, int> par;
typedef std::complex<double> complex;

static struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	/* inline operator ll () { ll x; return scanf("%lld", &x), x; } */
	/* template<class T> inline void operator () (T &x) { x = *this; } */
	/* template<class T, class ...A> inline void operator () (T &x, A &...a) */
	/* { x = *this; this -> operator () (a...); } */
} read;

const int maxn = 1 << 20;
int R[maxn];
complex W[maxn];

void init (int n) {
	for (int i = 1; i < n; i ++)
		R[i] = R[i >> 1] >> 1 | (i & 1) * (n >> 1);
	complex w(std::cos(2 * M_PI / n), std::sin(2 * M_PI / n));
	W[n / 2] = 1;
	for (int i = n / 2 + 1; i < n; i ++)
		W[i] = W[i - 1] * w;
	for (int i = n / 2 - 1; i; i --)
		W[i] = W[i << 1];
}

void DFT (complex *a, int n) {
	for (int i = 0; i < n; i ++)
		if (i < R[i])
			std::swap(a[i], a[R[i]]);
	for (int m = 1; m < n; m <<= 1)
		for (int i = 0; i < n; i += m << 1)
			for (int k = i; k < i + m; k ++) {
				complex x = a[k], y = a[k + m] * W[m + k - i];
				a[k] = x + y;
				a[k + m] = x - y;
			}
}

void IDFT (complex *a, int n) {
	std::reverse(a + 1, a + n);
	DFT(a, n);
	for (int i = 0; i < n; i ++)
		a[i] /= n;
}

complex f[maxn];
par st[20][maxn];
int hb[maxn];

int main () {
	int n = 500000, len = 1 << 20;
	init(len);
	for (int i = 1; i <= n; i ++)
		for (int j = i; j <= n; j += i)
			f[j] += 1;
	DFT(f, len);
	for (int i = 0; i < len; i ++)
		f[i] *= f[i];
	IDFT(f, len);

	for (int i = 2; i <= n; i ++)
		hb[i] = hb[i >> 1] + 1;
	for (int i = 1; i <= n; i ++)
		st[0][i] = par(f[i].real() + 0.5, -i);
	/* for (int i = 1; i <= n; i ++) */
	/* 	debug("%lld\n", st[0][i].first); */
	for (int k = 1; k < 20; k ++)
		for (int i = 1; i + (1 << k) - 1 <= n; i ++)
			st[k][i] = std::max(st[k - 1][i], st[k - 1][i + (1 << k >> 1)]);

	int q = read;
	while (q --) {
		int l = read, r = read;
		int k = hb[r - l + 1];
		par p = std::max(st[k][l], st[k][r - (1 << k) + 1]);
		printf("%d %lld\n", - p.second, p.first);
	}
}
