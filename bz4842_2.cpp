#if 0
2020.01.15

我他妈要是再写消圈的费用流我就是孙子。

将一个长为 k 的连续段覆盖 n 个点这个关系换成用 n 个点覆盖 n - k + 1 个段。
强制选 S ，只考虑改 E ，那么每个段被覆盖的 E 的次数就有上界和下界。
而每个点去作为 E 覆盖若干段会有若干收益。
这是个经典的会有正环的最大费用可行流问题，正环新建源汇点先强制满流即可。

具体的，对于正边 (u -> v, cap, cost) ，以及新源汇点 S, T 。
建边 (S -> v, cap, 0), (v -> u, cap, -cost), (u -> T, cap, 0) ，
并使流量初始加 cost 。
事实上第二条边就是原边的反边。
#endif
#include <cstdio>
#include <algorithm>
#include <queue>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
} read;

const int maxn = 1010, maxm = 6010;
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
	std::fill(dis, dis + t + 1, - 1000000000000000000);
	std::fill(inq, inq + t + 1, 0);
	dis[s] = 0;
	q.push(s);
	while(!q.empty()) {
		int u = q.front();
		q.pop();
		inq[u] = 0;
		vis[u] = 1;
		for(int i = head[u]; i; i = nxt[i])
			if(cap[i] and dis[u] + cost[i] > dis[to[i]]) {
				dis[to[i]] = dis[u] + cost[i];
				from[to[i]] = i ^ 1;
				if(!inq[to[i]]) {
					q.push(to[i]);
					inq[to[i]] = 1;
				}
			}
	}
	return dis[t] > - 1000000000000000000;
}

bool fuck[maxn];
ll update(int s, int x) {
	int flow = cap[from[x] ^ 1];
	ll sum = cost[from[x] ^ 1];
	for(int u = to[from[x]]; u != s; u = to[from[u]]) {
		flow = std::min(flow, cap[from[u] ^ 1]);
		sum += cost[from[u] ^ 1];
	}
	cap[from[x] ^ 1] -= flow;
	cap[from[x]] += flow;
	for(int u = to[from[x]]; u != s; u = to[from[u]]) {
		cap[from[u] ^ 1] -= flow;
		cap[from[u]] += flow;
	}
	return sum * flow;
}

ll mincostmaxflow(int s, int t) {
	ll res = 0;
	while(spfa(s, t))
		res += update(s, t);
	return res;
}

int a[maxn], b[maxn];
int main() {
	int n = read, k = read, min = read, max = k - read;
	for(int i = 1; i <= n; i ++)
		read(a[i]);
	ll ans = 0;
	for(int i = 1; i <= n; i ++) {
		int x = read;
		ans += x;
		a[i] -= x;
	}

	int s = n - k + 3, t = n - k + 4, S = s + 2, T = t + 2;
	for(int i = 1; i <= n - k + 1; i ++) {
		add(i, i + 1, max - min, 0);
		add(s, i + 1, min, 0);
		add(i, t, min, 0);
	}

	for(int i = 1; i <= n; i ++) {
		int l = std::max(1, i - k + 1);
		int r = std::min(n - k + 1, i);
		b[i] = hp + 1;
		add(r + 1, l, 1, a[i]);
		if(a[i] > 0) {
			-- cap[b[i]];
			++ cap[b[i] ^ 1];
			add(S, l, 1, 0);
			add(r + 1, T, 1, 0);
			ans += a[i];
		}
	}

	add(t, s, 1000000000, 0);

	ans += mincostmaxflow(S, T);
	ans += mincostmaxflow(s, t);
	printf("%lld\n", ans);
	for(int i = 1; i <= n; i ++)
		if(cap[b[i]]) putchar('E');
		else putchar('S');
	puts("");
}
