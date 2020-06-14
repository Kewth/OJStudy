/*
 * Since g++10 is released, some characters is not valid inside #if 0 :(
 * So, why not using clang++? :D

 * Date:
    2020.06.14

 * Solution:
 * 重链剖分，维护重心，size 排序

    定根，枚举删边算重心，内子树和外子树分别考虑。

    对于内子树，记 f[u] 表示 u 子树的重心，显然 f 是可以从重儿子继承然后跳父亲边的。
分析这样做的复杂度，在每条重链上 f 都最多从链底跳到链顶，因此复杂度是重链长度和，即
O(n) 。

    那么对于外子树是否也可以直接这样做，记个 g[u] 表示 u 的外子树重心？很遗憾，这样
做并不能保证复杂度，例如有一个点 u ，u 到根的点数 O(n) ，u 的重儿子是一条长 O(n) 的
链，u 还有 O(n) 个儿子，这样一来所有轻儿子的 g 都要暴力跳 O(n) 次，复杂度会到 O(n^2) 。

    但是稍加变换还是能做的，不妨令树根为原树重心，如果删边在根的重儿子内，那么重心
一定是在根和次大的儿子的重链上，把根的重儿子子树所有节点按 size 排序然后维护重心即
可。如果删边不在根的重儿子内，重心一定在根所在重链上，直接把其他节点按 size 排序维
护重心即可。

 * Digression:
    真实大菜逼。

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
#include <vector>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 300000;
std::vector<int> G[maxn];
int size[maxn], son[maxn], fa[maxn];
int ns[maxn];
int f[maxn];

void dfs (int u) {
	size[u] = 1;
	son[u] = 0;
	for (int v : G[u])
		if (v != fa[u]) {
			fa[v] = u;
			dfs(v);
			size[u] += size[v];
			if (size[v] >= size[son[u]])
				son[u] = v;
		}
}

ll ans = 0;

void dp1 (int u) {
	for (int v : G[u])
		if (v != fa[u])
			dp1(v);
	if (!fa[u]) return;
	int &x = f[u];
	if (son[u]) {
		x = f[son[u]];
		while (x != u and size[u] > size[x] * 2)
			x = fa[x];
	} else
		x = u;
	ans += x;
	if (x != u and size[u] == size[x] * 2)
		ans += fa[x];
	/* debug("%d %lld\n", u, ans); */
}

int tmp[maxn], tp;
void find (int u) {
	tmp[++ tp] = u;
	for (int v : G[u])
		if (v != fa[u])
			find(v);
}

bool cmp (int x, int y) { return size[x] < size[y]; }

int main () {
	int T = read;
	while (T --) {
		int n = read;
		for (int i = 1; i <= n; i ++) G[i].clear();
		for (int i = 1; i < n; i ++) {
			int u = read, v = read;
			G[u].push_back(v);
			G[v].push_back(u);
		}

		fa[1] = 0;
		dfs(1);

		int rt = 1;
		while (size[son[rt]] * 2 > n)
			rt = son[rt];
		fa[rt] = 0;
		dfs(rt);

		ans = 0;
		dp1(rt);

		if (son[rt]) {
			tp = 0;
			find(son[rt]);
			int srt = 0;
			for (int v : G[rt])
				if (v != son[rt] and size[v] > size[srt])
					srt = v;
			std::swap(srt, son[rt]);
			std::sort(tmp, tmp + tp + 1, cmp);
			for (int i = 1, x = rt; i <= tp; i ++) {
				int u = tmp[i];
				while (size[son[x]] * 2 > n - size[u]) x = son[x];
				ans += x;
				if (size[son[x]] * 2 == n - size[u]) ans += son[x];
				/* debug(" > %d %d\n", u, x); */
			}
			std::swap(srt, son[rt]);

			tp = 0;
			for (int v : G[rt])
				if (v != son[rt])
					find(v);
			std::sort(tmp, tmp + tp + 1, cmp);
			for (int i = 1, x = rt; i <= tp; i ++) {
				int u = tmp[i];
				while (size[son[x]] * 2 > n - size[u]) x = son[x];
				ans += x;
				if (size[son[x]] * 2 == n - size[u]) ans += son[x];
			}
		}

		printf("%lld\n", ans);
	}
}
