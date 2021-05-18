/*
 * Author: Kewth

 * Date:
  2021.05.15

 * Solution:
  根据麦克劳林级数，函数 f 的 k 阶导在 0 处的值就是 f 的展开后的多项式的第 k 项
乘上 k! 。那么问题等价于求 f(x) 的前 $k+1$ 项系数，爆算多项式即可平方。

 * Digression:
  smctr
  难度：4~5 / 12

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
	template<class T> inline void operator () (T &x) { x = *this; }
	/* template<class T, class ...A> inline void operator () (T &x, A &...a) */
	/* { x = *this; this -> operator () (a...); } */
} read;

const int maxn = 2020, mod = 998244353;
ll a[maxn], b[maxn];
ll eg[maxn];

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

int main () {
	int n = read, m = read, K = read;
	for (int i = 1; i <= n; i ++)
		read(a[i]);
	for (int i = 1; i <= m; i ++)
		read(b[i]);

	eg[0] = 1;
	for (int i = 1; i <= K; i ++) {
		for (int j = 1; j <= i; j ++)
			(eg[i] += j * a[j] * eg[i - j]) %= mod;
		(eg[i] *= power(i, -1)) %= mod;
	}

	/* for (int j = 1; j <= n; j ++) { */
	/* 	for (int i = K; i >= j; i --) { */
	/* 		ll now = 0, ak = 1; */
	/* 		for (int k = 0; k * j <= i; k ++) { */
	/* 			(now += ak * eg[i - k * j] % mod * ifac[k]) %= mod; */
	/* 			(ak *= a[j]) %= mod; */
	/* 		} */
	/* 		eg[i] = now; */
	/* 	} */
	/* } */

	ll ans = 0, fac = 1;
	for (int k = 1; k <= K; k ++) {
		(fac *= k) %= mod;
		for (int i = 1; i <= m and i <= k; i ++)
			(ans += b[i] * fac % mod * eg[k - i]) %= mod;
	}
	printf("%lld\n", ans);
}
