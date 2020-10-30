/*
 * Author: Kewth

 * Date:
  2020.10.29

 * Solution:
 * 寻找真正需要关注的变量（小质数），快速遍历

  注意到如果 C(n, m) 有平方质因子 p ，那么一定有 p <= sqrt(n) ，也就是说我们只需要关注
这些“小质数”，它们只有七十多个。

  考虑对于每一行，找出所有没有平方因子的组合数。假设当前 C(n, m) 是有平方质因子 p ，考
虑求出最小的 k 满足 k > m 且 C(n, k) 没有平方质因子 p 。

  设大于 m 的最小的 p 的倍数为 x ，不难发现 (m, x) 之间的 k 都是不合法的，那么我们把 k
调到 x 进行一次检查，如果 k = x 也是不合法的，设大于 m 的最小的 p^2 的倍数是 y ，不难发
现 (x, y) 之间的 k 都是不合法的。以此类推，花费 O(log) 的时间就能找到合法的 k 。

  这个算法可以在帕斯卡三角形上按顺序不遗漏地遍历所有没有平方因子的组合数，现在的问题是
这样的组合数有多个。事实上似乎是 O(n) 的，但是不知道怎么证明。

  有论文指出这个数量趋近于 10.66n ？

 * Digression:

  Eigenray 真是救星啊！

 * CopyRight:
   __  __                  __   __
  |  |/  |.-----.--.--.--.|  |_|  |--.
  |     < |  -__|  |  |  ||   _|     |
  |__|\__||_____|________||____|__|__|

 */

#pragma GCC optimize(3)
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <set>
#include <unordered_set>
#include <vector>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

static struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 150005, maxs = 400, maxp = 80;

bool nop[maxs];
int pr[maxp], pp;
int v[maxn][maxp];
ll ans[maxn];
std::unordered_set<ll> vis;
/* std::set<ll> vis; */

struct Mod {
	int mod;
	ll fac[maxn], ifac[maxn];

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
		return fac[n] * ifac[m] % mod * ifac[n - m] % mod;
	}

	Mod (int mod): mod(mod) {
		int N = maxn - 1;
		fac[0] = 1;
		for (int i = 1; i <= N; i ++) fac[i] = fac[i - 1] * i % mod;
		ifac[N] = power(fac[N], -1);
		for (int i = N; i; i --) ifac[i - 1] = ifac[i] * i % mod;
	}
} m1(1000000007), m2(998244353);

inline int check (int n, int m) {
	for (int k = 1; k <= pp; k ++)
		if (v[n][k] - v[m][k] - v[n - m][k] >= 2)
			return k;
	return 0;
}

int main () {
	std::vector<int> Q;
	int q = read, N = 2;
	while (q --) {
		int n = read - 1;
		Q.push_back(n);
		N = std::max(n, N);
	}

	int S = int(sqrt(N));
	for (int i = 2; i <= S; i ++)
		if (!nop[i]) {
			pr[++ pp] = i;
			for (int j = i + i; j <= S; j += i)
				nop[j] = 1;
		}

	for (int i = 1; i <= N; i ++)
		for (int k = 1; k <= pp; k ++) {
			v[i][k] = v[i - 1][k];
			int x = i;
			while (x % pr[k] == 0)
				++ v[i][k], x /= pr[k];
		}

	int tot = 0;
	ll now = 0;
	for (int n = 0; n <= N; n ++) {
		for (int m = 0; m <= n - m; m ++) {
			for (int k = check(n, m); k; k = check(n, m))
				for (int p = pr[k]; v[n][k] - v[m][k] - v[n - m][k] >= 2; p *= pr[k]) {
					m += p - m % p;
					if (m > n - m)
						goto out;
				}
			++ tot;
			ll x = m1.C(n, m), y = m2.C(n, m);
			y = x * 1000000009ll + y;
			if (!vis.count(y)) {
				vis.insert(y);
				now += x;
			}
		}
out:
		ans[n] = now % m1.mod;
	}
	/* debug("%lf\n", 1.0 * tot / N); */

	for (int n : Q)
		printf("%lld\n", ans[n]);
}
