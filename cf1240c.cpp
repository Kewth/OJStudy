#if 0
2020.04.09

问题相当于给边染色 1 到 k ，同色边必须是匹配，最大化被染色的边权和。
DP 设 g[u], h[u] 分别表示在 u 子树内，u 的儿子边是否被染满了 k 中颜色的前提下的最大权。
转移对于每个儿子 v ，可以发现如果对 (u, v) 染色，收益是 g[v] + w(u, v) ，否则收益是 h[v] 。
将两个收益差值排序，选择收益差值最大的若干儿子染色即可。
#endif
#include <cstdio>
#include <algorithm>
#include <vector>
#include <functional>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
} read;

const int maxn = 500005;
struct Edge { int v, w; };
std::vector<Edge> G[maxn];
ll g[maxn], h[maxn];

int m;
void dp (int u, int fa) {
	std::vector<ll> tmp;
	ll sum = 0;
	for (Edge e : G[u])
		if (e.v != fa) {
			dp(e.v, u);
			sum += h[e.v];
			tmp.push_back(g[e.v] + e.w - h[e.v]);
		}
	g[u] = h[u] = sum;
	std::sort(tmp.begin(), tmp.end(), std::greater<ll> ());
	int tot = 0;
	for (ll x : tmp)
		if (x > 0) {
			++ tot;
			if (tot <= m - 1) g[u] += x;
			if (tot <= m) h[u] += x;
		}
	/* debug("%d : %lld %lld\n", u, g[u], h[u]); */
}

int main () {
	int T = read;
	while (T --) {
		int n = read;
		read(m);
		for (int i = 1; i <= n; i ++) G[i].clear();
		for (int i = 1; i < n; i ++) {
			int u = read, v = read, w = read;
			G[u].push_back({v, w});
			G[v].push_back({u, w});
		}
		dp(1, 0);
		printf("%lld\n", h[1]);
	}
}
