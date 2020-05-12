#if 0
2020.05.12

  愉悦一下。
  如果模数是大质数，那么利用范德蒙恒等式把 C(i * d, x) 拆 d 次，稍加整理即可得到 f 的递
推式，时间复杂度 O(md) 。
  需要注意的在推式子的时候组合数需要推广到 n < 0 的情况，否则范德蒙恒等式不会成立。
  众所周知出道烂题只需要把模数换成一搬模数，把模数质因数分解，用中国剩余定理合并即可。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
} read;

const int maxn = 3000005, maxd = 105;
int mod;
ll f[maxn], C[maxd], inv[maxn];

int main () {
	int n = read, m = read, d = read;
	read(mod);
	f[0] = n % mod;

	inv[1] = 1;
	for (int x = 2; x <= m or x <= d; x ++)
		inv[x] = (mod - mod / x) * inv[mod % x] % mod;

	C[0] = 1;
	for (int i = 1; i <= d; i ++)
		C[i] = C[i - 1] * (d - i + 1) % mod * inv[i] % mod;

	ll Cx = 1, ans = 0;
	for (int x = 0; x < m; x ++) {
		(Cx *= n * d - x) %= mod;
		(Cx *= inv[x + 1]) %= mod;
		f[x] = Cx;
		for (int j = 1; j < d and j <= x; j ++)
			(f[x] += (mod - C[j + 1]) * f[x - j]) %= mod;
		(f[x] *= inv[d]) %= mod;
		ans ^= f[x];
		/* debug("f[%d] = %lld\n", x, f[x]); */
	}

	printf("%lld\n", ans);
}
