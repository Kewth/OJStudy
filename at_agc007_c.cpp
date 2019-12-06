#if 0
2019.12.06

按顺序考虑，考虑第一个滚动的球，期望滚动距离为 E 。
由于距离是等差数列，不难得出 E 关于 d, x 的表达式。
接下来就不会算了。

对球和坑按顺序标号，处理完第一个球后剩下的球数和坑数都会少 1 ，对它们重新标号。
然后考虑新标号后的球坑，考虑新的球坑之间的距离，经过归纳可以的出期望距离仍然是等差数列。
根据期望线性，接下来转换为一个新的子问题，求出新的 d, x 并依次解决即可，复杂度 O(n) 。
#endif
#include <cstdio>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
} read;

int main() {
	int n = read;
	double d = int(read), x = int(read);
	double ans = 0;

	while(n) {
		ans += d + (n * 2 - 1) * x / 2;
		/* debug("+%lf %lf %lf\n", d + (n * 2 - 1) * x / 2, d, x); */
		d = (n + 1) * d / n + 2.5 * x / n;
		x *= (n + 2.0) / n;
		-- n;
	}

	printf("%.10lf\n", ans);
}
