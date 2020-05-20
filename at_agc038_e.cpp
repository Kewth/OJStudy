#if 0
2020.05.20

  《喂鸽子》和《百鸽笼》的结合？
  还是一波 min-max 容斥，问题转换为求 F(S) 表示只考虑集合 S 中的点，至少一个位置满足条件
的期望时间。利用操作序列求 F(S) ，枚举第一个满足条件的位置，剩下的数用背包背起来，对于所
有可能的序列长度算贡献即可。
  注意到 F(S) 对答案的贡献系数只与 S 的大小的奇偶性以及 sum(A) 有关，事实上枚举 S 是没有
必要的，直接对于每个序列长度背包 DP 求出 f[i][j] = sum([sum(A) = i, |S| mod 2 = j] F(S))
然后枚举第一个满足条件的位置把它在背包里删掉算贡献即可，复杂度 O(sum(A) sum(B)^2) 。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator () (a...); }
} read;

const int maxn = 405, mod = 998244353;
ll fac[maxn], ifac[maxn], inv[maxn];
ll coe[maxn][maxn];
ll f[maxn][maxn], g[maxn][maxn];
ll tmp[maxn];
int A, B;

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

	inv[1] = 1;
	for (int i = 2; i <= n; i ++)
		inv[i] = (mod - mod / i) * inv[mod % i] % mod;
}

void add (int a, int b) {
	tmp[0] = 1;
	for (int k = 1; k < b; k ++)
		tmp[k] = tmp[k - 1] * a % mod;
	for (int i = A; i >= 0; i --)
		for (int j = B; j >= 0; j --)
			for (int k = 0; k < b; k ++) {
				(f[i + a][j + k] += g[i][j] * C(j + k, j) % mod * tmp[k]) %= mod;
				(g[i + a][j + k] += f[i][j] * C(j + k, j) % mod * tmp[k]) %= mod;
			}
	A += a;
	B += b - 1;
}

void erase (int a, int b) {
	A -= a;
	B -= b - 1;
	tmp[0] = 1;
	for (int k = 1; k < b; k ++)
		tmp[k] = tmp[k - 1] * a % mod;
	for (int i = 0; i <= A; i ++)
		for (int j = 0; j <= B; j ++)
			for (int k = 0; k < b; k ++) {
				(f[i + a][j + k] += (mod - g[i][j]) * C(j + k, j) % mod * tmp[k]) %= mod;
				(g[i + a][j + k] += (mod - f[i][j]) * C(j + k, j) % mod * tmp[k]) %= mod;
			}
}

int a[maxn], b[maxn];

int main () {
	combinator_init(400);
	int n = read;
	f[0][0] = 1;
	for (int i = 1; i <= n; i ++) {
		read(a[i], b[i]);
		add(a[i], b[i]);
	}

	for (int i = 0; i <= A; i ++) {
		coe[i][0] = inv[i];
		for (int j = 1; j <= B + 1; j ++)
			coe[i][j] = coe[i][j - 1] * inv[i] % mod;
		for (int j = 0; j <= B + 1; j ++)
			(coe[i][j] *= j) %= mod;
	}

	ll ans = 0;
	for (int i = 1; i <= n; i ++) {
		erase(a[i], b[i]);
		ll sf = 0, sg = 0;
		/* for (int x = 0; x <= A; x ++) { */
		/* 	for (int y = 0; y <= B; y ++) */
		/* 		debug(" %lld-%lld", f[x][y], g[x][y]); */
		/* 	debug("\n"); */
		/* } */
		/* debug("\n"); */
		for (int x = 0; x <= A; x ++)
			for (int y = 0; y <= B; y ++) {
				(sf += f[x][y] * C(y + b[i] - 1, y) % mod * coe[x + a[i]][y + b[i]]) %= mod;
				(sg += g[x][y] * C(y + b[i] - 1, y) % mod * coe[x + a[i]][y + b[i]]) %= mod;
			}
		(sf *= power(a[i], b[i])) %= mod;
		(sg *= power(a[i], b[i])) %= mod;
		add(a[i], b[i]);
		ans += sf + mod - sg;
	}

	printf("%lld\n", ans * A % mod);
}
