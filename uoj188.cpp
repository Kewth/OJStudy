#if 0
2019.10.15

问题实质是求 f 的前缀和，其中 f(x) 是合数 x 的次小质因子。
考虑像 min25 那样去用最小质因子筛 f 。
设 S(n, i) 表示前 n 个数最小质因子大于 P[i] 的 f 的和。
同样是枚举比 P[i] 大的 P[k] 以及指数 e ，
而转移还需要区间质数个数，这个可以设一个完全积性函数 f(x) = 1 ，
那么用 min25 筛出 f 在质数上的取值即可。
#endif
#include <cstdio>
#include <cmath>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;

inline lolong linput() { lolong x; scanf("%lld", &x); return x; }

const int maxb = 1000000;
int ptot, M, s;
lolong N;
lolong w[maxb];
int prime[maxb], pp;
bool nop[maxb];
lolong g[maxb];

inline int id(lolong x) {
	return int(x <= s ? x : M - (N / x) + 1);
}

lolong S(lolong n, int i) {
	if(prime[i] > n) return 0;
	lolong res = 0;
	for(int k = i + 1; 1ll * prime[k] * prime[k] <= n; k ++) {
		lolong p = prime[k], e = 1;
		while(p <= n) {
			res += S(n / p, k) + prime[k] * (std::max(g[id(n / p)] - k, 0ll) + (e > 1));
			p *= prime[k];
			e ++;
		}
	}
	return res;
}

lolong solve(lolong n) {
	N = n;
	s = int(sqrt(N));
	M = 0;

	for(lolong l = 1, r; l <= n; l = r + 1) {
		w[++ M] = r = n / (n / l);
		g[M] = w[M] - 1;
	}

	for(int i = 1; 1ll * prime[i] * prime[i] <= n; i ++)
		for(int j = M; j and 1ll * prime[i] * prime[i] <= w[j]; j --)
			g[j] -= g[id(w[j] / prime[i])] - (i - 1);

	/* for(int i = 1; i <= M; i ++) */
	/* 	debug("g(%lld) = %lld\n", w[i], g[i]); */

	return S(n, 0);
}

int main() {
	for(int i = 2; i < maxb; i ++)
		if(!nop[i]) {
			prime[++ pp] = i;
			for(lolong j = 1ll * i * i; j < maxb; j += i)
				nop[j] = 1;
		}

	lolong ans = -solve(linput() - 1);
	/* debug("%lld\n", ans); */
	ans += solve(linput());
	printf("%lld\n", ans);
}
