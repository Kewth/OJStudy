/*
 * Author: Kewth

 * Date:
  2020.11.19

 * Solution:
  In blog.

 * Digression:

 * CopyRight:
   __  __                  __   __
  |  |/  |.-----.--.--.--.|  |_|  |--.
  |     < |  -__|  |  |  ||   _|     |
  |__|\__||_____|________||____|__|__|

 */

#include <cstdio>
#include <algorithm>
#include <vector>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

static struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator () (a...); }
} read;

const int maxn = 105;
int px[maxn], py[maxn];
ll dis[maxn][maxn];
int match[maxn];
std::vector<int> G[maxn];
bool vis[maxn], mark[maxn];

bool find (int u) {
	for (int v : G[u])
		if (!vis[v]) {
			vis[v] = 1;
			if (!match[v] or find(match[v])) {
				match[v] = u;
				match[u] = v;
				return 1;
			}
		}
	return 0;
}

void dfs (int u) {
	mark[u] = 1;
	for (int v : G[u]) {
		int mv = match[v];
		if (mv and !mark[mv])
			dfs(mv);
	}
}

/* void minicover (std::vector<int> */ 

int main () {
	int n = read;
	ll d = read;
	d *= d;

	for (int i = 1; i <= n; i ++)
		read(px[i], py[i]);
	for (int i = 1; i <= n; i ++)
		for (int j = 1; j <= n; j ++)
			dis[i][j] = ll(px[i] - px[j]) * (px[i] - px[j]) +
				ll(py[i] - py[j]) * (py[i] - py[j]);

	std::vector<int> ans;
	ans.push_back(1);
	for (int i = 1; i <= n; i ++)
		for (int j = i + 1; j <= n; j ++) {
			ll r = dis[i][j];
			std::vector<int> p, now;
			if (r <= d) {
				for (int k = 1; k <= n; k ++)
					if (k != i and k != j and dis[i][k] <= r and dis[j][k] <= r)
						p.push_back(k);
				/* if (i == 1 and j == 3) */
				/* 	for (int u : p) */
				/* 		debug("%d %lld %lld\n", u, dis[u][i], dis[u][j]); */
				for (int u : p) {
					mark[u] = match[u] = 0;
					for (int v : p)
						if (v != u and dis[u][v] > r)
							G[u].push_back(v);
				}
				for (int u : p)
					if (!match[u]) {
						for (int x : p) vis[x] = 0;
						find(u);
					}
				for (int u : p)
					if (!match[u] and !mark[u])
						dfs(u);
				for (int u : p)
					if (match[u] and !mark[u] and !mark[match[u]])
						dfs(u);
				for (int u : p)
					G[u].clear();
				now.push_back(i);
				now.push_back(j);
				for (int u : p)
					if (mark[u])
						now.push_back(u);
				if (now.size() > ans.size())
					ans = now;
			}
		}

	printf("%lu\n", ans.size());
	for (int u : ans)
		printf("%d ", u);
	puts("");
}
