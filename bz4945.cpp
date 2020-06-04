/*
 * Since g++10 is released, some characters is not valid inside #if 0 :(
 * So, why not using clang++? :D

 * Date:
  2020.06.04

 * Solution:
  如果没有 x ，每个地图只有两个选择，就是个 2-SAT ，对于 x ，2^d 枚举一个集合换成 a ，
其他换成 b 即可。
  注意 x -> y 连边的同时必须连一条对应的边 !y -> !x 。

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
#include <algorithm>
#include <vector>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator char () { char x[3]; return scanf("%s", x), *x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator () (a...); }
} read;

const int maxn = 100005;
std::vector<int> G[maxn];
char s[maxn];
char map[maxn][2];
int ma[maxn], mb[maxn];
char mx[maxn], my[maxn];
int key[10];
int dfn[maxn], low[maxn], ip;
int stack[maxn], sp;
int bel[maxn], bp;
bool ins[maxn];

void dfs (int u) {
	dfn[u] = low[u] = ++ ip;
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
			bel[x] = bp;
			ins[x] = 0;
			/* debug(" x_%d=%d", x >> 1, x & 1); */
		}
		/* debug("\n"); */
	}
}

void getmap (int i) {
	if (s[i] == 'a')
		map[i][0] = 'B', map[i][1] = 'C';
	if (s[i] == 'b')
		map[i][0] = 'A', map[i][1] = 'C';
	if (s[i] == 'c')
		map[i][0] = 'A', map[i][1] = 'B';
}

int main () {
	int n = read, K = read;
	scanf("%s", s + 1);
	int d = 'A' - 'a';

	int p = 0;
	for (int i = 1; i <= n; i ++)
		if (s[i] == 'x')
			key[p ++] = i;
		else
			getmap(i);

	if (p != K) return 1;

	int m = read;
	for (int i = 1; i <= m; i ++) read(ma[i], mx[i], mb[i], my[i]);

	for (int S = 0; S < (1 << K); S ++) {
		for (int i = 0; i < K; i ++) {
			s[key[i]] = S >> i & 1 ? 'a' : 'b';
			getmap(key[i]);
		}

		for (int i = 1; i <= n * 2 + 1; i ++) {
			G[i].clear();
			ins[i] = bel[i] = dfn[i] = low[i] = stack[i] = 0;
		}
		ip = sp = bp = 0;

		for (int i = 1; i <= m; i ++) {
			if (s[ma[i]] + d == mx[i]) continue;
			int x = mx[i] == map[ma[i]][1];
			if (s[mb[i]] + d == my[i])
				/* debug("x_%d=%d -> x_%d=%d\n", ma[i], x, ma[i], !x), */
				G[ma[i] << 1 | x].push_back(ma[i] << 1 | !x);
			else {
				int y = my[i] == map[mb[i]][1];
				/* debug("x_%d=%d -> x_%d=%d\n", ma[i], x, mb[i], y), */
				G[ma[i] << 1 | x].push_back(mb[i] << 1 | y);
				G[mb[i] << 1 | !y].push_back(ma[i] << 1 | !x); // IMPORTANT!
			}
		}

		for (int i = 2; i <= n * 2 + 1; i ++)
			if (!dfn[i])
				dfs(i);

		for (int i = 1; i <= n; i ++)
			if (bel[i << 1 | 0] == bel[i << 1 | 1])
				goto fail;

		for (int i = 1; i <= n; i ++)
			putchar(map[i][bel[i << 1 | 0] > bel[i << 1 | 1]]);
		puts("");
		return 0;
fail:;
	}

	puts("-1");
}
