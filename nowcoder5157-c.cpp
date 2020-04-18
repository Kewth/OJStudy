#if 0
2020.04.17

直接线段树维护即可，对于等差数列打标记，由于两个等差数列的和仍然是等差数列，标记是可以合并的。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
} read;

const int maxn = 200005, mod = 111546435;
ll ta[maxn << 2], tb[maxn << 2], seg[maxn << 3];

inline ll sum (ll a, ll b, ll k) {
	return (a * k + (k * (k - 1) / 2) % mod * b) % mod;
}

inline void update (int now, int L, int R) {
	seg[now] = (sum(ta[now], tb[now], R - L + 1) +
			seg[now << 1] + seg[now << 1 | 1]) % mod;
}

void modify (int now, int L, int R, int l, int r, ll a, ll b) {
	if (r < L or l > R) return;
	if (l <= L and R <= r) {
		(ta[now] += a + (L - l) * b) %= mod;
		(tb[now] += b) %= mod;
		update(now, L, R);
		return;
	}
	int M = (L + R) >> 1;
	modify(now << 1, L, M, l, r, a, b);
	modify(now << 1 | 1, M + 1, R, l, r, a, b);
	update(now, L, R);
}

ll query (int now, int L, int R, int l, int r) {
	if (r < L or l > R) return 0;
	if (l <= L and R <= r) return seg[now];
	int kl = std::max(l, L);
	int kr = std::min(r, R);
	ll res = sum((ta[now] + (kl - L) * tb[now]) % mod, tb[now], kr - kl + 1);
	int M = (L + R) >> 1;
	res += query(now << 1, L, M, l, r);
	res += query(now << 1 | 1, M + 1, R, l, r);
	return res % mod;
}

int main () {
	int n = read;
	for (int i = 1; i <= n; i ++)
		modify(1, 1, n, i, i, read, 0);
	int q = read;
	while (q --) {
		int o = read;
		if (o == 1) {
			int l = read, r = read, a = read, b = read;
			modify(1, 1, n, l, r, a, b);
		}
		if (o == 2) {
			int l = read, r = read, m = read;
			/* debug("%lld\n", query(1, 1, n, l, r)); */
			printf("%lld\n", query(1, 1, n, l, r) % m);
		}
	}
}
