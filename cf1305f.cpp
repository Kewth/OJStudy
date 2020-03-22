#if 0
2020.03.21

如果令最终的 gcd 为 2 的倍数，可以发现答案的上界是 n 。
那么有至少一半的点最终变化大小不超过 1 。
随机选择一个点，设其大小为 x ，把 gcd 钦定为 x - 1, x, x + 1 分别暴力计算答案。
这样就有至少 1/2 的概率可以算出最优解，多次随机取点就可以使得概率足够大。
神奇的是原生的 rand() 会被卡，需要扩大 rand 值域或者使用 mt19937 。
#endif
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <random>
#include <chrono>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
} read;

const int maxn = 200005;
ll a[maxn];

ll ans;
void solve (ll x, int n) {
	ll res = 0;
	for (int i = 1; i <= n; i ++) {
		ll y = a[i] % x;
		if (y == a[i]) res += x - y;
		else res += std::min(y, x - y);
	}
	/* debug("%lld : %lld\n", x, res); */
	ans = std::min(ans, res);
}

void test (ll x, int n) {
	for (ll p = 2; p * p <= x; p ++)
		if (x % p == 0) {
			solve(p, n);
			while (x % p == 0)
				x /= p;
		}
	if (x > 1)
		solve(x, n);
}

std::mt19937 rng(unsigned(std::chrono::steady_clock::now().time_since_epoch().count()));

int mrand() {
	return rand() << 15 | rand();
}

int main () {
	char *cp = new char;
	srand((unsigned)(unsigned long long)cp);
	delete cp;

	int n = read;
	for (int i = 1; i <= n; i ++)
		a[i] = read;
	ans = n;

	int t = 35;
	while (t --) {
        /* int i = std::uniform_int_distribution<int>(0, n - 1)(rng); */
		int i = 1 + mrand() % n;
		/* int i = 1 + rand() % n; */
		test(a[i] - 1, n);
		test(a[i], n);
		test(a[i] + 1, n);
	}

	printf("%lld\n", ans);
}
