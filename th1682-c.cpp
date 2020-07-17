/*
 * Since g++10 is released, some characters is not valid inside #if 0 :(
 * So, why not using clang++? :D

 * Date:
  2020.07.16

 * Solution:
 * AC 自动机，自动机 DP ，状态优化，倍增

  朴素的做法可以建出 ACAM 然后枚举左端点放在 ACAM 上跑一遍。复杂度 O(n^2) 。第二个子任务
保证了 fail 树深度很小，这给出了一些提示，注意到对于一个固定的右端点 R ，设 [1, R] 在自动
机上对应的节点为 u ，那么所有 [L, R] 对应的节点都是 u 在 fail 树的祖先。

  可以设计一个 DP f[u][r] 表示所有右端点为 r ，在 ACAM 对应的节点为 u 的子串的最大权值。
根据上述，该 DP 的状态数是 O(mh) 的，其中 h 是 fail 树深度。

  但还是不够，上述 DP 的状态仍可以进一步优化。设 [1, R] 在 ACAM 对应的节点为 node[R] 。那
么对于 f[u][R], u != node[R] ，观察这个 f[u][R] 代表的所有子串的集合，可以发现它竟然与 R
无关！画个图可以很好理解。

  设 u 在 fail 树上的一个儿子 v 是 node[R] 的祖先，那么用 g[v] 表示所有这样 f[u][R] 的值，
用 h[i] 表示 f[node[i]][i] ，状态数就进一步优化到了 O(L + m) ，转移从 f 的转移推广，可以
发现就是一条链取 max ，倍增即可，复杂度带个 log 。

  求一条链的最大值用倍增太慢了，不如干脆暴力扫这条链，有趣的是复杂度是对的。g 的转移直接
在链上暴力扫，不难发现扫的次数就是 trie 图的边数，也就是 O(Ls) ，其中 s 是字符集大小。h
的转移也可以暴力跳，复杂度和跳 fail 一样，为 O(m) 。

 * Digression:
  听说还有线性做法？想不出来，我琢磨着建 ACAM 的复杂度不都要 O(Ls) 吗？

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

#pragma GCC optimize(3)
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 1000005, maxc = 26;
int ch[maxn][maxc], fail[maxn], from[maxn], cp = 1;
ll val[maxn];
char s[maxn];
ll f[maxn], g[maxn];

int main () {
	int n = read;
	read.operator int();

	for (int i = 1; i <= n; i ++) {
		scanf("%s", s);
		int now = 1;
		for (char *t = s; *t; ++ t) {
			int &to = ch[now][*t - 'a'];
			if (!to) from[to = ++ cp] = now;
			now = to;
		}
		val[now] += int(read);
	}

	std::queue<int> q;
	q.push(1);
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		val[u] += val[fail[u]];

		if (u > 1) f[u] = - 1000000000000000000;
		for (int x = from[u]; x != from[fail[u]]; x = fail[x])
			f[u] = std::max(f[u], f[x]);
		g[u] = std::max(f[u] += val[fail[u]], g[fail[u]]);

		for (int c = 0, v; c < maxc; c ++)
			if ((v = ch[u][c])) {
				int x = fail[u];
				while (x and !ch[x][c]) x = fail[x];
				fail[v] = x ? ch[x][c] : 1;
				q.push(v);
			}
	}

	ll ans = 0;

	scanf("%s", s);
	int now = 1;
	ll F = 0;
	for (char *t = s; *t; ++ t) {
		int top = now;
		while (top and !ch[top][*t - 'a'])
			F = std::max(F, f[top]), top = fail[top];
		now = top ? ch[top][*t - 'a'] : 1;
		ans = std::max(ans, g[now]);
		ans = std::max(ans, F += val[now]);
	}

	printf("%lld\n", ans);
}
