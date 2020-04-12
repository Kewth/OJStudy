#if 0
2020.04.12

a 乘 b 为 k 次方和是个套路，把质因子指数对 k 取模后 a 和 b 是相互唯一对应的。
在 DAG 上直接 DP 即可。
#endif
#include <cstdio>
#include <algorithm>
#include <vector>
#include <map>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	/* inline operator ll () { ll x; return scanf("%lld", &x), x; } */
	template<class T> inline void operator () (T &x) { x = *this; }
	/* template<class T, class ...A> inline void operator () (T &x, A &...a) */
	/* { x = *this; this -> operator () (a...); } */
} read;

const int maxn = 200005, maxw = 100005;
struct Edge { int v, w, l; };
std::vector<Edge> G[maxn];
std::map<int, int> f[maxn];
bool vis[maxn];
ll match[maxw];
int shit[maxw];
int K;

void forcematch (int x) {
	if (K == 1)
		return shit[x] = 1, match[1] = 1, void();
	int o = x, z = x;
	ll y = 1;
	for (int p = 2; p * p <= x; p ++)
		if (!(x % p)) {
			int k = 0;
			while (!(x % p))
				x /= p, ++ k;
			while (k >= K) {
				for (int i = 0; i < K; i ++)
					z /= p;
				k -= K;
			}
			while (k and k < K)
				y *= p, ++ k;
		}
	if (x > 1)
		for (int k = 1; k < K; k ++)
			y *= x;
	/* debug("%d %d %lld\n", o, z, y); */
	shit[o] = z;
	match[z] = y;
}

int ans = 0;
void dp (int u) {
	if (vis[u]) return;
	vis[u] = 1;
	for (Edge e : G[u]) {
		dp(e.v);
		int x = match[e.w] >= maxw ? 999999999 : int(match[e.w]);
		if (f[e.v].count(x))
			f[u][e.w] = std::max(f[u][e.w], f[e.v][x] + e.l);
		else
			f[u][e.w] = std::max(f[u][e.w], e.l);
		ans = std::max(ans, f[u][e.w]);
	}
}

int main () {
	int n = read, m = read;
	read(K);

	int W = 100000;
	for (int x = 1; x <= W; x ++)
		forcematch(x);

	for (int i = 1; i <= m; i ++) {
		int u = read, v = read, w = read, l = read;
		G[u].push_back({v, shit[w], l});
	}

	for (int i = 1; i <= n; i ++)
		dp(i);
	printf("%d\n", ans);
}
