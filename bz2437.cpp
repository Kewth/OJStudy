#if 0
2020.01.20

看做空格移动，交替移动到白点黑点，
任何时候与空格距离奇偶性不正确的白点黑点都永远无法被空格走到，可以看做障碍。
而一个点被走过后一定奇偶性改变，从而一个点不会被经过两次。
转换后同 JSOI2009 Game 。

同 test20191109bigraph:

求出一组二分图最大匹配，如果先手在非匹配点，那么先手必败，
因为如果先手有边走一定会通过非匹配边走到一个匹配点，
此时后手就一定可以走匹配边并删掉当前点，使得到达的点仍然是一个非匹配点。
那么只要先手所在的点在任意一组最大匹配中是非匹配点就必败。

考虑先手所在点在所有最大匹配中都是匹配点的情况，
此时先手选择一条匹配边并删掉当前点，后手所在的点就在该匹配中是非匹配点。
那么只要先手所在的点在所有最大匹配中都是匹配点就必胜。

问题转换为求哪些点在所有最大匹配都是匹配点。
求出一组最大匹配，考虑匹配点 u ，设其匹配的是 v 。
如果把 u 删掉之后再从 v 开始增广（事实上这就直接对应了博弈过程中先手的决策），
如果 v 开始有增广路（事实上这直接对应接下来的后手决策）说明存在一组最大匹配 u 是非匹配点。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 45, maxm = 7000, maxq = 1010;
int head[maxn * maxn], nxt[maxm << 1], to[maxm << 1], hp = 1;

inline void add(int u, int v) {
	nxt[++ hp] = head[u];
	head[u] = hp;
	to[hp] = v;
}

int match[maxn * maxn];
bool vis[maxn * maxn];
bool dfs(int u) {
	for(int i = head[u]; i; i = nxt[i]) {
		int v = to[i];
		if(vis[v]) continue;
		vis[v] = 1;
		if(!match[v] or dfs(match[v])) {
			match[u] = v;
			match[v] = u;
			return 1;
		}
	}
	return 0;
}

int id[maxq];
int erase_and_match(int u, int n, int lim, bool undo) {
	if(!match[u]) return -1;
	int v = match[u];
	match[u] = match[v] = 0;
	std::fill(vis + 1, vis + n + 1, 0);
	for(int j = 0; j <= lim; j ++)
		vis[id[j]] = 1;
	if(dfs(v)) return 1;
	if(undo) {
		match[u] = v;
		match[v] = u;
	}
	return 0;
}

char s[maxn][maxn];
bool t[maxn][maxn];
int ans[maxq], ap;
int main() {
	int n = read, m = read;
	for(int i = 1; i <= n; i ++)
		scanf("%s", s[i] + 1);

	int x = 1, y = 1;
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= m; j ++)
			if(s[i][j] == '.') {
				x = i;
				y = j;
				s[i][j] = 'X';
			}

	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= m; j ++)
			if((x - i + y - j) & 1)
				t[i][j] = s[i][j] == 'O';
			else
				t[i][j] = s[i][j] == 'X';

	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= m; j ++) {
			if(t[i][j] and t[i + 1][j]) {
				add((i - 1) * m + j, i * m + j);
				add(i * m + j, (i - 1) * m + j);
			}
			if(t[i][j] and t[i][j + 1]) {
				add((i - 1) * m + j, (i - 1) * m + j + 1);
				add((i - 1) * m + j + 1, (i - 1) * m + j);
			}
		}

	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= m; j ++) {
			int u = (i - 1) * m + j;
			if(!match[u] and t[i][j]) {
				std::fill(vis + 1, vis + n * m + 1, 0);
				dfs(u);
			}
		}

/* 	for(int i = 1; i <= n; i ++) { */
/* 		for(int j = 1; j <= m; j ++) */
/* 			debug("%d", t[i][j]); */
/* 		debug("\n"); */
/* 	} */

	id[0] = (x - 1) * m + y;
	bool win = erase_and_match(id[0], n * m, 0, 1) == 0;

	int q = read;
	for(int i = 1; i <= q * 2; i ++) {
		int nx = read, ny = read;
		erase_and_match(id[i - 1], n * m, i - 1, 0);
		id[i] = (nx - 1) * m + ny;

		bool nwin = erase_and_match(id[i], n * m, i, 1) == 0;

/* 		for(int u = 1; u <= n * m; u ++) */
/* 			if(match[u] > u) */
/* 				debug("%d - %d\n", u, match[u]); */
/* 		debug("\n"); */

		if(i & 1 and win and nwin)
			ans[++ ap] = (i + 1) >> 1;
		win = nwin;
	}

	printf("%d\n", ap);
	for(int i = 1; i <= ap; i ++)
		printf("%d\n", ans[i]);
}
