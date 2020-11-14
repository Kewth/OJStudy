/*
 * Author: Kewth

 * Date:
  2020.11.13

 * Solution:
  仙人掌图有 f = n - m + c ，其中 f, n, m, c 分别代表联通块数，点数，边数，环数。
  这个随机模型中上式可以推广到期望，有 E(f) = E(n) - E(m) + E(c) 。E(n) 始终等于
n - k ，E(m) 和 E(c) 可以独立到每个边和每个环，E(m) 是与图的形态无关的，我们要求
最大化 E(f) ，事实上就是最大化 E(c) ，容易发现一个环越大其保留下来的概率就越小，
因此我们不妨假设所有环是三元环，这样就可以求出 E(c) 了。

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
} read;

const int mod = 1000000007;

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
	int n = read, m = read, k = read;
	ll En = n - k;
	ll Em = m;
	ll Ec = m - n + 1;
	for (int i = 0; i < 2; i ++) {
		(Em *= n - k - i) %= mod;
		(Em *= power(n - i, -1)) %= mod;
	}
	for (int i = 0; i < 3; i ++) {
		(Ec *= n - k - i) %= mod;
		(Ec *= power(n - i, -1)) %= mod;
	}
	printf("%lld\n", (En + mod - Em + Ec) % mod);
}
