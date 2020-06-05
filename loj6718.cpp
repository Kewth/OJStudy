/*
 * Since g++10 is released, some characters is not valid inside #if 0 :(
 * So, why not using clang++? :D

 * Date:
  2020.06.05

 * Solution:
  如果模数很友好，单位根反演一波可以得到答案就是 sum((1 + W^k)^n) ，但是单位根不一定存在。
设多项式 F(x) = (1 + x)^n ，那么答案就是 F(x) 在 W^k 上的取值的和，也就是 (1 + x)^n 循环
卷积意义下的常数项，MTT 多项式快速幂即可。

 * Digression:

 * CopyRight:
          ▁▃▄▄▄▃▃▃▃▄▶
        ▗▇▀▔    ▔▔▔▔
       ▄▛   ▃▅━━■▄▂
      ▟▊   ▐▘     ▀▙
     ▟▜▌   ▐▖   ▋  ▐▍
    ▟▘ ▜   ▝▀▇▆●▘  ▐▌
  ▗▟▘   ▜▃       ▁▅▛
  ▔▀▼▅▄▃▃██▅▄▄▄▅■▀▔
        ▔▔▔▔▔▔
 */

#include <cstdio>
#include <complex>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
} read;


const int maxl = 1 << 16;
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

void MTT (ll *a, ll *b, int n, int mod) {
	int B = int(sqrt(mod));
	static complex P1[maxl], P2[maxl], Q1[maxl], Q2[maxl];
	for (int i = 0; i < n; i ++) {
		P1[i] = int(a[i] / B), P2[i] = a[i] % B;
		Q1[i] = int(b[i] / B), Q2[i] = b[i] % B;
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
	// 循环卷积
	for (int i = 0; i < n; i ++)
		a[i] = 0;
	for (int i = 0; i < len; i ++)
		(a[i % n] += num(P1[i]) * B * B + (num(P2[i]) + num(Q1[i])) * B + num(Q2[i])) %= mod;
}

ll f[maxl], g[maxl];

int main () {
	ll n = read;
	int m = read;
	f[0] = 1;
	g[0] = 1;
	g[1 % m] += 1;

	while (n) {
		if (n & 1)
			MTT(f, g, m, 998244853);
		MTT(g, g, m, 998244853);
		n >>= 1;
	}

	printf("%lld\n", f[0]);
}
