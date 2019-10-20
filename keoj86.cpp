#if 0
2019.10.18

共轭优化了一波，把 3 次 FFT 搞成两次，实测效果并不明显，大概能减少 10% 的耗时？
然而好像 NTT 更快。
妈蛋重测了 10+ 遍才过。
#endif
#include <cstdio>
#include <algorithm>
#include <cmath>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;

namespace io {
	const int SIZE = (1 << 21) + 1;
	char ibuf[SIZE], *iS, *iT, obuf[SIZE], *oS = obuf, *oT = oS + SIZE - 1, c, qu[55]; int f, qr, flg;
	#define gc() (iS == iT ? (iT = (iS = ibuf) + fread (ibuf, 1, SIZE, stdin), (iS == iT ? EOF : *iS ++)) : *iS ++)
	inline void flush () {
		fwrite (obuf, 1, size_t(oS - obuf), stdout);
		oS = obuf;
	}
	inline void pc (char x) {
		*oS ++ = x;
		if (oS == oT) flush ();
	}
	template <class I>
	inline int gi (I &x) {
		for (f = 1, c = gc(); c != EOF && (c < '0' || c > '9'); c = gc()) if (c == '-') f = -1;
		for (flg = x = 0; c != EOF && c <= '9' && c >= '0'; c = gc()) flg = 1, x = x * 10 + (c & 15); x *= f;
		return flg || c != EOF;
	}
	template <class I>
	inline void print (I x) {
		if (!x) pc ('0'); if (x < 0) pc ('-'), x = -x;
		while (x) qu[++ qr] = x % 10 + '0',  x /= 10;
		while (qr) pc (qu[qr --]);
	}
	struct Flusher_ {~Flusher_(){flush();}}io_flusher_;
}
using io :: gi;
using io :: print;
using io :: pc;
inline int input() { int x; gi(x); return x;}

/* typedef std::complex<double> complex; */
struct complex { // 兼容 std::complex<double>
	double _real, _imag;
	inline double real() { return _real; }
	complex(double _r = 0, double _i = 0): _real(_r), _imag(_i) { }
};
inline complex operator * (complex a, complex b) {
	return complex(a._real * b._real - a._imag * b._imag,
			a._real * b._imag + a._imag * b._real);
}
inline complex operator + (complex a, complex b) {
	return complex(a._real + b._real, a._imag + b._imag);
}
inline complex operator - (complex a, complex b) {
	return complex(a._real - b._real, a._imag - b._imag);
}
inline complex operator / (complex a, int b) {
	return complex(a._real / b, a._imag / b);
}
namespace std { complex conj(complex); };
inline complex std::conj(complex a) {
	return complex(a._real, - a._imag);
}

const int maxn = 9000005;
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
				W = W * Wn;
			}
		}
	}

	if(t == -1)
		for(int i = 0; i < n; i ++)
			A[i] = A[i] / n;
}

complex a[maxn], b[maxn];

inline unsigned num(complex x) {
	double d = x.real();
	return d < 0 ? unsigned(d - 0.5) : unsigned(d + 0.5);
}

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
		a[i] = a[i] + I * b[i];

	for(int i = 1; i < len; i ++)
		R[i] = R[i >> 1] >> 1 | ((i & 1) * (len >> 1));

	FFT(a, len, 1);
	for(int i = 0; i < len; i ++)
		b[i] = std::conj(a[i ? len - i : 0]);
	for(int i = 0; i < len; i ++) {
		complex p = a[i], q = b[i];
		a[i] = (p + q) * 0.5;
		b[i] = (q - p) * 0.5 * I;
	}
	for(int i = 0; i < len; i ++)
		a[i] = a[i] * b[i];
	FFT(a, len, -1);

	unsigned ans = 0;
	for(int i = 1; i <= n + m; i ++)
		ans += num(a[i]) * unsigned(i) * 377;
	print(ans);
	pc('\n');
}
