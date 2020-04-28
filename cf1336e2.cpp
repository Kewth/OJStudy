#if 0
2020.04.26

  建出线性基，设线性基大小为 K 。如果 K 足够小，2^K 枚举出能被线性基表示出来的数即可。
因此只考虑 K 足够大的情况。
  从另一个角度考虑，给每个基构造一个数组，然后它们的异或卷积就是所有能被线性基表示的数。
那么对于基 x ，其对应的数组 X 只有 0 和 x 为 1 ，那么 FWT(X) 就只有 0 和 2 。设所有
FWT(X) 的点积是 B ，所有能被线性基表示出来的数组成数组 A ，那么有 B = FWT(A) 。而 B 只
有 0 和 2^K 两种值，所有取值为 2^K 的下标共有 2^(m-K) 个，组成了一组大小为 m - K 的线性
基。
  假设这个大小为 m - K 的线性基是已知的（事实上可以从原来的大小为 K 的线性基得到，这里
略去）。那么可以 2^(m-K) 枚举间接得到 B ，考虑怎么通过 B 求出答案。
  对于第 c 个答案，构造数组 F 只在 popcount 为 c 的数上有值为 1 ，那么 A 和 F 的异或卷
积的第 0 项就是这第 c 个答案。
  观察 FWT(F) ，不难发现 FWT(F) 第 i 项的值只与 popcount(i) 有关，对于每个 popcount = d
选出一个代表下标 2^d - 1 ，不难得出 FWT(F) 在该位置的值，设为 w[d] 。那么有了 w 数组，
B 对第 c 个答案的贡献就显而易见了。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef unsigned long long ull;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
} read;

const int maxm = 53, mod = 998244353;
ll bas[maxm];
ll fac[maxm + 1], ifac[maxm + 1];

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
	if (m > n) return 0;
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

void insert (ll x, int m) {
	for (int k = m - 1; k >= 0; k --)
		if (x >> k & 1) {
			if (bas[k]) x ^= bas[k];
			else return bas[k] = x, void();
		}
}

inline int count (ll x) {
	return __builtin_popcountll(ull(x));
}

ll a[maxm], b[maxm];
ll ans[maxm + 1], pans[maxm + 1];
int p[maxm];
bool matrix[maxm][maxm];
ll w[maxm + 1][maxm + 1];

inline void swap (int m, int X, int Y) {
	for (int i = 0; i < m; i ++)
		std::swap(matrix[i][X], matrix[i][Y]);
	std::swap(p[X], p[Y]);
}

inline void operation (int m, int i, int j) {
	for (int k = 0; k < m; k ++)
		matrix[j][k] ^= matrix[i][k];
}

void dfs (int i, ll x, ll *A, ll *B) {
	if (i < 0) return ++ B[count(x)], void();
	dfs(i - 1, x, A, B);
	dfs(i - 1, x ^ A[i], A, B);
}

int main () {
	int n = read, m = read;
	for (int i = 1; i <= n; i ++) insert(read, m);
	combinator_init(m);

	int K = 0;
	for (int k = 0; k < m; k ++)
		if (bas[k])
			a[K ++] = bas[k];

	if (K <= m - K)
		dfs(K - 1, 0, a, ans);

	else {
		for (int i = 0; i < K; i ++)
			for (int k = 0; k < m; k ++)
				matrix[m - K + i][k] = a[i] >> k & 1;

		for (int k = 0; k < m; k ++)
			p[k] = k;
		for (int i = m - 1; i >= m - K; i --) {
			int key = m - 1;
			while (!matrix[i][key]) -- key;
			swap(m, key, i);
		}

		for (int i = m - K; i < m; i ++)
			for (int j = i + 1; j < m; j ++)
				if (matrix[j][i])
					operation(m, i, j);

		for (int i = m - K; i < m; i ++)
			for (int j = 0; j < m - K; j ++)
				matrix[j][i] = matrix[i][j];
		for (int i = 0; i < m - K; i ++)
			matrix[i][i] = 1;

		/* for (int i = 0; i < m; i ++) { */
		/* 	for (int j = 0; j < m; j ++) */
		/* 		debug("%d", matrix[i][j]); */
		/* 	debug("\n"); */
		/* } */
		/* debug("\n"); */

		for (int i = 0; i < m - K; i ++)
			for (int j = 0; j < m; j ++)
				b[i] ^= ll(matrix[i][j]) << p[j];

		dfs(m - K - 1, 0, b, pans);

		/* for (int i = 0; i <= m; i ++) */
		/* 	debug("%lld\n", pans[i]); */

		for (int i = 0; i <= m; i ++)
			for (int j = 0; j <= m; j ++) {
				// XXX: 离谱，下面这个开 O2 会被错误地 skip 掉。
				/* for (int k = 0; k <= i and k <= j; k ++) { */
				for (int k = 0; k <= std::min(i, j); k ++) {
					ll now = C(j, k) * C(m - j, i - k) % mod;
					if (k & 1) w[i][j] += mod - now;
					else w[i][j] += now;
				}
				w[i][j] %= mod;
			}

		ll coe = power(2, K - m);
		for (int i = 0; i <= m; i ++) {
			for (int j = 0; j <= m; j ++)
				(ans[i] += pans[j] * w[i][j]) %= mod;
			(ans[i] *= coe) %= mod;
		}

		/* for (int i = 0; i <= m; i ++) { */
		/* 	for (int j = 0; j <= m; j ++) */
		/* 		debug(" %lld", w[i][j]); */
		/* 	debug("\n"); */
		/* } */
	}

	ll coe = power(2, n - K);
	for (int k = 0; k <= m; k ++)
		printf("%lld ", ans[k] * coe % mod);
	puts("");
}
