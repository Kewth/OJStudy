#if 0
2019.08.21

设 mx为 max(p[i]) ,考虑每个 x < mx ，求能凑出 k * mx + x 的最小的 k 是多少。
那么对于所有不小于 k 的 k' 都能凑出 k' * mx + x ，因为可以用 mx 。
怎么求？建一个图，连边 (x, (x + p[i]) % mx)，如果跨过了 mx 就有 1 的距离，
求一遍最短路即可，这也算是同余最短路板子。
#endif
#include <cstdio>
#include <algorithm>
#include <queue>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef std::pair<int, int> Par;

inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 505, maxm = 300005, maxv = 10005;
int p[maxn];
int a[maxm];
int dis[maxv];

void dijkstra(int n, int max) {
	std::priority_queue<Par> q;

	for(int i = 1; i < max; i ++)
		dis[i] = 1000000000;

	q.push(Par(0, 0));

	while(not q.empty()) {
		int d = - q.top().first, u = q.top().second;
		q.pop();

		if(d > dis[u])
			continue;

		for(int i = 1; i <= n; i ++) {
			int v = u + p[i], w = 0;
			if(v >= max) {
				v -= max;
				w ++;
			}

			if(dis[u] + w < dis[v]) {
				dis[v] = dis[u] + w;
				q.push(Par(- dis[v], v));
			}
		}
	}
}

int main() {
	int n = input(), m = input();
	for(int i = 1; i <= n; i ++)
		p[i] = input();
	for(int i = 1; i <= m; i ++)
		a[i] = input();

	int max = 0;
	for(int i = 1; i <= n; i ++)
		max = std::max(max, p[i]);

	dijkstra(n, max);

	int ans = 0;

	if(max)
		for(int i = 1; i <= m; i ++)
			if(a[i] / max >= dis[a[i] % max])
				/* debug("%d\n", a[i]), */
				ans ++;

	printf("%d\n", ans);
}
