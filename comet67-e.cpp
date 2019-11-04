#if 0
2019.11.02

如果已知伤害 k ，那么把 k 点伤害分配到 n 个敌人的方案就是在 k - 1 个空隙中插 n - 1 个板。
考虑将两个攻击上限分别为 b1, b2 的单位合并为一个，
设前者查 k 个板的方案数是 A[k], 后者是 B[k]，目标是求出合并后的 C[k] 。
讨论是否有板插在两者中间，不难得出 C[k] = sum{i+j=k} A[i] B[j] + sum_{i+j=k-1} A[i] B[j] 。
类似卷积的形式，把 A, B 的生成函数乘起来再乘 (1 + x) 即可得出 C 的生成函数。
那么对于一种单位就是多项式快速幂，不同单位直接卷积，中间模 x^n 即可。
现在唯一的问题是初始化一种单位的生成函数，设当前单位的伤害上限为 b ，
枚举打出的伤害，不难得出第 k 项系数是 sum_{i=1}^b C(i - 1, k) ，即 C(b, k + 1) 。
线性（或带 log ）处理一排组合数即可。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
} read;

const int maxn = 100005, mod = 998244353;
typedef ll Poly[maxn << 2];
typedef ll *pit;
ll inv[maxn];
int ra[maxn << 2];
ll G[maxn << 2];

inline ll power(ll x, ll k) {
	if(k < 0) k += mod - 1;
	ll res = 1;
	while(k) {
		if(k & 1) (res *= x) %= mod;
		(x *= x) %= mod;
		k >>= 1;
	}
	return res;
}

ll INV;
void NTT(pit a, int n, bool intt) {
	for(int i = 0; i < n; i ++)
		if(i < ra[i])
			std::swap(a[i], a[ra[i]]);

	for(int m = 1; m < n; m <<= 1)
		for(int i = 0; i < n; i += m << 1)
			for(int k = i; k < i + m; k ++) {
				ll a0 = a[k], a1 = a[k + m] *
					(intt ? G[n - (k - i) * (n / (m << 1))] :
					 G[(k - i) * (n / (m << 1))]) % mod;
				/* debug("G_%d^%d = %lld\n", m << 1, k - i, G[(k - i) * (n / (m << 1))]); */
				/* ll a0 = a[k], a1 = a[k + m] * g % mod; */
				a[k] = a0 + a1;
				a[k + m] = a0 - a1;
				if(a[k] >= mod) a[k] -= mod;
				if(a[k + m] < 0) a[k + m] += mod;
			}

	if(intt)
		for(int i = 0; i < n; i ++)
			(a[i] *= INV) %= mod;
}

Poly tmp;
void mul(pit a, pit b, int n, int len) {
	NTT(a, len, 0);
	for(int i = 0; i < len; i ++)
		tmp[i] = b[i];
	NTT(tmp, len, 0);
	for(int i = 0; i < len; i ++)
		(a[i] *= tmp[i]) %= mod;
	NTT(a, len, 1);
	for(int i = n; i < len; i ++)
		a[i] = 0;
}

void mulself(pit a, int n, int len) {
	NTT(a, len, 0);
	for(int i = 0; i < len; i ++)
		(a[i] *= a[i]) %= mod;
	NTT(a, len, 1);
	for(int i = n; i < len; i ++)
		a[i] = 0;
}

Poly f, g;

int main() {
	int n = read, m = read;

	inv[1] = 1;
	for(int i = 2; i <= n; i ++)
		inv[i] = (mod - mod / i) * inv[mod % i] % mod;

	int len = 1;
	while(len < n * 2)
		len <<= 1;

	INV = power(len, -1);

	ll gg = power(3, (mod - 1) / len);
	G[0] = G[len] = 1;
	for(int i = 1; i < len; i ++)
		G[i] = G[i - 1] * gg % mod;

	for(int i = 1; i < len; i ++)
		ra[i] = (ra[i >> 1] >> 1) | (len >> 1) * (i & 1);

	f[0] = 1;

	while(m --) {
		int a = read, b = read;

		g[0] = b;
		for(int i = 1; i < n; i ++)
			g[i] = g[i - 1] * (b - i) % mod * inv[i + 1] % mod;

		/* for(int i = 0; i < n; i ++) */
		/* 	debug(" %lld", g[i]); */
		/* debug(" in g\n"); */

		for(int i = n - 1; i; i --) {
			g[i] += g[i - 1];
			if(g[i] >= mod) g[i] -= mod;
		}

		while(a) {
			if(a & 1) mul(f, g, n, len);
			mulself(g, n, len);
			a >>= 1;
		}
	}

	// inv of (1 + x)
	for(int i = 0; i < n; i ++)
		g[i] = i & 1 ? mod - 1 : 1;
	mul(f, g, n, len);

	/* for(int i = 0; i < len; i ++) */
	/* 	debug(" %lld", f[i]); */
	/* debug("\n"); */

	printf("%lld\n", f[n - 1]);
}
