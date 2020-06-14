/*
 * Since g++10 is released, some characters is not valid inside #if 0 :(
 * So, why not using clang++? :D

 * Date:
  2020.06.14

 * Solution:
  直接枚举答案（当然显然可以二分），若答案为 k ，那么只需要考虑每个数二进制的最后 k 位。
这样一来两个数可以相连当且仅当它们完全相同。
  那么每个对实际上可以看做一条边，建图，由于要构造一个环，那么就是要在图上找一个欧拉回
路。

 * Digression:

 * CopyRight:
          ▁▃▄▄▄▃▃▃▃▄▶
        ▗▇▀▔    ▔▔▔▔
       ▄▛   ▃▅━━■▄▂
      ▟▊   ▐▘     ▀▙
     ▟▜▌   ▐▖   ▋  ▐▍
    ▟▘ ▜   ▝▀▇▆●▘  ▐▌
  ▗▟▘   ▜▃       ▁▅▛
  ▔▀▼▅▄▃▃██▅▄▄▄▅■▀▔
        ▔▔▔▔▔▔
 */

#include <cstdio>
#include <algorithm>
#include <vector>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef size_t si;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator () (a...); }
} read;

const int maxn = 500005, maxw = 1 << 20;
int to[maxn << 1];
std::vector<int> G[maxw];
std::vector<int>::iterator cur[maxw];
bool vis[maxn];
int deg[maxw];
int fa[maxw];
int ans[maxn << 1], ap;

void dfs (int u) {
	while (cur[u] != G[u].end()) {
		int e = *cur[u];
		++ cur[u];
		if (vis[e >> 1]) continue;
		vis[e >> 1] = 1;
		dfs(to[e]);
		ans[++ ap] = e;
		ans[++ ap] = e ^ 1;
	}
}

int find (int x) {
	if (fa[x] == x) return x;
	return fa[x] = find(fa[x]);
}

bool check (int n, int w) {
	for (int i = 0; i < w; i ++) fa[i] = i, deg[i] = 0;
	for (int i = 1; i <= n; i ++) {
		++ deg[to[i << 1]];
		++ deg[to[i << 1 | 1]];
		fa[find(to[i << 1])] = find(to[i << 1 | 1]);
	}
	int first = -1;
	for (int i = 0; i < w; i ++)
		if (deg[i]) {
			if (deg[i] & 1) return 0;
			if (first == -1) first = i;
			else if (find(i) != find(first)) return 0;
		}
	return 1;
}

int main () {
	int n = read;
	for (int i = 1; i <= n; i ++)
		read(to[i << 1], to[i << 1 | 1]);
	int Ans = 20;
	while (!check(n, 1 << Ans)) {
		-- Ans;
		for (int i = 1; i <= n; i ++) {
			to[i << 1 | 0] &= (1 << Ans) - 1;
			to[i << 1 | 1] &= (1 << Ans) - 1;
		}
	}
	for (int i = 1; i <= n; i ++) {
		G[to[i << 1]].push_back(i << 1 | 1);
		G[to[i << 1 | 1]].push_back(i << 1);
	}
	int rt = -1;
	for (int i = 0; i < (1 << Ans); i ++) {
		cur[i] = G[i].begin();
		if (deg[i])
			rt = i;
	}
	dfs(rt);
	printf("%d\n", Ans);
	for (int i = ap; i; i --)
		printf("%d ", ans[i] - 1);
	puts("");
}
