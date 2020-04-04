#if 0
2020.02.11

绝了，狄利克雷前缀和竟然如此 NB 。

设 f(x) 表示 gcd = x 的集合数量，g(x) 表示与 x 互质的数的数量。
那么枚举集合的 gcd ，可以知道 sum(f(x) g(x) [x > 1]) 即为答案。

考虑计算 g ，g(x) 的互质条件用莫比乌斯函数拆开，
不难得到 g(x) = sum(mu(d) h(d) [d | x]) ，
其中 h(d) 表示 d 的倍数的数的数量，
那么 g 就是 mu * h 的狄利克雷前缀和。

考虑计算 h ，根据定义 h(x) = sum(c(k) [x | k]) ，
其中 c(k) 表示数列中 k 的个数。
那么 h 就是 c 的狄利克雷后缀和。

考虑计算 f ，gcd 恰好为 x 的集合数量不好统计，
不妨设 F(x) 表示 gcd 为 x 的倍数的集合数量，
也就是所有数都是 x 的倍数的集合数量，有 F(x) = 2^h(x) - 1 ，
而 F 和 f 的关系是显而易见的： F(x) = sum(f(k) [x | k]) 。
已知 F 求 f ，众所周知可以莫比乌斯反演，
但是事实上 F 是 f 的狄利克雷后缀和，而后缀和的逆运算是后缀差分，
那么只需要对 F 做“狄利克雷后缀差分”即可得到 f 。

总复杂度 O(WloglogW) ，
很多本来调和级数 O(WlogW) 的地方都能用狄利克雷后缀和优化。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 10000005, mod = 1000000007;
int f[maxn], g[maxn], h[maxn];
int pow2[maxn];
int prime[664580], pp;
bool nop[maxn];

int main() {
	int n = read;
	while(n --)
		++ h[read];

	n = 10000000;
	g[1] = 1;
	for(int i = 2; i <= n; i ++) {
		if(!nop[i]) {
			prime[++ pp] = i;
			g[i] = -1;
		}
		for(int k = 1; prime[k] <= n / i; k ++) {
			nop[i * prime[k]] = 1;
			if(!(i % prime[k])) break;
			g[i * prime[k]] = - g[i];
		}
	}

	for(int k = 1; k <= pp; k ++)
		for(int x = n / prime[k]; x; x --)
			h[x] += h[x * prime[k]];

	for(int x = 1; x <= n; x ++)
		g[x] *= h[x];
	for(int k = 1; k <= pp; k ++)
		for(int x = 1; x <= n / prime[k]; x ++)
			g[x * prime[k]] += g[x];

	pow2[0] = 1;
	for(int x = 1; x <= n; x ++)
		pow2[x] = (pow2[x - 1] << 1) % mod;

	for(int x = 1; x <= n; x ++)
		f[x] = pow2[h[x]] - 1;
	for(int k = 1; k <= pp; k ++)
		for(int x = 1; x <= n / prime[k]; x ++) {
			f[x] -= f[x * prime[k]];
			if(f[x] < 0) f[x] += mod;
		}

	ll ans = 0;
	for(int x = 2; x <= n; x ++)
		(ans += 1ll * f[x] * g[x]) %= mod;
	printf("%lld\n", ans);
}
