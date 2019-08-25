#if 0
2019.08.24

对于 k 个 A 中的一个 a[i] 暴力求出右边比它小的，再求整个 A 中比它小的，
简单统计计算答案即可。
#endif
#include <cstdio>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;

inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 2020, mod = 1000000007;
int a[maxn];

int main() {
	int n = input(), k = input();
	for(int i = 1; i <= n; i ++)
		a[i] = input();

	lolong ans = 0;
	for(int i = 1; i <= n; i ++) {
		int tot = 0, s = 0;
		for(int j = i + 1; j <= n; j ++)
			if(a[j] < a[i])
				tot ++;
		for(int j = 1; j <= n; j ++)
			if(a[j] < a[i])
				s ++;
		ans += 1ll * tot * k % mod + (1ll * k * (k - 1) >> 1) % mod * s % mod;
	}

	printf("%lld\n", ans % mod);
}
