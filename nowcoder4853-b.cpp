#if 0
2020.03.27

对于三个点，其曼哈顿距离和就是 2 (max(x) - min(x) + max(y) - min(y)) 。
那么 x, y 两维可以分开算，每一维排序后枚举 max 和 min 即可。
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

const int maxn = 1005, mod = 998244353;
int x[maxn], y[maxn];

int main () {
	int n = read;
	for (int i = 1; i <= n; i ++)
		read(x[i], y[i]);
	std::sort(x + 1, x + n + 1);
	std::sort(y + 1, y + n + 1);
	ll ans = 0;
	for (int l = 1; l <= n; l ++)
		for (int r = l + 2; r <= n; r ++) {
			ans += 1ll * (x[r] - x[l]) * (r - l - 1);
			ans += 1ll * (y[r] - y[l]) * (r - l - 1);
			ans %= mod;
		}
	printf("%lld\n", (ans << 1) % mod);
}
