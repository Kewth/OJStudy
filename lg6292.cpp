/*
 * Author: Kewth

 * Date:
  2020.07.20

 * Solution:
 * 扫描线，SAM ，树状数组，树链剖分

  区间本质不同子串数，用扫描线扫右端点，维护每个左端点的答案。考虑让每个字符串在最后一个
出现的位置产生贡献。每次右端点移动到 R 的时候，以 R 为结尾的所有子串都会产生新的贡献，这
个是很好算的，麻烦的在于要把这些子串之前产生的贡献减掉。

  设 max[S] 表示一个串 right 集合的最大值，在 SAM 上考虑，每次要考虑一个节点 x 到根的链，
可以发现 max 相同的一段可以合并在一起，那么树链剖分一下就变成前缀覆盖的问题，区间覆盖可
以用 odt ，前缀覆盖一个栈就可以了。

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
#include <cstring>
#include <algorithm>
#include <vector>
#include <stack>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef size_t si;
typedef std::pair<int, int> par;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 100005, maxq = 200005, maxc = 26;
int ch[maxn << 1][maxc], len[maxn << 1], fa[maxn << 1], cp = 1;
std::vector<int> G[maxn << 1];
int size[maxn << 1], son[maxn << 1], deep[maxn << 1], top[maxn << 1];
std::stack<par> st[maxn << 1];
std::vector<int> con[maxn << 1];
int max[maxn << 1];
char s[maxn];
int pos[maxn];
ll bit1[maxn], bit2[maxn];
std::vector<par> qu[maxn];
ll ans[maxq];

int insert (int pre, int c) {
	int now = ++ cp;
	len[now] = len[pre] + 1;
	while (pre and !ch[pre][c]) ch[pre][c] = now, pre = fa[pre];
	if (pre) {
		int preto = ch[pre][c];
		if (len[preto] == len[pre] + 1) fa[now] = preto;
		else {
			int sp = ++ cp;
			len[sp] = len[pre] + 1;
			std::copy(ch[preto], ch[preto] + maxc, ch[sp]);
			fa[sp] = fa[preto];
			while (pre and ch[pre][c] == preto) ch[pre][c] = sp, pre = fa[pre];
			fa[now] = fa[preto] = sp;
		}
	} else fa[now] = 1;
	return now;
}

void add (int l, int r, int n, int x) {
	if (l > r) return;
	for (int k = l; k <= n; k += k & -k) {
		bit1[k] += x;
		bit2[k] += x * (n - l + 1);
	}
	for (int k = r + 1; k <= n; k += k & -k) {
		bit1[k] -= x;
		bit2[k] -= x * (n - r);
	}
}

ll query (int l, int r, int n) {
	ll res = 0;
	for (int k = r; k; k -= k & -k)
		res += bit2[k] - bit1[k] * (n - r);
	for (int k = l - 1; k; k -= k & -k)
		res -= bit2[k] - bit1[k] * (n - l + 1);
	return res;
}

void dfs1 (int u) {
	deep[u] = deep[fa[u]] + 1;
	size[u] = 1;
	for (int v : G[u]) {
		dfs1(v);
		size[u] += size[v];
		if (size[v] > size[son[u]])
			son[u] = v;
	}
}

void dfs2 (int u) {
	if (!top[u]) top[u] = u;
	if (son[u]) top[son[u]] = top[u];
	con[top[u]].push_back(u);
	for (int v : G[u]) dfs2(v);
}

int main () {
	scanf("%s", s + 1);
	int n = int(strlen(s + 1));
	pos[0] = 1;
	for (int i = 1; i <= n; i ++)
		pos[i] = insert(pos[i - 1], s[i] - 'a');

	for (int x = 2; x <= cp; x ++)
		G[fa[x]].push_back(x);
	dfs1(1);
	dfs2(1);

	int q = read;
	for (int i = 1; i <= q; i ++) {
		int l = read, r = read;
		qu[r].push_back(par(l, i));
	}

	for (int i = 1; i <= n; i ++) {
		add(1, i, n, 1);
		for (int x = pos[i], y; x; x = fa[y]) {
			y = top[x];
			par p = par(0, 0);
			int las = fa[y];
			while (!st[y].empty() and p.first < deep[x]) {
				p = st[y].top();
				st[y].pop();
				int z = con[y][si(p.first - deep[y])];
				add(p.second - len[z] + 1, p.second - len[las], n, -1);
				las = z;
			}
			if (p.first > deep[x]) {
				st[y].push(p);
				add(p.second - len[las] + 1, p.second - len[x], n, 1);
			}
			st[y].push(par(deep[x], i));
		}
		for (par p : qu[i])
			ans[p.second] = query(p.first, i, n);
	}

	for (int i = 1; i <= q; i ++) printf("%lld\n", ans[i]);
}
