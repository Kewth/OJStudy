#pragma GCC optimize(2)
#if 0
2020.05.07

  CC 的题一向他妈离谱，写吐了。
  注意到需要的答案数目不多，考虑直接求出所有可能的答案。也就是对于确定的每一组图，求出
f[k] 表示恰好在第 k 步停下的方案数。
  直接求 f 比较困难，因为有个“每一步选的子集非空的限制”，考虑求出去掉这个限制的情况下的
方案数 g ，那么根据 g 关于 f 的关系可以从 g 反演得到 f （二项式反演），问题转换为求 g 。
而求 g 的话每张图之间是相互独立的，设 h[i][j] 表示第 i 张图走 j 步回到原点的方案数，那么
g[j] 就是对应所有 f[i][j] 的乘积。
  现在单独考虑每张图求出 h ，设该图邻接矩阵为 A ，可以发现 h[k] = tr((A+I)^k) ，其中 tr
表示矩阵主对角线元素和，通过这个直接求的复杂度是 n^3 k ，无法接受。
  根据哈密尔顿-凯莱定理，设矩阵 B = A + I ，p[i] 是 B 的特征多项式的 i 次项，那么有：
    sum(p[i] B^i) = 0
  对于任意 w ，两边同时乘上 B^w ，得到 sum(p[i] B^{i+w}) = 0 。
  根据 tr() 的线性性，可以整理得到：
    sum(p[i] tr(B^{i+w})) = 0
  即：
    sum(p[i] h[i + w]) = 0
  这就是 h 的常系数齐次线性递推，暴力求出前 n 项后用这个递推即可，复杂度 O(n^4 + Kn) 。
  另外还需要插值求特征多项式，也是 O(n^4) 的。
  问题至此就解决了。然而对于 f, g 的二项式反演需要卷积优化，而模数很草，需要大力 MTT 。
  最后加上一点小常数优化就能通过了 :) 。
#endif
#include <cstdio>
#include <algorithm>
#include <vector>
#include <complex>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef double ld;
typedef std::pair<int, int> par;
typedef std::complex<ld> complex;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxt = 52, maxn = 10005, maxq = 200005, mod = 1000000007;

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

// Matrix {{{
struct matrix {
	ll m[maxt][maxt];
	static int len;
	ll det () {
		/* for (int i = 0; i < len; i ++) { */
		/* 	for (int j = 0; j < len; j ++) */
		/* 		debug(" %lld", m[i][j]); */
		/* 	debug("\n"); */
		/* } */
		ll fg = 1;
		for (int i = 0; i < len; i ++) {
			for (int j = i + 1; j < len and !m[i][i]; j ++)
				if (m[j][i]) {
					std::swap(m[i], m[j]);
					fg *= -1;
				}
			ll inv = power(m[i][i], -1);
			for (int j = i + 1; j < len; j ++) {
				ll x = m[j][i] * inv % mod;
				for (int k = i; k < len; k ++)
					(m[j][k] += (mod - x) * m[i][k]) %= mod;
			}
		}
		ll res = 1;
		for (int i = 0; i < len; i ++)
			(res *= m[i][i]) %= mod;
		(res *= mod + fg) %= mod;
		/* debug("det = %lld\n", res); */
		return res;
	}
};
matrix operator * (matrix a, matrix b) {
	matrix c;
	for (int i = 0; i < matrix::len; i ++)
		for (int j = 0; j < matrix::len; j ++) {
			c.m[i][j] = 0;
			for (int k = 0; k < matrix::len; k ++)
				(c.m[i][j] += a.m[i][k] * b.m[k][j]) %= mod;
		}
	return c;
}
int matrix::len = 0;
// }}}

// MTT {{{
const int maxl = 1 << 15;
int R[maxl];
complex Wn[maxl];
complex P1[maxl], P2[maxl], Q1[maxl], Q2[maxl];

inline void __a(ll &x) { if(x >= mod) x -= mod; }
inline void __d(ll &x) { if(x < 0) x += mod; }

