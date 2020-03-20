#if 0
2020.03.13

初中知识线性规划，一个巨坑的地方是求的是整点，
因此直接套公式解出来的最优点并不一定能取到，哪怕向下取整。
没脑子，先求出实数域下的最优解向下取整，然后暴力搜，
如果当前答案不合法就 -- ans ，直到合法为止。
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
	int T = read;
	while(T --) {
		ll a = read, b = read;
		ll t = std::min({a / 2, b, (a + b) / 5});

		while(1) {
			ll L = (3 * t - b + 1) / 2, R = (a - 2 * t) / 2;
			if(L <= R and R >= 0)
				break;
			-- t;
		}

		printf("%lld\n", t);
	}
}

