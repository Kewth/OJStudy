#if 0
2020.03.22

DP 设 f[i] 表示从 i 走到 i + 1 的期望步数。
DP 设 g[i] 表示从 i 所属的关键点走到 i + 1 的期望步数。
DP 设 h[i] 表示从 1 走到 i + 1 的期望步数。
列出转移式，(f[i], g[i], h[i]) 可以由 (f[i - 1], g[i - 1], h[i - 1]) 转移而来。
并且 f[i] 实际上不会出现在转移中，因此可以直接把 f 去掉，然后把 (g, h) 的转移写成矩阵。
序列上动态 DP 维护转移矩阵乘积即可。
#endif
#include <cstdio>
#include <algorithm>
#include <cmath>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
} read;

const int maxn = 200005, mod = 998244353;
struct Matrix {
	ll x[3][3];
};
Matrix operator * (Matrix a, Matrix b) {
	Matrix c;
	for (int i = 0; i < 3; i ++)
		for (int j = 0; j < 3; j ++)
			c.x[i][j] = (a.x[i][0] * b.x[0][j] +
					a.x[i][1] * b.x[1][j] + a.x[i][2] * b.x[2][j]) % mod;
	return c;
}
Matrix operator + (Matrix a, Matrix b) {
	Matrix c;
	for (int i = 0; i < 3; i ++)
		for (int j = 0; j < 3; j ++)
			c.x[i][j] = (a.x[i][j] + b.x[i][j]) % mod;
	return c;
}

Matrix seg[maxn << 2];
void modify (int now, int L, int R, int p, Matrix m) {
	if (L == R) return seg[now] = m, void();
	int M = (L + R) >> 1;
	if (p <= M) modify (now << 1, L, M, p, m);
	else modify (now << 1 | 1, M + 1, R, p, m);
	seg[now] = seg[now << 1] * seg[now << 1 | 1];
}

bool status[maxn];
ll p[maxn], ip[maxn];
Matrix ikey[maxn], nkey[maxn];

inline ll power(ll x, int k) {
	if(k < 0) k += mod - 1;
	ll res = 1;
	while(k) {
		if(k & 1) (res *= x) %= mod;
		(x *= x) %= mod;
		k >>= 1;
	}
	return res;
}

void De (Matrix M) {
	debug("{");
	for (int i = 0; i < 3; i ++) {
		for (int j = 0; j < 3; j ++)
			debug(" %lld", M.x[i][j]);
		debug(" |");
	}
	debug(" }\n");
}

int main () {
	Matrix I, F, O;
	for (int i = 0; i < 3; i ++)
		for (int j = 0; j < 3; j ++)
			O.x[i][j] = 0;
	I = O;
	I.x[0][0] = I.x[1][1] = I.x[2][2] = 1;
	F = O;
	F.x[0][0] = 1;

	int n = read, q = read;
	for (int i = 1; i <= n; i ++)
		ip[i] = power(p[i] = read, -1);

	for (int i = 1; i <= n; i ++) {
		ikey[i] = nkey[i] = O;
		ikey[i].x[0][0] = nkey[i].x[0][0] = 1;
		ikey[i].x[0][1] = nkey[i].x[0][1] = 100 * ip[i] % mod;
		ikey[i].x[0][2] = nkey[i].x[0][2] = 100 * ip[i] % mod;
		nkey[i].x[1][1] = 100 * ip[i] % mod;
		nkey[i].x[1][2] = (100 - p[i]) * ip[i] % mod;
		ikey[i].x[2][2] = nkey[i].x[2][2] = 1;
		modify (1, 1, n, i, nkey[i]);
	}

	/* for (int i = 1; i <= n; i ++) */
	/* 	De(nkey[i]); */
	/* debug("\n"); */

	/* for (int i = 1; i <= n; i ++) */
	/* 	De(ikey[i]); */
	/* debug("\n"); */

	while (q --) {
		int i = read;
		if (status[i] == 0)
			modify (1, 1, n, i, ikey[i]);
		else
			modify (1, 1, n, i, nkey[i]);
		status[i] ^= 1;

		printf("%lld\n", (F * seg[1]).x[0][2]);
	}
}
