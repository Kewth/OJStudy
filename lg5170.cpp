/*
 * Since g++10 is released, some characters is not valid inside #if 0 :(
 * So, why not using clang++? :D

 * Date:
  2020.07.19

 * Solution:
  学到许多，万能欧几里得可以直接一套带走。
  但是直接用矩阵乘法会带来巨大的常数，需要换成可以任意顺序合并（满足结合律）的分治结构。

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
#include <cstring>
#include <string>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int mod = 998244353;

struct Matrix { // 矩阵太慢了，要换成分治结构
	ll ans1, ans2, ans3;
	ll x, y;
	ll sum;
	/* std::string s; */
};

Matrix operator * (Matrix a, Matrix b) {
	Matrix c;
	c.ans1 = (a.y * b.x + a.ans1 + b.ans1) % mod;
	c.ans2 = (a.y * a.y % mod * b.x + a.y * b.ans1 * 2 + a.ans2 + b.ans2) % mod;
	c.ans3 = (a.y * b.sum + a.y * a.x % mod * b.x +
			a.x * b.ans1 + a.ans3 + b.ans3) % mod;
	c.x = (a.x + b.x) % mod;
	c.y = (a.y + b.y) % mod;
	c.sum = (a.x * b.x + a.sum + b.sum) % mod;
	/* c.s = a.s + b.s; */
	return c;
}

Matrix power (Matrix x, ll k) {
	Matrix res = {0, 0, 0, 0, 0, 0};
	while (k) {
		if (k & 1) res = res * x;
		x = x * x;
		k >>= 1;
	}
	return res;
}

Matrix solve (int P, int R, int Q, ll n, Matrix X, Matrix Y) {
	/* debug("%d %d %d %d %s %s\n", P, R, Q, n, X.s.c_str(), Y.s.c_str()); */
	if (R >= Q) return power(Y, R / Q) * solve(P, R % Q, Q, n, X, Y);
	if (!n) return X;
	if (P >= Q) return X * solve(P % Q, R + P % Q, Q, n - 1, power(Y, P / Q) * X, Y);
	ll t = (n * P + R) / Q;
	if (!t) return power(X, n + 1);
	return solve(Q, Q - R + P - 1, P, t - 1, Y, X) *
		power(X, n + 1 - (Q * (t - 1) + Q - R + P - 1) / P);
}

int main () {
	/* Matrix M = 0, X = 1, Y = 1; */

	/* M(1, 1) = 0; // X 的数量 x */
	/* M(1, 2) = 0; // Y 的数量 y */
	/* M(1, 3) = 0; // ans1 */
	/* M(1, 4) = 0; // ans2 */
	/* M(1, 5) = 0; // ans3 */
	/* M(1, 6) = 1; // 常数 */
	/* M(1, 7) = 0; // y * y */
	/* M(1, 8) = 0; // x * y */

	/* X(6, 1) = 1; */
	/* X(2, 3) = 1; */
	/* X(7, 4) = 1; */
	/* X(8, 5) = 1; */
	/* X(2, 8) = 1; */

	/* Y(6, 2) = 1; */
	/* Y(2, 7) = 2; */
	/* Y(6, 7) = 1; */
	/* Y(1, 8) = 1; */

	/* X.s = 'X'; */
	/* Y.s = 'Y'; */

	Matrix M = {0, 0, 0, 0, 0, 0};
	Matrix X = {0, 0, 0, 1, 0, 0};
	Matrix Y = {0, 0, 0, 0, 1, 0};

	int T = read;
	while (T --) {
		int n = read, P = read, R = read, Q = read;
		Matrix m = M * solve(P, R, Q, n, X, Y);
		printf("%lld %lld %lld\n", m.ans1, m.ans2, m.ans3);
		/* printf("%lld %lld %lld\n", m(1, 3), m(1, 4), m(1, 5)); */
		/* debug("%s\n", m.s.c_str()); */
	}
}
