#if 0
2019.05.16

扩展 Lucas 模板。
算阶乘时要去掉模数 p ，单独统计组合数 p 的次数。
求逆元不能用费马。
#endif
#include <cstdio>
#include <cstdint>
#include <vector>
#include <cassert>

typedef long long lolong;

inline lolong input() {
	lolong x;
	scanf("%lld", &x);
	return x;
}

lolong exgcd(lolong a, lolong b, lolong &x, lolong &y) {
	while(not b) {
		x = 1;
		y = 0;
		return a;
	}
	lolong _x, _y;
	lolong res = exgcd(b, a % b, _x, _y);
	x = _y;
	y = _x - a / b * _y;
	return res;
}

lolong inv(lolong x, int p) {
	lolong res, tmp;
	exgcd(x, p, res, tmp);
	if(res < 0) res += p;
	return res;
}

lolong power(lolong x, lolong k, lolong p = INT64_MAX) {
	lolong res = 1;
	while(k) {
		if(k & 1) (res *= x) %= p;
		(x *= x) %= p;
		k >>= 1;
	}
	return res;
}

lolong fuck;
int flag;
lolong fatorial(lolong n, int p, int k) {
	if(not n) return 1;
	lolong k2 = n / p;
	assert(power(p, k) <= INT32_MAX);
	int mod = int(power(p, k));
	lolong res = 1;
	fuck += k2 * flag;
	(res *= fatorial(k2, p, k)) %= mod;
	lolong x = 1;
	for(int i = 1; i <= mod; i ++)
		if(i % p)
			(x *= i) %= mod;
	(res *= power(x, n / mod, mod));
	for(int i = 1; i <= n % mod; i ++)
		if(i % p)
			(res *= i) %= mod;
	return res;
}

lolong C(lolong n, lolong m, int p) {
	const int P = p;
	int M = 1;
	std::vector<std::pair<lolong, int> > v;
	for(int x = 2; x <= p; x ++)
		if(not(p % x)) {
			int k = 0;
			while(not(p % x)) {
				p /= x;
				k ++;
			}
			int mod = int(power(x, k));
			fuck = 0, flag = 1;
			lolong a = fatorial(n, x, k);
			flag = -1;
			(a *= inv(fatorial(m, x, k), mod)) %= mod;
			(a *= inv(fatorial(n - m, x, k), mod)) %= mod;
			(a *= power(x, fuck, mod)) %= mod;
			v.push_back(std::make_pair(a, mod));
			M *= mod;
			/* fprintf(stderr, "%lld=%lld/(%lld*%lld)*%d^%d %d=%d^%d\n", */
			/* 		a, fatorial(n, x, k), */
			/* 		fatorial(m, x, k), fatorial(n - m, x, k), */
			/* 		x, fuck, */
			/* 		mod, x, k); */
		}
	lolong res = 0;
	for(auto eq : v) {
		lolong _a = eq.first;
		int _p = eq.second;
		(res += (M / _p) * inv(M / _p, _p) % P * _a % P) %= P;
	}
	return res;
}

int main() {
	lolong n = input(), m = input(), p = input();
	printf("%lld\n", C(n, m, int(p)));
}
