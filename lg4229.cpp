#if 0
2020.04.16

区间 max = h 可以转换为两个条件：区间所有数都不超过 h ，区间存在数等于 h 。
根据第一个条件，求出 up[i] 表示第 i 个点的限制。
而对于第二个条件，可以发现能满足这个条件的数一定是满足 up[i] 恰好等于 h 的数。
那么对于每个 h ，可以把对应的限制和点单独拿出来处理，不同的处理之间相互不影响。
那么问题转换为有若干区间一个序列和序列限制 x ，要求每个区间都必须有一个数恰好等于 x 。
DP 设 f[i][j] 表示考虑序列的前缀 i ，最后一个等于 x 的位置在 j ，这样的贡献和。

用线段树可以简单地把转移优化到 log ，而更精细的操作似乎可以优化到 O(1) 。
然而快速幂和计算 up 仍然是一个瓶颈。
#endif
#include <cstdio>
#include <algorithm>
#include <vector>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator () (a...); }
} read;

const int maxn = 505, mod = 998244353;
struct Shit { int l, r, x; } s[maxn];
int tmp[maxn << 1], tp;
int up[maxn << 1];
ll f[maxn << 1][maxn << 1];
int lpos[maxn << 1];

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

ll solve (int x) {
	/* debug("solve\n"); */
	f[0][0] = 1;
	int las = 0, max = 0;
	for (int r = 1; r <= tp; r ++) {
		if (up[r] == x) {
			std::fill(f[r], f[r] + r + 1, 0);
			ll po1 = power(x, tmp[r] - tmp[r - 1]);
			ll po2 = power(x - 1, tmp[r] - tmp[r - 1]);
			for (int j = max; j <= las; j ++)
				(f[r][r] += f[las][j] * (po1 + mod - po2)) %= mod;
			max = std::max(lpos[r], max);
			for (int i = max; i <= las; i ++)
				f[r][i] = f[las][i] * po2 % mod;
			las = r;
			max = 0;
		} else
			max = std::max(lpos[r], max);
		/* for (int i = 0; i <= r; i ++) */
		/* 	debug(" %lld", f[r][i]); */
		/* if (up[r] == x) debug(" !"); */
		/* debug("\n"); */
	}
	ll ans = 0;
	for (int i = max; i <= tp; i ++)
		ans += f[las][i];
	return ans % mod;
}

int main () {
	int T = read;
	while (T --) {
		int n = read, m = read, lim = read;
		for (int i = 1; i <= m; i ++)
			read(s[i].l, s[i].r, s[i].x);
		std::sort(s + 1, s + m + 1, [] (Shit a, Shit b) {
					return a.x < b.x;
				});

		tp = 0;
		for (int i = 1; i <= m; i ++) {
			if (s[i].l > 1)
				tmp[++ tp] = s[i].l - 1;
			tmp[++ tp] = s[i].r;
		}
		tmp[++ tp] = n;
		std::sort(tmp + 1, tmp + tp + 1);
		tp = int(std::unique(tmp + 1, tmp + tp + 1) - tmp - 1);
		for (int i = 1; i <= m; i ++) {
			s[i].l = int(std::lower_bound(tmp, tmp + tp + 1, s[i].l - 1) - tmp) + 1;
			s[i].r = int(std::lower_bound(tmp, tmp + tp + 1, s[i].r) - tmp);
		}

		for (int i = 1; i <= tp; i ++) up[i] = lim + 1;
		for (int i = 1; i <= m; i ++)
			for (int j = s[i].l; j <= s[i].r; j ++)
				up[j] = std::min(up[j], s[i].x);

		ll ans = 1;
		for (int l = 1, r; l <= m; l = r + 1) {
			r = l;
			while (r < m and s[r + 1].x == s[r].x) ++ r;
			std::fill(lpos, lpos + tp + 1, 0);
			for (int i = l; i <= r; i ++)
				lpos[s[i].r] = std::max(lpos[s[i].r], s[i].l);
			(ans *= solve(s[l].x)) %= mod;
		}

		for (int i = 1; i <= tp; i ++)
			if (up[i] > lim)
				(ans *= power(lim, tmp[i] - tmp[i - 1])) %= mod;

		printf("%lld\n", ans);
	}
}
