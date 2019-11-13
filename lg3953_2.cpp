#if 0
2019.11.13

直接把一个点拆成 k + 1 个点，(u, i) 分别表示 u 拆出来的 dis 比最短路多 i 的情况。
然后边 dij 边计数，先一遍 dij （这一遍只有 n 个点）求出单源最短路，
然后由于有 0 边，再一遍 dij 求出每个点的入度。
然后最后 dij 求出每个点的方案，其中每次访问 (v, i) 时将其入度减 1 ，
只有当 (v, k) 入度为 0 时才放进队列，无解当且仅当存在 (n, i) 的入度没有被减为 0 。
复杂度 O(nklogn) ，其实跑不过，换成 spfa 勉强能过去。
事实上最短路和统计方案两个步骤似乎是可以分开来的，
但是比较麻烦，对 0 边的处理也更复杂，复杂度可以做到 O(n(k+logn)) 。
#endif
#include <cstdio>
#include <vector>
#include <queue>
#define debug(...) fprintf(stderr, __VA_ARGS__)
// 一键 spfa
#define priority_queue queue
#define top front

typedef long long ll;
typedef std::pair<int, int> Par;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
} read;

const int maxn = 100005, maxk = 52;
std::vector<Par> G[maxn];
int dis[maxn];
int f[maxn][maxk];
bool vis[maxn][maxk];
int deg[maxn][maxk];

int main() {
	int T = read;
	while(T --) {
		int n = read, m = read, k = read, mod = read;

		for(int i = 1; i <= n; i ++)
			G[i].clear();

		for(int i = 1; i <= m; i ++) {
			int u = read, v = read, w = read;
			G[u].push_back(Par(v, w));
		}

		for(int i = 1; i <= n; i ++)
			dis[i] = 1000000000;

		std::priority_queue<Par> q;
		q.push(Par(dis[1] = 0, 1));

		while(!q.empty()) {
			int u = q.top().second, d = - q.top().first;
			q.pop();
			if(d > dis[u]) continue;
			for(Par p : G[u])
				if(dis[u] + p.second < dis[p.first]) {
					dis[p.first] = dis[u] + p.second;
					q.push(Par(- dis[p.first], p.first));
				}
		}

		for(int i = 1; i <= n; i ++)
			for(int j = 0; j <= k; j ++)
				deg[i][j] = 0;

		int TOT = 0;
		q.push(Par(0, 1));
		while(!q.empty()) {
			++ TOT;
			int u = q.top().second, d = - q.top().first;
			q.pop();
			for(Par p : G[u]) {
				int v = p.first, w = p.second;
				if(d + w <= dis[v] + k) {
					int vk = d + w - dis[v];
					if(++ deg[v][vk] >= n)
						deg[v][vk] = 2000000000;
					else if(deg[v][vk] == 1)
						q.push(Par(- d - w, v));
				}
			}
		}

		for(int i = 1; i <= n; i ++)
			for(int j = 0; j <= k; j ++)
				vis[i][j] = f[i][j] = 0;

/* 		for(int i = 1; i <= n; i ++) */
/* 			for(int j = 0; j <= k; j ++) */
/* 				if(deg[i][j]) */
/* 					debug("deg[%d][%d] = %d\n", i, j, deg[i][j]); */

		q.push(Par(0, 1));
		f[1][0] = 1;
		while(!q.empty()) {
			int u = q.top().second, d = - q.top().first;
			q.pop();

			if(vis[u][d - dis[u]]) continue;
			vis[u][d - dis[u]] = 1;
			/* debug("f[%d][%d] = %d\n", u, d - dis[u], f[u][d - dis[u]]); */

			for(Par p : G[u]) {
				int v = p.first, w = p.second;
				if(d + w <= dis[v] + k) {
					int vk = d + w - dis[v];
					(f[v][vk] += f[u][d - dis[u]]) %= mod;
					if(-- deg[v][vk] == 0)
						q.push(Par(- d - w, v));
				}
			}
		}

		int ans = 0;
		for(int i = 0; i <= k; i ++)
			if(deg[n][i]) {
				ans = -1;
				break;
			} else
				(ans += f[n][i]) %= mod;

		printf("%d\n", ans);
		debug("%d\n", TOT);
	}
}
