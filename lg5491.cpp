#if 0
2019.10.21

二次剩余 cipolla 模板。
#endif
#include <cstdio>
#include <cstdlib>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;

inline int input() { int x; scanf("%d", &x); return x; }
inline lolong linput() { lolong x; scanf("%lld", &x); return x; }

int mod;
lolong I_mul_I;
struct complex {
	lolong real, imag;
	complex(lolong real = 0, lolong imag = 0): real(real), imag(imag) { }
};
inline bool operator == (complex x, complex y) {
	return x.real == y.real and x.imag == y.imag;
}
inline complex operator * (complex x, complex y) {
	return complex((x.real * y.real + I_mul_I * x.imag % mod * y.imag) % mod,
			(x.imag * y.real + x.real * y.imag) % mod);
}

complex power(complex x, int k) {
	complex res = 1;
	while(k) {
		if(k & 1) res = res * x;
		x = x * x;
		k >>= 1;
	}
	return res;
}

int main() {
	srand(19491001);
	int T = input();
	while(T --) {
		int n = input();
		mod = input();
		I_mul_I = 0;

		if(n == 0) {
			puts("0");
			continue;
		}

		if(power(n, (mod - 1) >> 1) == mod - 1) {
			puts("Hola!");
			continue;
		}

		lolong a = rand() % mod;
		while(!(power(I_mul_I = (a * a + mod - n) % mod, (mod - 1) >> 1) == mod - 1))
			a = rand() % mod;

		/* debug("%lld %lld\n", a, I_mul_I); */

		lolong x = power(complex(a, 1), (mod + 1) >> 1).real;
		if(x > mod - x)
			x = mod - x;
		printf("%lld %lld\n", x, mod - x);
	}
}
