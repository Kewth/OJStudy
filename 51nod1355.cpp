#if 0
2020.01.04

lcm 就是对质因子的次数取 max ，gcd 就是取 min 。
将 min-max 容斥推广到 lca-gcd 容斥，就是这样：
lcm(S) = prod_{T} gcd(T)^{(-1)^{|T|-1}}
而根据 gcd 的辗转相减和斐波那契的递推，有 gcd(F[x], F[y]) = F[gcd(x, y)] 。
那么要求的就是 prod_{T} F[gcd(T)]^{(-1)^{|T|-1}} 。
枚举 x = gcd(T) ，设其对应的 F[x] 的次数的和为 a[x] ，考虑求出所有 a[x] 。
a[x] = sum_{T} [gcd(T)=x] (-1)^{|T|-1}
套路推一推式子，用莫比乌斯函数化掉 gcd ，得到 a[x] = sum_{k} mu[k] f[xk] 。
其中 f[x] 为 1 当且仅当给定的集合中存在 x 的倍数。
那么 VlogV 预处理 f ，然后 VlogV 计算 a ，然后计算所有斐波那契数求个快速幂即可。
#endif
#include <cstdio>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
} read;

const int maxn = 50005, maxv = 1000005, mod = 1000000007;
bool contain[maxv];
ll f[maxv];
int mu[maxv], minp[maxv];

inline ll power(ll x, int k) {
	if(k < 0) k += mod - 1;
	ll res = 1;
	while(k) {
		if(k & 1) (res *= x) %= mod;
		(x *= x) %= mod;
		k >>= 1;
	}
	return res;
}

int main() {
	int n = read;
	for(int i = 1; i <= n; i ++)
		contain[read] = 1;

	int V = 1000000;
	for(int x = 1; x <= V; x ++)
		for(int k = 1; x * k <= V and !contain[x]; k ++)
			contain[x] |= contain[x * k];

	mu[1] = 1;
	for(int x = 2; x <= V; x ++) {
		if(!minp[x]) {
			minp[x] = x;
			if(x <= V / x)
				for(int y = x * x; y <= V; y += x)
					if(!minp[y])
						minp[y] = x;
		}
		if(minp[x / minp[x]] != minp[x])
			mu[x] = - mu[x / minp[x]];
	}

	f[1] = 1;
	for(int x = 2; x <= V; x ++)
		f[x] = (f[x - 1] + f[x - 2]) % mod;

	ll ans = 1;
	for(int x = 1; x <= V; x ++) {
		int a = 0;
		for(int k = 1; x * k <= V; k ++)
			if(contain[x * k])
				a += mu[k];
		/* if(a) debug("%d %lld %d\n", x, f[x], a); */
		(ans *= power(f[x], a)) %= mod;
	}

	printf("%lld\n", ans);
}
