#if 0
2020.01.17

首先 n, m 可以约分，接下来的讨论假定 n, m 互质。

分类讨论，如果 m > n ，那么所有点都会向后面定长距离连边，当且仅当 m 是 n 的倍数时没有周期。
如果 2m < n ，后面 n - 2m 个字符随便选，没有周期。
如果 2m = n ，周期为 n / 2 。

重点是 2m > n 且 m <= n 的情况。
不妨将串倍长得到 2n 个点，前 m 个点 i 会向 i + m 连边，前 n 个点 i 会向 i + n 连边。
那么每个点的度数最多为 2 ，要求图是否联通。
注意到最后两个点的度数一定为 1 ，那么图联通，当且仅当图是一条链，端点是最后两个点。
这个条件等价于 m = n - 1 ，否则会有更多点的度数为 1 ，而这个条件下其他点度数都为 2 且图无环。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
} read;

int main() {
	int q = read;
	while(q --) {
		ll n = read, m = read;
		if(m > n) {
			if(m % n == 0)
				puts("Yes");
			else
				puts("No");
		} else if(m * 2 == n)
			puts("No");
		else if(m * 2 < n)
			puts("Yes");
		else {
			ll d = std::__gcd(m, n - m);
			n /= d;
			m /= d;
			if(m == n - 1)
				puts("No");
			else
				puts("Yes");
		}
	}
}
