/*
 * Since g++10 is released, some characters is not valid inside #if 0 :(
 * So, why not using clang++? :D

 * Date:
  2020.06.05

 * Solution:
  假设所有数都是质数，那么问题就是求区间的不同的数的乘积，很经典的做法是记一个 pre ，
然后查询区间 [l, r] 内 pre < l 的数的乘积，用组合数维护即可。
  当然每个数未必是质数，lcm 会稍微有点不同，对于质数 p ，如果在最后答案的指数为 k ，
那么答案要有 p^k ，而 p^1, p^2, ... p^k 都在区间中出现过。那么不妨把每个数 x 分解，
对于每个因子分别记 pre 即可。
  本质上就是把 max(X) 转换为 sum([X >= i]) 。

 * Digression:
  经典套路完全不会。
  另外也可以值域分块，此不做讨论。

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
#include <vector>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef std::pair<int, int> par;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator () (a...); }
} read;

const int maxa = 50005, maxn = 50005, mod = 1000000007;
int minp[maxa];
int pre[maxa];

std::vector<par> rv[maxn];

struct Tree {
	int lti, rti;
	ll val;
} pool[maxn * 100];
int pp;
#define self pool[now]

void lain (int &now, int L, int R, int p, int x) {
	pool[++ pp] = self;
	now = pp;
	if (!self.val) self.val = x;
	else (self.val *= x) %= mod;
	if (L == R) return;
	int M = (L + R) >> 1;
	if (p <= M) lain(self.lti, L, M, p, x);
	else lain(self.rti, M + 1, R, p, x);
}

ll query (int now, int L, int R, int l, int r) {
	if (r < L or l > R or !now) return 1;
	if (l <= L and R <= r) return self.val;
	int M = (L + R) >> 1;
	return query(self.lti, L, M, l, r) * query(self.rti, M + 1, R, l, r) % mod;
}

int seg[maxn];

int main () {
	int A = 50000;
	minp[1] = 1;
	for (int i = 2; i <= A; i ++)
		if (!minp[i]) {
			minp[i] = i;
			if (i <= A / i)
				for (int j = i * i; j <= A; j += i)
					if (!minp[j])
						minp[j] = i;
		}

	int n = read, q = read;
	for (int i = 1; i <= n; i ++) {
		int x = read;
		while (x > 1) {
			int p = minp[x], y = 1;
			while (x % p == 0) {
				x /= p;
				y *= p;
				rv[pre[y] + 1].push_back(par(i, p));
				pre[y] = i;
			}
		}
	}

	for (int i = 1; i <= n; i ++) {
		seg[i] = seg[i - 1];
		for (par p : rv[i])
			lain(seg[i], 1, n, p.first, p.second);
	}

	while (q --) {
		int l = read, r = read;
		printf("%lld\n", query(seg[l], 1, n, l, r));
	}
}
