#if 0
2019.11.11

miller_rabin，求快速幂的时候一遍预处理即可，无需多次求快速幂。
pollard_rho，由于 gcd(a, n) > 1 必有 gcd(ab, n) > 1 ，而 gcd(ab % n, n) = gcd(ab, n) ，
倍增在 rho 上跳，每次积累若干样本的乘积再与 n 取 gcd 可以减少 gcd 的调用。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef long double ld;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
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

const int len = 9;
const int pr[len] = {2, 3, 5, 7, 11, 13, 17, 19, 23};
bool isprime(ll n) {
	for(int i = 0; i < len; i ++)
		if(n == pr[i]) return 1;
	for(int i = 0; i < len; i ++)
		if(!miller(n, pr[i])) return 0;
	return 1;
}

inline ll nxt(ll x, ll c, ll n) {
	ll res = mul(x, x, n) + c;
	return res >= n ? res - n : res;
}

ll pollard(ll n) {
	for(int i = 0; i < len; i ++)
		if(!(n % pr[i])) return pr[i];

	ll c = 1ll * rand() * rand() % n;
	ll a = nxt(rand(), c, n);
	ll b = nxt(a, c, n);

	int lim = 1;
	while(a != b) {
		ll v = 1;
		for(int i = 0; i < lim and a != b; i ++) {
			v = mul(v, std::abs(a - b), n);
			a = nxt(a, c, n);
			b = nxt(nxt(b, c, n), c, n);
		}
		ll d = std::__gcd(v, n);
		if(d > 1) return d;
		lim <<= 1;
	}

	return pollard(n);
}

void findmaxp(ll n, ll &ans) {
	if(n <= ans or n == 1) return;
	if(isprime(n)) return ans = n, void();
	ll d = pollard(n);
	while(!(n % d)) n /= d;
	findmaxp(d, ans);
	findmaxp(n, ans);
}

int main() {
	srand(19291001);
	int T = read;
	while(T --) {
		ll n = read;
		ll ans = 1;
		findmaxp(n, ans);
		if(ans == n) puts("Prime");
		else printf("%lld\n", ans);
	}
}
