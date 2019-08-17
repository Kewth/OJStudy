#if 0
2019.07.30

Miller Robin 模板，卡常，得 O(1) 快速乘。
#endif
#include <cstdio>
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

int main() {
	lolong n;
	while((n = input()))
		printf("%c\n", "NY"[is_prime(n)]);
}

