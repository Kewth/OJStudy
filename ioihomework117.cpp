/*
 * Author: Kewth

 * Date:
  2020.11.11

 * Solution:
  In blog.

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
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
} read;

const int X = 2096, maxx = X + 5, maxp = 320;
int prime[maxp], pp;
int nop[maxx];
int wei[maxp];
ll f[maxp][maxx]; // 范围内的集合数
ll g[maxp][maxx]; // 范围内的总长度
int pre[maxp], prewei;
char s[1000000];

void dfs (int n, int d, ll L, ll R, ll l, ll r) {
	if (R < l or L > r) return;
	if (!n) {
		// TODO: print
		int p = 0;
		s[p ++] = ' ';
		s[p ++] = ',';
		s[p ++] = ']';
		for (int i = d; i; i --) {
			for (int x = prime[pre[i]]; x; x /= 10) s[p ++] = '0' + x % 10;
			if (i > 1) s[p ++] = ' ', s[p ++] = ',';
		}
		s[p ++] = '[';
		std::reverse(s, s + p);
		/* s[p] = 0; */
		/* for (int i = 1; i <= d; i ++) debug("%d ", pre[i]); */
		/* debug("| %lld %lld |", L, R); */
		/* debug("%s\n", s); */
		for (ll i = L; i <= R; i ++)
			if (l <= i and i <= r)
				putchar(s[i - L]);
		return;
	}
	/* if (!d) debug(" >>> %d %lld %lld\n", n, L, R); */
	ll las = L - 1;
	for (int t = pre[d] + 1; prime[t] <= n; t ++) {
		ll now = (g[t][n] - g[t + 1][n] - g[t][n - 1] + g[t + 1][n - 1]) +
			prewei * (f[t][n] - f[t + 1][n] - f[t][n - 1] + f[t + 1][n - 1]);
		pre[d + 1] = t;
		prewei += wei[t];
		/* debug(" > %d %d, %lld %lld\n", n, prime[t], las + 1, las + now); */
		dfs(n - prime[t], d + 1, las + 1, las + now, l, r);
		prewei -= wei[t];
		las += now;
	}
}

int main () {
	for (int i = 2; i <= X; i ++)
		if (!nop[i]) {
			prime[++ pp] = i;
			for (int j = i + i; j <= X; j += i)
				nop[j] = 1;
			wei[pp] = 2;
			for (int x = i; x; x /= 10) ++ wei[pp];
		}
	prime[pp + 1] = X + 1;

	for (int t = pp; t; t --) {
		std::copy(f[t + 1], f[t + 1] + X + 1, f[t]);
		std::copy(g[t + 1], g[t + 1] + X + 1, g[t]);
		for (int n = X; n >= prime[t]; n --) {
			f[t][n] += f[t + 1][n - prime[t]] + 1;
			g[t][n] += g[t + 1][n - prime[t]] + 2 + wei[t] * (f[t + 1][n - prime[t]] + 1);
		}
	}
	/* debug("%lld\n", g[1][X]); */

	ll l = read, r = read;
	for (int n = 1; n <= X; n ++)
		dfs(n, 0, g[1][n - 1] + 1, g[1][n], l, r);
}
