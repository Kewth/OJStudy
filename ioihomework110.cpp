/*
 * Author: Kewth

 * Date:
  2020.11.07

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
#include <cstring>
#include <algorithm>
#include <map>
#include <vector>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef unsigned long long ull;

static struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 5050;
std::map<ull, int> lid, rid;
char s[555];
int ex[maxn], ey[maxn];
std::vector<int> G[maxn << 1];
int match[maxn << 1];
bool vis[maxn << 1];
bool mark[maxn << 1];
std::vector<int> ansset[maxn << 1];

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

int main () {
	int n = read, m = read, ip = 0;
	for (int i = 1; i <= n; i ++) {
		scanf("%s", s + 1);
		int len = int(strlen(s + 1));
		ull X = 0, Y = 0;
		for (int j = 1; j <= m; j ++) {
			X = X * 29 + ull(s[j] - 'A' + 1);
			Y = Y * 29 + ull(s[len - j + 1] - 'A' + 1);
		}
		int &x = lid[X], &y = rid[Y];
		if (!x) x = ++ ip;
		if (!y) y = ++ ip;
		G[x].push_back(y);
		G[y].push_back(x);
		ex[i] = x, ey[i] = y;
	}
	for (int u = 1; u <= ip; u ++)
		if (!match[u]) {
			std::fill(vis, vis + ip + 1, 0);
			find(u);
		}
	for (int u = 1; u <= ip; u ++)
		if (!match[u] and !mark[u])
			dfs(u);
	for (int u = 1; u <= ip; u ++)
		if (match[u] and !mark[u] and !mark[match[u]])
			dfs(u);
	int ans = 0;
	for (int u = 1; u <= ip; u ++)
		if (!mark[u])
			++ ans;
	for (int i = 1; i <= n; i ++)
		ansset[mark[ex[i]] ? ey[i] : ex[i]].push_back(i);
	printf("%d\n", ans);
	for (int u = 1; u <= ip; u ++)
		if (!mark[u]) {
			printf("%lu", ansset[u].size());
			for (int i : ansset[u])
				printf(" %d", i);
			puts("");
		}
}
