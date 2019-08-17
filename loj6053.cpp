#if 0
2019.08.02

min25 模板，对于质数 p ，f(p) = p - 1 或者 f(2) = 3 。
那么 sum(f(p)) 可以找到两个完全积性函数 f1(p) = 1 和 f2(p) = p 的 sum(f2(p)) - sum(f1(p)) + 2 求出。
#endif
#include <cstdio>
#include <vector>
#include <cmath>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;
inline lolong input() { lolong x; scanf("%lld", &x); return x; }

const int maxs = 200005, mod = 1000000007;
bool not_p[maxs];
int prime[maxs];
lolong g1[maxs], g2[maxs], g[maxs];
lolong sg1[maxs], sg2[maxs], sg[maxs];
lolong w[maxs];

lolong n, m, s, p;
inline int id(lolong x) {
	return x <= s ? x : m - (n / x) + 1;
}

lolong S(lolong i, int j) {
	if(prime[j] > i) return 0;
	lolong res = g[id(i)] - sg[j] + mod;
	for(int k = j + 1; k <= p and 1ll * prime[k] * prime[k] <= i; k ++) {
		int e = 1;
		lolong pr = prime[k];
		while(pr <= i) {
			res += (prime[k] ^ e) * (S(i / pr, k) + (e > 1)) % mod;
			pr *= prime[k];
			e ++;
		}
	}
	res %= mod;
	// debug("S(%lld, %d) = %lld (p=%d)\n", i, j, res, prime[j]);
	return res;
}

int main() {
	n = input();
	s = sqrt(n);
	for(int i = 2; i <= s; i ++)
		if(not not_p[i]) {
			prime[++ p] = i;
			for(lolong j = 1ll * i * i; j <= s; j += i)
				not_p[j] = true;
			sg1[p] = (sg1[p - 1] + 1) % mod;
			sg2[p] = (sg2[p - 1] + i) % mod;
			sg[p] = (sg[p - 1] + (i ^ 1)) % mod;
		}
	for(lolong l = 1, r; l <= n; l = r + 1) {
		w[++ m] = r = n / (n / l);
		g1[m] = w[m] - 1;
		if(w[m] & 1)
			g2[m] = ((2 + w[m]) % mod * ((w[m] - 1) >> 1) % mod) % mod;
		else
			g2[m] = (((2 + w[m]) >> 1) % mod * (w[m] - 1) % mod) % mod;
		// debug("g2[%lld, %d] = %lld\n", w[m], 0, g2[m]);
	}
	for(int j = 1; j <= p; j ++) {
		// debug("prime[%d] = %d\n", j, prime[j]);
		for(int i = m; i and w[i] >= 1ll * prime[j] * prime[j]; i --) {
			g1[i] = g1[i] - (g1[id(w[i] / prime[j])] - sg1[j - 1]) + mod;
			g2[i] = g2[i] - prime[j] * (g2[id(w[i] / prime[j])] - sg2[j - 1] + mod) % mod + mod;
			g1[i] %= mod;
			g2[i] %= mod;
		}
		// for(int i = 1; i <= m; i ++)
			// debug("g2[%lld, %d] = %lld\n", w[i], j, g2[i]);
	}
	for(int i = 1; i <= m; i ++)
		g[i] = (g2[i] - g1[i] + 2 + mod) % mod;
	g[1] = 0;
	// for(int i = 1; i <= m; i ++)
		// debug("g[%lld] = %lld\n", w[i], g[i]);
	printf("%lld\n", (S(n, 0) + 1) % mod);
}
