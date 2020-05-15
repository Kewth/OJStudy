#if 0
2020.05.13

  设 F[i] 表示游戏在第 i 个位置停止对答案的贡献，那么答案就是 sum(F[i]) 。
  但是直接求 F[i] 是很困难的，因为有很多限制，比如在 i 获得所有饼干前不能有其他位置获得
所有饼干。
  考虑忽略掉这个限制，设 G[i] 表示游戏永不停止，第 i 个位置第一次获得所有饼干的期望时间。
  那么不难发现 G[i] 只与 a[i] 有关，设 H[x] 表示 a[i] = x 时的 G[i] ，那么 H[x] 有三种转
移，可以列为： H[x] = A[x] H[x - 1] + B[x] H[x] + C[x] H[x + 1] ，线性消元即可求出 H 。
那么考虑 G[i] 和 F 的关系，枚举第一个获得所有饼干的位置 j ，可以得到：
    G[i] = sum(F[j] + C(j, i) P[j])
  其中，C(j, i) 表示从 j 获得所有饼干开始游戏，i 第一次获得所有饼干的期望时间，不难发现
当 i = j 时 C(j, i) = 0 ，否则 C(j, i) = H[0] 。
  而 P[j] 表示第一个获得所有饼干的位置是 j 的概率，这个也很难计算，但是有 sum(P[j]) = 1 。
  对于所有 i ，把上式加起来，可以得到：
    sum(G[i]) = n sum(F[i]) + sum(C(j, i) P[j])
              = n sum(F[i]) + sum(P[j] sum(H[0] [i != j]))
              = n sum(F[i]) + H[0] sum(P[j] sum([i != j]))
              = n sum(F[i]) + H[0] sum(P[j]) (n - 1)
              = n sum(F[i]) + (n - 1) H[0]
  那么 sum(F[i]) 的值就可以通过 H 简单求出了。

  UPDATE:
  学到许多，由于 H[i] = A H[i - 1] + B H[i] + C H[i + 1] 满足 A + B + C = 1 ，虽然 H 不能
直接递推，但是差分后 H[i] - H[i - 1] 是可以直接递推的，并且在这里它递推的分母是在预处理范
围内的值，因此可以优化到 O(m + logP) 。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 300005, mod = 998244353;
int a[maxn];
ll f[maxn], g[maxn];
ll pi[maxn], pd[maxn], ps[maxn];

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

int main () {
	int n = read, m = 0;
	for (int i = 1; i <= n; i ++)
		m += a[i] = read;

	ll Invm = power(m, -1), Invn_ = power(n - 1, -1);
	for (int x = 0; x <= m; x ++) {
		pi[x] = (m - x) * Invm % mod * Invn_ % mod;
		ps[x] = (m - x) * Invm % mod * (mod + 1 - Invn_) % mod;
		pd[x] = x * Invm % mod;
	}

	for (int x = 0; x < m; x ++) {
		f[x] = (pi[x] + pd[x] + ps[x] + (x ? f[x - 1] : 0) * pd[x]) % mod;
		g[x] = pi[x];
		ll X = ((x ? g[x - 1] : 0) * pd[x] + ps[x]) % mod;
		ll Inv = power(mod + 1 - X, -1);
		(f[x] *= Inv) %= mod;
		(g[x] *= Inv) %= mod;
	}

	for (int x = m; x; x --)
		(f[x - 1] += g[x - 1] * f[x]) %= mod;

	ll ans = 0;
	for (int i = 1; i <= n; i ++)
		ans += f[a[i]];
	ans -= (n - 1) * f[0];
	ans %= mod;
	ans += mod;
	(ans *= power(n, -1)) %= mod;
	printf("%lld\n", ans);

	/* for (int x = 0; x <= m; x ++) */
	/* 	debug("%d: %lld %lld %lld\n", x, pi[x], pd[x], f[x]); */

	/* for (int x = 1; x < m; x ++) */
	/* 	if (f[x] != (1 + pi[x] * f[x + 1] + ps[x] * f[x] + pd[x] * f[x - 1]) % mod) */
	/* 		return 1; */
	/* for (int x = 0; x <= m; x ++) */
	/* 	if ((pd[x] + ps[x] + pi[x]) % mod != 1) */
	/* 		return 1; */
}
