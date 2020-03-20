#if 0
2020.03.18

贪心，先考虑最小值。
一条边如果两边都是偶数个点，那么这条边一定没有贡献，可以反证。
否则这条边一定贡献一次，原因一致。
考虑最大值，也是类似，一条边的贡献次数是两边点数的最小值，
可以证明如果没达到这个值，那么一定可以将两边的点再配对使得答案更大。
#endif
#include <cstdio>
#include <algorithm>
#include <vector>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 200005;
struct Edge { int to, w; };
std::vector<Edge> G[maxn];
int size[maxn];

ll minans, maxans;
int n;

void dfs(int u, int fa, int fw) {
	size[u] = 1;
	for(Edge e : G[u])
		if(e.to != fa) {
			dfs(e.to, u, e.w);
			size[u] += size[e.to];
		}
	if(size[u] & 1)
		minans += fw;
	maxans += 1ll * std::min(size[u], n - size[u]) * fw;
}

int main() {
	int T = read;
	while(T --) {
		n = read << 1;
		for(int i = 1; i <= n; i ++) G[i].clear();
		for(int i = 1; i < n; i ++) {
			int u = read, v = read, w = read;
			G[u].push_back({v, w});
			G[v].push_back({u, w});
		}
		minans = maxans = 0;
		dfs(1, 0, 0);
		printf("%lld %lld\n", minans, maxans);
	}
}
