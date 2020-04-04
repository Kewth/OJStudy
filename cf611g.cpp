#if 0
2020.02.14

用点的叉积求面积，具体的，如果一个逆时针排列的多边形是 P1, P2, ... Pn ，
其两倍面积就是 P1 x P2 + P2 x P3 + ... + Pn x P1 。

考虑求出所有小的部分的面积和以及所有大的部分的面积和。

枚举对角线的一个端点 Pa ，
然后考虑求出最大的 b 使得 Pa - Pb 之间的多边形小于一半。
那么求出这部分小面积和，列出式子，用一些前缀和维护即可。
而对每个 a 求出对应的 b 只需要双指针。

根据小面积 + 大面积 = 总面积不能在上述过程中求出大面积和。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	inline operator char () { char x[3]; return scanf("%s", x), *x; }
} read;

const int maxn = 1000005, mod = 1000000007;
ll x[maxn], y[maxn];
ll sx[maxn], sy[maxn], s[maxn], si[maxn];

ll area(int i, int j, int k) {
	return
		x[i] * y[j] - x[j] * y[i] +
		x[j] * y[k] - x[k] * y[j] +
		x[k] * y[i] - x[i] * y[k];
}

int main() {
	int n = read;
	for(int i = 0; i < n; i ++) {
		x[n * 2 - i] = x[n - i] = read;
		y[n * 2 - i] = y[n - i] = read;
	}

	int N = n << 1;
	for(int i = 1; i <= N; i ++) {
		sx[i] = (sx[i - 1] + x[i] + mod) % mod;
		sy[i] = (sy[i - 1] + y[i] + mod) % mod;
	}
	for(int i = 1; i < N; i ++) {
		ll shit = (x[i] * y[i + 1] - x[i + 1] * y[i]) % mod;
		if(shit < 0) shit += mod;
		s[i] = (s[i - 1] + shit) % mod;
		si[i] = (si[i - 1] + shit * i) % mod;
	}

	ll tot = 0, now = 0;
	for(int i = 3; i <= n; i ++)
		tot += area(1, i - 1, i);

	ll minsum = 0, maxsum = 0;
	for(int a = 1, b = 2; a <= n; a ++) {
		if(b <= a) b = a + 1;
		while(b + 1 < a + n and now + area(a, b, b + 1) <= (tot - 1) / 2) {
			// debug("%d %d %d : %lld\n", a, b, b + 1, area(a, b, b + 1));
			now += area(a, b, b + 1);
			++ b;
		}

		ll X = sx[b] - sx[a - 1] + mod;
		ll Y = sy[b] - sy[a - 1] + mod;
		ll sum = (X * (y[a] + mod) + (mod - x[a]) * Y) % mod;

		sum += b * (s[b - 1] - s[a - 1] + mod);
		(sum += si[a - 1] - si[b - 1] + mod) %= mod;

		// debug("%d -> %d (now = %lld) (sum = %lld)\n", a, b, now, sum);

		if(b >= a + 2)
			now -= area(a, a + 1, b);

		minsum += sum;
		(maxsum += tot % mod * (b - a - 1) + mod - sum) %= mod;
	}

	ll ans = maxsum - minsum % mod;
	if(ans < 0) ans += mod;
	printf("%lld\n", ans);
}
