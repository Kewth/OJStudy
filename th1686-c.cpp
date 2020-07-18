/*
 * Since g++10 is released, some characters is not valid inside #if 0 :(
 * So, why not using clang++? :D

 * Date:
  2020.07.18

 * Solution:
 * 二维平面，dsu on tree ，扫描线，树状数组

  把询问区间看做二维平面上的一个点，然后考虑每个点 u 作为 lca 时会对哪些点产生贡献。u 点
作为 lca 就是要在 u 点两个不同的子树里选点，考虑子树合并，每次合并一个子树时，一个朴素的
想法是暴力扫这个子树的所有点 x ，然后可以发现只需要关注 x 在已经合并的子树中的前驱和后继
即可。

  但对每个子树都暴力扫是不行的，注意到合并子树的第一个子树不需要扫，不妨把重儿子放在第一
个，暴力扫每个轻儿子合并进去，事实上就是 dsu on tree ，这样在 u 点上就会产生若干点 (l, r)
表示当询问区间 (L, R) 满足 L <= l 且 R >= r 时 u 点会对该询问产生贡献。所有的这样的点的
数量和是 O(nlog) 的。

  那么把所有 dep 相同的 u 拿出来，把对应的 (l, r) 来一手矩形并，把矩形并对应的面积在二维
平面上加 1 即可。注意这里的矩形只有右下角，用排序 + 单调栈即可实现矩形并。

  然而动态地在二维平面上做矩形 +1 是两个 log 的，会使总复杂度退化到 3 个 log ，注意并不
需要在线回答询问，把询问离线下来做个扫描线 + 树状数组即可。

  总复杂度两个 log ，但两个 log 的操作很多，所以常数可能还有点大。

 * Digression:
  ~~样例都不需要测直接一遍过，这种数据结构题就不存在难度~~

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
#include <set>
#include <algorithm>
#include <vector>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 100005, maxq = 500005;
struct Edge { int v, w; };
std::vector<Edge> G[maxn];
int size[maxn], son[maxn];
ll dis[maxn], tmp[maxn], tp;
int cor[maxn];
std::set<int> light[maxn];
struct Pos { int x, y; };
std::vector<Pos> mat[maxn];
Pos stack[maxn];

void dfs (int u, int fa) {
	tmp[++ tp] = dis[u];
	size[u] = 1;
	for (Edge e : G[u])
		if (e.v != fa) {
			dis[e.v] = dis[u] + e.w;
			dfs(e.v, u);
			size[u] += size[e.v];
			if (size[e.v] > size[son[u]])
				son[u] = e.v;
		}
}

std::set<int> soset;

void solve (int u, int fa) {
	if (son[u]) {
		for (Edge e : G[u])
			if (e.v != fa and e.v != son[u]) {
				solve(e.v, u);
				light[e.v] = soset;
				soset.clear();
			}
		solve(son[u], u);
		for (Edge e : G[u])
			if (e.v != fa and e.v != son[u]) {
				for (int x : light[e.v]) {
					auto it = soset.upper_bound(x);
					if (it != soset.end()) mat[cor[u]].push_back({x, *it});
					if (it != soset.begin()) mat[cor[u]].push_back({*(--it), x});
				}
				for (int x : light[e.v]) soset.insert(x);
			}
	}
	mat[cor[u]].push_back({u, u});
	soset.insert(u);
}

struct Ele { int x, w; };
std::vector<Ele> shit[maxn], quer[maxn];
int ans[maxq];
int bit[maxn];

void add (int p, int n, int x) {
	for (int k = p; k <= n; k += k & -k)
		bit[k] += x;
}

int query (int p) {
	int res = 0;
	for (int k = p; k; k -= k & -k)
		res += bit[k];
	return res;
}

int main () {
	int n = read, q = read;
	for (int i = 1; i < n; i ++) {
		int u = read, v = read, w = read;
		G[u].push_back({v, w});
		G[v].push_back({u, w});
	}

	dfs(1, 0);
	std::sort(tmp + 1, tmp + tp + 1);
	for (int u = 1; u <= n; u ++) cor[u] = int(std::lower_bound(tmp + 1, tmp + tp + 1, dis[u]) - tmp);
	solve(1, 0);

	for (int i = 1; i <= tp; i ++) {
		std::sort(mat[i].begin(), mat[i].end(), [] (Pos a, Pos b) {
					return a.x == b.x ? a.y > b.y : a.x < b.x;
				});
		int sp = 0;
		for (Pos p : mat[i]) {
			while (sp and p.y <= stack[sp].y) -- sp;
			stack[++ sp] = p;
		}
		for (int j = 1; j <= sp; j ++) {
			shit[stack[j].y].push_back({stack[j].x, 1});
			if (j > 1)
				shit[stack[j].y].push_back({stack[j - 1].x, -1});
		}
	}

	for (int i = 1; i <= q; i ++) {
		int l = read, r = read;
		quer[r].push_back({l, i});
	}

	for (int i = 1; i <= n; i ++) {
		for (Ele e : shit[i])
			add(n - e.x + 1, n, e.w);
		for (Ele e : quer[i])
			ans[e.w] = query(n - e.x + 1);
	}

	for (int i = 1; i <= q; i ++)
		printf("%d\n", ans[i]);
}
