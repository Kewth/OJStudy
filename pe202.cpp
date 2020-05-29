#if 0
2020.05.27

  不断翻折三角形，把射线翻折成为一条直线，那么用无穷个三角形填充整个平面，射线最终是一个
从 C 点到目标点 D 的一个线段，问题转换为求多少合法点 D 。
  不妨把 CA 和 CB 作为基向量建系，那么对于 D(x, y) (x, y > 0) ，需要满足三个条件：
  1. CD 之间经过了恰好 n 条三角形的边。不难得到经过的边数就是 2x + 2y - 3 ，那么这个条件
就是 2x + 2y - 3 = n 。
  2. D 翻折前对应原来的点 C 。因为任选一个 D 把射线还原后实际上可能是一条从 A 或者 B 射
出的射线，这是不合法的，而满足这个条件就等价于 CD 向量能用整数个 (1, 1) 和 (2, -1) 表示，
也就是要满足 x = y (mod 3) 。
  3. CD 之间不经过除 C, D 以外的任何格点。这个显然就是 gcd(x, y) = 1 。

  于是得到了一个朴素做法：枚举 x ，y 就唯一确定，然后判定是否合法即可。
  把这个朴素做法用求和式表示，设 x + y = s ，那么 gcd(x, y) = gcd(x, s) ，枚举这个 gcd
莫比乌斯反演，就可以得到一个很简单的 O(1) 求和式，那么就只需要枚举 s 的所有因子算 mu 即
可。

  复杂度的一个上界是 O(n^{3/4}) ，这个上界似乎不够紧，并且大多时候是很快的，实践 1e18
内的大多数的耗时在 20s 内，选取了若干 1e17 左右的数（都存在答案）测试平均用时 2.26s 。

  波给出了一个优化，由于 mu 有值的位置质因子两两不同，pollard 分解质因数后 2^k 枚举所
有这样的值算贡献即可，这样 1e18 内的数都能在 1s 跑完。
        ▁▃▄▄▄▃▃▃▃▄▶
      ▗▇▀▔    ▔▔▔▔
     ▄▛   ▃▅━━■▄▂
    ▟▊   ▐▘     ▀▙
   ▟▜▌   ▐▖   ▋  ▐▍
  ▟▘ ▜   ▝▀▇▆●▘  ▐▌
▗▟▘   ▜▃       ▁▅▛
▔▀▼▅▄▃▃██▅▄▄▄▅■▀▔   CopyRight :)
      ▔▔▔▔▔▔
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef long long ld;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
} read;

inline ll mul(ll x, ll y, ll mod) {
	return ll(__int128(x) * y % mod);
	// FIXME: 快速乘 WA 了？
	/* x %= mod; */
	/* y %= mod; */
	/* /1* if (mod <= 1000000000) return (x % mod) * (y % mod) % mod; *1/ */
    /* ll tmp = x * y - ll(ld(x) / mod * y + 0.5) * mod; */
    /* return tmp < 0 ? tmp + mod : tmp; */
}

ll power(ll x, ll k, ll mod) {
	ll res = 1;
	while(k) {
		if(k & 1) res = mul(res, x, mod);
		x = mul(x, x, mod);
		k >>= 1;
	}
	return res;
}

bool miller(ll n, int p) {
	ll t = n - 1;
	while(!(t & 1)) t >>= 1;
	ll y = power(p, t, n), ny;
	while((t << 1) < n) {
		ny = mul(y, y, n);
		if(ny == 1 and !(y == 1 or y == n - 1)) return 0;
		t <<= 1;
		y = ny;
	}
	return y == 1;
}

bool is_prime(ll n) {
	const int len = 9, p[len] = {2, 3, 5, 7, 11, 13, 17, 19, 23};
	if(n == 1) return 0;
	for(int i = 0; i < len; i ++) if(n == p[i]) return 1;
	if(!(n & 1)) return 0;
	for(int i = 0; i < len; i ++) if(!miller(n, p[i])) return 0;
	return 1;
}

inline ll nxt(ll x, ll c, ll n) {
	ll res = mul(x, x, n) + c;
	return res >= n ? res - n : res;
}

ll pollard(ll n) {
	if (n == 4) return 2;
	ll c = 1ll * rand() * rand() % n;
	ll a = nxt(rand(), c, n);
	ll b = nxt(a, c, n);
	int lim = 2;
	while(a != b) {
		ll v = 1;
		for(int i = 0; i < lim and a != b; i ++) {
			v = mul(v, std::abs(a - b), n);
			a = nxt(a, c, n);
			b = nxt(nxt(b, c, n), c, n);
		}
		ll d = std::__gcd(v, n);
		if(d > 1) return d;
		if(lim < 128) lim <<= 1;
	}
	return pollard(n);
}

ll prime[30];
int pp;

void factor (ll n) {
	if (n == 1) return;
	if (is_prime(n)) {
		prime[pp ++] = n;
		return;
	}
	/* debug("div %lld\n", n); */
	ll x = pollard(n);
	while (x == n) x = pollard(n);
	/* debug("%lld -> %lld\n", n, x); */
	while (n % x == 0) n /= x;
	factor(n);
	factor(x);
}

void solve (ll n) {
	if (n % 2 == 0) return puts("0"), void();
	ll s = (n + 3) >> 1;
	if (s % 3 == 0) return puts("0"), void();

	pp = 0;
	factor(s);
	std::sort(prime, prime + pp);
	pp = int(std::unique(prime, prime + pp) - prime);

	ll ans = 0;
	for (int S = 0; S < (1 << pp); S ++) {
		ll d = 1, flag = 1;
		for (int i = 0; i < pp; i ++)
			if (S >> i & 1)
				d *= prime[i], flag *= -1;
		ll lim = s / d, now = (d % 3 != s % 3) ? (lim + 2) / 3 : (lim + 1) / 3;
		ans += now * flag;
	}

	printf("%lld\n", ans);
}

int main () {
#ifdef PE
	solve(12017639147);
#else
	int q = read;
	while (q --)
		solve(read);
#endif
}
