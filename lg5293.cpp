#if 0
2020.04.06

不妨设 n = 1 且 k = 1 ，那么枚举舞步长度 l ，贡献系数就是 F * A^l * C(L, l) 。
通过二项式定理可以知道答案就是 F * (A + 1)^L ，其中 F = 1, A 是跳一步的方案数。

对于 n > 1 ，把 F, A 换成矩阵，在矩阵乘法的意义下使用二项式定理即可。
对于 k > 1 ，通过单位根反演可以知道答案可以表示为如下形式：
ans[t] = sum(S[i] X(t)^i)

事实上 ans[t] 就是多项式 sum(S[i] x^i) 在 X(t) 处的点值，并且 X(t) 实际上是 k 次单位根的幂。
如果 k 是二的整次幂，将多项式 DFT 一遍即可得到这些点值。
但是 k 是任意值，就需要用到 Bluestein 算法转换为多项式乘法问题，其中实现需要用到 MTT 。

ps: Bluestein 浅显地讲就是通过恒等式 ij = C(i + j, 2) - C(i, 2) - C(j, 2) ，
把指数代换掉，进而配出卷积形式。
#endif
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <complex>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
} read;

int mod;

struct Matrix {
	int x[3][3];
	inline Matrix () { memset(x, 0, sizeof x); }
};
Matrix operator * (Matrix a, Matrix b) {
	Matrix c;
	for (int i = 0; i < 3; i ++)
		for (int j = 0; j < 3; j ++)
			for (int k = 0; k < 3; k ++)
				c.x[i][j] = (c.x[i][j] + 1ll * a.x[i][k] * b.x[k][j]) % mod;
	return c;
}

inline ll power (ll x, int k) {
	if (k < 0) k += mod - 1;
	ll res = 1;
	while (k) {
		if (k & 1) (res *= x) %= mod;
		(x *= x) %= mod;
		k >>= 1;
	}
	return res;
}

int getG () {
	int fac[30];
	int p = 0;
	int x = mod - 1;
	for (int i = 2; i * i <= x; i ++)
		while (!(x % i)) {
			fac[p ++] = i;
			x /= i;
		}
	if (x > 1)
		fac[p ++] = x;
	int g = 2;
	while (1) {
		for (int i = 0; i < p; i ++)
			if (power(g, (mod - 1) / fac[i]) == 1)
				goto FAIL;
		return g;
FAIL:
		g ++;
	}
}

const int maxk = 65536; // 1 << 16
typedef std::complex<double> complex;
int R[maxk << 2];
complex P1[maxk << 2], P2[maxk << 2], Q1[maxk << 2], Q2[maxk << 2];
complex Wn[maxk << 2];

void init(int n) {
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

ll S[maxk], W[maxk + 1];

inline ll C2 (ll n) { return n * (n - 1) >> 1 % mod; }

inline ll num(complex x) {
	double d = x.real();
	return d < 0 ? mod + ll(d - 0.5) % mod : ll(d + 0.5) % mod;
}

int main () {
	int ml = read, K = read, L = read, X = read, Y = read;
	read(mod);

	Matrix A, F;
	for (int i = 0; i < ml; i ++)
		for (int j = 0; j < ml; j ++)
			read(A.x[i][j]);
	F.x[0][X - 1] = 1;

	W[0] = 1;
	W[1] = power(getG(), (mod - 1) / K);
	for (int l = 2; l <= K; l ++)
		W[l] = W[l - 1] * W[1] % mod;

	for (int l = 0; l < K; l ++) {
		int k = L;
		Matrix f = F, a;
		for (int i = 0; i < 3; i ++)
			for (int j = 0; j < 3; j ++)
				a.x[i][j] = (W[l] * A.x[i][j] + (i == j)) % mod;
		while (k) {
			if (k & 1) f = f * a;
			a = a * a;
			k >>= 1;
		}
		S[l] = f.x[0][Y - 1];
	}

/* 	for (int t = 0; t < K; t ++) { */
/* 		ll ans = 0; */
/* 		for (int l = 0; l < K; l ++) */
/* 			(ans += W[K - t * l % K] * S[l]) %= mod; */
/* 		(ans *= mod - (mod - 1) / K) %= mod; */
/* 		printf("%lld\n", ans); */
/* 	} */

	int B = int(sqrt(mod));
	/* B = 1; */

	for (int l = 0; l < K * 2; l ++) {
		ll x = W[K - C2(l) % K], y = l < K ? S[l] * W[C2(l) % K] % mod : 0;
		P1[K * 2 - l] = x / B;
		P2[K * 2 - l] = x % B;
		Q1[l] = y / B;
		Q2[l] = y % B;
	}

	int len = 1;
	while (len < K * 3) len <<= 1;
	init(len);

	/* for (int l = 0; l < len; l ++) */
	/* 	debug(" %lld", num(P1[l])); */
	/* debug("\n"); */
	/* for (int l = 0; l < len; l ++) */
	/* 	debug(" %lld", num(Q1[l])); */
	/* debug("\n"); */

	DFT(P1, len);
	DFT(P2, len);
	DFT(Q1, len);
	DFT(Q2, len);

	for (int i = 0; i < len; i ++) {
		complex p1 = P1[i], p2 = P2[i], q1 = Q1[i], q2 = Q2[i];
		P1[i] = p1 * q1;
		P2[i] = p1 * q2;
		Q1[i] = p2 * q1;
		Q2[i] = p2 * q2;
	}

	IDFT(P1, len);
	IDFT(P2, len);
	IDFT(Q1, len);
	IDFT(Q2, len);

	for (int i = K * 2; i > K; i --) {
		ll p1 = num(P1[i]), p2 = num(P2[i]), q1 = num(Q1[i]), q2 = num(Q2[i]);
		printf("%lld\n", (p1 * B * B + p2 * B + q1 * B + q2) % mod *
				W[C2(K * 2 - i) % K] % mod * (mod - (mod - 1) / K) % mod);
	}
}
