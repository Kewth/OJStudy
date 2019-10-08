#if 0
2019.10.08

快速幂复杂度固然是对的，但是常数略大。
注意到模数 1e9+9 ，此时根号 5 是有二次剩余的。
那么直接套用斐波那契通项公式即可。
#endif
#include <cstdio>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;

inline int input() { int x; scanf("%d", &x); return x; }
inline lolong linput() { lolong x; scanf("%lld", &x); return x; }

const lolong sqrt5 = 383008016;
const int mod = 1000000009;

lolong power(lolong x, int k) {
	if(k < 0) k += mod - 1;
	lolong res = 1;
	while(k) {
		if(k & 1) (res *= x) %= mod;
		(x *= x) %= mod;
		k >>= 1;
	}
	return res;
}

int main() {
	lolong a = (1 + sqrt5 + mod) >> 1;
	lolong b = (1 - sqrt5 + mod) >> 1;
	lolong inv = power(sqrt5, -1);

	int T = input();
	while(T --) {
		lolong n = linput();
		lolong A = power(a, n % (mod - 1));
		lolong B = power(b, n % (mod - 1));
		printf("%lld\n", (A - B + mod) * inv % mod);
	}
}
