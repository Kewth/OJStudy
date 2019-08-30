#if 0
date +%Y.%m.%d

交换 i, j 的枚举顺序，按 i / j 将 i 分类，然后式子就是 O(n) 的了。
#endif
#include <cstdio>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;
inline int input() { int x; scanf("%d", &x); return x; }

lolong calc(int n) {
	lolong res = 0;
	for(int i = 1; i <= n; i ++) {
		int d = (n + 1) / i;
		lolong now = (1ll * i * d * (d - 1) >> 1) +
			1ll * ((n + 1) % i) * (n / i);
		res += (i & 1) ? - now : now;
		/* debug("%d : %lld\n", i, now); */
	}
	return res;
}

int main() {
	lolong ans = - calc(input() - 1);
	ans += calc(input());
	printf("%lld\n", ans);
}
