#if 0
2020.05.20

  把每次操作选择的位置构成的序列称作操作序列，一个 naive 的想法是每个操作序列是以等概率
出现的，因此每个点作为操作序列最后一个点的概率就是 a[i] / sum 。
  然而操作序列并不是等概率出现的，因为当一个点的数被选完后其他点的选择概率会发生改变。
  对于一个点 i ，计算其在最后出现的概率较为困难，而计算其第一个被选完的概率是相对较为简
单的，因为在它被选完前没有任何点被选完，每个点被选中的概率始终不变。考虑两者的关系，利用
子集容斥，不难得出 A(i) = sum((-1)^{|S|+1} B(S, i)) ，其中 A(i) 表示第 i 个点在所有点中
最后被选完的概率，B(S, i) 表示只考虑 S 集合内的点，i 在其中第一个被选完的概率。
  B 的计算只需做背包 DP ，枚举 S 内每个点再枚举插入多少个数，用组合数算贡献即可。
  注意到实际上枚举集合是没有必要的，不妨设 C(k, i) = sum([|S|=k] B(S, i)) ，直接背包 DP
也能求出 C ，此时复杂度 O(n^6) ，这里认为 n 与 a 同阶。
  每次求 A(i) 也没必要重新做一遍背包，预先做一遍背包后对于每个 A(i) 在背包里删掉 i 这个
点的贡献即可，复杂度 O(n^5) 。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 35, mod = 998244353;
int a[maxn];
ll f[maxn][maxn * maxn], g[maxn][maxn * maxn];
ll fac[maxn * maxn], ifac[maxn * maxn];
int size, len;

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

void add (int lim) {
	for (int i = size; i >= 0; i --)
		for (int j = len; j >= 0; j --)
			for (int x = 0; x < lim; x ++)
				(f[i + 1][j + x] += f[i][j] * C(j + x, x)) %= mod;
	++ size;
	len += lim - 1;
}

void erase (int lim) {
	-- size;
	len -= lim - 1;
	for (int i = 0; i <= size; i ++)
		for (int j = 0; j <= len; j ++)
			for (int x = 0; x < lim; x ++)
				(f[i + 1][j + x] += (mod - f[i][j]) * C(j + x, x)) %= mod;
}

int main () {
	int n = read;
	combinator_init(900);
	f[0][0] = 1;
	for (int i = 1; i <= n; i ++) add(a[i] = read);

	for (int i = 0; i <= size; i ++) {
		ll x = power(i, -1);
		g[i][0] = 1;
		for (int j = 1; j <= len + 1; j ++)
			g[i][j] = g[i][j - 1] * x % mod;
	}

	for (int i = 1; i <= n; i ++) {
		erase(a[i]);
		int k = a[i] - 1;
		ll ans = 0;
		for (int s = 0; s <= size; s ++) {
			ll sum = 0;
			for (int l = 0; l <= len; l ++) {
				/* debug("f[%d][%d] = %lld\n", s, l, f[s][l]); */
				ll now = f[s][l] * C(l + k, k) % mod;
				(sum += now * g[s + 1][l + k + 1]) %= mod;
			}
			if (s & 1) ans += mod - sum;
			else ans += sum;
		}
		printf("%lld ", ans % mod);
		add(a[i]);
	}
	puts("");
}
