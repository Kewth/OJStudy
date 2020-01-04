#if 0
2020.01.04

和 51nod 的“斐波那契最小公倍数”一个套路，
将 min-max 容斥扩展到 gcd-lcm 容斥然后根据 gcd(f[x], f[y]) = f[gcd(x, y)] 推式子，
莫比乌斯反演一下最后得到 g[i] 的式子，g[i] 的式子直接计算是 O(nlogn) 的，
但 h[i] = g[i] / g[i - 1] 很好计算，可以在 O(nlogn) 时间计算出 h 再做前缀积。
#endif
#include <cstdio>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
} read;

const int maxn = 1000005;
int mu[maxn], minp[maxn];
ll f[maxn], invf[maxn], g[maxn];

inline ll power(ll x, int k, int mod) {
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
	int N = 1000000;
	mu[1] = 1;
	for(int x = 2; x <= N; x ++) {
		int &p = minp[x];
		if(!p) {
			p = x;
			if(x <= N / x)
				for(int y = x * x; y <= N; y += x)
					if(!minp[y])
						minp[y] = x;
		}
		if(minp[x / p] != p) mu[x] = - mu[x / p];
	}
	invf[1] = f[1] = 1;

	int T = read;
	while(T --) {
		int n = read, mod = read;
		for(int i = 2; i <= n; i ++) f[i] = (2 * f[i - 1] + f[i - 2]) % mod;
		for(int i = 2; i <= n; i ++) invf[i] = power(f[i], -1, mod);
		for(int i = 1; i <= n; i ++) g[i] = 1;
		for(int i = 1; i <= n; i ++)
			for(int j = i; j <= n; j += i)
				if(mu[i] == 1) (g[j] *= f[j / i]) %= mod;
				else if(mu[i] == -1) (g[j] *= invf[j / i]) %= mod;
		for(int i = 2; i <= n; i ++)
			(g[i] *= g[i - 1]) %= mod;
		ll ans = 0;
		for(int i = 1; i <= n; i ++)
			(ans += i * g[i]) %= mod;
		printf("%lld\n", ans);
	}
}
