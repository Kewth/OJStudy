#if 0
2020.03.21

考虑一个暴力的贪心做法，从大到小枚举 S = x + y + z ，
然后对于所有 (x, y, z) ，如果之前没有与之连边的点被选，那么这个点一定要出现在最优解中。
可以给边定向，边从小连到大，那么整个图就是 DAG ，在 DAG 中抽象这个贪心：
每次选择一个点满足其到的点都没有被选，然后删掉选择它加入最优解集合。
那么一个点被选当且仅当其到的点都没被选，一个点没被选当且仅当其到的点存在被选的点（或没有出度）。
这可以对应到博弈中的必胜必败态，这个 DAG 可以看做博弈转移图，答案就是求所有必败态的权值和。

然而点数很大。
考虑对于一个 (x, y, z) ，如何快速求出其必胜必败态，
每次移动只能移动一维，这个博弈三维独立，就相当于每个维度有一个子游戏。
对于每一维求出 SG 值 f[x], g[y], h[z] ，三者异或和就是这个的 SG 值。
考虑计数，FWT 做异或卷积即可（事实上也可以三维暴力枚举 SG 值，SG 值的上界是 O(sqrt(M)) 的）。
#endif
#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 200005, mod = 998244353;
std::vector<int> G[maxn];
int sg[3][maxn];
ll f[3][maxn], g[maxn];
ll po[maxn * 3];

void FWT (ll *a, int n) {
	for (int m = 1; m < n; m <<= 1)
		for (int i = 0; i < n; i += m << 1)
			for (int k = i; k < i + m; k ++) {
			ll x = a[k], y = a[k + m];
			(a[k] = x + y) %= mod;
			(a[k + m] = x + mod - y) %= mod;
		}
}

void iFWT (ll *a, int n) {
	FWT(a, n);
	ll inv = mod - (mod - 1) / n;
	for (int i = 0; i < n; i ++)
		(a[i] *= inv) %= mod;
}

int main () {
	int n = read, len = 1;
	while (len < n)
		len <<= 1;

	po[0] = 1;
	ll bs = 1000000000000000000ll % mod;
	for (int i = 1; i <= n * 3; i ++)
		po[i] = po[i - 1] * bs % mod;

	for (int o = 0; o < 3; o ++) {
		int m = read;
		for (int i = 1; i <= n; i ++)
			G[i].clear();
		for (int i = 1; i <= m; i ++) {
			int u = read, v = read;
			if (u < v) G[u].push_back(v);
			if (v < u) G[v].push_back(u);
		}
		for (int i = n; i; i --) {
			std::set<int> mex;
			for (int j : G[i])
				mex.insert(sg[o][j]);
			while (mex.count(sg[o][i]))
				++ sg[o][i];
		}
		for (int i = 1; i <= n; i ++)
			(f[o][sg[o][i]] += po[i]) %= mod;
		FWT(f[o], len);
	}

	for (int i = 0; i < len; i ++)
		g[i] = f[0][i] * f[1][i] % mod * f[2][i] % mod;
	iFWT(g, len);

	printf("%lld\n", g[0]);
}
