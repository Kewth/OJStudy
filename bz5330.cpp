/*
 * Since g++10 is released, some characters is not valid inside #if 0 :(
 * So, why not using clang++? :D

 * Date:
    2020.06.10

 * Solution:
 * 回文串计数，分离算贡献，反演，大数分解

    如果不考虑循环移位，回文串的个数显然是 g(n) = K^ceil(n/2) ，考虑上循环移位的话，设一
个回文串的最小循环节为 k ，那么一个自然的想法是它对答案贡献恰好 k 次。

    但稍加观察可以发现并不尽然，当 k 为偶数的时候循环移位 k / 2 次会得到另一个回文串，那
么这两个回文串会对同一批串产生贡献，因此可以考虑把贡献平摊，每个串的对答案贡献 k / 2 次。
设 h(x) 表示循环节为 x 的串的贡献系数，有 h(2k + 1) = 2k + 1, h(2k) = k 。

    那么答案写出来自然就是 sum([x | n] h(x) f(x)) ，其中 f(x) 是循环节恰为 x 的回文串数。
f 是很难计算的，但观察 f 和 g 之间的联系，不难发现有 g(n) = sum([x | n] f(x)) ，换言之 g
莫比乌斯反演后的结果就是 f （事实上这里不太严谨，有混淆概念之嫌），那么 f 代换后交换求和
顺序，就是要对每个 n 的因子 d 求 sum([k | n/d] h(kd) mu(k)) 。

    如果 h(kd) 能拆成 k h(d) ，把 h(d) 提出去后里头就是一个狄利克雷卷积（卷恒等函数），可
以很好维护。但不见得总能拆开，不能拆开当且仅当 k 为偶数而 d 为奇数，也就是 d 为奇数而 n/d
为偶数时会有这种情况，此时 h(kd) 可以拆成 h(k) d ，设 v(n) = sum([x | n] h(x) mu(x)) ，稍
加观察可以发现 n 为偶数的时候有 v(n) = 0 恒成立。

    关于上述的概念混淆，需要注意的是 f(x) 与 n 无关，准确的定义为 f(x) 是长度为 x 的没有
循环节的字符串数量。

 * Digression:
    Miller-rabin 和 Porllard-rho 都懒得做优化了，还是原始的版本更自然。

 * CopyRight:
          ▁▃▄▄▄▃▃▃▃▄▶
        ▗▇▀▔    ▔▔▔▔
       ▄▛   ▃▅━━■▄▂
      ▟▊   ▐▘     ▀▙
     ▟▜▌   ▐▖   ▋  ▐▍
    ▟▘ ▜   ▝▀▇▆●▘  ▐▌
  ▗▟▘   ▜▃       ▁▅▛
  ▔▀▼▅▄▃▃██▅▄▄▄▅■▀▔
        ▔▔▔▔▔▔
 */

#include <cstdio>
#include <algorithm>
#include <map>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef std::pair<ll, int> par;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
} read;

inline ll mul (ll a, ll b, ll c) {
	return __int128(a) * b % c;
}

ll power (ll x, ll k, ll mod) {
	ll res = 1;
	while (k) {
		if (k & 1) res = mul(res, x, mod);
		x = mul(x, x, mod);
		k >>= 1;
	}
	return res;
}

bool miller (ll n, int p) {
	ll x = n - 1, test = power(p, x, n);
	if (test != 1) return 0;
	while (!(x & 1) and test == 1) {
		x >>= 1;
		test = power(p, x, n);
		if (test != 1 and test != n - 1) return 0;
	}
	return 1;
}

bool is_prime (ll n) {
	int prime[] = {2, 3, 5, 7, 11, 13, 17, 19, 23};
	for (int p : prime) if (n == p) return 1;
	for (int p : prime) if (n % p == 0) return 0;
	for (int p : prime) if (!miller(n, p)) return 0;
	return 1;
}

ll gcd (ll a, ll b) {
	if (!b) return a;
	return gcd(b, a % b);
}

ll nxt (ll x, ll c, ll n) {
	ll res = mul(x, x, n) + c;
	return res >= n ? res - n : res;
}

ll porllard (ll n) {
	if (n == 4) return 2;
	ll c = (rand() * (ll(RAND_MAX) + 1) + rand()) % n;
	ll a = nxt(rand(), c, n), b = nxt(a, c, n);
	while (a != b) {
		ll g = gcd(n, std::abs(a - b));
		if (g > 1 and g < n) return g;
		a = nxt(a, c, n);
		b = nxt(b, c, n);
		b = nxt(b, c, n);
	}
	return porllard(n);
}

std::map<ll, int> get;
void factor (ll n, int coe) {
	if (n == 1) return;
	if (is_prime(n)) return get[n] += coe, void();
	ll d = porllard(n);
	int k = 0;
	while (n % d == 0) n /= d, ++ k;
	factor(n, coe);
	factor(d, coe * k);
}

par pr[100];
ll ans;
void dfs (int i, ll d, ll c, ll n, ll K, ll mod) {
	if (!i) {
		if (d & 1 and !(n / d & 1)) return;
		ll g = power(K, (d + 1) >> 1, mod);
		ll h = d & 1 ? d : d >> 1;
		ans += mul(mul(g, h, mod), c, mod);
		return;
	}
	for (int k = 0; k <= pr[i].second; k ++) {
		if (k) d *= pr[i].first;
		dfs(i - 1, d, k == pr[i].second ? c : c * (1 - pr[i].first), n, K, mod);
	}
}

int main () {
	int T = read;
	while (T --) {
		ll n = read, K = read, mod = read;
		get.clear();
		factor(n, 1);
		int pp = 0;
		for (par p : get)
			pr[++ pp] = p;
		ans = 0;
		dfs(pp, 1, 1, n, K, mod);
		ans %= mod;
		if (ans < 0) ans += mod;
		printf("%lld\n", ans);
	}
}
