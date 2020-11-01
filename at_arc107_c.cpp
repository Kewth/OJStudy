/*
 * Author: Kewth

 * Date:
  2020.11.01

 * Solution:
  显然行和列是独立的，考虑行的合法排列数，把两个可以交换的行连边，那么每个联通块独立，
单个联通块的方案数就是其大小的阶乘。

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
	template<class T> inline void operator () (T &x) { x = *this; }
} read;

const int maxn = 55, mod = 998244353;
int a[maxn][maxn];
int fa[maxn], size[maxn];
ll fac[maxn];

int find (int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }

ll ans = 1;
void solve (int n, int m) {
	for (int i = 1; i <= n; i ++) fa[i] = i, size[i] = 1;
	for (int i = 1; i <= n; i ++) {
		for (int j = 1; j <= n; j ++) {
			bool ok = 1;
			for (int k = 1; k <= n; k ++)
				ok &= a[i][k] + a[j][k] <= m;
			if (ok) {
				int x = find(i), y = find(j);
				if (x != y)
					fa[x] = y, size[y] += size[x];
			}
		}
	}
	for (int i = 1; i <= n; i ++)
		if (fa[i] == i)
			(ans *= fac[size[i]]) %= mod;
}

int main () {
	int n = read, m = read;
	for (int i = 1; i <= n; i ++)
		for (int j = 1; j <= n; j ++)
			read(a[i][j]);
	fac[0] = 1;
	for (int i = 1; i <= n; i ++)
		fac[i] = fac[i - 1] * i % mod;
	solve(n, m);
	for (int i = 1; i <= n; i ++)
		for (int j = 1; j <= i; j ++)
			std::swap(a[i][j], a[j][i]);
	solve(n, m);
	printf("%lld\n", ans);
}
