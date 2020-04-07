#if 0
2020.04.06

直接处理所有答案 f[x][y] ，一个朴素的暴力是枚举连边转移，复杂度 O(m^2) 。

将点按 01 分为两类，把边根据是否连接类别相同的点分为两类。
可以发现同种类别的边构成的偶环是没用的，
因为总可以在任意一条该类别的边上之间反复横跳以代替所有偶环。
也就是说对于同类别的边构成的每一个联通块，事实上只需要关心这个联通块是否是二分图。

如果是二分图，只需要保留一颗生成树，否则就在树的基础上加任意一个奇环（自环即可）。
这样一来 m 就可以转换为 O(n) 的级别。
#endif
#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef std::pair<int, int> par;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 5050;
char s[maxn];
std::vector<int> G[2][maxn], T[maxn];
int color[maxn];
bool f[maxn][maxn];

bool fail;
void dfs (int u, int o) {
	for (int v : G[o][u])
		if (!color[v]) {
			color[v] = 3 - color[u];
			dfs (v, o);
			T[u].push_back(v);
			T[v].push_back(u);
		} else if (color[v] == color[u])
			fail = 1;
}

int main () {
	int n = read, m = read, q = read;
	scanf("%s", s + 1);
	for (int i = 1; i <= m; i ++) {
		int u = read, v = read, o = s[u] == s[v];
		G[o][u].push_back(v);
		G[o][v].push_back(u);
	}

	for (int o = 0; o < 2; o ++) {
		std::fill(color, color + n + 1, 0);
		for (int i = 1; i <= n; i ++)
			if (!color[i]) {
				fail = 0;
				color[i] = 1;
				dfs(i, o);
				if (fail)
					T[i].push_back(i);
			}
	}

	std::queue<par> qu;
	for (int x = 1; x <= n; x ++) {
		qu.push(par(x, x));
		f[x][x] = 1;
		for (int y : T[x])
			if (!f[x][y] and s[x] == s[y])
				qu.push(par(x, y)), f[x][y] = 1;
	}

	while (!qu.empty()) {
		int X = qu.front().first, Y = qu.front().second;
		qu.pop();
		for (int x : T[X])
			for (int y : T[Y])
				if (!f[x][y] and s[x] == s[y])
					qu.push(par(x, y)), f[x][y] = 1;
	}

	while (q --)
		puts(f[read][read] ? "YES" : "NO");
}
