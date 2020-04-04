#if 0
2020.02.01

建立新的网络图，先不考虑容量，对于原来的每条边 u -> v ，
新图中 u -> v 的流量为代表原图中 u -> v 的流量增量，
增量没有上界，因此容量正无穷，但是费用为 1 。
而 v -> u 的流量代表原图中 u -> v 的流量减少量。
减少量有上界，即原图流量 f ，同样费用为 1 。

为了满足流量平衡，对于点 u ，
如果流入流量比流出流量大 x ，说明需要增加出边流量或者减少入边流量，
连边 S -> u ，其中 S 是新建源点，
这条边的流量必须为 x ，上下界都为 x ，没有费用。
同理如果流出流量比流入流量大 x ，连边 u -> T ，上下界为 x ，无费用。
特别的原图的源汇点不需要满足流量平衡，
连边 S -> 1 和 n -> T ，容量正无穷。

这样新图的最小费用可行流就是答案，前提是忽略原图流量限制。

考虑到原图流量限制，对于边 (u, v, c, f) ：
1) c > f
流量增量不超过 c - f 时费用为 1 。
如果流量增量超过 c - f ，每次流量增加的同时需要增加容量，因此费用为 2 。
流量减少量的费用仍然为 1 。
2) c < f
先把答案加上 f - c ，默认容量被加到了 f 。
首先流量增量的费用始终是 2 。
流量减少的话，说明容量没必要增加到 f ，流量减少的同时减少容量，最多减到 c ，
因此流量减少量不超过 f - c 时费用为 0 。
如果流量减少量超过 f - c 费用仍然为 1 。

把需要分段的边拆成两条，这样新图的最小费用可行流加上提到的 f - c 就是答案了。
#endif
#include <cstdio>
#include <algorithm>
#include <queue>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 110, maxm = 1010;
int head[maxn], nxt[maxm], to[maxm], cap[maxm], cost[maxm], hp = 1;

inline void add(int u, int v, int ca, int co) {
	if((hp & 1) and !ca) return;
	nxt[++ hp] = head[u];
	head[u] = hp;
	to[hp] = v;
	cap[hp] = ca;
	cost[hp] = co;
	if(!(hp & 1)) add(v, u, 0, - co);
}

int dis[maxn];
bool inq[maxn];

bool spfa(int s, int t) {
	std::queue<int> q;
	std::fill(dis, dis + t + 1, 1000000000);
	std::fill(inq, inq + t + 1, 0);
	dis[s] = 0;
	q.push(s);
	while(!q.empty()) {
		int u = q.front();
		q.pop();
		inq[u] = 0;
		for(int i = head[u]; i; i = nxt[i])
			if(cap[i] and dis[u] + cost[i] < dis[to[i]]) {
				dis[to[i]] = dis[u] + cost[i];
				if(!inq[to[i]]) {
					q.push(to[i]);
					inq[to[i]] = 1;
				}
			}
	}
	return dis[t] < 1000000000;
}

int cur[maxn];
int dinic(int u, int t, int flow) {
	inq[u] = 1;
	if(u == t) return flow;
	for(int &i = cur[u]; i; i = nxt[i])
		if(cap[i] and !inq[to[i]] and dis[u] + cost[i] == dis[to[i]]) {
			int f = dinic(to[i], t, std::min(flow, cap[i]));
			if(f) {
				cap[i] -= f;
				cap[i ^ 1] += f;
				inq[u] = 0;
				return f;
			}
		}
	inq[u] = 0;
	return 0;
}

int mincostmaxflow(int s, int t) {
	int res = 0;
	while(spfa(s, t)) {
		std::copy(head, head + t + 1, cur);
		int f = 0;
		do {
			f = dinic(s, t, 2147483647);
			res += dis[t] * f;
		} while(f);
	}
	return res;
}

int deg[maxn];
int main() {
	int n = read, m = read;
	int ans = 0;
	for(int i = 1; i <= m; i ++) {
		int u = read, v = read, c = read, f = read;
		if(c < f) {
			ans += f - c;
			add(v, u, f - c, 0);
			add(v, u, c, 1);
			add(u, v, 1000000000, 2);
		} else {
			add(u, v, c - f, 1);
			add(v, u, f, 1);
			add(u, v, 1000000000, 2);
		}
		deg[u] -= f;
		deg[v] += f;
	}

	int s = n + 1, t = n + 2, ss = n + 3, tt = n + 4;
	add(s, 1, 1000000000, 0);
	add(n, t, 1000000000, 0);
	add(t, s, 1000000000, 0);
	for(int i = 1; i <= n; i ++) {
		if(deg[i] > 0) {
			add(ss, i, deg[i], 0);
			add(s, tt, deg[i], 0);
		}
		if(deg[i] < 0) {
			add(ss, t, -deg[i], 0);
			add(i, tt, -deg[i], 0);
		}
	}

	ans += mincostmaxflow(ss, tt);
	printf("%d\n", ans);
}
