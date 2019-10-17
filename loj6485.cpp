#if 0
2019.10.17

把每个 a 单独算贡献，然后就有个 [i % 4 = k] 的限制，用单位根反演去展开它即可。
#endif
#include <cstdio>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;

inline int input() { int x; scanf("%d", &x); return x; }
inline lolong linput() { lolong x; scanf("%lld", &x); return x; }

const int mod = 998244353, W = 911660635;

lolong power(lolong x, lolong k) {
	x %= mod;
	k %= mod - 1;
	if(k < 0) k += mod - 1;
	lolong res = 1;
	while(k) {
		if(k & 1) (res *= x) %= mod;
		(x *= x) %= mod;
		k >>= 1;
	}
	return res;
}

int main() {
	int T = input();
	while(T --) {
		lolong n = linput(), s = linput(), ans = 0;
		for(int k = 0; k < 4; k ++) {
			lolong a = linput();
			for(int j = 0; j < 4; j ++)
				(ans += a % mod * power(4 * power(W, k * j), -1) % mod *
					power(1 + s % mod * power(W, j), n)) %= mod;
		}
		printf("%lld\n", ans);
	}
}
