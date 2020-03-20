#if 0
2020.03.15

钦定根节点，然后把剩下的点和集合做一个匹配，
也就是在在每个集合选一个代表点，然后要求代表点两两不同。
构造方案时只需要从根开始 bfs 加边，每次从当前节点中选一个未考虑过的集合，
并对该集合的关键点连边。
#endif
#include <cstdio>
#include <queue>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
} read;

const int maxn = 100005;
int head[maxn << 1], nxt[maxn << 3], to[maxn << 3], cap[maxn << 3], hp = 1;
int cur[maxn << 1], level[maxn << 1];

inline void add(int u, int v, int c) {
	nxt[++ hp] = head[u];
	head[u] = hp;
	to[hp] = v;
	cap[hp] = c;
	if(!(hp & 1)) add(v, u, 0);
}

bool bfs(int s, int t) {
	std::queue<int> q;
	q.push(s);
	std::fill(level, level + t + 1, 0);
	level[s] = 1;
	while(!q.empty()) {
		int u = q.front();
		q.pop();
		for(int i = head[u]; i; i = nxt[i])
			if(cap[i] and !level[to[i]]) {
				level[to[i]] = level[u] + 1;
				q.push(to[i]);
			}
	}
	return level[t];
}

int dinic(int u, int t) {
	if(u == t) return 1;
	for(int &i = cur[u]; i; i = nxt[i])
		if(cap[i] and level[to[i]] == level[u] + 1) {
			int f = dinic(to[i], t);
			if(f) {
				cap[i] -= f;
				cap[i ^ 1] += f;
				return f;
			}
		}
	return 0;
}

bool vis[maxn];
int match[maxn];
int ansx[maxn], ansy[maxn], ap;

int main() {
	int n = read;

	int s = n * 2, t = n * 2 + 1;
	for(int i = 1; i < n; i ++)
		add(s, i, 1);
	for(int i = 1; i < n; i ++)
		add(n + i, t, 1);

	for(int i = 1; i < n; i ++) {
		int k = read;
		while(k --)
			add(read, n + i, 1);
	}

	int flow = 0;
	while(bfs(s, t)) {
		std::copy(head, head + t + 1, cur);
		int f;
		while((f = dinic(s, t)))
			flow += f;
	}

	if(flow != n - 1) return puts("-1"), 0;

	for(int u = n + 1; u < n * 2; u ++)
		for(int i = head[u]; i; i = nxt[i])
			if(cap[i])
				match[u - n] = to[i];

	std::queue<int> q;
	q.push(n);
	while(!q.empty()) {
		int u = q.front();
		q.pop();
		for(int i = head[u]; i; i = nxt[i])
			if(to[i] != s and !vis[to[i] - n]) {
				vis[to[i] - n] = 1;
				q.push(match[to[i] - n]);
				++ ap;
				ansx[to[i] - n] = u;
				ansy[to[i] - n] = match[to[i] - n];
			}
	}

	if(ap != n - 1) return puts("-1"), 0;

	for(int i = 1; i <= ap; i ++)
		printf("%d %d\n", ansx[i], ansy[i]);
}
