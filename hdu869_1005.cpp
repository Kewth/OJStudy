#if 0
2019.08.23

中间那个 gcd 纯粹在吓人，由于 a, b 互质且 i, j 互质，其实那玩意就是 i - j 。
于是就可以把互质条件换成 mu ，一波套路后，得到以下式子：
ans = sum(mu[i] * i * f(n / i)) ，其中 f(n) 是一到 n 的和加平方和除以 2 。
整除分块的话，问题在于求 mu[i] * i 的区间和，直接预处理是 O(n) 的。
事实上直接杜教筛即可。
#endif
#include <cstdio>
#include <vector>
#include <unordered_map>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;
inline int input() { int x; scanf("%d", &x); return x; }

const int mod = 1000000007;
const int maxn = 1000000;
bool nop[maxn];
int mu[maxn];
int s[maxn];

lolong power(lolong x, int k) {
	if(k < 0)
		k += mod - 1;
	lolong res = 1;
	while(k) {
		if(k & 1) (res *= x) %= mod;
		(x *= x) %= mod;
		k >>= 1;
	}
	return res;
}

lolong inv12 = power(12, -1), inv4 = power(4, -1);

lolong f(lolong n) {
	return (n * (n + 1) % mod * (n * 2 + 1) % mod * inv12 % mod + mod -
			n * (n + 1) % mod * inv4 % mod) % mod;
}

void sieve() {
	std::vector<int> Pr;
	s[1] = mu[1] = 1;
	for(int i = 2; i < maxn; i ++) {
		if(not nop[i]) {
			Pr.push_back(i);
			mu[i] = -1;
		}
		for(size_t j = 0; j < Pr.size(); j ++) {
			int p = Pr[j];
			if(1ll * i * p >= maxn)
				break;
			nop[i * p] = true;
			if(not (i % p))
				break;
			mu[i * p] = mu[i] * mu[p];
		}
		s[i] = (s[i - 1] + mu[i] * i) % mod;
	}
}

lolong suf(lolong n) {
	return (n * (n + 1) >> 1) % mod;
}

std::unordered_map<int, lolong> map;
lolong S(int n) {
	if(n < maxn)
		return s[n];
	if(map.count(n))
		return map[n];
	lolong res = mod - 1;
	for(int l = 2, r; l <= n; l = r + 1) {
		r = n / (n / l);
		res += (suf(r) - suf(l - 1)) * S(n / l);
	}
	res = (mod - res % mod) % mod;
	map[n] = res;
	/* debug("%d : %lld\n", n, res); */
	return res;
}

int main() {
	sieve();
	int T = input();
	while(T --) {
		int n = input(), a = input(), b = input();
		lolong ans = 0;
		for(int l = 1, r; l <= n; l = r + 1) {
			r = n / (n / l);
			ans += (S(r) - S(l - 1) + mod) * f(n / l) % mod;
		}
		ans %= mod;
		printf("%lld\n", ans);
	}
}
