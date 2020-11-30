/*
 * Author: Kewth

 * Date:
  2020.11.21

 * Solution:
  In blog.

 * Digression:

 * CopyRight:
   __  __                  __   __
  |  |/  |.-----.--.--.--.|  |_|  |--.
  |     < |  -__|  |  |  ||   _|     |
  |__|\__||_____|________||____|__|__|

 */

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

static struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 500005;
char pool[maxn << 1], *s[maxn];
int len[maxn], pos[maxn];
int ch[2][maxn << 1], cp = 1;
std::vector<int> key[maxn << 1];
int np = 1;

void insert (int i) {
	int now = 1;
	for (int j = 1; j <= len[i]; j ++) {
		int x = s[i][j] - '0', &to = ch[x][now];
		if (!to) to = ++ cp;
		now = to;
	}
	key[now].push_back(++ np);
}

std::vector<int> G[maxn * 6], T[maxn << 1];
int up[maxn << 1], down[maxn << 1];

void dfs (int now, int fa) {
	if (!now) return;
	for (int u : key[now]) {
		up[u] = ++ np;
		down[u] = ++ np;
		T[fa].push_back(u);
		fa = u;
	}
	dfs(ch[0][now], fa);
	dfs(ch[1][now], fa);
}

void build (int u) {
	for (int v : T[u]) {
		G[up[v]].push_back(up[u]);
		G[up[v]].push_back(u ^ 1);
		build(v);
		G[down[u]].push_back(down[v]);
		G[down[u]].push_back(v ^ 1);
	}
	G[u].push_back(up[u]);
	G[u].push_back(down[u]);
}

int dfn[maxn * 6], low[maxn * 6], ip;
int stack[maxn * 6], sp;
int bl[maxn * 6], bp;
bool ins[maxn * 6];

void tarjan (int u) {
	low[u] = dfn[u] = ++ ip;
	ins[stack[++ sp] = u] = 1;
	for (int v : G[u])
		if (!dfn[v])
			tarjan(v), low[u] = std::min(low[u], low[v]);
		else if (ins[v]) // XXX: 漏了 ins[v]
			low[u] = std::min(low[u], dfn[v]);
	/* debug("%d : %d %d\n", u, dfn[u], low[u]); */
	/* for (int v : G[u]) */
	/* 	debug("  -> %d\n", v); */
	if (low[u] == dfn[u]) {
		++ bp;
		while (stack[sp + 1] != u) {
			int x = stack[sp --];
			ins[x] = 0;
			bl[x] = bp;
		}
	}
}

int main () {
	s[0] = pool;
	int n = read;
	for (int i = 1; i <= n; i ++) {
		s[i] = s[i - 1] + 1 + len[i - 1];
		scanf("%s", s[i] + 1);
		len[i] = int(strlen(s[i] + 1));
		pos[i] = 1;
		while (pos[i] <= len[i] and s[i][pos[i]] != '?') ++ pos[i];
		s[i][pos[i]] = '0', insert(i);
		s[i][pos[i]] = '1', insert(i);
		s[i][pos[i]] = 0;
	}
	dfs(1, 1);
	for (int u : T[1])
		build(u);
	for (int u = 2; u <= np; u ++)
		if (!dfn[u])
			tarjan(u);
	for (int i = 1; i <= n; i ++) {
		int u0 = i << 1 | 0, u1 = i << 1 | 1;
		if (bl[u0] == bl[u1])
			return puts("NO"), 0;
	}
	puts("YES");
	for (int i = 1; i <= n; i ++) {
		int u0 = i << 1 | 0, u1 = i << 1 | 1;
		s[i][pos[i]] = bl[u0] < bl[u1] ? '0' : '1';
		s[i][len[i] + 1] = 0;
		puts(s[i] + 1);
	}
}
