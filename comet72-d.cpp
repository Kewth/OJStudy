#if 0
2019.10.25

将 a^0.5 看做虚数单位进行扩域，然后就可以用二项式定理 + 2 次单位根反演解决问题。
#endif
#include <cstdio>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;
typedef __int128_t big;

inline int input() { int x; scanf("%d", &x); return x; }
inline lolong linput() { lolong x; scanf("%lld", &x); return x; }

lolong mod;
big ImulI;
struct complex {
	big real, imag;
	complex(big real = 0, big imag = 0): real(real), imag(imag) { }
};

complex operator * (complex x, complex y) {
	/* debug("%lld %lld %lld %lld\n", */
	/* 		lolong(x.real), lolong(x.imag), lolong(y.real), lolong(y.imag)); */
	return complex((x.real * y.real + ImulI * x.imag % mod * y.imag) % mod,
			(x.imag * y.real + x.real * y.imag) % mod);
}

complex power(complex x, lolong k) {
	complex res = 1;
	while(k) {
		if(k & 1) res = res * x;
		x = x * x;
		k >>= 1;
	}
	return res;
}

int main() {
	int T = input();
	while(T --) {
		lolong n = linput(), a = linput(), b = linput();
		mod = linput();
		ImulI = a;
		complex A(b, 1), B(b, mod - 1);
		A = power(A, n);
		B = power(B, n);
		/* debug("%lld %lld\n", lolong(A.real), lolong(A.imag)); */
		/* debug("%lld %lld\n", lolong(B.real), lolong(B.imag)); */
		/* A = 1 * A; */
		/* A = A * complex(1, 0); */
		/* debug("%lld %lld\n", lolong(A.real), lolong(A.imag)); */
		/* debug("%lld %lld\n", lolong(B.real), lolong(B.imag)); */
		big ans = A.real + B.real;
		/* debug("%lld %lld\n", lolong(ans), lolong(A.imag + B.imag)); */
		if(mod & 1) (ans *= (mod + 1) >> 1) %= mod;
		else ans >>= 1;
		printf("%lld\n", lolong(ans));
	}
}
