#if 0
2019.10.18

共轭优化了一波，把 3 次 FFT 搞成两次，实测效果并不明显，大概能减少 10% 的耗时？
#endif
#include <cstdio>
#include <complex>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;
typedef std::complex<double> complex;

inline int input() { int x; scanf("%d", &x); return x; }
inline lolong linput() { lolong x; scanf("%lld", &x); return x; }

const int maxn = 400005;
const complex I(0, 1);
int R[maxn];

void FFT(complex *A, int n, int t) {
	for(int i = 0; i < n; i ++)
		if(i < R[i])
			std::swap(A[i], A[R[i]]);

	for(int m = 1; m < n; m <<= 1) {
		complex Wn(cos(M_PI / m), sin(M_PI / m) * t);
		for(int i = 0; i < n; i += m << 1) {
			complex W = 1;
			for(int k = i; k < i + m; k ++) {
				complex a0 = A[k], a1 = A[k + m] * W;
				A[k] = a0 + a1;
				A[k + m] = a0 - a1;
				W *= Wn;
			}
		}
	}

	if(t == -1)
		for(int i = 0; i < n; i ++)
			A[i] /= n;
}

complex a[maxn], b[maxn];
complex p[maxn], q[maxn];

int main() {
	int n = input(), m = input();

	for(int i = 0; i <= n; i ++)
		a[i] = input();
	for(int i = 0; i <= m; i ++)
		b[i] = input();

	int len = 1;
	while(len < n + m + 1)
		len <<= 1;

	for(int i = 0; i < len; i ++)
		p[i] = a[i] + I * b[i];

	for(int i = 1; i < len; i ++)
		R[i] = R[i >> 1] >> 1 | ((i & 1) * (len >> 1));

	FFT(p, len, 1);
	for(int i = 0; i < len; i ++)
		q[i] = std::conj(p[i ? len - i : 0]);
	for(int i = 0; i < len; i ++)
		a[i] = (p[i] + q[i]) * 0.5;
	for(int i = 0; i < len; i ++)
		b[i] = (q[i] - p[i]) * 0.5 * I;
	for(int i = 0; i < len; i ++)
		a[i] *= b[i];
	FFT(a, len, -1);

	for(int i = 0; i <= n + m; i ++)
		printf("%.0lf ", a[i].real() + 0.1);
	puts("");
}
