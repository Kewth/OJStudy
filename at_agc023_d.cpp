/*
 * Since g++10 is released, some characters is not valid inside #if 0 :(
 * So, why not using clang++? :D

 * Date:
  echo -n '  ' && date +%Y.%m.%d # Just Run this (Type !!sh in Vim).

 * Solution:
 * 考虑边界，推导结论，子问题递归求解

  如果 S <= p[1] 或者 S >= p[n] ，显然所有人投票都是一个方向，不妨假设 p[1] < S < p[n] 。

  考虑处在最边上的 1 号点和 n 号点，如果 a[1] >= a[n] ，那么一定先到 1 ，否则先到 n 。归
纳证明，如果 n = 2 显然成立，对于 n >= 3 ，若 S >= a[n - 1] 显然成立，否则 S < a[n - 1] ，
此时考虑 1 和 n - 1 ，如果先到 n - 1 就会回到 S >= a[n - 1] 的情况。

  不妨假设 a[1] >= a[n] ，那么到 n 的时间就一定是到 1 的时间加上 1 到 n 的距离，那么 n 想
要最小化到达 n 的时间其实就是等价于最小化到达 1 的时间，可以赋值 a[1] = a[1] + a[n] 并赋
值 n = n - 1 转换为子问题，递归求解，可以求出每个点的到达时间。

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
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator () (a...); }
} read;

const int maxn = 1000005;
int p[maxn];
ll a[maxn];
ll t[maxn];

void solve (int l, int r, int S) {
	if (S <= p[l]) {
		for (int i = l; i <= r; i ++)
			t[i] = p[i] - S;
		return;
	}
	if (S >= p[r]) {
		for (int i = l; i <= r; i ++)
			t[i] = S - p[i];
		return;
	}
	if (a[l] >= a[r]) {
		a[l] += a[r];
		solve(l, r - 1, S);
		t[r] = t[l] + p[r] - p[l];
	} else {
		a[r] += a[l];
		solve(l + 1, r, S);
		t[l] = t[r] + p[r] - p[l];
	}
}

int main () {
	int n = read, S = read;
	for (int i = 1; i <= n; i ++) read(p[i], a[i]);
	solve(1, n, S);
	ll ans = 0;
	for (int i = 1; i <= n; i ++) ans = std::max(ans, t[i]);
	printf("%lld\n", ans);
}
