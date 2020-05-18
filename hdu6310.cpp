#if 0
2019.10.10

朴素 DP 设 f[n][x] 表示答案，转移枚举最大的数的位置，以及两边的权值和，乘个组合数即可。
不难发现这构成了一个笛卡尔树的结构，由此可以证明有值的 x 是 O(nlogn) 的，
另外实践 x 到 800 即可，开太大会 MLE 。

考虑优化，将 f[n] 看做多项式，不难发现转移其实只需要枚举最大的数的位置，
而权值和的枚举和分配实际上是在做卷积。
那么用任意模数 NTT 或者 MTT 或许就可以做了，但是有办法避开它，
随便取点值预处理每个 f[n] 的点值表示，对于询问 (n, k) ，
只需拉格朗日插值算出 f[n] 的 x^k 的系数即可，由于询问较少，这是可以接受的。

至于拉格朗日插值求多项式 x^k 的系数的方法，
依次考虑每个 L_i(x) ，分母和 Y_i 是常数可以直接算，
而分子部分是所有 (x - X_j) 的乘积，只要算出这个的 x^k 系数即可，
而由于是 V - 1 （ V 表示点值的数量）个简单多项式相乘，
其实 x^k 的系数就是在之中选 V - k - 1 个常数。
DP 预处理 pre[i][k] 表示 (x - X_1) 到 (x - X_i) 中选 k 个常数的系数和，
同理 suf[i][k] 表示 (x - X_i) 到 (x - X_V) 中选 k 个常数的系数和即可。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;

inline int input() { int x = 0; scanf("%d", &x); return x; }

const int N = 200, V = 800;
const int maxn = N + 2, maxv = V + 2;
lolong f[maxn][maxv];
lolong X[maxv][maxv];
lolong C[maxn][maxn];
lolong pre[maxv][maxv], suf[maxv][maxv];

int mod;
lolong power(lolong x, int k) {
	if(k < 0) k += mod - 1;
	lolong res = 1;
	while(k) {
		if(k & 1) (res *= x) %= mod;
		(x *= x) %= mod;
		k >>= 1;
	}
	return res;
}

lolong la(int n, int i, int k) {
	lolong A = 1;
	for(int j = 1; j <= V; j ++)
		if(i != j)
			(A *= i + mod - j) %= mod;
	lolong B = 0;
	for(int l = 0; l <= V - k - 1; l ++)
		B += pre[i - 1][l] * suf[i + 1][V - k - 1 - l] % mod;
	B %= mod;
	return B * power(A, -1) % mod * f[n][i] % mod;
}

int main() {
	mod = input();

	for(int i = 0; i <= N; i ++) {
		C[i][0] = 1;
		for(int j = 1; j <= i; j ++)
			C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % mod;
	}

	for(int i = 0; i <= V; i ++) {
		pre[i][0] = 1;
		for(int j = 1; j <= i; j ++)
			pre[i][j] = (pre[i - 1][j] + pre[i - 1][j - 1] * (mod - i)) % mod;
	}

	for(int i = V + 1; i; i --) {
		suf[i][0] = 1;
		for(int j = 1; j <= V - i + 1; j ++)
			suf[i][j] = (suf[i + 1][j] + suf[i + 1][j - 1] * (mod - i)) % mod;
	}

#if 0 // 系数表示
	f[0][0] = 1;
	for(int i = 1; i <= N; i ++)
		for(int x = 0; x <= V; x ++) {
			for(int j = 0; j < i; j ++) {
				int t = std::min(j, i - j - 1) + 1;
				for(int y = 0; y + t <= x; y ++)
					f[i][x] += f[j][y] * f[i - j - 1][x - y - t] % mod *
						C[i - 1][j] % mod;
			}
			f[i][x] %= mod;
			if(f[i][x])
				debug("%d %d : %lld\n", i, x, f[i][x]);
		}
#else // 点值表示
	for(int i = 1; i <= V; i ++)
		f[0][i] = 1;
	for(int i = 0; i <= V; i ++)
		for(int j = 1; j <= V; j ++)
			X[i][j] = power(j, i);

	for(int i = 1; i <= N; i ++) {
		for(int j = 0; j < i; j ++) {
			int t = std::min(j, i - j - 1) + 1;
			for(int k = 1; k <= V; k ++)
				f[i][k] += f[j][k] * f[i - j - 1][k] % mod *
					X[t][k] % mod * C[i - 1][j] % mod;
		}
		for(int k = 1; k <= V; k ++)
			f[i][k] %= mod;
		/* for(int k = 1; k <= V; k ++) */
		/* 	debug(" %lld", f[i][k]); */
		/* debug("\n"); */
	}
#endif

	while(1) {
		int n = input(), k = input();
		if(!n) break;
		if(k > V)
			puts("0");
		else {
			lolong ans = 0;
			for(int i = 0; i <= V; i ++)
				ans += la(n, i, k);
			printf("%lld\n", ans % mod);
			/* debug("la:\n"); */
			/* for(int i = 0; i <= V; i ++) */
			/* 	debug("la %d = %lld\n", i, la(n, i, k)); */
		}
	}
}
