/*
 * Author: Kewth

 * Date:
  2020.11.13

 * Solution:

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
	template<class T> inline void operator () (T &x) { x = *this; }
} read;

const int maxn = 1000005;
int wei[maxn];
struct Edge { int v, w; };
std::vector<Edge> G[maxn];
ll ans;

void dp (int u, int fa, int fv, int k) {
	wei[u] %= k;
	for (Edge e : G[u])
		if (e.v != fa) {
			dp(e.v, u, e.w, k);
			if ((wei[u] += wei[e.v]) >= k)
				wei[u] -= k;
		}
	if (wei[u])
		ans += fv;
}

int main () {
	int n = read, k = read;
	for (int i = 1; i <= n; i ++) read(wei[i]);
	for (int i = 1; i < n; i ++) {
		int u = read, v = read, w = read;
		G[u].push_back({v, w});
		G[v].push_back({u, w});
	}
	dp(1, 0, 0, k);
	printf("%lld\n", ans);
}
