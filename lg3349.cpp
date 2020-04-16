#if 0
2020.04.15

本质是统计映射或者排列 P ，一个朴素 DP 是设 f[u][x][S] 表示考虑 u 的子树，
P[u] = x 且 u 的子树的 P 的集合为 S 的方案数。
转移复杂度爆炸，用集合并卷积似乎可以做到 O(n^4 2^n) ，然后就行不通了。

换个角度，直接忽略掉第三维，设 f[u][x] 表示考虑 u 的子树且 P[u] = x 的方案数。
这样会把不合法的答案算进去，最后的 P 可能会有多对一的情况。
容斥，枚举最后的 P 的集合 S ，然后 O(n^3) 做一次上述 DP 即可，容斥系数是 (-1)^(|S|-n) 。
#endif
#include <cstdio>
#include <algorithm>
#include <vector>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	/* inline operator ll () { ll x; return scanf("%lld", &x), x; } */
	template<class T> inline void operator () (T &x) { x = *this; }
	/* template<class T, class ...A> inline void operator () (T &x, A &...a) */
	/* { x = *this; this -> operator () (a...); } */
} read;

const int maxn = 17;
std::vector<int> G[maxn];
ll f[maxn][maxn];
bool link[maxn][maxn];
std::vector<int> set;

int n;
void dp (int u, int fa) {
	for (int x : set)
		f[u][x] = 1;
	for (int v : G[u])
		if (v != fa) {
			dp(v, u);
			for (int x : set) {
				ll sum = 0;
				for (int y : set)
					if (link[x][y])
						sum += f[v][y];
				f[u][x] *= sum;
			}
		}
}

int main () {
	read(n);
	int m = read;
	for (int i = 1; i <= m; i ++) {
		int x = read - 1, y = read - 1;
		link[x][y] = link[y][x] = 1;
	}

	for (int i = 1; i < n; i ++) {
		int u = read - 1, v = read - 1;
		G[u].push_back(v);
		G[v].push_back(u);
	}

	ll ans = 0;
	for (int S = 0; S < (1 << n); S ++) {
		set.clear();
		for (int i = 0; i < n; i ++)
			if (S >> i & 1)
				set.push_back(i);
		dp(0, -1);
		ll now = 0;
		for (int x : set) now += f[0][x];
		if (n - int(set.size()) & 1) ans -= now;
		else ans += now;
	}

	printf("%lld\n", ans);
}