void fft_init (int n) {
	for (int i = 1; i < n; i ++)
		R[i] = R[i >> 1] >> 1 | ((i & 1) * (n >> 1));
	ld pi = std::acos(ld(-1));
	for (int i = 0; i < n; i ++)
		Wn[i] = complex(std::cos(pi / n * i), std::sin(pi / n * i));
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

inline ll num (complex x) {
	ld d = x.real();
	return d < 0 ? mod + ll(d - ld(0.5)) % mod : ll(d + ld(0.5)) % mod;
}
// }}}

ll tr[maxt][maxn];
std::vector<par> qset[maxt][maxt];
ll ans[maxq];
ll fac[maxn], ifac[maxn];
ll f[maxn], tmp[maxn];
complex tp1[maxl], tp2[maxl];

inline ll C (int n, int m) {
	return fac[n] * ifac[m] % mod * ifac[n - m] % mod;
}

void combinator_init (int n) {
	fac[0] = 1;
	for (int i = 1; i <= n; i ++)
		fac[i] = fac[i - 1] * i % mod;
	ifac[n] = power(fac[n], -1);
	for (int i = n; i; i --)
		ifac[i - 1] = ifac[i] * i % mod;
}

ll de[maxt], po[maxt];
void la (int n) {
	static ll tmp[maxt], tmp2[maxt];
	std::fill(tmp, tmp + n + 1, 0);
	tmp[0] = 1;
	for (int x = 0; x <= n; x ++) {
		for (int i = n + 1; i; i --)
			tmp[i] = (tmp[i] * x + mod - tmp[i - 1]) % mod;
		(tmp[0] *= x) %= mod;
	}
	std::fill(po, po + n + 1, 0);
	for (int x = 0; x <= n; x ++) {
		ll a = 1;
		for (int i = 0; i <= n; i ++)
			if (i != x)
				(a *= i + mod - x) %= mod;
		a = de[x] * power(a, -1) % mod;
		tmp2[n + 1] = tmp[n + 1];
		for (int i = n + 1; i; i --) {
			ll t = mod - tmp2[i];
			(po[i - 1] += t * a) %= mod;
			tmp2[i - 1] = (tmp[i - 1] + (mod - t) * x) % mod;
		}
		if (tmp2[0]) exit(1);
	}
}

int graph[maxt];
matrix li[maxt];

matrix I;
int main () {
	for (int i = 0; i < maxt; i ++)
		I.m[i][i] = 1;

	int T = read;
	for (int t = 1; t <= T; t ++) {
		int n = read, m = read;
		li[t] = I;
		for (int i = 1; i <= m; i ++) {
			int u = read, v = read;
			-- u, -- v;
			li[t].m[u][v] = li[t].m[v][u] = 1;
		}
		graph[t] = n;
	}

	int K = 1, q = read;
	for (int i = 1; i <= q; i ++) {
		int l = read, r = read, k = read;
		K = std::max(K, k);
		qset[l][r].push_back(par(k, i));
	}

	combinator_init(K);

	for (int t = 1; t <= T; t ++) {
		int n = matrix::len = graph[t];

		for (int x = 0; x <= n; x ++) {
			matrix ma;
			for (int i = 0; i < n; i ++)
				for (int j = 0; j < n; j ++)
					__d(ma.m[i][j] = li[t].m[i][j] - I.m[i][j] * x);
			de[x] = ma.det();
		}

		/* for (int i = 0; i < n; i ++) { */
		/* 	for (int j = 0; j < n; j ++) */
		/* 		debug(" %lld", li.m[i][j]); */
		/* 	debug("\n"); */
		/* } */

		/* for (int x = 0; x <= n; x ++) */
		/* 	debug(" %lld", de[x]); */
		/* debug(" det\n"); */

		la(n);

		/* for (int x = 0; x <= n; x ++) */
		/* 	debug(" %lld", po[x]); */
		/* debug(" poly\n"); */

		matrix mu = I;
		for (int i = 0; i < n; i ++) {
			for (int j = 0; j < n; j ++)
				tr[t][i] += mu.m[j][j];
			tr[t][i] %= mod;
			mu = mu * li[t];
		}

		ll ic = power(mod - po[n], -1);
		for (int i = n; i <= K; i ++) {
			for (int j = 0; j < n; j ++)
				(tr[t][i] += po[j] * tr[t][i - n + j]) %= mod;
			(tr[t][i] *= ic) %= mod;
		}

		/* for (int i = 0; i <= 10; i ++) */
		/* 	debug(" %lld", tr[t][i]); */
		/* debug("\n"); */
	}

	int B = int(sqrt(mod));
	for (int k = 0; k <= K; k ++) {
		tmp[k] = k & 1 ? mod - ifac[k] : ifac[k];
		tp1[k] = int(tmp[k] / B);
		tp2[k] = int(tmp[k] % B);
	}

	int len = 1;
	while (len < K * 2 + 1) len <<= 1;
	fft_init(len);
	DFT(tp1, len);
	DFT(tp2, len);

	for (int l = 1; l <= T; l ++)
		for (int r = l; r <= T; r ++) {
			for (int k = 0; k <= K; k ++) {
				f[k] = 1;
				for (int i = l; i <= r; i ++)
					(f[k] *= tr[i][k]) %= mod;
				(f[k] *= ifac[k]) %= mod;
			}

			for (int i = 0; i <= K; i ++) {
				Q1[i] = int(f[i] / B);
				Q2[i] = int(f[i] % B);
			}

			/* for (int i = 0; i <= K; i ++) */
				/* debug("%lld %lld %lld %lld\n", */
				/* 		num(P1[i]), num(P2[i]), num(Q1[i]), num(Q2[i])); */
				/* debug("%lld %lld\n", */
				/* 		num(P1[i]) * B + num(P2[i]), num(Q1[i]) * B + num(Q2[i])); */

			std::copy(tp1, tp1 + len, P1);
			std::copy(tp2, tp2 + len, P2);
			std::fill(Q1 + K + 1, Q1 + len, 0);
			std::fill(Q2 + K + 1, Q2 + len, 0);
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

			for (int i = 0; i <= K; i ++) {
				ll p1 = num(P1[i]), p2 = num(P2[i]), q1 = num(Q1[i]), q2 = num(Q2[i]);
				f[i] = (p1 * B * B + p2 * B + q1 * B + q2) % mod;
			}

			f[0] = 0;
			for (int k = 0; k <= K; k ++)
				(f[k] *= fac[k]) %= mod;
			for (int k = 1; k <= K; k ++)
				__a(f[k] += f[k - 1]);
			for (par p : qset[l][r])
				ans[p.second] = f[p.first];
		}

	for (int i = 1; i <= q; i ++)
		printf("%lld\n", ans[i]);

	/* debug("%lf\n", (sizeof f) / 1024. / 1024.); */
}
