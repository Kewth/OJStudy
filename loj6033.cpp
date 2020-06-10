#if 0
2020.06.09

同《游戏》(JSOI2009) ：

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
#include <vector>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef std::pair<int, int> par;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 105, maxm = 40010;
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

bool firwin[maxn][maxn];
char s[maxn][maxn];

int main() {
	int n = read, m = read;
	for(int i = 1; i <= n; i ++)
		scanf("%s", s[i] + 1);

	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= m; j ++) {
			if(s[i][j] == '.' and s[i + 1][j] == '.') {
				add((i - 1) * m + j, i * m + j);
				add(i * m + j, (i - 1) * m + j);
			}
			if(s[i][j] == '.' and s[i][j + 1] == '.') {
				add((i - 1) * m + j, (i - 1) * m + j + 1);
				add((i - 1) * m + j + 1, (i - 1) * m + j);
			}
		}

	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= m; j ++) {
			int u = (i - 1) * m + j;
			if(!match[u] and s[i][j] == '.') {
				std::fill(vis + 1, vis + n * m + 1, 0);
				dfs(u);
			}
		}

	bool win = 0;
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= m; j ++) {
			int u = (i - 1) * m + j;
			if(match[u]) {
				int v = match[u];
				match[u] = match[v] = 0;
				std::fill(vis + 1, vis + n * m + 1, 0);
				vis[u] = 1;
				if(!dfs(v)) {
					match[u] = v;
					match[v] = u;
					firwin[i][j] = 1;
				}
			}
			if(!firwin[i][j])
				win = 1;
		}

	if(win) {
		std::vector<par> ans;
		for(int i = 1; i <= n; i ++)
			for(int j = 1; j <= m; j ++)
				if(s[i][j] == '.' and !firwin[i][j])
					ans.push_back(par(i, j));
		printf("%lu\n", ans.size());
		for (par p : ans)
			printf("%d %d\n", p.first, p.second);
	}
	else
		puts("0");
}
