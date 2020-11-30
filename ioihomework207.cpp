/*
 * Author: Kewth

 * Date:
  2020.11.24

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
#include <set>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

static struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
} read;

const int maxn = 200005;
struct ele { ll x, y; };
ll val[maxn];
std::vector<int> G[maxn];
std::multiset<ele> s[maxn];

bool operator < (ele a, ele b) { return a.x < b.x; }

ele topof (int u) {
	ele res = *s[u].begin();
	s[u].erase(s[u].begin());
	return res;
}

ll greedy (ll now, int u) {
	while (!s[u].empty() and now >= s[u].begin() -> x) {
		ele t = topof(u);
		now += t.y - t.x;
	}
	return now;
}

void dfs (int u, int fa) {
	s[u].clear();
	for (int v : G[u])
		if (v != fa) {
			dfs(v, u);
			if (s[u].size() < s[v].size())
				std::swap(s[u], s[v]);
			for (ele e : s[v])
				s[u].insert(e);
		}
	if (val[u] >= 0)
		s[u].insert({0, val[u]});
	else {
		ll ex = -val[u], ey = greedy(0, u);
		while (ex > ey) {
			if (s[u].empty()) return;
			ele t = topof(u);
			ex += t.x - ey;
			ey = greedy(t.y, u);
		}
		s[u].insert({ex, ey});
	}
}

int main () {
	ll W = 1000000000000;
	int T = read;
	while (T --) {
		int n = read, t = read;
		for (int u = 1; u <= n; u ++)
			read(val[u]), G[u].clear();
		G[n + 1].clear();
		for (int i = 1; i < n; i ++) {
			int u = read, v = read;
			G[u].push_back(v);
			G[v].push_back(u);
		}
		G[t].push_back(n + 1);
		G[n + 1].push_back(t);
		val[n + 1] = W;
		dfs(1, 0);
		if (greedy(0, 1) >= W) puts("escaped");
		else puts("trapped");
	}
}
