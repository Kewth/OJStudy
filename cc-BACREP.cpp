/*
 * Author: Kewth

 * Date:
  2022.07.10

 * Solution:
  To be updated after "Accept".

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
	inline operator char () { char x[10]; return scanf("%s", x), x[0]; }
} read;

const int maxn = 500005, maxq = 1000005;
struct Operation {
	int u, x;
};
std::vector<Operation> T[maxn + maxq];
std::vector<int> G[maxn];
int dep[maxn], size[maxn], dfn[maxn], clk;
ll ans[maxq];
ll bit1[maxn], bit2[maxn];

void add (ll *bit, int l, int n, int x) {
	for (int i = l; i <= n; i += i & -i)
		bit[i] += x;
}
ll query (ll *bit, int k) {
	ll res = 0;
	for (int i = k; i; i -= i & -i)
		res += bit[i];
	return res;
}

void dfs (int u) {
	dfn[u] = ++ clk;
	size[u] = 1;
	for (int v : G[u])
		if (!dfn[v]) {
			dep[v] = dep[u] + 1;
			dfs(v);
			size[u] += size[v];
		}
}

int main () {
	int n = read, q = read;
	for (int i = 1; i < n; i ++) {
		int u = read, v = read;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	dfs(1);
	for (int u = 1; u <= n; u ++)
		T[n + 0 - dep[u]].push_back({u, read});
	int tot = 0;
	for (int t = 1; t <= q; t ++) {
		char o = read;
		int u = read;
		if (o == '+')
			T[n + t - dep[u]].push_back({u, read});
		if (o == '?')
			T[n + t - dep[u]].push_back({u, - (++ tot)});
	}
	for (int i = 0; i <= n + q; i ++) {
		for (Operation o : T[i])
			if (o.x < 0) {
				ans[-o.x] = size[o.u] == 1 ? query(bit2, dfn[o.u])
					: query(bit1, dfn[o.u]);
			} else {
				add(bit1, dfn[o.u], n, o.x);
				add(bit1, dfn[o.u] + size[o.u], n, -o.x);
				add(bit2, dfn[o.u], n, o.x);
				add(bit2, dfn[o.u] + size[o.u], n, -o.x);
			}
		for (Operation o : T[i])
			if (o.x > 0) {
				add(bit1, dfn[o.u], n, -o.x);
				add(bit1, dfn[o.u] + size[o.u], n, o.x);
			}
	}
	for (int i = 1; i <= tot; i ++)
		printf("%lld\n", ans[i]);
}
