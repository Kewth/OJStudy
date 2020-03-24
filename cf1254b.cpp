#if 0
2020.03.23

求出所有数的和 sum ，最后的 gcd 一定是 sum 的因子。
对 sum 质因数分解，然后对于每个质因子 p ，钦定最后所有数都是 p 的倍数求答案。
设 b[i] = a[i] % p ，只需考虑序列 b ，最后所有数都一定恰好为 p 或 0 。
而且最后任意一个 p 都是由一段连续区间构成的。
找出所有这样的连续区间，然后选择带权中点作为最后 p 的位置即可。
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

const int maxn = 1000005;
ll a[maxn], b[maxn];

ll ans = 1000000000000000000;
void force (int n, ll x) {
	/* debug("x = %lld\n", x); */
	ll res = 0, tmp = 0, sum = 0;
	for (int i = 1; i <= n; i ++) sum += b[i] = a[i] % x;
	for (int l = 1, r; sum; l = r) {
		ll now = b[l];
		r = l;
		while (now < x) now += b[++ r];
		/* if (r > n) return; */
		tmp = now - x;
		/* debug("%d %d %lld\n", l, r, tmp); */
		b[r] -= tmp;
		sum -= x;
		int p = l;
		ll pre = b[l];
		while (pre < x - pre) pre += b[++ p];
		for (int i = l; i <= r; i ++)
			res += b[i] * std::abs(i - p);
		b[r] = tmp;
	}
	ans = std::min(ans, res);
}

int main () {
	int n = read;
	ll sum = 0;
	for (int i = 1; i <= n; i ++)
		sum += a[i] = read;

	if (sum == 1) return puts("-1"), 0;

	for (ll d = 2; d * d <= sum; d ++)
		if (sum % d == 0) {
			force(n, d);
			while (sum % d == 0) sum /= d;
		}
	if (sum > 1)
		force(n, sum);

	printf("%lld\n", ans);
}
