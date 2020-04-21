#if 0
2020.04.19

  设答案为 F(n, m) ，欲根据组合数的递推得到 F 的递推式。
  但是可以发现还必须加上一维， F(n, m, k) 表示答案的组合数中把 mi 改成 mi - k 。于是就可以
得到 F(n, m, k) 的递推式，而可以发现 F(n, m, am + b) = F(n + a, m, b) ，事实上第三维是 O(m)
的。
  设 F(n, m, k) = f[n * m + k] ，可以知道 f[i] = f[i - m] + f[i - m + 1], f[0] = 1 。
  这是个常系数齐次线性递推。
#endif
#include <cstdio>
#include <algorithm>
#include <complex>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	/* template<class T, class ...A> inline void operator () (T &x, A &...a) */
	/* { x = *this; this -> operator () (a...); } */
} read;

const int maxn = 5050, maxl = 1 << 17;
typedef std::complex<double> complex;
int R[maxl];
complex Wn[maxl];

void init (int n) {
    for (int i = 1; i < n; i ++)
		R[i] = R[i >> 1] >> 1 | ((i & 1) * (n >> 1));
    for (int i = 0; i < n; i ++)
		Wn[i] = complex(cos(M_PI / n * i), sin(M_PI / n * i));
}

void DFT (complex *A, int n) {
	for (int i = 0; i < n; i ++)
		if (i < R[i])
			std::swap(A[i], A[R[i]]);
	for (int m = 1; m < n; m <<= 1)
		for (int i = 0; i < n; i += m << 1)
			for (int k = i; k < i + m; k ++) {
				complex a0 = A[k], a1 = A[k + m] * Wn[n / m * (k - i)];
				A[k] = a0 + a1;
				A[k + m] = a0 - a1;
			}
}

void IDFT (complex *A, int n) {
	std::reverse(A + 1, A + n);
	DFT(A, n);
	for(int i = 0; i < n; i ++)
		A[i] /= n;
}

void MTT (int *a, int *b, int n, int mod) {
	int B = int(sqrt(mod));
	static complex P1[maxl], P2[maxl], Q1[maxl], Q2[maxl];
	for (int i = 0; i < n; i ++) {
		P1[i] = a[i] / B, P2[i] = a[i] % B;
		Q1[i] = b[i] / B, Q2[i] = b[i] % B;
	}
	int len = 1;
	while (len < n * 2 - 1) len <<= 1;
	init(len);
	std::fill(P1 + n, P1 + len, 0);
	std::fill(P2 + n, P2 + len, 0);
	std::fill(Q1 + n, Q1 + len, 0);
	std::fill(Q2 + n, Q2 + len, 0);
	DFT(P1, len), DFT(P2, len);
	DFT(Q1, len), DFT(Q2, len);
	for (int i = 0; i < len; i ++) {
		complex p1 = P1[i], p2 = P2[i], q1 = Q1[i], q2 = Q2[i];
		P1[i] = p1 * q1, P2[i] = p1 * q2;
		Q1[i] = p2 * q1, Q2[i] = p2 * q2;
	}
	IDFT(P1, len), IDFT(P2, len);
	IDFT(Q1, len), IDFT(Q2, len);
	auto num = [&] (complex x) -> ll {
		double d = x.real();
		return d < 0 ? mod + ll(d - 0.5) % mod : ll(d + 0.5) % mod;
	};
	/* for (int i = 0; i < n; i ++) debug(" %d", a[i]); debug("\n"); */
	/* for (int i = 0; i < n; i ++) debug(" %d", b[i]); debug("\n"); */
	for (int i = 0; i < len; i ++)
		a[i] = (num(P1[i]) * B * B + (num(P2[i]) + num(Q1[i])) * B + num(Q2[i])) % mod;
	/* for (int i = 0; i < len; i ++) debug(" %d", a[i]); debug("\n"); */
}

int mod, len;
int c[maxn], g[maxn], tmp[maxl];

inline void __a (int &x) { if (x >= mod) x -= mod; }

void pmul (int *a, int *b) {
	std::copy(a, a + len, tmp);
	std::fill(tmp + len, tmp + len * 2, 0);
	MTT(tmp, b, len, mod);
	// pmod
	for (int i = 0; i < len; i ++)
		a[i] = tmp[i];
	for (int i = 0; i < len - 1; i ++) {
		__a(a[i] += tmp[len + i]);
		__a(a[i + 1] += tmp[len + i]);
	}
}

void ppow (int *a, int *b, __int128 k) {
	while (k) {
		if (k & 1) pmul(a, b);
		pmul(b, b);
		k >>= 1;
	}
}

int main () {
	ll n = read;
	int m = read;
	read(mod);

	c[0] = 1;
	g[1] = 1;

	len = m;
	ppow(c, g, __int128(n) * m);
	printf("%d\n", (c[0] + c[m - 1]) % mod);
}
