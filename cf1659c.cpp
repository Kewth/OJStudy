/*
 * Author: Kewth

 * Date:
  2022.04.17

 * Solution:
  设 f[i] 表示征服到 i 并将其作为首都的最小代价。
  决策单调值单峰，尺取即可。

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
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator () (a...); }
} read;

const int maxn = 200005;
int x[maxn];
ll pre[maxn];
ll f[maxn];

ll a, b;
inline ll trans (int j, int i) {
	return f[j] + b * (pre[i] - pre[j] - x[j] * ll(i - j))
		+ a * (x[i] - x[j]);
}

int main () {
	int T = read;
	while (T --) {
		int n = read;
		read(a, b);
		for (int i = 1; i <= n; i ++) read(x[i]);
		for (int i = 1; i <= n; i ++) pre[i] = pre[i - 1] + x[i];
		int j = 0;
		ll ans = pre[n] * b;
		for (int i = 1; i <= n; i ++) {
			while (j + 1 < i and trans(j + 1, i) < trans(j, i))
				++ j;
			f[i] = trans(j, i);
			ans = std::min(ans, trans(i, n) - a * (x[n] - x[i]));
		}
		printf("%lld\n", ans);
	}
}
