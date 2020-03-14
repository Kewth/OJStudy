#if 0
2020.03.13

假设操作只进行一轮。
那么每个点 u 对答案的贡献一定是一个系数 coe[u] 乘上它的权值 val[u] 。
考虑模拟一轮操作求出这个贡献系数，度数分块，
对于度数小的点按定义暴力算，对于度数大的点打标记。
这样求出贡献系数 coe 后，如果一个点没有出现在序列中但是 val[u] * coe[u] > 0 ，
那么这个点对答案的贡献是不收敛的。
否则，该点第一轮的贡献为 x = val[u] * coe[u] ，假设在序列中出现了 k 次，
那么其在第二轮的贡献就是 x / 2^k ，在第三轮是 x / 2^2k ...
通过无穷等比数列求和可以算出该点对全局的贡献。
#endif
#include <cstdio>
#include <vector>
#include <cmath>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
} read;

const int maxn = 100005, mod = 1000000007;
struct Big {
	int to, tag;
};
std::vector<Big> tobig[maxn];
std::vector<int> G[maxn];
int val[maxn], now[maxn], cnt[maxn], coe[maxn];
int seq[maxn];

ll power(ll x, int k) {
	if(k < 0) k += mod - 1;
	ll res = 1;
	while(k) {
		if(k & 1) (res *= x) %= mod;
		(x *= x) %= mod;
		k >>= 1;
	}
	return res;
}

int main() {
	int n = read, m = read, k = read;
	for(int i = 1; i <= n; i ++)
		val[i] = read;
	for(int i = 1; i <= k; i ++)
		seq[i] = read;
	for(int i = 1; i <= m; i ++) {
		int u = read, v = read;
		G[u].push_back(v);
		G[v].push_back(u);
	}

	int inv2 = (mod + 1) >> 1;
	size_t B = size_t(sqrt(m * 1));

	for(int i = 1; i <= n; i ++)
		now[i] = 1;

	for(int u = 1; u <= n; u ++)
		if(G[u].size() > B)
			for(int v : G[u])
				tobig[v].push_back({u, 0});

	for(int i = 1; i <= k; i ++) {
		int u = seq[i];
		if(G[u].size() <= B)
			for(int v : G[u])
				if((coe[v] += now[v]) >= mod)
					coe[v] -= mod;
		for(Big &b : tobig[u]) {
			int x = b.to;
			coe[u] = (coe[u] + 1ll * (cnt[x] - b.tag) * now[u]) % mod;
			b.tag = cnt[x];
		}
		now[u] = 1ll * now[u] * inv2 % mod;
		++ cnt[u];
	}

	for(int u = 1; u <= n; u ++)
		for(Big &b : tobig[u]) {
			int x = b.to;
			coe[u] = (coe[u] + 1ll * (cnt[x] - b.tag) * now[u]) % mod;
			b.tag = cnt[x];
		}

	ll ans = 0;
	for(int i = 1; i <= n; i ++)
		if(coe[i] and val[i] and !cnt[i])
			return puts("-1"), 0;
		else
			(ans += 1ll * val[i] * coe[i] % mod *
			 power(mod + 1 - now[i], -1)) %= mod;

	printf("%lld\n", ans);
}

