#if 0
2019.07.13

记 1 和所有质因子次数都大于 1 的数为 MAGIC ，
那么 n 以内 MAGIC 的数量是 O(sqrt(n)) 的。
根据 MAGIC 的这个性质，考虑找出两个积性函数 G, H ，使得 F = G * H ，
若 G 只在 MAGIC 上有值且 H 的前缀和 S 好求的话，由
ANS = \sum_{i=1}^n \sum_{d|x} G(d) H(d/x) = \sum_{d=1}^n G(d) S(n/d)
可以枚举 MAGIC 快速计算答案。

对于质数 p ，由 F(p) = H(1) G(p) + G(1) H(p) = H(p) 得 H(p) = p^k 。
干脆使 H(x) = x^k ，考虑如何构造对应的 G 。

F(p^m) = \sum_{i=0}^m G(p^i) H(p^(m-i))       (1)
p^k = \sum_{i=0}^m G(p^i) p^(km-ki)           (1) -> (2)
p^k = \sum_{i=0}^{m+1} G(p^i) p^(km+k-ki)     (2) -> (3)
p^(2k) = \sum_{i=0}^m G(p^i) p^(km+k-ki)      (2) -> (4)
p^k - p^(2k) = G(p^(m+1))                     (3) - (4) -> (5)

因此对于质数 p 有 G(p^m) =
1, m=0
0, m=1
p^k - p^(2k), m>1

已经构造出 G, H ，考虑实现。
< 求 H 的前缀和 S > 可以知道 S 最终是一个 (k + 1) 的多项式，
因此可以暴力计算 1~(k+2) 的 S 的值并通过拉格朗日插值 O(k) 求出 S(x) 。
< 枚举 MAGIC > MAGIC 的质因子一定是 sqrt(n) 以内的，
筛出 sqrt(n) 以内的所有质数，再枚举每个质数的次数即可，期间可以计算出 G 。

需要注意的是，时时刻刻需要防止爆 long long ，
比较 a * b 与 c 的大小用 a > c / b 代替 a * b > c ，这是等价的。
#endif
#include <cstdio>
#include <cmath>
#include <cassert>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;
inline lolong input() { lolong x; scanf("%lld", &x); return x; }

const int maxm = 105, maxs = 4000000, mod = 1000000007;
lolong s[maxm];
lolong B[maxm];
int pri[maxs], pp, pripow[maxs];
bool not_pri[maxs];

inline lolong power(lolong x, int k) {
	lolong res = 1;
	x %= mod;
	if(k < 0) k += mod - 1;
	while(k) {
		if(k & 1) (res *= x) %= mod;
		(x *= x) %= mod;
		k >>= 1;
	}
	return res;
}

inline void sieve(int n, int m) {
	assert(n < maxs);
	for(int i = 2; i <= n; i ++) {
		if(not not_pri[i]) {
			pp ++;
			pri[pp] = i;
			pripow[pp] = (power(i, m) - power(i, m << 1) + mod) % mod;
		}
		for(int j = 1; j <= pp; j ++) {
			int p = pri[j];
			if(1ll * i * p > n) break;
			not_pri[i * p] = true;
			if(i % p == 0) break;
		}
	}
}

inline void get_inv(lolong *a, lolong *inv, int n) {
	static lolong pre[maxm], invpre[maxm];
	pre[0] = 1;
	for(int i = 1; i <= n; i ++)
		pre[i] = pre[i - 1] * a[i] % mod;
	invpre[n] = power(pre[n], -1);
	for(int i = n; i; i --) {
		inv[i] = pre[i - 1] * invpre[i] % mod;
		invpre[i - 1] = a[i] * invpre[i] % mod;
	}
}

// FIXME: S(n, k) is wrong
inline lolong S(lolong x, int k) {
	static lolong a[maxm], inv[maxm];
	if(x <= k) return s[x];
	lolong res = 0, M = 1;
	for(int i = 1; i <= k; i ++)
		assert(x - i > 0);
	for(int i = 1; i <= k; i ++)
		a[i] = (x - i) % mod;
	for(int i = 1; i <= k; i ++)
		(M *= a[i]) %= mod;
	get_inv(a, inv, k);
	for(int i = 1; i <= k; i ++)
		res += M * B[i] % mod * inv[i] % mod * s[i] % mod;
	return res % mod;
}

int TOT = 0;
lolong search_magic(int i, lolong now, lolong n, int k, lolong g) {
	TOT ++;
	assert(now > 0 and now <= n);
	if(i > pp) {
		/* debug("magic=%lld: g=%lld, s=%lld\n", now, g, S(n / now, k)); */
		return g * S(n / now, k) % mod;
	}
	/* if(now * pri[i] > n or now * pri[i] * pri[i] > n) */
	if(now > n / pri[i] / pri[i])
		return search_magic(pp + 1, now, n, k, g);
	/* debug("%lld * %d\n", now, pri[i]); */
	lolong res = search_magic(i + 1, now, n, k, g);
	now *= pri[i];
	(g *= pripow[i]) %= mod;
	assert(now > 0);
	while(now <= n / pri[i]) {
		now *= pri[i];
		res += search_magic(i + 1, now, n, k, g);
	}
	return res % mod;
}

int main() {
	lolong n = input();
	int m = int(input());
	for(int i = 1; i <= m + 2; i ++)
		s[i] = (s[i - 1] + power(i, m)) % mod;
	for(int i = 1; i <= m + 2; i ++) {
		B[i] = 1;
		for(int j = 1; j <= m + 2; j ++)
			if(i != j)
				(B[i] *= mod + i - j) %= mod;
		B[i] = power(B[i], -1);
	}
	sieve(int(sqrt(n)), m);
	printf("%lld\n", search_magic(1, 1, n, m + 2, 1));
	debug("TOT %d\n", TOT);
}
