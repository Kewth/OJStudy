#if 0
2020.05.22

  DP 设 f[i][S] 表示从局面 S 开始，进行 i 次操作的期望收益。
  搜出所有可能的局面（只有 165 个），然后搜出局面之间的转移，列成矩阵，用矩阵快速幂即可。
对于多组询问，只需预处理每个转移矩阵 A 的每个 A^{2^k} ，然后就只要做 log 次向量与矩阵的
乘法。
  卡常，注意到预处理部分的开销明显比询问部分低，可以预处理每个 A^{l*2^k} ，然后询问就只
要做 log/2 次乘法。
        ▁▃▄▄▄▃▃▃▃▄▶
      ▗▇▀▔    ▔▔▔▔
     ▄▛   ▃▅━━■▄▂
    ▟▊   ▐▘     ▀▙
   ▟▜▌   ▐▖   ▋  ▐▍
  ▟▘ ▜   ▝▀▇▆●▘  ▐▌
▗▟▘   ▜▃       ▁▅▛
▔▀▼▅▄▃▃██▅▄▄▄▅■▀▔   CopyRight :)
      ▔▔▔▔▔▔
#endif
#include <cstdio>
#include <cstring>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
} read;

const int maxn = 166, maxk = 30, mod = 998244353;

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

int N = 0;
struct Matrix {
	ll x[maxn][maxn];
	inline ll & operator () (int i, int j) { return x[i][j]; }
	Matrix (ll y = 0) {
		memset(x, 0, sizeof x);
		for (int i = 1; i <= N; i ++)
			x[i][i] = y;
	}
};

struct Vector {
	ll x[maxn];
	inline ll & operator () (int i) { return x[i]; }
	Vector () { memset(x, 0, sizeof x); }
};

Matrix operator * (Matrix a, Matrix b) {
	Matrix c = 0;
	for (int i = 1; i <= N; i ++)
		// XXX: 交换下面两个 for 效率会有很大差异？
		for (int k = 1; k <= N; k ++)
			for (int j = 1; j <= N; j ++)
				(c(i, j) += a(i, k) * b(k, j)) %= mod;
	return c;
}

Vector operator * (Vector a, Matrix b) {
	Vector c;
	// XXX: 交换下面两个 for 效率会有很大差异？
	for (int k = 1; k <= N; k ++)
		for (int j = 1; j <= N; j ++)
			(c(j) += a(k) * b(k, j)) %= mod;
	return c;
}

int id[100000];
int a[10];
Matrix A, P[maxk][4];

int getid (int m, int max) {
	std::sort(a + 1, a + max + 1);
	int now = 0, bs = 1;
	for (int i = 1; i <= max; i ++)
		now += a[i] * bs, bs *= 4;
	if (!id[now]) {
		/* for (int i = 1; i <= max; i ++) debug(" %d", a[i]); debug("\n"); */
		id[now] = ++ N;
		int tot = 0;
		while (a[max - tot]) ++ tot;
		ll p = power(tot + 1, -1);
		A(id[now], id[now]) += p;
		A(1, id[now]) += p;
		int b[10];
		std::copy(a, a + max + 1, b);
		/* for (int i = 0; i < tot; i ++) { */
		/* 	std::copy(b, b + max + 1, a); */
		/* 	if (-- a[max - i] and !a[1]) a[1] = m; */
		/* 	std::sort(a + 1, a + max + 1); */
		/* 	for (int i = 1; i <= max; i ++) debug(" %d", a[i]); debug(" <\n"); */
		/* } */
		for (int i = 0; i < tot; i ++) {
			std::copy(b, b + max + 1, a);
			if (-- a[max - i] and !a[1]) a[1] = m;
			ll &x = A(getid(m, max), id[now]);
			if ((x += p) >= mod) x -= mod;
		}
	}
	return id[now];
}

int main () {
	int q = read, m = read, max = read;

	N = 1;
	Vector F;
	F(1) = 1;
	A(1, 1) = 1;

	a[1] = m;
	int first = getid(m, max);
	/* debug("%d\n", N); */

	for (int k = 0; k < maxk; k ++) {
		P[k][1] = k ? P[k - 1][2] * P[k - 1][2] : A;
		P[k][2] = P[k][1] * P[k][1];
		P[k][3] = P[k][2] * P[k][1];
	}

	while (q --) {
		ll n = read;
		Vector V = F;
		for (int k = 0; k < maxk; k ++) {
			int l = n >> (k * 2) & 3;
			if (l) V = V * P[k][l];
		}
		printf("%lld\n", V(first));
	}
}
