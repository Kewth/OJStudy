#if 0
2019.11.05

神奇 PE 数学题。

原递推式 a[n+1] = 6a[n]^2 + 10a[n] + 3, a[1] = 1 。
将递推式配个方，得到 6a[n+1] + 5 = (6a[n] + 5)^2 - 2 ，令其中 b[n] = 6a[n] + 5 。
现在递推 b 的最大难点在于后面的 -2 ，注意到 (x + 1/x)^2 - 2 = x^2 + 1/x^2 ，
那么不妨设 b[1] = x + 1/x ，那么很容易得出 b[n] = x^(2^(n-1)) + 1/x^(2^(n-1)) 。

那么可以对 x 做快速幂求 b ，然而指数巨大，这个稍后讨论。
由于 b[1] = 11 ，那么 x + 1/x = 11 ，得到一个解是 x = (11 + sqrt(117)) / 2 ，
对 117 开根不一定做得到，因为它可能是非二次剩余，
而对于非二次剩余的开根一个经典做法就是扩域，设 i^2 = 117 代入进行复数运算。

现在唯一的问题是快速幂的指数巨大，需要求出一个循环节，
也就是找到一个合适的模数对指数取模。
换言之找到一个 k 使得 x^k = 1 。
不难想到费马小定理，可惜在扩域后它并不成立，
但是根据二次剩余 cipolla 那套理论，117 是非二次剩余时，有 i^p = -i ，
而又有 (a+bi)^p = a^p + b^p i^p = a-bi ，那么 (a+bi)^(p+1) = a^2 - b^2 i^2 ，虚部为 0 ，
此时可以用费马小定理，有 ((a+bi)^(p+1))^(p-1) = 1 ，循环节取 p^2 - 1 即可。

需要特判模数为 2 或 3 的情况。
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

struct complex {
	ll real, imag;
	complex(ll real = 0, ll imag = 0): real(real), imag(imag) { }
};
int mod;
complex operator * (complex a, complex b) {
	return complex((a.real * b.real + 117 * a.imag % mod * b.imag) % mod,
			(a.real * b.imag + a.imag * b.real) % mod);
}
void operator *= (complex &a, complex b) { a = a * b; }
complex operator + (complex a, complex b) {
	return complex((a.real + b.real) % mod,
			(a.imag + b.imag) % mod);
}

int main() {
	int T = read;
	while(T --) {
		ll n = read;
		read(mod);

		if(mod == 2 or mod == 3)
			puts("1");

		else {
			ll inv2 = (mod + 1) >> 1;
			complex A(11 * inv2 % mod, inv2);
			complex B(11 * inv2 % mod, mod - inv2);

			__int128 p = 1, tmp = 2;
			ll k = 1ll * mod * mod - 1;
			n --;
			while(n) {
				if(n & 1) (p *= tmp) %= k;
				(tmp *= tmp) %= k;
				n >>= 1;
			}

			complex Am = 1, Bm = 1;
			while(p) {
				if(p & 1) Am *= A, Bm *= B;
				A *= A;
				B *= B;
				p >>= 1;
			}

			ll inv3 = ((mod + 1) % 3 ? (mod << 1 | 1) : mod + 1) / 3;
			printf("%lld\n", ((Am + Bm).real + mod - 5) * inv3 % mod * inv2 % mod);
		}
	}
}
