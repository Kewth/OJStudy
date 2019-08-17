#if 0
2019.07.30

Pollard_rho + miller_robin 模板。
十分卡常。
#endif
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;
inline lolong input() { lolong x = 0; scanf("%lld", &x); return x; }

inline lolong mul(lolong x, lolong y, lolong mod) {
	lolong tmp = x * y - lolong((long double)x / mod * y + 0.5) * mod;
	return tmp < 0 ? tmp + mod : tmp;
}

inline lolong power(lolong x, lolong k, lolong mod) {
	lolong res = 1;
	while(k) {
		if(k & 1) res = mul(res, x, mod);
		x = mul(x, x, mod);
		k >>= 1;
	}
	return res % mod;
}

inline bool miller(lolong n, int p) {
	if(power(p, n - 1, n) != 1)
		return false;
	lolong k = n - 1;
	while(not (k & 1)) {
		k >>= 1;
		lolong po = power(p, k, n);
		if(po == n - 1)
			return true;
		else if(po != 1)
			return false;
	}
	return true;
}

inline bool is_prime(lolong n) {
	static const int len = 9;
	static const lolong p[len] = {2, 3, 5, 7, 11, 13, 17, 19, 23};
	for(int i = 0; i < len; i ++)
		if(n == p[i])
			return true;
	for(int i = 0; i < len; i ++)
		if(n == p[i])
			return true;
		else if(not miller(n, p[i]))
			return false;
	return true;
}

lolong gcd(lolong x, lolong y) {
	if(not y) return x;
	return gcd(y, x % y);
}

inline lolong fast_gcd(lolong a, lolong b){
	if(!a) return b;
	if(!b) return a;
	int t = __builtin_ctzll(a|b) ;
	a >>= __builtin_ctzll(a) ;
	do{
		b >>= __builtin_ctzll(b) ;
		if(a > b) std::swap(a, b);
		b -= a;
	}while(b);
	return a << t;
}

inline lolong nxt(lolong x, lolong c, lolong mod) {
	x = mul(x, x, mod) + c;
	if(x >= mod) x -= mod;
	return x;
}

lolong pollard(lolong n) {
	if(n == 4) return 2;
	lolong c = 1ll * rand() * rand() % n;
	lolong a = nxt(rand(), c, n);
	lolong b = nxt(a, c, n);
	// debug("%lld %lld %lld %lld\n", a, b, c, n);
	while(a != b) {
		lolong d = fast_gcd(std::abs(a - b), n);
		// debug("%lld %lld %lld %lld\n", a, b, c, n);
		if(d > 1) return d;
		a = nxt(a, c, n);
		b = nxt(nxt(b, c, n), c, n);
	}
	return pollard(n);
}

lolong max;
void fuck(lolong n) {
	if(n <= max or n < 2) return;
	// debug("fuck %lld\n", n);
	if(is_prime(n)) {
		max = n;
		return;
	}
	lolong d = pollard(n);
	while(not (n % d))
		n /= d;
	fuck(n);
	fuck(d);
}


int main() {
	srand(19260817);
	int T = input();
	while(T --) {
		lolong n = input();
		max = 0;
		fuck(n);
		if(max == n) puts("Prime");
		else printf("%lld\n", max);
		// debug("max %lld : %lld\n", max, n);
	}
}

