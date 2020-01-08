#if 0
2020.01.07

最小费用可行流。
建一条链，n + 1 个点 n 条边，
令第 i 条边的流量表示第 i 天的人数，那么每条边都有流量下界。
对于一类志愿者，每个有 c 的代价，可以使 s 到 t 条边流量加 1 。
这个连边 t + 1 到 s 并设置代价即可，整张图的最小费用可行流就是答案。
转成最小费用最大流时有许多 s 到 t 的长为 0 的路径，
在建图的时候去掉它们，可以对建图进行简单优化。

我费用流太太太太慢啦，学习 hahawang 的类 dinic 的费用流。
#endif
#include <cstdio>
#include <queue>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
} read;

const int maxn = 1010, maxm = 26080;
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

ll dis[maxn];
bool inq[maxn];

bool spfa(int s, int t) {
	std::queue<int> q;
	std::fill(dis, dis + t + 1, 1000000000000000000);
	std::fill(inq, inq + t + 1, 0);
	dis[s] = 0;
	q.push(s);
	while(!q.empty()) {
		int u = q.front();
		q.pop();
		inq[u] = 0;
		/* debug("%d : %lld\n", u, dis[u]); */
		for(int i = head[u]; i; i = nxt[i])
			if(cap[i] and dis[u] + cost[i] < dis[to[i]]) {
				dis[to[i]] = dis[u] + cost[i];
				if(!inq[to[i]]) {
					q.push(to[i]);
					inq[to[i]] = 1;
				}
			}
	}
	return dis[t] < 1000000000000000000;
}

int cur[maxn];
int dinic(int u, int t, int flow) {
	/* debug("%d %lld %d\n", u, dis[u], flow); */
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

ll mincostmaxflow(int s, int t) {
	ll res = 0;
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

int ned[maxn];
int main() {
	int n = read, m = read;
	int s = n + 2, t = n + 3;

	for(int i = 1; i <= n; i ++) read(ned[i]);
	for(int i = 1; i <= n; i ++) {
		add(i, i + 1, 2147483647, 0);
		add(i, t, ned[i] - std::min(ned[i], ned[i - 1]), 0);
		add(s, i + 1, ned[i] - std::min(ned[i], ned[i + 1]), 0);
	}

	for(int i = 1; i <= m; i ++) {
		int a = read, b = read, c = read;
		add(b + 1, a, 2147483647, c);
	}

	printf("%lld\n", mincostmaxflow(s, t));
}
