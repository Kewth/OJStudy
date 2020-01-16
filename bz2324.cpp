#if 0
2020.01.15

每个人摧毁的建筑构成一个集合，这些集合是全集的一个划分，
并且每个人要按从小到大的顺序摧毁，从摧毁 i 到摧毁 j 之间不能走比 j 大的点。

floyd 预处理 d[i][j] 表示从摧毁 i 到摧毁 j 的最短距离。
建新图，每个点对 (i < j) 有边 (i -> j) ，容量为 1 费用为 d[i][j] 。
那么每个人对应一条 S 到 T 的流量，将 S 向 0 连边，所有点向 T 连边。
要求每个人的集合是全集的划分，每个点就必须被经过恰好一次，
也就是说每个点的流量下界为 1 上界也为 1 。
这个图的最小费用可行流即为答案。
#endif
#include <cstdio>
#include <algorithm>
#include <queue>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 305, maxm = 23333;
int head[maxn], nxt[maxm << 1], to[maxm << 1], cap[maxm << 1], cost[maxm << 1], hp = 1;
inline void add(int u, int v, int ca, int co) {
	if((hp & 1) and !ca) return;
	nxt[++ hp] = head[u];
	head[u] = hp;
	to[hp] = v;
	cap[hp] = ca;
	cost[hp] = co;
	if(!(hp & 1)) add(v, u, 0, - co);
}

ll dis[maxn];
bool inq[maxn], vis[maxn];
int from[maxn];
bool spfa(int s, int t) {
	std::queue<int> q;
	std::fill(dis, dis + t + 1, 1000000000000000000);
	std::fill(inq, inq + t + 1, 0);
	dis[s] = 0;
	q.push(s);
	while(!q.empty()) {
		int u = q.front();
		vis[u] = 1;
		q.pop();
		inq[u] = 0;
		for(int i = head[u]; i; i = nxt[i])
			if(cap[i] and dis[u] + cost[i] < dis[to[i]]) {
				dis[to[i]] = dis[u] + cost[i];
				from[to[i]] = i ^ 1;
				if(!inq[to[i]]) {
					q.push(to[i]);
					inq[to[i]] = 1;
				}
			}
	}
	return dis[t] < 1000000000000000000;
}

ll mincostmaxflow(int s, int t) {
	ll res = 0;
	while(spfa(s, t)) {
		int flow = cap[from[t] ^ 1];
		ll sum = cost[from[t] ^ 1];
		for(int u = to[from[t]]; u != s; u = to[from[u]]) {
			flow = std::min(flow, cap[from[u] ^ 1]);
			sum += cost[from[u] ^ 1];
		}
		cap[from[t] ^ 1] -= flow;
		cap[from[t]] += flow;
		for(int u = to[from[t]]; u != s; u = to[from[u]]) {
			cap[from[u] ^ 1] -= flow;
			cap[from[u]] += flow;
		}
		res += sum * flow;
	}
	return res;
}

int d[maxn][maxn];
int main() {
	int n = read, m = read, K = read;

	for(int i = 0; i <= n; i ++)
		for(int j = 0; j <= n; j ++)
			d[i][j] = 1000000000;

	for(int i = 1; i <= m; i ++) {
		int u = read, v = read, w = read;
		d[u][v] = std::min(d[u][v], w);
		d[v][u] = std::min(d[v][u], w);
	}

	for(int k = 0; k <= n; k ++)
		for(int i = 0; i <= n; i ++)
			for(int j = 0; j <= n; j ++)
				if(k < i or k < j)
					d[i][j] = std::min(d[i][j], d[i][k] + d[k][j]);

	int s = n * 2 + 2, t = n * 2 + 3;
	add(s, n * 2 + 1, K, 0);
	for(int i = 1; i <= n; i ++) {
		add(n * 2 + 1, i, 1, d[0][i]);
		add(n + i, t, 1, 0);
	}

	int S = s + 2, T = t + 2;
	for(int i = 1; i <= n; i ++) {
		add(S, n + i, 1, 0);
		add(i, T, 1, 0);
	}

	for(int i = 1; i <= n; i ++)
		for(int j = i + 1; j <= n; j ++)
			add(n + i, j, 1, d[i][j]);

	add(t, s, 1000000000, 0);
	ll A = mincostmaxflow(S, T);
	ll B = mincostmaxflow(s, t);
	printf("%lld\n", A + B);
}
