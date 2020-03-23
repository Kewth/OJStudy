#if 0
2020.03.22

补集转换，最小化非三元环的三元组数量。
可以发现一个三元组非三元环当且仅当三条边中有两条边具有公共入点。
那么一个点如果有 k 条出边，就会有 C(k, 2) 个非三元环三元组在这里统计。
那么就是要最小化 sum(C(k, 2)) = sum(k (k - 1) / 2) = sum(k^2 - k) / 2 。
出度和是个定值，最小化的实际是 sum(k^2) ，也就是出度平方和。

最小费用最大流，一条边一定会对一个点的出度贡献 1 ，但是有两种选择，
把边抽象成点，然后向两个端点连边，容量分别为 1 ，费用记到点上，一个点的流量就是出度，
向汇点连对应费用的边，跑出最小费用最大流的残量网络即可。
#endif
#include <cstdio>
#include <algorithm>
#include <queue>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxd = 3000, maxm = 100000;
int head[maxd], nxt[maxm << 1], to[maxm << 1], cap[maxm << 1], cost[maxm << 1], hp = 1;

inline void add(int u, int v, int ca, int co) {
	if((hp & 1) and !ca) return;
	nxt[++ hp] = head[u];
	head[u] = hp;
	to[hp] = v;
	cap[hp] = ca;
	cost[hp] = co;
	if(!(hp & 1)) add(v, u, 0, - co);
}

ll dis[maxd];
bool inq[maxd], vis[maxd];
int from[maxd];
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

const int maxn = 55;
bool force[maxn][maxn];
int eid[maxn][maxn];

int main () {
	int n = read, m = read;
	for (int i = 1; i <= m; i ++) {
		int x = read, y = read;
		force[x][y] = 1;
	}

	int p = n;
	for (int i = 1; i <= n; i ++)
		for (int j = i + 1; j <= n; j ++)
			eid[i][j] = ++ p;

	int s = ++ p, t = ++ p;

	for (int i = 1; i <= n; i ++)
		for (int j = i + 1; j <= n; j ++) {
			add(s, eid[i][j], 1, 0);
			add(eid[i][j], i, !force[j][i], 0);
			add(eid[i][j], j, !force[i][j], 0);
		}

	for (int i = 1; i <= n; i ++)
		for (int j = 1; j <= n; j ++)
			add(i, t, 1, j * j - (j - 1) * (j - 1));

	mincostmaxflow(s, t);

	for (int i = 1; i <= n; i ++)
		for (int j = i + 1; j <= n; j ++) {
			int u = eid[i][j];
			for (int k = head[u]; k; k = nxt[k])
				if (cap[k ^ 1] == 1)
					force[i == to[k] ? i : j][i == to[k] ? j : i] = 1;
	}

	for (int i = 1; i <= n; i ++) {
		for (int j = 1; j <= n; j ++)
			printf("%d", force[i][j]);
		puts("");
	}
}
