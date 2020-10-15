/*
 * Author: Kewth

 * Date:
  2020.10.12

 * Solution:
  可以发现一个点是关键点当且仅当初始关键点到其的路径数为奇数，这个条件等价于任意两个维
度的坐标减一的按位与恰为 0 。
  如果 L = 1 ，据此数位 DP 即可，然后套个暴力容斥可以处理更一般的情况。
  总复杂度 O(4^k k logR) 。

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
	/* template<class T> inline void operator () (T &x) { x = *this; } */
	/* template<class T, class ...A> inline void operator () (T &x, A &...a) */
	/* { x = *this; this -> operator () (a...); } */
} read;

const int maxk = 9, maxl = 51, mod = 998244353;
ll L[maxk], R[maxk];
ll f[maxl + 1][1 << maxk];

ll solve (int K, ll lim[maxk]) {
	for (int i = 0; i < K; i ++) if (lim[i] == -1) return 0;
	/* int U = (1 << K) - 1; */
	f[maxl][0] = 1;
	for (int k = maxl - 1; k >= 0; k --) {
		int lS = 0;
		for (int i = 0; i < K; i ++)
			if (lim[i] >> k & 1)
				lS |= 1 << i;
		for (int S = 0; S < (1 << K); S ++) f[k][S] = 0;
		for (int S = 0; S < (1 << K); S ++) {
			f[k][S | lS] += f[k + 1][S];
			for (int i = 0; i < K; i ++)
				if (S >> i & 1 or lS >> i & 1)
					f[k][S | (lS ^ (1 << i))] += f[k + 1][S];
		}
		for (int S = 0; S < (1 << K); S ++) f[k][S] %= mod;
	}
	ll res = 0;
	for (int S = 0; S < (1 << K); S ++) res += f[0][S];
	return res % mod;
}

int main () {
	int T = read;
	while (T --) {
		int K = read;
		for (int i = 0; i < K; i ++) L[i] = ll(read) - 1;
		for (int i = 0; i < K; i ++) R[i] = ll(read) - 1;
		for (int i = 0; i < K; i ++)
			if (R[i] < L[i] or R[i] + 1 > 2000000000000000)
			/* if (R[i] < L[i]) */
				return 1;

		ll ans = 0;
		for (int S = 0; S < (1 << K); S ++) {
			ll lim[maxk], x = 1;
			for (int i = 0; i < K; i ++)
				if (S >> i & 1)
					lim[i] = L[i] - 1, x = - x;
				else
					lim[i] = R[i];
			(ans += (mod + x) * solve(K, lim)) %= mod;
		}
		printf("%lld\n", ans);
	}
}
