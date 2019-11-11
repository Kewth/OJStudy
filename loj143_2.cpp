#if 0
2019.11.11

miller_rabin，求快速幂的时候一遍预处理即可，无需多次求快速幂。
#endif
#include <cstdio>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef long double ld;

struct {
	inline operator int () { int x = 0; return scanf("%d", &x), x; }
	inline operator ll () { ll x = 0; return scanf("%lld", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
} read;

inline ll mul(ll x, ll y, ll mod) {
	ll res = x * y - ll(ld(x) / mod * y + 0.5) * mod;
	return res < 0 ? res + mod : res;
}

bool miller(ll n, int p) {
	static ll power[70];
	ll x = n - 1;

	int maxk = 0;
	for(ll k = x; k; k >>= 1)
		++ maxk;

	power[maxk + 1] = 1;
	for(int k = maxk; k >= 0; k --) {
		power[k] = mul(power[k + 1], power[k + 1], n);
		if(x >> k & 1)
			power[k] = mul(power[k], p, n);
	}

	if(power[0] != 1) return 0;
	for(int k = 1; !(x & 1); k ++) {
		x >>= 1;
		if(power[k] == n - 1) return 1;
		if(power[k] != 1) return 0;
	}

	return 1;
}

bool isprime(ll n) {
	static const int len = 9;
	static const int p[len] = {2, 3, 5, 7, 11, 13, 17, 19, 23};
	for(int i = 0; i < len; i ++)
		if(n == p[i]) return 1;
	for(int i = 0; i < len; i ++)
		if(!miller(n, p[i])) return 0;
	return 1;
}

int main() {
	while(1) {
		ll n = read;
		if(!n) break;
		printf("%c\n", "NY"[isprime(n)]);
	}
}
