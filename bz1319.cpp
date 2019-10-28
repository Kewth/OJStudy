#if 0
2019.10.27

乍一看以为需要 BSGS 求多解，但事实上利用好原根的性质好像可以转换为一个扩欧。

求出原根 g ，设 x = g^X ，将 a 表示为 g^A ，那么问题转换为求解这样的方程：

Xk = A (mod p - 1)

扩欧计算即可。
#endif
#include <cstdio>
#include <unordered_map>
#include <cmath>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

inline int input() { int x; scanf("%d", &x); return x; }

ll power(ll x, ll k, int mod) {
	ll res = 1;
	while(k) {
		if(k & 1) (res *= x) %= mod;
		(x *= x) %= mod;
		k >>= 1;
	}
	return res;
}

ll tmp1, tmp2;
ll exgcd(ll a, ll b, ll &x = tmp1, ll &y = tmp2) {
	if(!b) {
		x = 1;
		y = 0;
		return a;
	}
	ll x0, y0;
	ll res = exgcd(b, a % b, x0, y0);
	x = y0;
	y = x0 - a / b * y0;
	return res;
}

ll bsgs(ll a, ll b, int mod) {
	std::unordered_map<ll, int> map;
	int s = int(sqrt(mod) + 1);
	ll A = 1;

	for(int i = 1; i <= s; i ++) {
		(A *= a) %= mod;
		map[b * A % mod] = i;
	}

	b = 1;
	for(int i = 1; i <= s; i ++) {
		(b *= A) %= mod;
		if(map[b])
			return i * s - map[b];
	}

	return -1;
}

ll getG(int mod) {
	int fac[30];
	int p = 0;
	int x = mod - 1;
	for(int i = 2; i * i <= x; i ++)
		while(!(x % i)) {
			fac[p ++] = i;
			x /= i;
		}
	if(x > 1)
		fac[p ++] = x;
	int g = 2;
	while(1) {
		for(int i = 0; i < p; i ++)
			if(power(g, (mod - 1) / fac[i], mod) == 1)
				goto FAIL;
		return g;
FAIL:
		g ++;
	}
}

ll ans[100000];
int main() {
	int mod = input(), k = input(), a = input();
	int p = mod;

	ll g = getG(p);
	a = int(bsgs(g, a, p));
	/* debug("%lld\n", g); */
	p --;

	ll x, y;
	ll gcd = exgcd(k, p, x, y);

	if(a % gcd) puts("0");
	else {
		int ap = 0;
		p /= gcd;
		x *= a / gcd;
		((x %= p) += p) %= p;
		while(x < mod) {
			ans[++ ap] = power(g, x, mod);
			x += p;
		}

		printf("%d\n", ap);
		std::sort(ans + 1, ans + ap + 1);
		for(int i = 1; i <= ap; i ++)
			printf("%lld\n", ans[i]);
	}
}
