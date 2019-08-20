#if 0
2019.08.20

每次加数或者减数，答案的更改相当与求数 x 与集合 S 的不互质的数的个数。
容斥，统计 s[x] 表示集合中 x 的倍数有多少个，
那么对当前数 x 用贡献的是所有 s[d] ，其中 d 是 x 的因子。
考虑容斥，不难得出贡献的系数就是 mu[d] 。
#endif
#include <cstdio>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;

inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 200005, maxv = 500005;
int a[maxn];
int mu[maxv];
bool not_prime[maxv];
bool use[maxn];
int s[maxv];

inline void modify(int x, int t) {
	for(int d = 1; d * d <= x; d ++)
		if(not (x % d)) {
			s[d] += t;
			if(x / d != d)
				s[x / d] += t;
		}
}

inline lolong calc(int x) {
	lolong res = 0;

	for(int d = 1; d * d <= x; d ++)
		if(not (x % d)) {
			res += s[d] * mu[d];
			if(x / d != d)
				res += s[x / d] * mu[x / d];
		}

	return res;
}

int main() {
	int n = input(), q = input();

	mu[1] = 1;

	for(int i = 2; i < maxv; i ++) {
		if(not not_prime[i]) {
			mu[i] = -1;
			for(int j = 2; i * j < maxv; j ++) {
				not_prime[i * j] = true;
				if(j % i)
					mu[i * j] = mu[i] * mu[j];
			}
		}
	}

	for(int i = 1; i <= n; i ++)
		a[i] = input();

	lolong ans = 0;
	while(q --) {
		int p = input();

		if(use[p]) {
			modify(a[p], -1);
			ans -= calc(a[p]);
		} else {
			ans += calc(a[p]);
			modify(a[p], 1);
		}

		use[p] ^= 1;

		printf("%lld\n", ans);
	}
}
