#if 0
2019.09.15

事实上积等于和这个条件在正整数域下十分苛刻，爆搜+剪枝即可。
具体的，先钦定数列单调不减，枚举数列后可以用组合数算出有序的方案数。
枚举时弄个估价函数，显然让和尽量比积大的方式是尽量选最小的。
那么如果后面的数全部选最小后和仍然比积小，直接 skip 掉。
#endif
#include <cstdio>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;
inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 3030, mod = 1000000007;
lolong fac[maxn];
lolong ifac[maxn];

bool bemod;
inline lolong power(lolong x, int k) {
	if(k < 0)
		k += mod - 1;
	lolong res = 1;
	bemod = 0;
	while(k) {
		if(k & 1) {
			res *= x;
			if(res >= mod) {
				bemod = 1;
				res %= mod;
			}
		}
		(x *= x) %= mod;
		k >>= 1;
	}
	return res;
}

inline lolong C(int n, int m) {
	return fac[n] * ifac[m] % mod * ifac[n - m] % mod;
}

lolong fuck(int n, lolong a, lolong b, int x, int t) {
	/* debug("%d %lld %lld\n", n, a, b); */
	if(n == 0)
		return a == b;
	lolong max = a * power(x, n);
	if(max > b + n * x or bemod)
		return 0;
	lolong res = fuck(n - 1, a * x, b + x, x, t + 1);
	int y = x + 1;
	while(y < 100000) {
		max = a * power(y, n);
		lolong f;
		if(max <= b + n * y and !bemod)
			f = fuck(n - 1, a * y, b + y, y, 1);
		else
			break;
		res += f * C(n + t, t) % mod;
		/* if(f) */
		/* 	debug("C(%d, %d) = %lld\n", n + t, t, C(n + t, t)); */
		y ++;
	}
	/* if(res) */
	/* 	debug("%d %lld %lld %d %d: %lld\n", n, a, b, x, t, res); */
	return res % mod;
}

int main() {
	int T = input();

	fac[0] = 1;
	for(int i = 1; i < maxn; i ++)
		fac[i] = fac[i - 1] * i % mod;
	for(int i = 0; i < maxn; i ++)
		ifac[i] = power(fac[i], -1);

	while(T --) {
		int n = input();
		printf("%lld\n", fuck(n, 1, 0, 1, 0));
	}
}
