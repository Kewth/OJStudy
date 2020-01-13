#if 0
2019.11.15

bfs 最短路，必须用 vector 增加 cache 命中率。
#endif
#include <queue>
#include <cstdio>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
} read;

const int maxn = 1010, mod = 252525252;
int dis[maxn];
std::vector<int> G[maxn];

void bfs(int s) {
	std::queue<int> q;
	q.push(s);
	while(!q.empty()) {
		int u = q.front();
		q.pop();
		for(int v : G[u])
			if(!dis[v] and v != s) {
				dis[v] = dis[u] + 1;
				q.push(v);
			}
	}
}

int main() {
	int n = read, m = read;

	for(int i = 1; i <= m; i ++) {
		int u = read, v = read;
		G[v].push_back(u);
	}

	for(int i = 1; i <= n; i ++) {
		for(int j = 1; j <= n; j ++)
			dis[j] = 0;
		bfs(i);
		ll ans = dis[1];
		for(int j = 2; j <= n; j ++)
			ans = (ans * j + dis[j]) % mod;
		printf("%lld\n", ans);
	}
}
