#if 0
2020.05.08

  考虑逐个加入右边的每个点，假设当前加入了 k 个点。对于左边每个大小为 k 的点集，称为单位
集合，那么用 DP 维护对于每个单位集合的集合（集合的族），所有满足所有到当前考虑的 k 个点
存在完美匹配的单位集合的集合恰好是这个状态的图的概率和。
  转移枚举新加入的点的所有 2^n 种连边情况，然后把每个存在完美匹配的单位集合扩展到新的存
在完美匹配的单位集合，把它们构成的族作为转移的新状态即可。
  注意到族的总数有 2^C(7, 3) 个，存不下，用 map 动态存储状态即可，事实上需要用到的状态最
多只有 30263 个。
#endif
#include <cstdio>
#include <algorithm>
#include <map>
#include <vector>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef size_t si;
typedef std::pair<ll, ll> par;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 7, mod = 1000000007;
ll pro[maxn][maxn];
std::map<ll, ll> f[maxn + 1];
std::vector<int> vs[maxn + 1];
si vid[1 << maxn];

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

int count (int S) { return __builtin_popcount(unsigned(S)); }

int main () {
	int n = read;
	for (int i = 0; i < n; i ++)
		for (int j = 0; j < n; j ++)
			pro[i][j] = read * power(100, -1) % mod;

	for (int S = 0; S < (1 << n); S ++) {
		vid[S] = vs[count(S)].size();
		vs[count(S)].push_back(S);
	}

	f[0][1] = 1;
	for (int k = 0; k < n; k ++) {
		for (int S = 0; S < (1 << n); S ++) {
			ll p = 1;
			for (int i = 0; i < n; i ++)
				(p *= (S >> i & 1) ? pro[i][k] : (mod + 1 - pro[i][k])) %= mod;
			for (par pr : f[k]) {
				ll A = pr.first, x = pr.second, B = 0;
				for (si i = 0; i < 60; i ++)
					if (A >> i & 1) {
						int T = vs[k][i];
						for (int j = 0; j < n; j ++)
							if (S >> j & 1 and !(T >> j & 1))
								B |= 1ll << vid[T ^ (1 << j)];
					}
				(f[k + 1][B] += x * p) %= mod;
			}
		}
		debug("%lu\n", f[k].size());
	}

	printf("%lld\n", f[n][1]);
}
