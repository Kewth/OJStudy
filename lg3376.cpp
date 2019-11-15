#if 0
2019.11.15

dinic 模板，惊奇地发现绝大多数数据下不需要反边也能过，甚至能 A 掉大多模板。
#endif
#include <cstdio>
#include <queue>
#include <cstring>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
} read;

const int maxn = 10005, maxm = 120005;
int head[maxn], nxt[maxm << 1], to[maxm << 1], cap[maxm << 1], hp = 1;
int mcap[maxm << 1];

inline void add(int u, int v, int w) {
	nxt[++ hp] = head[u];
	head[u] = hp;
	to[hp] = v;
	cap[hp] = w;
	mcap[hp] = w;
}

int level[maxn];

bool bfs(int s, int t) {
	std::queue<int> q;
	q.push(s);
	memset(level, 0, sizeof level);
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

int cur[maxn];
int dfs(int u, int t, int f) {
	if(u == t) return f;
	for(int &i = cur[u]; i; i = nxt[i])
		if(cap[i] and level[to[i]] == level[u] + 1) {
			int tf = dfs(to[i], t, std::min(f, cap[i]));
			if(tf) {
				cap[i] -= tf;
				cap[i ^ 1] += tf; // 去掉这句话，仍然能 AC 模板，甚至可以在加强版中拿更多分
				return tf;
			}
		}
	return 0;
}

ll dinic(int s, int t) {
	ll res = 0;
	while(bfs(s, t)) {
		int f;
		memcpy(cur, head, sizeof cur);
		do {
			f = dfs(s, t, 2000000000);
			res += f;
		} while(f);
	}
	return res;
}

int main() {
	int n = read, m = read, s = read, t = read;

	for(int i = 1; i <= m; i ++) {
		int u = read, v = read, w = read;
		add(u, v, w);
		add(v, u, 0);
	}

	printf("%lld\n", dinic(s, t));
}
