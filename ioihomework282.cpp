/*
 * Author: Kewth

 * Date:
  2020.11.26

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
} read;

const int maxn = 100005, maxk = 20;
std::vector<int> G[maxn];
bool isbegin[maxn], vis[maxn];
int to[maxn], toend[maxn], id[maxn];
int iid[maxk];
bool link[maxk][maxk];
int f[maxk][1 << maxk];

void dfs (int u) {
	vis[u] = 1;
	for (int v : G[u])
		if (!vis[v])
			dfs(v);
}

int main () {
	int n = read, m = read;
	for (int i = 1; i <= m; i ++) {
		int u = read, v = read;
		G[u].push_back(v);
	}

	dfs(1);
	for (int u = 1; u <= n; u ++)
		if (G[u].empty())
			return puts("There is no route, Karl!"), 0;
	for (int u = 1; u <= n; u ++)
		if (!vis[u])
			return puts("There is no route, Karl!"), 0;
	for (int u = 1; u <= n; u ++)
		isbegin[u] = 1, vis[u] = 0;
	for (int u = 1; u <= n; u ++)
		if (G[u].size() == 1) {
			int v = G[u].back();
			isbegin[v] = 0;
			to[u] = v;
		}

	int kp = 0;
	for (int u = 1; u <= n; u ++)
		if (isbegin[u])
			iid[id[u] = kp ++] = u;
	for (int u = 1; u <= n; u ++)
		if (isbegin[u]) {
			/* debug("%d\n", u); */
			int v = u;
			vis[u] = 1;
			while (to[v]) {
				v = to[v];
				if (vis[v])
					return puts("There is no route, Karl!"), 0;
				vis[v] = 1;
			}
			toend[u] = v;
			/* debug("  => %d\n", v); */
			for (int z : G[v])
				if (isbegin[z])
					/* debug(" -> %d\n", z), */
					link[id[u]][id[z]] = 1;
		}
	if (kp)
		for (int u = 1; u <= n; u ++)
			if (!vis[u])
				return puts("There is no route, Karl!"), 0;

	/* for (int i = 0; i < kp; i ++) */
	/* 	for (int j = 0; j < kp; j ++) */
	/* 		if (link[i][j]) */
	/* 			debug("%d %d\n", i, j); */
	for (int i = 0; i < kp; i ++)
		for (int S = 0; S < (1 << kp); S ++)
			f[i][S] = -1;
	for (int i = 0; i < kp; i ++)
		if (link[0][i])
			f[i][1 << i] = 0;
	for (int S = 1; S < (1 << kp); S ++)
		if (S & (S - 1))
			for (int i = 0; i < kp; i ++)
				if (S >> i & 1) {
					int T = S ^ (1 << i);
					f[i][S] = -1;
					for (int j = 0; j < kp; j ++)
						if (T >> j & 1 and link[j][i] and f[j][T] != -1)
							f[i][S] = j;
				}
	int S = (1 << kp) - 1, x = 0;
	if (f[x][S] == -1)
		return puts("There is no route, Karl!"), 0;
	while (S) {
		int y = f[x][S];
		to[toend[iid[y]]] = iid[x];
		S ^= 1 << x;
		x = y;
	}

	int u = 1;
	for (int i = 1; i <= n + 1; i ++)
		printf("%d ", u), u = to[u];
	puts("");
}
