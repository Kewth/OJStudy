/*
 * Author: Kewth

 * Date:
  2020.10.12

 * Solution:
  可以发现一个点是关键点当且仅当初始关键点到其的路径数为奇数，这个条件等价于任意两个维
度的坐标减一的按位与恰为 0 。
  如果 L = 1 ，据此数位 DP 即可，然后套个暴力容斥可以处理更一般的情况。
  但是也可以不用容斥，数位 DP 中用 0/1 处理了上界的问题，可以再加个 0/1 来处理下界的问
题，直接这样做复杂度同容斥。但是注意到在某一位上同时卡在上界和下界的话这个数是可以唯一
确定的，据此剪枝可以把复杂度中 4^K 的因子优化为 3^K 。

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

const int maxk = 9, maxl = 51, maxs = 19683, mod = 998244353;
ll L[maxk], R[maxk];
ll f[maxl + 1][maxs];
bool eq[maxk], leq[maxk];

void dfs (int k, int i, int use, int S, int T) {
	if (use > 1) return;
	if (i == -1) return f[k][T] += f[k + 1][S], void();
	S *= 3, T *= 3;
	if (eq[i]) {
		int x = R[i] >> k & 1;
		dfs(k, i - 1, use + x, S, T);
		return;
	}
	if (leq[i]) {
		dfs(k, i - 1, use + 0, S, T + 1);
		dfs(k, i - 1, use + 1, S, T + 2);
		return;
	}
	dfs(k, i - 1, use + 0, S + 0, T + 0);
	dfs(k, i - 1, use + 1, S + 0, T + 0);
	if (L[i] >> k & 1)
		dfs(k, i - 1, use + 1, S + 1, T + 1);
	else {
		dfs(k, i - 1, use + 0, S + 1, T + 1);
		dfs(k, i - 1, use + 1, S + 1, T + 0);
	}
	if (R[i] >> k & 1) {
		dfs(k, i - 1, use + 0, S + 2, T + 0);
		dfs(k, i - 1, use + 1, S + 2, T + 2);
	} else
		dfs(k, i - 1, use + 0, S + 2, T + 2);
}

int main () {
	int T = read;
	while (T --) {
		int K = read;
		for (int i = 0; i < K; i ++) L[i] = ll(read) - 1;
		for (int i = 0; i < K; i ++) R[i] = ll(read) - 1;
		for (int i = 0; i < K; i ++) eq[i] = 1;
		f[maxl][0] = 1;
		for (int k = maxl - 1; k >= 0; k --) {
			for (int i = 0; i < K; i ++) leq[i] = eq[i];
			for (int i = 0; i < K; i ++) eq[i] &= (L[i] >> k & 1) == (R[i] >> k & 1);
			for (int S = 0; S < maxs; S ++) f[k][S] = 0;
			dfs(k, K - 1, 0, 0, 0);
			for (int S = 0; S < maxs; S ++) f[k][S] %= mod;
		}
		ll ans = 0;
		for (int S = 0; S < maxs; S ++) ans += f[0][S];
		printf("%lld\n", ans % mod);
	}
}
