/*
 * Author: Kewth

 * Date:
  2021.01.30

 * Solution:
  In blog.

 * Digression:

 * CopyRight:
   __  __                  __   __
  |  |/  |.-----.--.--.--.|  |_|  |--.
  |     < |  -__|  |  |  ||   _|     |
  |__|\__||_____|________||____|__|__|

 */

#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

static struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
} read;

const int maxv = 10, mod = 1000000007;
struct Mat {
	__int128 x[maxv + 1][maxv + 1];
	Mat () {
		for (int i = 0; i <= maxv; i ++)
			for (int j = 0; j <= maxv; j ++)
				x[i][j] = 0;
	}
} po[100];
Mat operator * (Mat a, Mat b) {
	Mat c;
	for (int i = 0; i <= maxv; i ++)
		for (int j = 0; j <= maxv; j ++)
			for (int k = 0; k <= maxv; k ++)
				c.x[i][k] += a.x[i][j] * b.x[j][k];
	return c;
}

struct mat {
	int x[maxv * 2 + 1][maxv * 2 + 1];
	mat () {
		for (int i = 0; i <= maxv * 2; i ++)
			for (int j = 0; j <= maxv * 2; j ++)
				x[i][j] = 0;
	}
};
mat operator * (mat a, mat b) {
	mat c;
	for (int i = 0; i <= maxv * 2; i ++)
		for (int j = 0; j <= maxv * 2; j ++)
			for (int k = 0; k <= maxv * 2; k ++)
				c.x[i][k] = (c.x[i][k] + 1ll * a.x[i][j] * b.x[j][k]) % mod;
	return c;
}

void getm (ll n, int a, int b, ll &m, ll &sgm) {
	Mat M; // M.x[0][i] = sg(x + i)
	for (int i = 0; i < a; i ++)
		M.x[0][i] = 1;
	for (int i = a; i < b; i ++)
		M.x[0][i] = M.x[0][i - a] + 1;
	M.x[0][b] = 1; // constant

	po[0] = Mat();
	for (int i = 1; i < b; i ++)
		po[0].x[i][i - 1] += 1;
	po[0].x[b - a][b - 1] += 1;
	po[0].x[b - b][b - 1] += 1;
	po[0].x[b][b - 1] += 1;
	po[0].x[b][b] += 1;

	int p = 0;
	while ((M * po[p]).x[0][0] < n - 1)
		++ p, po[p] = po[p - 1] * po[p - 1];

	/* for (int i = 0; i <= b; i ++) { */
	/* 	for (int j = 0; j <= b; j ++) */
	/* 		debug("%lld", po[0].x[i][j]); */
	/* 	debug("\n"); */
	/* } */
	/* for (int k = 0; k <= p; k ++) { */
	/* 	Mat tmp = M * po[k]; */
	/* 	debug("sg[%lld]:", a + b + (1ll << k)); */
	/* 	for (int i = 0; i < b; i ++) */
	/* 		debug(" %lld", tmp.x[0][i]); */
	/* 	debug("\n"); */
	/* } */

	ll d = 0;
	for (int k = p - 1; k >= 0; k --)
		if ((M * po[k]).x[0][0] < n - 1)
			M = M * po[k], d += 1ll << k;
	m = d + a + b;
	sgm = ll(M.x[0][0]);
	/* debug("%lld %lld\n", m, sgm); */
}

int main () {
	int T = read;
	while (T --) {
		ll n = read, m, sgm;
		int a = read, b = read, mark = 0;
		if (a > b) std::swap(a, b);
		if (b <= 1) a *= 2, b *= 2, mark = 1;
		getm(n, a, b, m, sgm);

		mat M, X; // M: g(x) ... g(x + b - 1) h(x) ... h(x + b - 1) sh(x)
		M.x[0][0] = 1;
		for (int i = a; i < b; i ++)
			M.x[0][i] = M.x[0][i - a];
		for (int i = 0; i < b; i ++)
			M.x[0][b + i] = M.x[0][i] * (a + b + i);
		M.x[0][b * 2] = a + b;

		for (int i = 1; i < b; i ++)
			X.x[i][i - 1] = X.x[b + i][b + i - 1] = 1;
		X.x[b - a][b - 1] += 1;
		X.x[b - b][b - 1] += 1;
		X.x[b - a][b * 2 - 1] += a;
		X.x[b - b][b * 2 - 1] += b;
		X.x[b * 2 - a][b * 2 - 1] += 1;
		X.x[b * 2 - b][b * 2 - 1] += 1;
		X.x[b * 2][b * 2] += 1;
		X.x[b + 1][b * 2] += 1;

		ll k = m - a - b;
		/* while (k --) { */
		/* 	M = M * X; */
		/* 	/1* for (int i = 0; i <= b * 2; i ++) *1/ */
		/* 	/1* 	debug(" %d", M.x[0][i]); *1/ */
		/* 	/1* debug("\n"); *1/ */
		/* 	/1* debug("%d %d %d\n", M.x[0][0], M.x[0][b], M.x[0][b * 2]); *1/ */
		/* } */
		while (k) {
			if (k & 1) M = M * X;
			X = X * X;
			k >>= 1;
		}

		int shm = M.x[0][b * 2];
		/* debug("%d\n", shm); */
		ll ans = (shm + (n - 1 - sgm) % mod * ((m + 1) % mod)) % mod;
		if (mark) (ans *= (mod + 1) / 2) %= mod;
		printf("%lld\n", ans);
	}
}
