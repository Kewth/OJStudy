#if 0
2019.11.03

vfk 牛逼，反演果然是魔术。
给定 f 关于 g 的递推式和 f 求 g ，就是反演，推式子一步一步反演即可，过程略。
另外 get 到了反演黑科技。
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

const int maxn = 300005, mod = 998244353;

inline ll power(ll x, int k) {
	while(k < 0) k += mod - 1;
	ll res = 1;
	while(k) {
		if(k & 1) (res *= x) %= mod;
		(x *= x) %= mod;
		k >>= 1;
	}
	return res;
}

// 莫反 f(n) = sum(g(d) [d | n])
inline void invf(ll *f, int n) {
	for(int i = 1; i <= n; i ++)
		for(int j = i << 1; j <= n; j += i)
			f[j] -= f[i];
	for(int i = 1; i <= n; i ++)
		((f[i] %= mod) += mod) %= mod;
}

// 莫反 f(d) = sum(g(n) [d | n])
inline void invf2(ll *f, int n) {
	for(int i = n; i; i --)
		for(int j = i << 1; j <= n; j += i)
			f[i] -= f[j];
	for(int i = 1; i <= n; i ++)
		((f[i] %= mod) += mod) %= mod;
}

ll f[maxn];
ll h[maxn];
ll mu[maxn];
ll invd[maxn];

int main() {
	int n = read, c = read, d = read, q = read;

	mu[1] = 1;
	invf(mu, n);

	for(int i = 1; i <= n; i ++)
		h[i] = power(i, c - d);
	invf(h, n);

	for(int i = 1; i <= n; i ++)
		h[i] = power(h[i], -1);

	for(int i = 1; i <= n; i ++)
		invd[i] = power(i, -d);

	while(q --) {
		for(int i = 1; i <= n; i ++)
			read(f[i]);

		for(int i = 1; i <= n; i ++)
			(f[i] *= invd[i]) %= mod;

		/* for(int i = 1; i <= n; i ++) */
		/* 	debug("%lld ", f[i]); */
		/* debug(" A\n"); */

		invf(f, n);

		/* for(int i = 1; i <= n; i ++) */
		/* 	debug("%lld ", f[i]); */
		/* debug(" B\n"); */

		for(int i = 1; i <= n; i ++)
			if(!h[i] and f[i]) {
				puts("-1");
				goto FUCK;
			}

		for(int i = 1; i <= n; i ++)
			(f[i] *= h[i]) %= mod;

		/* for(int i = 1; i <= n; i ++) */
		/* 	debug("%lld ", f[i]); */
		/* debug(" C\n"); */

		invf2(f, n);

		/* for(int i = 1; i <= n; i ++) */
		/* 	debug("%lld ", f[i]); */
		/* debug(" D\n"); */

		for(int i = 1; i <= n; i ++)
			(f[i] *= invd[i]) %= mod;

		for(int i = 1; i <= n; i ++)
			printf("%lld ", f[i]);
		puts("");

FUCK:;
	}
}
