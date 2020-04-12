#pragma GCC optimize(3)
#if 0
2020.04.12

屑。

显然题目可以分为完全不相干的四个部分。

第一个部分 - 对于矩阵 a[i][j] = i j gcd(i, j) 操作。
单点询问：
傻逼。
子矩阵查询：
推式子，变成了数轮题，可以得到答案就是 sum{i^2 S(floor(n/i))^2 phi(i)} 。
其中 S(x) 是 1 到 x 的和。
直接线性筛 + 整除分块，前者会有点爆炸，可以使用杜教筛代替，和筛 phi 差不多。
行列式查询：
高消不会影响这个操作，因此这个操作稍后讨论。

第二个部分 - 求出 a 高消成上三角的矩阵 b 。
找找规律，设 f[i] = b[i][i] / i ，有 f[i] = i^2 - sum{[j|i and j<i] f[j] i / j} 。
而对于 b[i][j] ，有 b[i][j] = [i|j] f[i] j 。
但是这里复杂度是 5e6 log 的，可以用狄利克雷前缀和优化到 5e6 loglog 。
ps : 事实上 f[i] = phi(i) i

第三个部分 - 对于矩阵 b 操作。
单点询问：
傻逼。
子矩阵查询：
还是推式子，没营养，略。
行列式查询：
自然就是 b[i][i] 的前缀积，不知道这个操作和单点查有什么意义。

第四个部分 - 淦他妈卡常。
多交几次，充分利用评测机波动。
#endif
#include <cstdio>
#include <algorithm>
#include <bitset>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef size_t si;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator () (a...); }
} read;

const int maxn = 5000005, mod = 998244353;
std::bitset<100000005> nop;
int prime[5761460], pp; // 5761455 prime in [1, 1e8]
int phi[100000005];
int f[maxn], g[maxn], h[maxn];

inline void __a (int &x) { if (x >= mod) x -= mod; }

int fuck_n = 10000000;
void init (int n, int m) {
	n = std::max(n, m);
	if (n > fuck_n) n = fuck_n;
	phi[1] = 1;
	for (int i = 2; i <= n; i ++) {
		if (!nop[si(i)]) prime[++ pp] = i, phi[i] = i - 1;
		for (int j = 1; j <= pp; j ++) {
			int p = prime[j];
			if (p > n / i) break;
			nop[si(i * p)] = 1;
			if (!(i % p)) {
				phi[i * p] = phi[i] * p;
				break;
			}
			phi[i * p] = phi[i] * (p - 1);
		}
	}

	g[0] = 1;
	for (int i = 1; i <= m; i ++)
		h[i] = f[i] = 1ll * phi[i] * i % mod;
	for (int i = 1; i <= pp and prime[i] <= m; i ++) {
		int p = prime[i];
		for (int x = p; x <= m; x += p)
			__a(h[x] += h[x / p]);
	}
	for (int i = 1; i <= m; i ++) {
		g[i] = 1ll * g[i - 1] * f[i] % mod * i % mod;
		h[i] = (h[i - 1] + 1ll * h[i] * i) % mod;
	}

	for (int i = 1; i <= n; i ++)
		phi[i] = (1ll * phi[i] * i % mod * i + phi[i - 1]) % mod;
}

const int maxq = 100005;
int qo[maxq];
ll qx[maxq], qy[maxq];

int tmp[20000];
int w[20000];

inline int id (int x, int n, int m) {
	if (!x or x <= n / x) return x;
	return m - n / x + 1;
}

int main () {
	int q = read;
	int N = 1, M = 1;
	for (int i = 1, eatshit = 0; i <= q; i ++) {
		int o = qo[i] = int(read) + eatshit;
		if (o == 1) eatshit = 10;
		if (o == 2 or o == 12) read(qx[i], qy[i]);
		if (o == 3 or o == 13) read(qx[i]);
		if (o == 4 or o == 14) read(qx[i]);
		if (o == 3) N = std::max(N, int(qx[i]));
		if (o == 4 or o > 10) M = std::max(M, int(qx[i]));
	}
	init(N, M);

	for (int i = 1; i <= q; i ++) {
		int o = qo[i];
		/* debug("%d\n", o); */

		if (o == 2) {
			ll x = qx[i], y = qy[i];
			ll d = std::__gcd(x, y);
			printf("%lld\n", (x % mod) * (y % mod) % mod * d % mod);
		}

		if (o == 12) {
			int x = int(qx[i]), y = int(qy[i]);
			if (y % x) puts("0");
			else printf("%lld\n", 1ll * f[x] * y % mod);
		}

		if (o == 3) {
			int n = int(qx[i]), m = 0;
			ll ans = 0;
			for (int l = 1, r; l <= n; l = r + 1)
				w[++ m] = r = n / (n / l);
			for (int j = 1; j <= m; j ++)
				if (w[j] <= fuck_n)
					tmp[j] = phi[w[j]];
				else {
					auto G = [] (int x) -> ll {
						return x * __int128(x + 1) * (2 * x + 1) / 6 % mod;
					};
					int W = w[j], sum = tmp[j] = 0;
					for (int l = 2, r; l <= W; l = r + 1) {
						r = W / (W / l);
						sum = (sum + (G(r) + mod - G(l - 1)) * tmp[id(W / l, n, m)]) % mod;
					}
					ll s = 1ll * W * (W + 1) / 2 % mod;
					tmp[j] = (s * s + mod - sum) % mod;
				}
			for (int j = 1; j <= m; j ++) {
				int l = w[j - 1] + 1;
				ll d = n / l;
				ll s = d * (d + 1) / 2 % mod;
				(s *= s) %= mod;
				(ans += s * (tmp[j] - tmp[j - 1] + mod)) %= mod;
			}
			printf("%lld\n", ans);
		}

		if (o == 13) {
			int k = int(qx[i]);
			printf("%d\n", h[k]);
		}

		if (o == 4 or o == 14) {
			int k = int(qx[i]);
			printf("%d\n", g[k]);
		}
	}
}
