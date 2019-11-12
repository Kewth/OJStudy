#if 0
2019.11.12

套路推导，将 lcm 换为 gcd ，枚举 gcd ，得到一个互质的限制，换成莫比乌斯函数，
然后合理调整枚举顺序，得到 ans = n * (f * g)(n) ，
其中 f(n) = n (n + 1) / 2, g(n) = sum_{d|n} mu(d) d 。
g 用埃筛, f 直接算，然后搞 f, g 的狄利克雷卷积即可。

刷新三观，原来 i * j < n 不能换成 j < n / i （只有小于等于才能这么换），
神 tm 一直这么写没出过错。
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

const int maxn = 1000005;
int minp[maxn], mu[maxn];
ll f[maxn], g[maxn], h[maxn];

int main() {
	mu[1] = minp[1] = 1;
	for(int i = 2; i < maxn; i ++) {
		int &p = minp[i];
		if(!p) {
			p = i;
			for(ll j = 1ll * p * p; j < maxn; j += p)
				if(!minp[j])
					minp[j] = p;
		}
		if(minp[i / p] != p)
			mu[i] = - mu[i / p];
	}

	for(int i = 1; i < maxn; i ++)
		for(int j = i; j < maxn; j += i)
			g[j] += mu[i] * i;

	for(int i = 1; i < maxn; i ++)
		f[i] = 1ll * i * (i + 1) >> 1;

	for(int i = 1; i < maxn; i ++)
		for(int j = 1; i * j < maxn; j ++)
			h[i * j] += f[i] * g[j];

	int q = read;
	while(q --) {
		int n = read;
		printf("%lld\n", h[n] * n);
	}
}
