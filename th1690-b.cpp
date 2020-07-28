/*
 * Author: Kewth

 * Date:
  2020.07.27

 * Solution:
  In blog.

 * Digression:

 * CopyRight:
          ▁▃▄▄▄▃▃▃▃▄▶
        ▗▇▀▔    ▔▔▔▔
       ▄▛   ▃▅━━■▄▂
      ▟▊   ▐▘     ▀▙
     ▟▜▌   ▐▖   ▋  ▐▍
    ▟▘ ▜   ▝▀▇▆■▘  ▐▌
  ▗▟▘   ▜▃       ▁▅▛
  ▔▀▼▅▄▃▃██▅▄▄▄▅■▀▔
        ▔▔▔▔▔▔
 */

#include <vector>
#include <set>
#include "recover.h"
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef std::pair<int, int> par;

const int maxn = 2005;
std::vector<int> set[maxn];
std::vector<int> G[maxn];
int deg[maxn], col[maxn];
int stack[maxn], sp;
int vis[maxn];

int color (int n) {
	std::set<par> q;
	for (int u = 1; u <= n; u ++)
		q.insert(par(deg[u] = int(G[u].size()), u));
	std::fill(vis, vis + n + 1, 0);
	sp = 0;
	while (!q.empty()) {
		int u = q.begin() -> second;
		q.erase(q.begin());
		stack[++ sp] = u;
		vis[u] = sp;
		for (int v : G[u])
			if (!vis[v]) {
				q.erase(par(deg[v] --, v));
				q.insert(par(deg[v], v));
			}
	}
	int C = 0;
	while (sp) {
		int u = stack[sp --];
		std::set<int> s;
		for (int v : G[u])
			if (vis[v] > vis[u])
				s.insert(col[v]);
		int c = 1;
		while (s.count(c)) ++ c;
		col[u] = c;
		set[c].push_back(u);
		/* debug("%d -> %d\n", u, c); */
		C = std::max(C, c);
	}
	return C;
}

std::vector<par> recover (int n) {
	std::vector<par> res;
	int C = 0;
	for (int u = 1; u <= n; u ++) {
		/* debug("%d\n", u); */
		int find = 0;
		for (int i = 1; i <= C; i ++) {
			auto tmp = set[i];
			tmp.push_back(u);
			par e = query(tmp);
			if (e.first == -1) find = i;
			while (e.first != -1) {
				res.push_back(e);
				int x = e.first == u ? e.second : e.first;
				G[u].push_back(x);
				G[x].push_back(u);
				for (auto it = tmp.begin(); it != tmp.end(); ++ it)
					if (*it == x) {
						tmp.erase(it);
						break;
					}
				e = query(tmp);
			}
		}
		if (!find) {
			for (int i = 1; i <= C; i ++) set[i].clear();
			C = color(u);
		} else set[find].push_back(u);
	}
	return res;
}
