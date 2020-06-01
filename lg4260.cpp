#if 0
2020.06.01

  首先由于胜局完全确定，每种可能的局面的出现概率完全相等，P 就是个幌子。
  考虑对于 T = 1 求答案，设 s[i] 表示 i 轮游戏后败局减去胜局的值，那么不难发现最后的得分
就是 n - m + max(s) ，设 X = s[i] ，问题转换为求 E(X) 。
  枚举所有 X = k 考虑求 P(X = k) ，不妨考虑求 P(X >= k) ，那么就是在网格图上从 (0, 0) 走
到 (n, m) ，必须经过 y = x + s 这条直线的路径数，显然可以用折线法统计，整理式子后，问题
的瓶颈在于求：
    sum([k <= lim] C(n + m, k))
  直接求是 O(lim) 的，不妨设这个值为 F(n + m, lim) ，注意到 F(n, m) 推到 F(n +/- 1, m)
和 F(n, m +/- 1) 都是不难做到 O(1) 的，把所有询问需要的 F 放一起用莫队一起求出来即可。
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
#include <cmath>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 500005, mod = 1000000007;
ll fac[maxn], ifac[maxn];

inline ll power (ll x, int k) {
	if (k < 0) k += mod - 1;
	ll res = 1;
	while (k) {
		if (k & 1) (res *= x) %= mod;
		(x *= x) %= mod;
		k >>= 1;
	}
	return res;
}

inline ll C (int n, int m) {
	if (n < m) return 0;
	return fac[n] * ifac[m] % mod * ifac[n - m] % mod;
}

void combinator_init (int n) {
	fac[0] = 1;
	for (int i = 1; i <= n; i ++)
		fac[i] = fac[i - 1] * i % mod;
	ifac[n] = power(fac[n], -1);
	for (int i = n; i; i --)
		ifac[i - 1] = ifac[i] * i % mod;
}

struct oper {
	int n, m, id; // C(n, 0~m)
} op[maxn];
ll ans[maxn];
int qn[maxn], qm[maxn];

int main () {
	combinator_init(500000);
	int q = read;
	read.operator int();

	for (int i = 1; i <= q; i ++) {
		int n = qn[i] = read, m = qm[i] = read;
		int s = std::max(m - n, 0);
		ans[i] = C(n + m, m) * s;
		op[i] = {n + m, m - s - 1, i};
	}

	int B = 700;
	std::sort(op + 1, op + q + 1, [B] (oper a, oper b) {
				if (a.n / B == b.n / B)
					return a.n / B & 1 ? a.m < b.m : a.m > b.m;
				return a.n < b.n;
			});

	int n = 0, m = 0;
	ll now = 1, i2 = (mod + 1) >> 1;
	for (int i = 1; i <= q; i ++) {
		int N = op[i].n, M = op[i].m;
		while (n < N)
			now = (now * 2 + mod - C(n ++, m)) % mod;
		while (n > N)
			now = (now + C(-- n, m)) * i2 % mod;
		while (m < M)
			if ((now += C(n, ++ m)) >= mod)
				now -= mod;
		while (m > M)
			if ((now -= C(n, m --)) < 0)
				now += mod;
		ans[op[i].id] += now;
	}


	for (int i = 1; i <= q; i ++) {
		n = qn[i];
		m = qm[i];
		ans[i] = (ans[i] % mod * power(C(m + n, m), -1) + n + mod - m) % mod;
		printf("%lld\n", ans[i]);
	}
}
