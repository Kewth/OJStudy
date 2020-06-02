/*
 * Since g++10 is released, some characters is not valid inside #if 0 :(
 * So, why not using clang++? :D

 * Date:
  2020.06.02

 * Solution:
  由于两个方向向量线性无关，不妨以它们为基向量重新建系，那么问题转换为统计 (0, 0) 到
(X, Y) 的不经过任何关键点的路径数。
  如果没有关键点组合数就能直接算，普通的容斥需要枚举子集，不妨设 f[i][j] 表示从第 i
个点到第 j 个点的不经过任何关键点的路径数，转移容斥，用总路径数减去不合法路径数，统
计不合法路径数只需要枚举路径上第一个关键点 k 即可。

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
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator () (a...); }
} read;

int x1, y1, x2, y2;
void trans (int x0, int y0, int &a, int &b) {
	int a1 = x0 * y2 - y0 * x2;
	int a2 = x1 * y2 - y1 * x2;
	int b1 = x0 * y1 - y0 * x1;
	int b2 = x2 * y1 - y2 * x1;
	if (a1 % a2 or b1 % b2) a = b = -1;
	else {
		a = a1 / a2;
		b = b1 / b2;
		if (a < 0 or b < 0) a = b = -1;
	}
}

const int maxn = 505, mod = 1000000007;
ll fac[maxn * maxn * 2], ifac[maxn * maxn * 2];

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

inline ll C (int n, int m) {
	if (n < m) return 0;
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

ll f[maxn][maxn];
bool vis[maxn][maxn];
int bx[maxn], by[maxn];

bool cmp (int i, int j) {
	return bx[i] <= bx[j] and by[i] <= by[j];
}

ll path (int i, int j) {
	int x = bx[j] - bx[i], y = by[j] - by[i];
	return C(x + y, x);
}

ll F (int i, int j, int n) {
	if (vis[i][j]) return f[i][j];
	vis[i][j] = 1;
	f[i][j] = path(i, j);
	for (int k = 1; k <= n; k ++)
		if (k != i and k != j and cmp(i, k) and cmp(k, j))
			(f[i][j] += (mod - F(i, k, n)) * path(k, j)) %= mod;
	return f[i][j];
}

int main () {
	combinator_init(500000);

	int X = read, Y = read;
	int p = read;
	read(x1, y1, x2, y2);
	trans(X, Y, X, Y);
	if (X == -1 and Y == -1) return puts("0"), 0;

	/* debug("%d %d\n", X, Y); */

	int n = 0;
	while (p --) {
		int x = read, y = read;
		trans(x, y, x, y);
		if (x != -1 and y != -1 and x <= X and y <= Y) {
			++ n;
			bx[n] = x;
			by[n] = y;
			/* debug("%d %d\n", x, y); */
		}
	}

	bx[n + 1] = X;
	by[n + 1] = Y;

	printf("%lld\n", F(0, n + 1, n));
}
