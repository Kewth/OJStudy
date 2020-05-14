#if 0
2020.05.08

  二分答案，贪心检查。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
} read;

const int maxn = 100005;
ll a[maxn], b[maxn];

bool check (int n, ll d) {
	for (int i = 1; i <= n; i ++)
		b[i] = a[i] + d / n;
	for (int i = 1; i <= d % n; i ++)
		++ b[i];
	std::sort(b + 1, b + n + 1);
	ll x = 0, m = b[(1 + n) >> 1];
	/* debug("check %lld\n", d); */
	for (int i = 1; i <= n; i ++) {
		x += std::abs(b[i] - m);
		if (x > d) return 0;
	}
	/* for (int i = 1; i <= n; i ++) */
	/* 	debug(" %lld", b[i]); */
	/* debug(" -> %lld\n", x); */
	return 1;
}

int main () {
	int n = read;
	for (int i = 1; i <= n; i ++)
		read(a[i]);

	ll l = 0, r = 1000000000000000000;
	while (l < r) {
		ll mid = (l + r) >> 1;
		if (check(n, mid)) r = mid;
		else l = mid + 1;
	}
	printf("%lld\n", l);
}
