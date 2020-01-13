#if 0
2019.10.18

MTT 精度 wei 得一批好吧。
给 1e9 级别的数做 fft 。
必须每次用三角函数算单位根，一点乘法递推都不能有，乘起来递推就损精度。

蒯自己的题解。

拆系数就不说了，把两个多项式 $A(x), B(x)$ 分别拆成 $A_0(x), A_1(x)$ 和$B_0(x), B_1(x)$ 后，考虑求出它们的点值表示，也就是做 DFT 。
朴素地做 DFT 需要 4 次，但是由于这些多项式虚部都为 0 ，可以考虑将两次 DFT 合并成一次。

例如要给两个多项式 $A, B$ 做 DFT ，考虑构造两个多项式：

$$P(x) = A(x) + i B(x)$$
$$Q(x) = A(x) - i B(x)$$

那么由于 $A, B$ 的虚部都为 0 ，$P, Q$ 的每一项系数都互为共轭，同样每一个点值也互为共轭。
那么只需对 $P$ 做一次 DFT ，就可以通过共轭 $O(n)$ 求出 $Q$ 的点值表示。
然后通过 $P, Q$ 的点值表示求 $A, B$ 的点值表示就是解上面的二元二次方程组，也是可以 $O(n)$ 做到的。

于是就可以用两次 DFT 求出 $A_0, A_1, B_0, B_1$ 的点值表示。

接下来需要求 $A, B$ 之间的两两乘积。直接乘出来后要对 $A_0 B_0, A_0 B_1, A_1 B_0, A_1 B_1$ 四个多项式做 IDFT 。
并且这时候它们的虚部并不为 0 ，不能用上述的方法。

但是上述方法的思想仍可借鉴，考虑构造两个多项式：

$$P(x) = A_0(x) B_0(x) + i A_1(x) B_0(x)$$
$$Q(X) = A_0(x) B_1(x) + i A_1(x) B_1(x)$$

通过已知的点值求出此时 $P, Q$ 的点值，然后分别对 $P, Q$ 做 IDFT ，
由于 $A_0 B_0, A_0 B_1, A_1 B_0, A_1 B_1$ 这四个多项式卷起来后的系数表示中虚部一定为 0 ，
那么此时 $P$ 的实部和虚部就分别为 $A_0(x) B_0(x)$ 和 $A_1(x) B_0(x)$ ，
同样 $Q$ 的实部和虚部就分别为 $A_0(x) B_1(x)$ 和 $A_1(x) B_1(x)$ 。
#endif
#include <cstdio>
#include <complex>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;
typedef std::complex<double> complex;

inline int input() { int x; scanf("%d", &x); return x; }
inline lolong linput() { lolong x; scanf("%lld", &x); return x; }

const int maxn = 400005, maxk = 20;
const complex I(0, 1);
int R[maxn];
complex Wn[maxn];

void FFT(complex *A, int n, int t) {
	if(t == -1)
		for(int i = 1; i < n; i ++)
			if(i < (n - i))
				std::swap(A[i], A[n - i]);
	for(int i = 0; i < n; i ++)
		if(i < R[i])
			std::swap(A[i], A[R[i]]);

	for(int m = 1, l = 0; m < n; m <<= 1, l ++) {
		/* complex Wn(cos(M_PI / m), sin(M_PI / m) * t); */
		for(int i = 0; i < n; i += m << 1) {
			/* complex W = 1; */
			for(int k = i; k < i + m; k ++) {
				/* complex W(cos(M_PI / m * (k - i)), sin(M_PI / m * (k - i)) * t); */
				complex W = Wn[1ll * (k - i) * n / m];
				/* if(t == -1) W = std::conj(W); */
				complex a0 = A[k], a1 = A[k + m] * W;
				A[k] = a0 + a1;
				A[k + m] = a0 - a1;
				/* W *= Wn; */
			}
		}
	}

	if(t == -1)
		for(int i = 0; i < n; i ++)
			A[i] /= n;
}

int mod;
inline lolong num(complex x) {
	double d = x.real();
	return d < 0 ? lolong(d - 0.5) % mod : lolong(d + 0.5) % mod;
}

inline void FFTFFT(complex *a, complex *b, int len, int t) {
	for(int i = 0; i < len; i ++)
		a[i] = a[i] + I * b[i];
	FFT(a, len, t);
	for(int i = 0; i < len; i ++)
		b[i] = std::conj(a[i ? len - i : 0]);
	for(int i = 0; i < len; i ++) {
		complex p = a[i], q = b[i];
		a[i] = (p + q) * 0.5;
		b[i] = (q - p) * 0.5 * I;
	}
}

complex a0[maxn], a1[maxn], b0[maxn], b1[maxn];
/* complex a0b0[maxn], a1b0[maxn], a0b1[maxn], a1b1[maxn]; */
complex p[maxn], q[maxn];

int main() {
	int n = input(), m = input();
	mod = input();
	int M = int(sqrt(mod) + 1);

	for(int i = 0; i <= n; i ++) {
		int x = input() % mod;
		a0[i] = x / M;
		a1[i] = x % M;
	}
	for(int i = 0; i <= m; i ++) {
		int x = input() % mod;
		b0[i] = x / M;
		b1[i] = x % M;
	}

	int len = 1;
	while(len < n + m + 1)
		len <<= 1;

	for(int i = 1; i < len; i ++)
		R[i] = R[i >> 1] >> 1 | ((i & 1) * (len >> 1));

	for(int i = 0; i < len; i ++)
		Wn[i] = complex(cos(M_PI / len * i), sin(M_PI / len * i));

	FFTFFT(a0, a1, len, 1);
	FFTFFT(b0, b1, len, 1);

	for(int i = 0; i < len; i ++) {
		p[i] = a0[i] * b0[i] + I * a1[i] * b0[i];
		q[i] = a0[i] * b1[i] + I * a1[i] * b1[i];
	}

	FFT(p, len, -1);
	FFT(q, len, -1);

	for(int i = 0; i <= n + m; i ++)
		printf("%lld ", (M * M * num(p[i].real()) % mod +
				M * (num(p[i].imag()) + num(q[i].real())) % mod +
				num(q[i].imag())) % mod);
	puts("");
}
