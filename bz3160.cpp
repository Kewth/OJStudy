#if 0
2019.08.01

分别计算子序列和字段，相减即为答案，字段的回文马拉车即可，考虑子序列回文的计算。
记 A, B 数组表示 A[i] = [s[i] == 'a'], B 同理，不难发现回文子序列的计算类似于 A, B 自己卷积。
由于 A, B 的值只有 0, 1 ，直接 FFT 卷积即可，不会有问题。
#endif
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <complex>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef std::complex<double> complex;
typedef long long lolong;
inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 100005, mod = 1000000007;
char s[maxn << 1];
char t[maxn];
complex a[maxn << 2], b[maxn << 2];
int rev[maxn << 2];
int h[maxn << 1];

lolong power(lolong x, int k) {
	lolong res = 1;
	while(k) {
		if(k & 1) (res *= x) %= mod;
		(x *= x) %= mod;
		k >>= 1;
	}
	return res;
}

void FFT(complex *a, int n, int typ) {
	for(int i = 0; i < n; i ++)
		if(i < rev[i])
			std::swap(a[i], a[rev[i]]);
	for(int m = 2; m <= n; m <<= 1) {
		complex Wn(cos(M_PI * 2 / m), sin(M_PI * 2 / m) * typ);
		for(int i = 0; i < n; i += m) {
			complex W = 1;
			for(int k = i; k < i + (m >> 1); k ++) {
				complex a0 = a[k], a1 = a[k + (m >> 1)];
				a[k] = a0 + a1 * W;
				a[k + (m >> 1)] = a0 - a1 * W;
				W *= Wn;
			}
		}
	}
	if(typ == -1)
		for(int i = 0; i < n; i ++)
			a[i] /= n;
}

void manacher(int n) {
	int mid = 0, r = 0;
	for(int i = 1; i < n; i ++) {
		if(i > r) {
			r = i;
			mid = i;
		}
		h[i] = std::min(h[mid - (i - mid)], r - i);
		while(i - h[i] - 1 >= 0 and i + h[i] + 1 < n and s[i - h[i] - 1] == s[i + h[i] + 1])
			h[i] ++;
		if(i + h[i] > r) {
			r = i + h[i];
			mid = i;
		}
		// debug("%d: %c %d-%d, %d->%d\n", i, s[i], L, R, mid, r);
	}
}

int main() {
	scanf("%s", t);
	int n = strlen(t);
	for(int i = 0; i < n; i ++) {
		s[i << 1] = '.';
		s[i << 1 | 1] = t[i];
		if(t[i] == 'a')
			a[i] = 1;
		else
			b[i] = 1;
	}
	s[n << 1] = '.';
	n = n << 1 | 1;
	int len = 1, loglen = 0;
	while(len < n) {
		len <<= 1;
		loglen ++;
	}
	for(int i = 1; i < len; i ++)
		rev[i] = rev[i >> 1] >> 1 | ((i & 1) << (loglen - 1));
	// for(int i = 0; i < len; i ++)
		// debug("%d ", int(a[i].real() + 0.5));
	// debug("\n");
	// for(int i = 0; i < len; i ++)
		// debug("%d ", int(b[i].real() + 0.5));
	// debug("\n");
	FFT(a, len, 1);
	FFT(b, len, 1);
	for(int i = 0; i < len; i ++) {
		a[i] *= a[i];
		b[i] *= b[i];
	}
	FFT(a, len, -1);
	FFT(b, len, -1);
	a[0] = b[0] = 0;
	for(int i = n - 1; i; i --) {
		a[i] = int(a[i - 1].real() + 0.5) >> 1;
		b[i] = int(b[i - 1].real() + 0.5) >> 1;
	}
	lolong ans = 0;
	manacher(n);
	// for(int i = 0; i < n; i ++)
		// debug("%d ", int(a[i].real() + 0.5));
	// debug("\n");
	// for(int i = 0; i < n; i ++)
		// debug("%d ", int(b[i].real() + 0.5));
	// debug("\n");
	// for(int i = 0; i < n; i ++)
		// debug("%d ", h[i]);
	// debug("\n");
	for(int i = 0; i < n; i ++)
		if(s[i] == '.')
			ans += power(2, int(a[i].real() + b[i].real() + 0.5)) - (h[i] + 1) / 2 - 1;
		else
			ans += power(2, int(a[i].real() + b[i].real() + 0.5) + 1) - (h[i] / 2 + 1) - 1;
	printf("%lld\n", ans % mod);
}
