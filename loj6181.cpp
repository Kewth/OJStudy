#if 0
2019.11.11

通过组合数和二项式定理不难证明，
当 i 为质数时 f(i) = -1 ， 当 mu(i) = 0 时 f(i) = 0 ，其他情况都有 f(i) = 1 。
分别求出 [f(i)=1] 的和再减去 [f(i)=-1] 的和即可，
后者就是统计范围内的质数个数，用 min25 筛可以很好处理，
前者就是 sum([mu(i) != 0]) ，再次简单容斥，统计 sum([mu(i) = 0]) ，
mu(i) = 0 的充要条件是 i 存在一个大于 1 的平方因子，
枚举这个平方因子 x ， x 的范围在 sqrt(n) 内，
然后所有 x^2 的倍数，也就是有 floor(n / x^2) 个 i 满足其存在平方因子 x 。
但是如果一个数有多个平方因子会算重，考虑如果 i 的最大平方因子是 x ，
利用 1 - sum_{d|x}(mu(d)) = [x > 1] 进行容斥，
统计每个 x^2 倍数是乘上容斥系数 mu(x) 即可。

踩了个坑，整除分块的个数是两倍 sqrt ，数组要开两倍。
#endif
#include <cstdio>
#include <cmath>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
} read;

ll n;
int s;
int m;
inline int id(ll x) {
	return x <= s ? int(x) : m - int(n / x) + 1;
}

const int maxs = 100010, mod = 998244353;
int prime[maxs], pp;
ll g[maxs << 1];
int mu[maxs];
ll w[maxs << 1];
bool nop[maxs];

int main() {
	read(n);
	s = int(sqrt(n));
	m = 0;

	for(ll l = 1, r; l <= n; l = r + 1) {
		w[++ m] = r = n / (n / l);
		g[m] = w[m] - 1;
	}

	mu[1] = 1;
	for(int i = 2; i <= s; i ++) {
		if(!nop[i]) {
			prime[++ pp] = i;
			mu[i] = -1;
		}
		for(int j = 1; j <= pp; j ++) {
			if(prime[j] > s / i) break;
			nop[i * prime[j]] = 1;
			if(!(i % prime[j])) break;
			mu[i * prime[j]] = - mu[i];
		}
	}

	ll ans = n;
	for(int i = 2; i <= s; i ++)
		ans += mu[i] * (n / i / i);
	debug("%lld\n", ans);

	for(int i = 1; i <= pp; i ++)
		for(int j = m; prime[i] <= w[j] / prime[i]; j --)
			 g[j] -= g[id(w[j] / prime[i])] - (i - 1);
	debug("%lld\n", g[m]);

	(ans -= g[m] * 2) %= mod;
	if(ans < 0) ans += mod;
	printf("%lld\n", ans);
}
