#if 0
2020.01.29

考虑链的情况，把链看做数轴，
那么对于点 u 有 g(x) = dis(u, x)^1.5 ，g 是下凸函数。
设 f(x) 为所有这样的 g(x) 乘上点权的和，那么 f 也是下凸函数。
而题目要求的就是使得 f(x) 最小的点，在数轴上可以三分。

推广到树，每个点 u 同样有 g(x) = dis(u, x)^1.5 ，这里 x 是可以取在边上的。
类似地有在一个方向上 x 离 u 越远 g(x) 越大，g 是在树意义下的“下凸函数”，
同样定义 f(x) ，那么 f 也是树意义下的“下凸函数”，
换言之存在一个点 x 使 f(x) 取到最小值，在一个反向上离 x 越远 f 取值越大。

将三分推广到树上，
链上三分就是每次找到当前区间中点，然后考虑向相邻两点移动是否会更优。
树上自然就是每次找到当前子树重心，然后考虑向所有儿子移动是否会更优。
但是有一个明显的问题是一个点的儿子数量会很多，每个暴力检查一遍复杂度会退化。

当前重心为 u ，考虑儿子 v 是否会更优，其中 dis(u, v) = w 。
把 u - v 这条边放在数轴上，在这个数轴上定义 f(x) ，其中横坐标 x 是离 u 的距离。
那么只需要判断 u 向 v 移动一点点是否能让 f 取值变小即可。
也就是求 f 在 x = 0 处的导数是否小于 0 。
而这个导数是很好算的，只需要对 u 暴力 dfs 预处理一次即可。

需要注意的是该点导数小于 0 不一定说明 v 比 u 优，
可能是最优点在 u - v 边上面，这时候两边暴力检查即可。
#endif
#include <cstdio>
#include <vector>
#include <cmath>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
} read;

const int maxn = 200005;
// int head[maxn], nxt[maxn << 1], to[maxn << 1], len[maxn << 1], hp = 1;
struct Edge {
	int to, w;
};
std::vector<Edge> G[maxn];
int val[maxn];

bool vis[maxn];
int size[maxn];
int cen, csize;
void get(int u, int n) {
	size[u] = 1;
	int now = 0;
	vis[u] = 1;
	for(Edge e : G[u])
		if(!vis[e.to]) {
			get(e.to, n);
			size[u] += size[e.to];
			now = std::max(now, size[e.to]);
		}
	vis[u] = 0;
	now = std::max(now, n - size[u]);
	if(now < csize) {
		cen = u;
		csize = now;
	}
}

int dis[maxn];
double sq[maxn], sum;
void dfs(int u, int fa) {
	sq[u] = sqrt(dis[u]) * val[u];
	sum += sq[u] * dis[u];
	for(Edge e : G[u])
		if(e.to != fa) {
			dis[e.to] = dis[u] + e.w;
			dfs(e.to, u);
			sq[u] += sq[e.to];
		}
}

double ans = 1e100;
int anspos;
void divi(int s, int n) {
	csize = 1000000000;
	get(s, n);
	int u = cen;
	// debug("divi %d get %d\n", s, u);

	dis[u] = 0;
	sum = 0;
	dfs(u, 0);
	if(sum < ans) {
		ans = sum;
		anspos = u;
	}

	// debug("%d : %.5lf\n", u, sq[u]);
	// for(Edge e : G[u])
		// if(!vis[e.to])
			// debug("%d : %.5lf\n", e.to, sq[e.to]);

	int to = 0;
	for(Edge e : G[u])
		if(!vis[e.to] and sq[u] - sq[e.to] * 2 < 0)
			to = e.to;
	if(!to) return;

	vis[u] = 1;
	if(size[to] < size[u])
		divi(to, size[to]);
	else
		divi(to, n - size[u]);
}

int main() {
	int n = read;
	for(int i = 1; i <= n; i ++)
		val[i] = read;

	for(int i = 1; i < n; i ++) {
		int u = read, v = read, w = read;
		G[u].push_back({v, w});
		G[v].push_back({u, w});
	}

	divi(1, n);
	printf("%d %.7lf\n", anspos, ans);
}
