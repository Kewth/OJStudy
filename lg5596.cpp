#if 0
2019.10.23

设 y = x + k ，那么把 y^2 拆开后 x 就没有二次项了，
把 x 提到一边，得到 x = (k * k - b) / (a - 2 * k) 。
那么就是要求多少个 k 能使得 x 为自然数。
首先自然数要符号不为负，那么 k * k < b 和 2 * k < a 至少有一个成立。
前者枚举是 sqrt(b) 的，后者枚举是 a / 2 的。
#endif
#include <cstdio>
#include <cmath>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;

inline int input() { int x; scanf("%d", &x); return x; }
inline lolong linput() { lolong x; scanf("%lld", &x); return x; }

int main() {
	int a = input(), ans = 0;
	lolong b = linput();

	int s = int(sqrt(b));
	if(1ll * s * s == b and (s << 1) == a) {
		puts("inf");
		return 0;
	}

	for(int k = 0; (k << 1) < a or k <= s; k ++) {
		lolong x = 1ll * k * k - b;
		int y = a - (k << 1);
		if(y and !(x % y) and x / y >= 0)
			ans ++;
	}
	printf("%d\n", ans);
}
