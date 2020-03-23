#if 0
2020.03.22

首先奇偶分类，a + c 和 b + d 的差值不超过 1 。
先全放 01 ，然后考虑把一些数 +2 。
可以发现任何 0 +2 后都一定合法，那么只要考虑如何把 1 +2 ，
使得可以把尽量少的 0 +2 后序列合法。
很显然 +2 的 1 是连续的，并且如果有 1 在边界，要从边界的 1 开始。
#endif
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

const int maxn = 100005;
int ans[maxn];

int main () {
	int a = read, b = read, c = read, d = read;
	if (std::abs(a + c - b - d) > 1) return puts("NO"), 0;

	if (a + c - b - d <= 0) ans[1] = 1;
	int n = a + b + c + d;

	for (int i = 2; i <= n; i ++)
		ans[i] = 1 - ans[i - 1];

	if (ans[1] == 1) {
		for (int i = 1; i <= d; i ++)
			ans[i * 2 - 1] += 2;
		for (int i = 1; i <= c; i ++)
			ans[i * 2] += 2;
	} else {
		for (int i = 1; i <= d; i ++)
			ans[i * 2] += 2;
		for (int i = 1; i <= c; i ++)
			ans[i * 2 - 1] += 2;
	}

/* 	for (int i = 1; i <= n; i ++) */
/* 		debug("%d ", ans[i]); */
/* 	debug("\n"); */

	for (int i = 2; i <= n; i ++)
		if (std::abs(ans[i] - ans[i - 1]) != 1)
			return puts("NO"), 0;

	puts("YES");
	for (int i = 1; i <= n; i ++)
		printf("%d ", ans[i]);
	puts("");
}
