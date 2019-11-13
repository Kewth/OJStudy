#if 0
2019.11.12

最短路计数模板，直接在松弛的时候维护路径数即可。
#endif
#include <cstdio>
#include <vector>
#include <queue>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef std::pair<int, int> Par;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
} read;

const int maxn = 100005, mod = 100003;
std::vector<int> G[maxn];
int dis[maxn], tot[maxn];

int main() {
	int n = read, m = read;

	for(int i = 1; i <= m; i ++) {
		int u = read, v = read;
		G[u].push_back(v);
		G[v].push_back(u);
	}

	for(int i = 1; i <= n; i ++)
		dis[i] = 1000000000;

	std::priority_queue<Par> q;
	q.push(Par(dis[1] = 0, 1));
	tot[1] = 1;

	while(!q.empty()) {
		int u = q.top().second, d = - q.top().first;
		q.pop();
		if(d > dis[u]) continue;

		for(int v : G[u])
			if(dis[u] + 1 < dis[v]) {
				dis[v] = dis[u] + 1;
				tot[v] = tot[u];
				q.push(Par(- dis[v], v));
			} else if(dis[u] + 1 == dis[v])
				(tot[v] += tot[u]) %= mod;
	}

	for(int i = 1; i <= n; i ++)
		printf("%d\n", tot[i]);
}
