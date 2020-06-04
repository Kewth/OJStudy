/*
 * Since g++10 is released, some characters is not valid inside #if 0 :(
 * So, why not using clang++? :D

 * Date:
  2020.06.04

 * Solution:
  2-SAT 板子，输出方案只需要选拓扑序较大的取值即可。

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
#include <cstdlib>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct Inputer {
	static char buffer[64 * 1024 * 1024], *p;
	inline operator int () { return int(strtol(p, &p, 10)); }
	inline operator ll () { return strtoll(p, &p, 10); }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
	Inputer() { fread(buffer, 1, sizeof buffer, stdin); }
} read;
char *Inputer::p = Inputer::buffer;
char Inputer::buffer[] = {};

const int maxn = 2000005;
std::vector<int> G[maxn];
int dfn[maxn], low[maxn], ip;
int stack[maxn], sp;
int bel[maxn], bp;
bool ins[maxn];

void dfs (int u) {
	low[u] = dfn[u] = ++ ip;
	stack[++ sp] = u;
	ins[u] = 1;
	for (int v : G[u])
		if (!dfn[v]) {
			dfs(v);
			low[u] = std::min(low[u], low[v]);
		} else if (ins[v])
			low[u] = std::min(low[u], low[v]);
	if (low[u] == dfn[u]) {
		++ bp;
		while (stack[sp + 1] != u) {
			int x = stack[sp --];
			ins[x] = 0;
			bel[x] = bp;
		}
	}
}

int main () {
	int n = read, m = read;
	for (int i = 1; i <= m; i ++) {
		int a = read, x = read, b = read, y = read;
		G[a << 1 | !x].push_back(b << 1 | y);
		G[b << 1 | !y].push_back(a << 1 | x);
	}

	for (int i = 2; i <= n * 2 + 1; i ++)
		if (!dfn[i])
			dfs(i);

	for (int i = 1; i <= n; i ++)
		if (bel[i << 1 | 0] == bel[i << 1 | 1])
			return puts("IMPOSSIBLE"), 0;

	puts("POSSIBLE");
	for (int i = 1; i <= n; i ++)
		printf("%d ", bel[i << 1 | 0] > bel[i << 1 | 1]);
	puts("");
}
