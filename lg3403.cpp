#if 0
2019.08.21

同余最短路模板，注意到 x, y, z 很小。
不妨设 x <= y <= z ，
对于每个 a < z 求出 dis[a] 表示通过 x, y 能到达的形如 k * z + a 的最小的 k 。
那么对于所有 kk >= k 的 kk * z + a 都一定可以用 x, y, z 凑出来。
求法则是建图跑最短路。
#endif
#include <cstdio>
#include <algorithm>
#include <queue>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;
typedef std::pair<int, int> Par;
inline lolong input() { lolong x; scanf("%lld", &x); return x; }

const int maxn = 100005;
int dis[maxn];

void dijkstra(int a[2], int n) {
	for(int i = 0; i < n; i ++)
		dis[i] = 10000000;

	std::priority_queue<Par> q;
	q.push(Par(dis[0] = 0, 0));

	while(not q.empty()) {
		int d = - q.top().first, u = q.top().second;
		q.pop();

		if(d < dis[u])
			continue;

		for(int i = 0; i < 2; i ++) {
			int v = u + a[i], w = 0;
			if(v >= n) {
				v -= n;
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
	lolong h = input() - 1;
	int x = input(), y = input(), z = input();

	if(y > z) std::swap(y, z);
	if(x > y) std::swap(x, y);
	if(y > z) std::swap(y, z);

	int a[2] = {x, y};
	dijkstra(a, z);

	lolong ans = 0;

	for(int i = 0; i < z and i <= h; i ++)
		if(dis[i] < 10000000)
			ans += std::max(0ll, (h - i) / z + 1 - dis[i]);

	printf("%lld\n", ans);
}
