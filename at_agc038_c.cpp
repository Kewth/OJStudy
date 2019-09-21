#if 0
2019.09.21

忽略掉 i < j 统计答案 x ，容易从 x 得到 i < j 的答案。
把 lca 拆成 gcd ，枚举 gcd 的值 d ，此时有影响的 a 都是 d 的倍数，
a[i] 和 a[j] 有贡献需要满足 (a[i] / d, a[j] / d) 互质，将互质条件拆成 mu ，
此时又有枚举 a[i] / d 的约数 x ，提前 x 的枚举顺序，
这时候有影响的 a 都是 d * x 的倍数，考虑枚举 T = d * x 以及 T 的约数 d ，
这个时候答案就显而易见了，
将后面的求和预处理出 s[x] 表示所有 x 的倍数的 a[i] 的 a[i] 的和，
就得到了 O(V sqrt(V)) 的处理方式。
交换 d, T 的枚举顺序，类似于埃氏筛，此时复杂度为 O(V log(V)) 。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;

inline int input() { int x; scanf("%d", &x); return x; }
inline lolong linput() { lolong x; scanf("%lld", &x); return x; }

const int maxn = 200005, maxv = 1000005, mod = 998244353, inv2 = 499122177;
int a[maxn];
lolong s[maxv];
int mu[maxv];
bool nop[maxv];
int prime[maxv], pp;
int tot[maxv];

int main() {
	int n = input();

	int max = 0;
	for(int i = 1; i <= n; i ++) {
		a[i] = input();
		tot[a[i]] ++;
		max = std::max(a[i], max);
	}

	for(int d = 1; d <= max; d ++)
		for(int t = d; t <= max; t += d)
			s[d] += 1ll * (t / d) * tot[t] % mod;

	for(int i = 1; i <= max; i ++) {
		s[i] %= mod;
		s[i] *= s[i];
		s[i] %= mod;
	}

	mu[1] = 1;
	for(int i = 2; i <= max; i ++) {
		if(!nop[i]) {
			prime[++ pp] = i;
			mu[i] = -1;
		}

		for(int j = 1; j <= pp; j ++) {
			int p = prime[j];
			if(1ll * i * p > max)
				break;
			nop[i * p] = 1;
			if(i % p)
				mu[i * p] = mu[i] * mu[p];
		}
	}

	lolong ans = 0;
	for(int d = 1; d <= max; d ++)
		for(int t = d; t <= max; t += d) {
			ans += 1ll * (mod + mu[t / d]) * t % mod * (t / d) % mod * s[t] % mod;
			ans %= mod;
		}

	for(int i = 1; i <= n; i ++)
		ans -= a[i];

	ans %= mod;
	ans += mod;
	ans %= mod;

	(ans *= inv2) %= mod;

	printf("%lld\n", (ans % mod + mod) % mod);
}
