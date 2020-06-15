/*
 * Since g++10 is released, some characters is not valid inside #if 0 :(
 * So, why not using clang++? :D

 * Date:
  2020.06.15

 * Solution:
 * 随机撒点（确定任意一个关键点），建 dfs 树，问题转换，树上差分

    这个 20% 的条件很突兀，初看没什么用。实际上这是在提示要找到任意一个关键点，通过随机
加检验的方式，如果多次随机都失败，直接可以认为关键点数量少于 20% 。

    不妨假设 1 为关键点，以 1 为根建 dfs 树，那么所有非树边都是从下到上的返祖边，事实上
这样是一个点是关键点的充要条件。那么一个想法是用这个充要条件去检查每个点是否是关键点，
这样就陷进去了，事实上这个条件并不适合快速判断一个点是否为关键点。

    回归定义，一个点是关键点当且仅当它到所有点都只有恰好一条路径，在 dfs 树上可以得到一
个更简单但是等价的命题：一个点是关键点当且仅当它到它到根的每个点都只有恰好一条路径。这
样一来问题简单了很多，稍加转换就可以得到一个更好的条件：其父亲边被唯一一条非树边覆盖，
并且该非树边的出点是关键点。其充分性和必要性都比较显然，并且这个条件很好用作判断，做一
遍树上差分即可。

 * Digression:
  中间陷进 dfs 树没出来，看到题解一句话后立刻就悟了。

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
#include <random>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 100005;
std::vector<int> G[maxn];
int cover[maxn], keycover[maxn];
bool vis[maxn], ins[maxn];
bool isans[maxn];

int Root;
void force (int u) {
	vis[u] = ins[u] = 1;
	for (int v : G[u])
		if (!vis[v])
			force(v);
		else if (!ins[v])
			Root = 0;
	ins[u] = 0;
}

int tmp[maxn], tp;
void dfs (int u) {
	tmp[++ tp] = u;
	vis[u] = 1;
	for (int v : G[u])
		if (!vis[v]) {
			/* debug("%d -> %d\n", u, v); */
			dfs(v);
			cover[u] += cover[v];
			keycover[u] += keycover[v];
		}
		else { // ins[v] = 1
			/* debug(" (%d -> %d)\n", u, v); */
			++ cover[u];
			-- cover[v];
			keycover[u] += v;
			keycover[v] -= v;
		}
}

int main () {
	std::mt19937 engine(19260817);
	int T = read;
	while (T --) {
		int n = read, m = read;
		for (int i = 1; i <= n; i ++) G[i].clear();
		for (int i = 1; i <= m; i ++) {
			int u = read, v = read;
			G[u].push_back(v);
		}
		std::uniform_int_distribution<int> Rand(1, n);
		int test = 80;
		Root = 0;
		while (!Root and test --) {
			std::fill(vis, vis + n + 1, 0);
			force(Root = Rand(engine));
		}
		if (!Root) {
			puts("-1");
			continue;
		}
		std::fill(cover, cover + n + 1, 0);
		std::fill(keycover, keycover + n + 1, 0);
		std::fill(vis, vis + n + 1, 0);
		tp = 0;
		dfs(Root);
		isans[Root] = 1;
		int tot = 1;
		for (int i = 2; i <= tp; i ++) {
			int u = tmp[i];
			if (cover[u] == 1)
				isans[u] = isans[keycover[u]];
			else
				isans[u] = 0;
			tot += isans[u];
		}
		if (tot * 5 >= n) {
			for (int i = 1; i <= n; i ++)
				if (isans[i])
					printf("%d ", i);
			puts("");
		}
		else
			puts("-1");
	}
}
