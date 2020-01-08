#if 0
2020.01.08

一个工人修 k 个车，这 k 个车的代价分别要乘上 1, 2, ... k 。
可以把一个工人拆成 n 个，其中第 i 个要花 i 倍时间。
这样每辆车和每个工人的二分图最小权最大匹配就是答案。
#endif
#include <cstdio>
#include <queue>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
} read;

const int maxn = 800, maxm = 200000;
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


int main() {
	int m = read, n = read;
	int s = n * m + n + 1, t = n * m + n + 2;
	for(int i = 1; i <= n; i ++) {
		add(s, n * m + i, 1, 0);
		for(int j = 0; j < m; j ++) {
			int co = read;
			for(int k = 0; k < n; k ++) {
				add(n * m + i, j * n + k, 1, co * (k + 1));
			}
		}
	}

	for(int j = 0; j < m; j ++)
		for(int k = 0; k < n; k ++)
			add(j * n + k, t, 1, 0);

	printf("%.2lf\n", mincostmaxflow(s, t) * 1.0 / n);

	/* for(int j = 1; j <= n; j ++) { */
	/* 	int u = n * m + j; */
	/* 	for(int i = head[u]; i; i = nxt[i]) */
	/* 		if(!(i & 1) and !cap[i]) */
	/* 			debug("%d -> %d,%d\n", j, 1 + to[i] / n, 1 + to[i] % n); */
	/* } */
}
