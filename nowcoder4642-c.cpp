#if 0
2020.03.20

简单期望 DP ，首先随便落座一个人后环就可以看作链，
设 f[i] 表示长为 i 的链无人落座，链的端点两边都有人，期望能坐多少人。
朴素转移枚举第一个人坐的位置，但是写出转移式子后就可以发现坐什么位置转移系数都是一样的（概率一样），
那么前缀和优化即可。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 300005, mod = 998244353;
ll f[maxn], s[maxn];

inline ll power(ll x, int k) {
	if(k < 0) k += mod - 1;
	ll res = 1;
	while(k) {
		if(k & 1) (res *= x) %= mod;
		(x *= x) %= mod;
		k >>= 1;
	}
	return res;
}

int main () {
	int n = read - 1;
	ll p = read, q = read;

	if (p) {
		f[3] = f[4] = 1;
		s[3] = 1;
		s[4] = 2;
	}

	for (int i = 5; i <= n; i ++) {
		f[i] = (p * s[i - 2] * 2 + q * s[i - 3] * 2) % mod;
		(f[i] *= power((p * (i - 2) + q * (i - 4)) % mod, -1)) %= mod;
		++ f[i];
		s[i] = (s[i - 1] + f[i]) % mod;
	}

	printf("%lld\n", (f[n] + 1) % mod);
}
