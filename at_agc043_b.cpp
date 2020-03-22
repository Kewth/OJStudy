#if 0
2020.03.21

考虑一次操作后的序列，一定由 0, 1, 2 构成。
如果没有 2 ，那么 01 序列相邻作差可以看做求和模 2 ，通过组合数奇偶性即可得到最后的数。
考虑如果处理 2 ，如果没有 1 ，把所有数整体除以 2 （也就是把 2 看做 1 ）即可转换为 01 序列。
如果有 1 ，2 一定不会成为最后的答案，这个时候可以把 2 看做 0 。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 1000005;
char s[maxn];
int a[maxn];

int main () {
	int n = read;
	scanf("%s", s + 1);
	-- n;
	for (int i = 1; i <= n; i ++)
		a[i] = std::abs(s[i] - s[i + 1]);

	bool one = 0;
	for (int i = 1; i <= n; i ++)
		if (a[i] == 1)
			one = 1;

	if (one) {
		for (int i = 1; i <= n; i ++)
			if (a[i] == 2)
				a[i] = 0;
	}
	else {
		for (int i = 1; i <= n; i ++)
			if (a[i] == 2)
				a[i] = 1;
	}

	int ans = 0;
	int pc = 0;
	for (int i = 1; i <= n; i ++) {
		if (!pc and a[i]) ans ^= 1;
		if (i < n) {
			for (int x = n - i; !(x & 1); x >>= 1)
				++ pc;
			for (int x = i; !(x & 1); x >>= 1)
				-- pc;
		}
	}

	if (!one)
		ans <<= 1;
	printf("%d\n", ans);
}
