#if 0
2020.02.02

本质上就是求几个自然数幂和，略。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	inline operator char () { char x[3]; return scanf("%s", x), *x; }
} read;

const int maxn = 55, mod = 1000000007;

ll power(ll x, int k) {
	if(k < 0) k += mod - 1;
	ll res = 1;
	while(k) {
		if(k & 1) (res *= x) %= mod;
		(x *= x) %= mod;
		k >>= 1;
	}
	return res;
}

ll f[maxn], fac[maxn];
ll powersum(ll n, int m) {
	n %= mod;
	for(int i = 1; i <= m + 1; i ++)
		f[i] = (f[i - 1] + power(i, m)) % mod;

	if(n <= m + 1)
		return f[n];

	ll ans = 0;
	for(int i = 0; i <= m + 1; i ++) {
		ll now = f[i];
		(now *= power(n - i, -1)) %= mod;
		(now *= power(fac[i], -1)) %= mod;
		(now *= power(fac[m + 1 - i], -1)) %= mod;
		if((m + 1 - i) & 1)
			now = mod - now;
		ans += now;
	}
	ans %= mod;
	for(int i = 0; i <= m + 1; i ++)
		(ans *= n - i) %= mod;

	return ans;
}

ll a[maxn];
int main() {
	fac[0] = 1;
	for(int i = 1; i < maxn; i ++)
		fac[i] = fac[i - 1] * i % mod;

	int T = read;
	while(T --) {
		ll n = read;
		int m = read;
		for(int i = 1; i <= m; i ++)
			a[i] = read;
		std::sort(a + 1, a + m + 1);

		if(a[m] < n)
			a[++ m] = ++ n;

		ll ans = 0;
		for(int i = 1; i <= m; i ++) {
			ans += powersum(n - a[i - 1], m);
			for(int j = i; j <= m; j ++)
				ans += mod - power(a[j] - a[i - 1], m);
		}
		printf("%lld\n", ans % mod);
	}
}
