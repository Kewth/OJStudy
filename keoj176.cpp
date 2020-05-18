#if 0
2020.05.18

  以下的矩阵都是方阵。

  对于一个矩阵，称其 (x, y) 位置的余子式为去掉第 x 行第 y 列后的矩阵行列式。
  对于一个矩阵，称其 (x, y) 位置的代数余子式为其余子式乘上 (-1)^{x+y} 。
  引理 1: 对于一个矩阵的任意一行或任意一列，对应位置的代数余子式乘上对应位置矩阵的值就
是该矩阵的行列式。
  引理 2: 对于任意矩阵 A ，设其代数余子式构成的矩阵的转置为 B ，那么有： A B = I det(A)
事实上引理 2 严格比引理 1 强，但引理 1 看起来更自然。

  设 A 是原图出度基尔霍夫矩阵去掉第 n 行第 n 列后的矩阵。
  考虑每条边 (x, y) 对答案的贡献，也就是这条边出现在了多少颗生成树中，可以用总生成树个
数减去删掉这条边后的生成树个数来算，也就是要求 (x, y) 对 det(A) 的贡献，注意到 (x, y)
只会至多影响到 A 的某一行的两个位置，那么只要对于这一行，用对应位置代数余子式乘上对应位
置的 A 的值就可以求出 det(A) ，而根据定义该行的值改变不会影响到该行的代数余子式，因此这
个 det(A) 的变化量是可以 O(1) 求的，总复杂度 O(n^3 + m) 。
#endif
#include <cstdio>
#include <cstring>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator () (a...); }
} read;

const int maxn = 303, maxm = 100005, mod = 998244353;
int N = 0;
struct Matrix {
	ll x[maxn][maxn];
	inline ll & operator () (int i, int j) { return x[i][j]; }
	Matrix (ll y = 0) {
		memset(x, 0, sizeof x);
		for (int i = 1; i <= N; i ++)
			x[i][i] = y;
		/* for (int i = 1; i <= N; i ++) */
		/* 	for (int j = 1; j <= N; j ++) */
		/* 		x[i][j] = i == j ? y : 0; */
	}
};

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

ll det (Matrix m) {
	ll res = 1;
	for (int i = 1; i <= N; i ++) {
		(res *= m(i, i)) %= mod;
		ll mii = power(m(i, i), -1);
		for (int j = i + 1; j <= N; j ++) {
			ll x = m(j, i) * mii % mod;
			for (int k = i; k <= N; k ++)
				(m(j, k) += (mod - x) * m(i, k)) %= mod;
		}
	}
	return res;
}

Matrix inv (Matrix m) {
	Matrix I = 1;
	for (int i = 1; i <= N; i ++) {
		ll mii = power(m(i, i), -1);
		for (int j = 1; j <= N; j ++)
			if (i != j) {
				ll x = m(j, i) * mii % mod;
				for (int k = 1; k <= N; k ++) {
					(m(j, k) += (mod - x) * m(i, k)) %= mod;
					(I(j, k) += (mod - x) * I(i, k)) %= mod;
				}
			}
		for (int k = 1; k <= N; k ++) {
			(m(i, k) *= mii) %= mod;
			(I(i, k) *= mii) %= mod;
		}
	}
	/* for (int i = 1; i <= N; i ++) { */
	/* 	for (int j = 1; j <= N; j ++) */
	/* 		debug(" %lld", I(i, j)); */
	/* 	debug("\n"); */
	/* } */
	return I;
}

Matrix operator * (Matrix m, ll x) {
	for (int i = 1; i <= N; i ++)
		for (int j = 1; j <= N; j ++)
			(m(i, j) *= x) %= mod;
	return m;
}

Matrix transpose (Matrix m) {
	for (int i = 1; i <= N; i ++)
		for (int j = 1; j < i; j ++)
			std::swap(m(i, j), m(j, i));
	return m;
}

int ex[maxm], ey[maxm], ew[maxm];
Matrix A;

int main () {
	int n = read, m = read;
	for (int i = 1; i <= m; i ++) {
		read(ex[i], ey[i], ew[i]);
		++ A(ex[i], ex[i]);
		-- A(ex[i], ey[i]);
	}
	N = n - 1;

	for (int i = 1; i <= N; i ++)
		for (int j = 1; j <= N; j ++)
			if (A(i, j) < 0)
				A(i, j) += mod;

	Matrix B = transpose(inv(A) * det(A));

	/* for (int i = 1; i <= N; i ++) { */
	/* 	for (int j = 1; j <= N; j ++) */
	/* 		debug(" %lld", A(i, j)); */
	/* 	debug("\n"); */
	/* } */

	ll ans = 0;
	for (int i = 1; i <= m; i ++)
		if (ex[i] != n)
			(ans += ew[i] * (B(ex[i], ex[i]) + mod - B(ex[i], ey[i]))) %= mod;
	printf("%lld\n", ans);
}
