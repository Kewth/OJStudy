#if 0
2019.10.22

大型同余计算现场。
利用斐波那契的通项公式，将 ((1 + sqrt(5)) / 2) ^ n 看做 t ，
那么 F[n] = C 可以看做一个关于 t 的二次方程，在同余意义下求解，
利用求根公式即可，需要用到二次剩余。
解出 t 后就是要求最小的 n 满足 t 的式子， BSGS 即可。
本题保证了 5 是二次剩余，因此 sqrt(5) 可以看做常数。
A 不掉， CC 太慢了，做你大爷。
#endif
#include <cstdio>
#include <cstdlib>
#include <unordered_map>
#include <cmath>
#include <climits>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;

inline int input() { int x; scanf("%d", &x); return x; }

int mod;
lolong I_mul_I;

struct complex {
	lolong real, imag;
	complex(lolong real = 0, lolong imag = 0): real(real), imag(imag) { }
};
bool operator == (complex x, complex y) {
	return x.real == y.real and x.imag == y.imag;
}
complex operator * (complex x, complex y) {
	return complex((x.real * y.real + I_mul_I * x.imag % mod * y.imag) % mod,
			(x.imag * y.real + x.real * y.imag) % mod);
}

inline complex power(complex x, int k) {
	complex res = 1;
	while(k) {
		if(k & 1) res = res * x;
		x = x * x;
		k >>= 1;
	}
	return res;
}

inline lolong power(lolong x, int k) {
	if(k < 0) k += mod - 1;
	lolong res = 1;
	while(k) {
		if(k & 1) (res *= x) %= mod;
		(x *= x) %= mod;
		k >>= 1;
	}
	return res;
}

inline bool check(lolong x) {
	return power(x, (mod - 1) >> 1) == 1;
}

bool sqrt(lolong n, lolong &x0, lolong &x1) {
	if(!check(n)) return 0;

	if(n == 0) {
		x0 = x1 = 0;
		return 1;
	}

	lolong a = rand() % mod;
	while(a * a == n or check((a * a + mod - n) % mod))
		a = rand() % mod;

	I_mul_I = (a * a + mod - n) % mod;
	/* debug("ImI = %lld\n", I_mul_I); */

	x0 = power(complex(a, 1), (mod + 1) >> 1).real;
	x1 = mod - x0;
	/* debug("sqrt(%lld) = %lld %lld\n", n, x0, x1); */
	return 1;
}

int solve(lolong a, lolong b, lolong c, lolong &x0, lolong &x1) {
	lolong d = ((b * b - 4 * a * c) % mod + mod) % mod;
	if(!sqrt(d, x0, x1)) return 0;
	if(x0 == x1) {
		x0 = x1 = (mod - b) * power(a << 1, -1) % mod;
		return 1;
	}
	x0 = (x0 + mod - b) * power(a << 1, -1) % mod;
	x1 = (x1 + mod - b) * power(a << 1, -1) % mod;
	/* debug("solve %lld %lld %lld - %lld %lld\n", a, b, c, x0, x1); */
	return 2;
}

int log(lolong b, lolong a, bool odd) {
	std::unordered_map<lolong, int> map;
	int s = int(sqrt(mod) + 1);
	for(int i = 1; i <= s; i ++) {
		(b *= a) %= mod;
		map[b] = i + 1;
		/* debug("map[%lld] = %d\n", b, i); */
	}
	a = b = power(a, s);
	for(int i = 1; i <= s; i ++) {
		int j = map[b];
		if(j) {
			int ans = i * s - (j - 1);
			if((ans & 1) == odd)
				return ans;
		}
		(b *= a) %= mod;
	}
	return -1;
}

int main() {
	int T = input();
	while(T --) {
		lolong c = input();
		mod = input();
		I_mul_I = 0;

		lolong sqrt5;
		if(!sqrt(5, sqrt5, sqrt5)) {
			// What can i do ?????
			debug("FUCK\n");
			puts("-1");
			continue;
		}

		lolong t = (1 + sqrt5) * power(2, -1) % mod;
		(c *= sqrt5) %= mod;
		/* debug("t = %lld\n", t); */

		int ans = INT_MAX;
		lolong x0, x1;
		if(solve(1, mod - c, 1, x0, x1)) {
			int k = log(x0, t, 1);
			if(~k)
				ans = std::min(ans, k);
			/* debug("log %lld %d\n", x0, k); */
			k = log(x1, t, 1);
			if(~k)
				ans = std::min(ans, k);
			/* debug("log %lld %d\n", x1, k); */
		}

		if(solve(1, mod - c, mod - 1, x0, x1)) {
			int k = log(x0, t, 0);
			if(~k)
				ans = std::min(ans, k);
			/* debug("log %lld %d\n", x0, k); */
			k = log(x1, t, 0);
			if(~k)
				ans = std::min(ans, k);
			/* debug("log %lld %d\n", x1, k); */
		}

		if(ans == INT_MAX)
			ans = -1;
		printf("%d\n", ans);
	}
}
